#!/usr/bin/env python3
"""
Extract final evolution Pokemon from Google Sheets CSV.
Uses Modified stats if available, otherwise Original stats.
Outputs to a clean CSV for the "Data Changes" tab.
"""

import csv
import re

INPUT_CSV = r"c:\Users\neoxi\Downloads\Just for data.xlsx - PokéChanges.csv"
OUTPUT_CSV = "final_evolutions_data_changes.csv"

def parse_pokemon_data():
    """Parse the CSV and extract Pokemon data."""
    pokemon_data = {}
    
    with open(INPUT_CSV, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        rows = list(reader)
    
    current_pokemon_id = None
    
    for i, row in enumerate(rows):
        # Skip first 2 rows (header/metadata)
        if i < 2:
            continue
        
        # Ensure row has enough columns
        while len(row) < 12:
            row.append("")
        
        # Column 1: Pokemon number, Column 3: Name, Column 5: "Original"/"Modified"
        pokemon_num = row[1].strip() if len(row) > 1 else ""
        pokemon_name = row[3].strip() if len(row) > 3 else ""
        row_type = row[5].strip() if len(row) > 5 else ""
        
        # Check if this is a new Pokemon entry
        if pokemon_num and pokemon_name and pokemon_name != "#N/A" and pokemon_name != "Name":
            # Skip Megas (check if name contains "Mega")
            if "Mega" in pokemon_name or "mega" in pokemon_name:
                current_pokemon_id = None
                continue
            
            # Skip form variants (has letters after number like '267s', '267t')
            if pokemon_num.lower().endswith('m') or re.match(r'^\d+[a-z]', pokemon_num.lower()):
                current_pokemon_id = None
                continue
            
            # Extract Pokemon ID
            base_num = re.match(r'^(\d+)', pokemon_num)
            if base_num:
                current_pokemon_id = int(base_num.group(1))
                
                # Initialize entry
                if current_pokemon_id not in pokemon_data:
                    pokemon_data[current_pokemon_id] = {
                        'name': pokemon_name,
                        'number': current_pokemon_id,
                        'original': {},
                        'modified': {}
                    }
                else:
                    pokemon_data[current_pokemon_id]['name'] = pokemon_name
        
        # Extract stats if we have a current Pokemon
        if current_pokemon_id is not None:
            # Check if this row has "Original" or "Modified" in column 3
            if row_type in ["Original", "Modified"]:
                try:
                    # Extract types (columns 7, 8) - but check if Type 2 exists
                    # Looking at the structure: col 7 = Type 1, col 8 might be Type 2 or HP
                    # If col 8 is a number, it's HP and there's no Type 2
                    type1 = row[7].strip() if len(row) > 7 and row[7].strip() and row[7].strip() != '#N/A' else ""
                    
                    # Check if col 8 is a number (HP) or a type name
                    if len(row) > 8:
                        col8 = row[8].strip()
                        if col8 and col8 != '#N/A' and not col8.isdigit():
                            type2 = col8
                            stat_start = 9
                        else:
                            type2 = ""
                            stat_start = 8
                    else:
                        type2 = ""
                        stat_start = 8
                    
                    # Extract stats starting from stat_start
                    stats = {}
                    stat_cols = [stat_start, stat_start+1, stat_start+2, stat_start+3, stat_start+4, stat_start+5]
                    stat_names = ['HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE']
                    
                    for col_idx, stat_name in zip(stat_cols, stat_names):
                        if len(row) > col_idx and row[col_idx].strip() and row[col_idx].strip() != '#N/A':
                            try:
                                val = int(row[col_idx])
                                stats[stat_name] = val
                            except ValueError:
                                stats[stat_name] = None
                        else:
                            stats[stat_name] = None
                    
                    # Only save if we have at least one stat
                    if any(v is not None for v in stats.values()):
                        pokemon_data[current_pokemon_id][row_type.lower()] = {
                            'stats': stats,
                            'type1': type1,
                            'type2': type2
                        }
                except (ValueError, IndexError) as e:
                    pass
            # Also check if stats are on the same row as the Pokemon name (when row_type is empty but stats exist)
            elif not row_type and len(row) > 8:
                # This might be an "Original" row with stats on the same line
                try:
                    type1 = row[7].strip() if len(row) > 7 and row[7].strip() and row[7].strip() != '#N/A' else ""
                    
                    # Check if col 8 is Type 2 or HP
                    if len(row) > 8:
                        col8 = row[8].strip()
                        if col8 and col8 != '#N/A' and not col8.isdigit():
                            type2 = col8
                            stat_start = 9
                        else:
                            type2 = ""
                            stat_start = 8
                    else:
                        type2 = ""
                        stat_start = 8
                    
                    stats = {}
                    stat_cols = [stat_start, stat_start+1, stat_start+2, stat_start+3, stat_start+4, stat_start+5]
                    stat_names = ['HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE']
                    
                    for col_idx, stat_name in zip(stat_cols, stat_names):
                        if len(row) > col_idx and row[col_idx].strip() and row[col_idx].strip() != '#N/A':
                            try:
                                stats[stat_name] = int(row[col_idx])
                            except ValueError:
                                stats[stat_name] = None
                        else:
                            stats[stat_name] = None
                    
                    if any(v is not None for v in stats.values()):
                        if not pokemon_data[current_pokemon_id].get('original'):
                            pokemon_data[current_pokemon_id]['original'] = {
                                'stats': stats,
                                'type1': type1,
                                'type2': type2
                            }
                except (ValueError, IndexError):
                    pass
    
    return pokemon_data

def identify_final_evolutions(pokemon_data):
    """Identify which Pokemon are final evolutions and extract their final stats."""
    final_evolutions = []
    
    # Sort by Pokemon number
    sorted_pokemon = sorted(pokemon_data.items())
    
    for pokemon_id, data in sorted_pokemon:
        # Get Original and Modified data
        original_data = data.get('original', {})
        modified_data = data.get('modified', {})
        original_stats = original_data.get('stats', {}) if original_data else {}
        modified_stats = modified_data.get('stats', {}) if modified_data else {}
        
        # Merge stats: use Modified if available, otherwise use Original
        final_stats = {}
        for stat in ['HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE']:
            final_stats[stat] = modified_stats.get(stat) if modified_stats.get(stat) is not None else original_stats.get(stat)
        
        # Skip if we don't have all 6 stats
        if not all(final_stats.get(stat) is not None for stat in ['HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE']):
            continue
        
        # Use Modified types if available, otherwise Original
        type1 = modified_data.get('type1', '') or original_data.get('type1', '')
        type2 = modified_data.get('type2', '') or original_data.get('type2', '')
        
        # Calculate total
        total = sum([final_stats['HP'], final_stats['ATK'], final_stats['DEF'], 
                     final_stats['SPA'], final_stats['SPD'], final_stats['SPE']])
        
        final_evolutions.append({
            'number': pokemon_id,
            'name': data['name'],
            'type1': type1,
            'type2': type2,
            'HP': final_stats['HP'],
            'ATK': final_stats['ATK'],
            'DEF': final_stats['DEF'],
            'SPA': final_stats['SPA'],
            'SPD': final_stats['SPD'],
            'SPE': final_stats['SPE'],
            'Total': total
        })
    
    return final_evolutions

def write_output(final_evolutions):
    """Write final evolutions to CSV."""
    with open(OUTPUT_CSV, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        
        # Write header
        writer.writerow(['#', 'Name', 'Type 1', 'Type 2', 'HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE', 'Total'])
        
        # Write data
        for pokemon in final_evolutions:
            writer.writerow([
                pokemon['number'],
                pokemon['name'],
                pokemon['type1'],
                pokemon['type2'],
                pokemon['HP'],
                pokemon['ATK'],
                pokemon['DEF'],
                pokemon['SPA'],
                pokemon['SPD'],
                pokemon['SPE'],
                pokemon['Total']
            ])
    
    print(f"✓ Wrote {len(final_evolutions)} final evolution Pokemon to {OUTPUT_CSV}")

def main():
    print("Parsing Pokemon data from CSV...")
    pokemon_data = parse_pokemon_data()
    print(f"✓ Found {len(pokemon_data)} Pokemon entries")
    
    # Debug: print first few entries
    if pokemon_data:
        print("\nSample entries:")
        for pid in sorted(pokemon_data.keys())[:5]:
            print(f"  {pid}: {pokemon_data[pid]['name']} - Original: {bool(pokemon_data[pid].get('original'))}, Modified: {bool(pokemon_data[pid].get('modified'))}")
    
    print("\nIdentifying final evolutions...")
    final_evolutions = identify_final_evolutions(pokemon_data)
    print(f"✓ Found {len(final_evolutions)} final evolution Pokemon")
    
    print("\nWriting output CSV...")
    write_output(final_evolutions)
    
    print("\nDone! The file 'final_evolutions_data_changes.csv' is ready to import into your 'Data Changes' tab.")

if __name__ == '__main__':
    main()
