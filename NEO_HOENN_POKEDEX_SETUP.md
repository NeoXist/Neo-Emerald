# Neo-Hoenn Custom Regional Pokédex Setup

## ✅ What Has Been Done

I've successfully created and integrated a **custom regional Pokédex** for your Neo-Emerald project containing exactly **494 Pokémon** from your specified list.

### Files Modified:

1. **`include/constants/pokedex.h`**
   - Added `DEX_MODE_NEO_HOENN` to the Pokédex mode enum
   - Added `NEO_HOENN_DEX_COUNT` definition (495 including NONE)

2. **`src/data/pokemon/pokedex_orders.h`**
   - Added `gPokedexOrder_NeoHoenn[]` array with all 494 Pokémon in order
   - This defines the exact ordering your custom regional dex will use

3. **`src/pokedex.c`**
   - Updated `sDexModeOptions[]` to include Neo-Hoenn dex option
   - Updated `sPokedexModes[]` to include all three modes (Hoenn, Neo-Hoenn, National)
   - Changed default initialization from `DEX_MODE_HOENN` to `DEX_MODE_NEO_HOENN`
   - Updated all fallback cases to use Neo-Hoenn when National Dex is disabled
   - Added support for Neo-Hoenn dex numbering display
   - Updated dex count handling to support Neo-Hoenn (495 entries)

4. **`src/pokemon.c`**
   - Added `NationalToNeoHoennOrder()` function to convert National Dex → Neo-Hoenn Dex numbers
   - Added extern declaration for `gPokedexOrder_NeoHoenn[]`

5. **`include/pokemon.h`**
   - Added function declaration for `NationalToNeoHoennOrder()`

6. **`src/strings.c`**
   - Added `gText_DexNeoHoennTitle` = "NEO-HOENN DEX"
   - Added `gText_DexNeoHoennDescription` = "NEO-HOENN region's POKéDEX"
   - Added `gText_DexNeoHoenn` = "NEO-HOENN"

7. **`include/strings.h`**
   - Added extern declarations for the new text strings

## 🎮 How It Works

### In-Game Behavior:

- **Default Pokédex**: Neo-Hoenn Regional (494 Pokémon)
- **National Dex**: Available after unlocking (contains all Pokémon)
- **Original Hoenn Dex**: Still available for compatibility

Players can switch between dexes using the Pokédex search menu:
- Press SELECT in the Pokédex
- Choose "MODE" 
- Select between HOENN DEX / NEO-HOENN DEX / NATIONAL DEX

### Default Pokédex at Game Start:

When a new game is started, the Pokédex will default to **NEO-HOENN DEX** and show only the 494 Pokémon you've included in your game.

## 📝 Your Pokémon List (494 Total)

The Neo-Hoenn dex includes all Pokémon from your list:
- Kanto starters and their lines (Bulbasaur, Squirtle families)
- Johto starters and their lines (Chikorita, Cyndaquil, Totodile families)
- Hoenn region Pokémon with custom evolutions (Brawyena, Empyrena, etc.)
- Sinnoh Pokémon (Turtwig, Chimchar, Piplup families, etc.)
- Unova Pokémon (Snivy, Tepig, Oshawott families, etc.)
- Kalos Pokémon (Fennekin, Froakie, Fletchling families, etc.)
- Alola Pokémon (Rowlet, Popplio families, etc.)
- Galar Pokémon (Scorbunny, Rookidee families, etc.)
- Paldea Pokémon (Sprigatito, Fuecoco families, etc.)
- Regional forms (Alolan, Galarian, Hisuian variants)
- Mega Evolutions (noted in your list but handled via forms)

## 🔧 Remaining Steps (Optional)

### If You Want to Remove the Old Hoenn Dex Option:

Since you have a custom dex, you might want to remove the original Hoenn dex option from the search menu:

1. Change `sPokedexModes[]` in `src/pokedex.c`:
   ```c
   // From:
   static const u8 sPokedexModes[] = {DEX_MODE_HOENN, DEX_MODE_NEO_HOENN, DEX_MODE_NATIONAL};
   
   // To:
   static const u8 sPokedexModes[] = {DEX_MODE_NEO_HOENN, DEX_MODE_NATIONAL};
   ```

2. This will give players only two options: Neo-Hoenn (default) and National

### To Update Pokédex Completion Certificate:

The diploma text currently references "{STR_VAR_1} POKéDEX". This will automatically show "NEO-HOENN POKéDEX" when completed!

## 🧪 Testing

To test your custom Pokédex:

1. Compile the ROM: `make`
2. Start a new game or load a save
3. Open the Pokédex (after receiving it from the Professor)
4. Press SELECT → Search Menu → MODE
5. You should see three options: HOENN DEX, NEO-HOENN DEX (default), NATIONAL DEX
6. Verify only your 494 Pokémon appear in Neo-Hoenn mode

## 📊 Benefits of Custom Regional Dex:

✅ **No Empty Slots** - Players won't see unavailable Pokémon  
✅ **Cleaner UI** - No confusing gaps in the dex  
✅ **Better Performance** - Smaller dex = faster loading  
✅ **Custom Ordering** - You control the exact order Pokémon appear  
✅ **Completionist-Friendly** - Players can actually complete the regional dex!  

## 🔄 Future Updates

If you want to add or remove Pokémon later:

1. Update your Pokémon list
2. Edit the `gPokedexOrder_NeoHoenn[]` array in `src/data/pokemon/pokedex_orders.h`
3. Update `NEO_HOENN_DEX_COUNT` in `include/constants/pokedex.h`
4. Recompile

---

Your custom Neo-Hoenn Pokédex is now fully integrated and ready to use! 🎉






