#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Ram Head boosts the power of ramming moves by 30%")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TACKLE; }
    PARAMETRIZE { move = MOVE_BULLDOZE; }
    PARAMETRIZE { move = MOVE_TAKE_DOWN; }
    PARAMETRIZE { move = MOVE_WILD_CHARGE; }
    PARAMETRIZE { move = MOVE_FLAME_CHARGE; }
    PARAMETRIZE { move = MOVE_IRON_HEAD; }
    PARAMETRIZE { move = MOVE_HEAD_CHARGE; }
    PARAMETRIZE { move = MOVE_ROLLOUT; }
    PARAMETRIZE { move = MOVE_GIGA_IMPACT; }
    PARAMETRIZE { move = MOVE_HEADBUTT; }
    PARAMETRIZE { move = MOVE_ZEN_HEADBUTT; }
    PARAMETRIZE { move = MOVE_HEAD_SMASH; }
    PARAMETRIZE { move = MOVE_HORN_LEECH; }
    
    GIVEN {
        PLAYER(SPECIES_RAMPARDOS) { Ability(ABILITY_RAM_HEAD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Ram Head does not boost non-ramming moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_EMBER; }
    PARAMETRIZE { move = MOVE_WATER_GUN; }
    PARAMETRIZE { move = MOVE_THUNDERBOLT; }
    PARAMETRIZE { move = MOVE_PSYCHIC; }
    PARAMETRIZE { move = MOVE_ICE_BEAM; }
    PARAMETRIZE { move = MOVE_DRAGON_PULSE; }
    PARAMETRIZE { move = MOVE_DARK_PULSE; }
    PARAMETRIZE { move = MOVE_FAIRY_WIND; }
    PARAMETRIZE { move = MOVE_ROCK_THROW; }
    
    GIVEN {
        PLAYER(SPECIES_RAMPARDOS) { Ability(ABILITY_RAM_HEAD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.0), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Ram Head works with different Pokemon")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_RAMPARDOS; }
    PARAMETRIZE { species = SPECIES_CRANIDOS; }
    PARAMETRIZE { species = SPECIES_SKIDDO; }
    PARAMETRIZE { species = SPECIES_GOGOAT; }
    
    GIVEN {
        PLAYER(species) { Ability(ABILITY_RAM_HEAD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}
