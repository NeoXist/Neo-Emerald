#!/usr/bin/env python3
"""
Extract final evolution Pokemon and their base stats from the codebase.
Outputs a CSV file that can be imported into Google Sheets.
"""

import re
import os
from pathlib import Path
from collections import defaultdict

# Paths
BASE_DIR = Path(__file__).parent
SPECIES_INFO_H = BASE_DIR / "src" / "data" / "pokemon" / "species_info.h"
SPECIES_CONSTANTS = BASE_DIR / "include" / "constants" / "species.h"
OUTPUT_CSV = BASE_DIR / "final_evolutions_stats.csv"

def parse_species_constants():
    """Parse species.h to get species ID to name mapping."""
    species_map = {}
    with open(SPECIES_CONSTANTS, 'r', encoding='utf-8') as f:
        for line in f:
            match = re.match(r'#define\s+SPECIES_(\w+)\s+(\d+)', line)
            if match:
                name = match.group(1)
                species_id = int(match.group(2))
                species_map[species_id] = name
    return species_map

def parse_species_data():
    """Parse species_info.h and all included family files to extract Pokemon data."""
    species_data = {}
    has_evolutions = set()  # Set of species that have evolutions defined
    
    # Read the main species_info.h file
    with open(SPECIES_INFO_H, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Find all included family files
    family_files = re.findall(r'#include\s+"species_info/([^"]+)"', content)
    
    # Parse each family file
    family_dir = SPECIES_INFO_H.parent / "species_info"
    
    for family_file in family_files:
        file_path = family_dir / family_file
        if not file_path.exists():
            continue
        
        with open(file_path, 'r', encoding='utf-8') as f:
            file_content = f.read()
        
        # Split by species entries - look for [SPECIES_NAME] = {
        # We need to handle nested braces properly
        species_pattern = r'\[SPECIES_(\w+)\]\s*=\s*\{'
        
        pos = 0
        while True:
            match = re.search(species_pattern, file_content[pos:])
            if not match:
                break
            
            species_name = match.group(1)
            start_pos = pos + match.end()
            
            # Find the matching closing brace
            brace_count = 1
            current_pos = start_pos
            while brace_count > 0 and current_pos < len(file_content):
                if file_content[current_pos] == '{':
                    brace_count += 1
                elif file_content[current_pos] == '}':
                    brace_count -= 1
                current_pos += 1
            
            if brace_count == 0:
                block_content = file_content[start_pos:current_pos-1]
                
                # Extract base stats
                # Handle both simple numbers and conditional expressions like: P_UPDATED_STATS >= GEN_2 ? 109 : 85
                stats = {}
                stat_fields = ['baseHP', 'baseAttack', 'baseDefense', 'baseSpeed', 'baseSpAttack', 'baseSpDefense']
                
                for stat_name in stat_fields:
                    # Pattern 1: Simple assignment: .baseStat = number
                    simple_pattern = rf'\.{stat_name}\s*=\s*(\d+)'
                    stat_match = re.search(simple_pattern, block_content)
                    if stat_match:
                        stats[stat_name] = int(stat_match.group(1))
                    else:
                        # Pattern 2: Conditional: .baseStat = CONDITION ? number1 : number2
                        # Extract the first number after ? (updated stat) or the number after : (old stat)
                        cond_pattern = rf'\.{stat_name}\s*=\s*[^?]+\?\s*(\d+)\s*:\s*(\d+)'
                        cond_match = re.search(cond_pattern, block_content)
                        if cond_match:
                            # Use the first number (after ?) which is typically the updated/modified stat
                            stats[stat_name] = int(cond_match.group(1))
                
                # Extract National Dex number - if it's NATIONAL_DEX_NONE (0), skip this Pokemon
                nat_dex_pattern = r'\.natDexNum\s*=\s*(NATIONAL_DEX_\w+|\d+)'
                nat_dex_match = re.search(nat_dex_pattern, block_content)
                if nat_dex_match:
                    nat_dex_value = nat_dex_match.group(1)
                    # If it's NATIONAL_DEX_NONE or 0, this Pokemon is not in the Pokedex
                    if nat_dex_value == 'NATIONAL_DEX_NONE' or nat_dex_value == '0':
                        continue
                    # Try to extract numeric value if it's a number
                    try:
                        nat_dex_num = int(nat_dex_value)
                        if nat_dex_num == 0:
                            continue
                        stats['natDexNum'] = nat_dex_num
                    except ValueError:
                        # It's a constant name, we'll check it later
                        stats['natDexNum'] = nat_dex_value
                else:
                    # If natDexNum is not specified, assume it's not in Pokedex (skip)
                    continue
                
                # Check for evolutions - look for .evolutions = EVOLUTION(
                # Note: EVOLUTION macro expands to an array, so we check if .evolutions exists
                if re.search(r'\.evolutions\s*=\s*EVOLUTION\(', block_content, re.DOTALL):
                    has_evolutions.add(species_name)
                
                # Store species data if we found stats
                if stats:
                    species_data[species_name] = stats
            
            pos = current_pos
    
    return species_data, has_evolutions

def is_base_form(species_name):
    """Check if this is a base form (not a Mega, regional form, etc.)."""
    # Skip forms with common suffixes
    form_suffixes = [
        '_MEGA', '_MEGA_X', '_MEGA_Y',
        '_ALOLA', '_GALAR', '_HISUI', '_PALDEA',
        '_GMAX', '_TOTEM', '_BUSTED',
        '_PRIMAL', '_ULTRA', '_ETERNAL',
        '_ASH', '_PARTNER', '_CAP',
        '_10', '_25', '_50', '_100',  # Pikachu forms
        '_SPIKED_EAR', '_ROCK_STAR', '_BELLE', '_POP_STAR', '_PH_D', '_LIBRE',  # Pikachu cosplay
        '_ORIGIN', '_THERIAN', '_INCARNATE',
        '_ATTACK', '_DEFENSE', '_SPEED',  # Deoxys forms
        '_NORMAL', '_FIRE', '_WATER', '_ELECTRIC', '_GRASS', '_ICE', '_FIGHTING', '_POISON', '_GROUND', '_FLYING', '_PSYCHIC', '_BUG', '_ROCK', '_GHOST', '_DRAGON', '_DARK', '_STEEL', '_FAIRY',  # Arceus forms
        '_RED_STRIPED', '_BLUE_STRIPED',  # Basculin
        '_MALE', '_FEMALE',  # Some gender forms
        '_PHONY', '_ANTIQUE',  # Polteageist
        '_SINGLE_STRIKE', '_RAPID_STRIKE',  # Urshifu
        '_AMPED', '_LOW_KEY',  # Toxtricity
        '_BAILE', '_PA_OM', '_SENSU', '_KOMOO', '_HULA', '_ORA', '_POM_POM', '_RIBA',  # Oricorio
        '_RED', '_BLUE', '_YELLOW', '_GREEN', '_ORANGE', '_PINK', '_PURPLE', '_BROWN', '_WHITE', '_BLACK',  # Minior
        '_SMALL', '_LARGE', '_SUPER',  # Pumpkaboo/Gourgeist
        '_50_PERCENT', '_10_PERCENT', '_COMPLETE',  # Zygarde
        '_CORE', '_ARMOR',  # Necrozma
        '_ICE_RIDER', '_SHADOW_RIDER',  # Calyrex
        '_SPRING', '_SUMMER', '_AUTUMN', '_WINTER',  # Deerling/Sawsbuck
        '_ARCHER', '_CLOWN', '_DANCER', '_MIME', '_JESTER', '_LEAD', '_MATADOR', '_SOLDIER', '_SENSOR',  # Mime Jr. evolutions
    ]
    
    for suffix in form_suffixes:
        if species_name.endswith(suffix):
            return False
    
    # Also check for patterns like SPECIES_NAME_FORM
    # If there's an underscore and it's not just a simple name, it might be a form
    # But we need to be careful - some base Pokemon have underscores (like MR_MIME)
    # So we'll use a whitelist approach instead
    
    return True

def find_final_evolutions(species_data, has_evolutions, species_map):
    """Identify final evolution Pokemon (those that don't evolve into anything else)."""
    final_evolutions = []
    
    for species_name, stats in species_data.items():
        # Skip if no stats found
        if not stats:
            continue
        
        # Skip special entries like SPECIES_NONE, SPECIES_EGG
        if species_name in ['NONE', 'EGG']:
            continue
        
        # Skip alternate forms (Mega, regional, etc.)
        if not is_base_form(species_name):
            continue
        
        # Only include Pokemon that are in the Pokedex (have a valid natDexNum)
        if 'natDexNum' not in stats:
            continue
        
        nat_dex = stats['natDexNum']
        # If natDexNum is 0 or NATIONAL_DEX_NONE, skip (not in Pokedex)
        if isinstance(nat_dex, int) and nat_dex == 0:
            continue
        if isinstance(nat_dex, str) and nat_dex == 'NATIONAL_DEX_NONE':
            continue
        
        # Check if this species evolves into something
        if species_name in has_evolutions:
            # This species can evolve, so it's not a final evolution
            continue
        
        # This species doesn't evolve, so it's a final evolution
        # (or a single-stage Pokemon)
        species_id = None
        for sid, name in species_map.items():
            if name == species_name:
                species_id = sid
                break
        
        if species_id is None:
            continue
        
        # Remove natDexNum from stats before adding (we don't need it in the CSV)
        stats_copy = {k: v for k, v in stats.items() if k != 'natDexNum'}
        
        final_evolutions.append({
            'species_id': species_id,
            'species_name': species_name,
            'display_name': species_name.replace('_', ' ').title(),
            **stats_copy
        })
    
    # Sort by species ID
    final_evolutions.sort(key=lambda x: x['species_id'])
    
    return final_evolutions

def write_csv(final_evolutions):
    """Write final evolutions to CSV file."""
    with open(OUTPUT_CSV, 'w', encoding='utf-8') as f:
        # Write header
        f.write('Species ID,Species Name,HP,Attack,Defense,Special Attack,Special Defense,Speed,Total BST\n')
        
        # Write data
        for pokemon in final_evolutions:
            hp = pokemon.get('baseHP', 0)
            attack = pokemon.get('baseAttack', 0)
            defense = pokemon.get('baseDefense', 0)
            sp_attack = pokemon.get('baseSpAttack', 0)
            sp_defense = pokemon.get('baseSpDefense', 0)
            speed = pokemon.get('baseSpeed', 0)
            total_bst = hp + attack + defense + sp_attack + sp_defense + speed
            
            f.write(f"{pokemon['species_id']},{pokemon['species_name']},{hp},{attack},{defense},{sp_attack},{sp_defense},{speed},{total_bst}\n")
    
    print(f"✓ Wrote {len(final_evolutions)} final evolution Pokemon to {OUTPUT_CSV}")

def main():
    print("Parsing species constants...")
    species_map = parse_species_constants()
    print(f"✓ Found {len(species_map)} species definitions")
    
    print("\nParsing species data files...")
    species_data, has_evolutions = parse_species_data()
    print(f"✓ Found {len(species_data)} species with stat data")
    print(f"✓ Found {len(has_evolutions)} species with evolutions")
    
    print("\nIdentifying final evolutions...")
    final_evolutions = find_final_evolutions(species_data, has_evolutions, species_map)
    print(f"✓ Found {len(final_evolutions)} final evolution Pokemon")
    
    print("\nWriting CSV file...")
    write_csv(final_evolutions)
    
    print("\nDone! You can now import final_evolutions_stats.csv into Google Sheets.")
    print("\nColumns:")
    print("  - Species ID: Internal species ID")
    print("  - Species Name: Internal name (e.g., VENUSAUR)")
    print("  - HP, Attack, Defense, Special Attack, Special Defense, Speed: Base stats")
    print("  - Total BST: Base Stat Total (sum of all stats)")

if __name__ == '__main__':
    main()

