#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Resolve boosts Special Attack moves by 50% when statused")
{
    u32 status;
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    
    GIVEN {
        PLAYER(SPECIES_PETILIL) { Ability(ABILITY_RESOLVE); Status1(status); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.5), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Resolve does not boost Physical moves when statused")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TACKLE; }
    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_QUICK_ATTACK; }
    PARAMETRIZE { move = MOVE_BITE; }
    PARAMETRIZE { move = MOVE_HEADBUTT; }
    
    GIVEN {
        PLAYER(SPECIES_PETILIL) { Ability(ABILITY_RESOLVE); Status1(STATUS1_BURN); }
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

SINGLE_BATTLE_TEST("Resolve does not boost Special moves when not statused")
{
    u32 move;
    PARAMETRIZE { move = MOVE_PSYCHIC; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; }
    PARAMETRIZE { move = MOVE_THUNDERBOLT; }
    PARAMETRIZE { move = MOVE_ICE_BEAM; }
    PARAMETRIZE { move = MOVE_ENERGY_BALL; }
    
    GIVEN {
        PLAYER(SPECIES_PETILIL) { Ability(ABILITY_RESOLVE); }
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

SINGLE_BATTLE_TEST("Resolve works with different Pokemon")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_PETILIL; }
    PARAMETRIZE { species = SPECIES_LILLIGANT; }
    PARAMETRIZE { species = SPECIES_DUCKLETT; }
    PARAMETRIZE { species = SPECIES_SWANNA; }
    PARAMETRIZE { species = SPECIES_THIEVUL; }
    
    GIVEN {
        PLAYER(species) { Ability(ABILITY_RESOLVE); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.5), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Resolve works with all Special move categories")
{
    u32 move;
    PARAMETRIZE { move = MOVE_PSYCHIC; }      // Special Psychic
    PARAMETRIZE { move = MOVE_FLAMETHROWER; } // Special Fire
    PARAMETRIZE { move = MOVE_THUNDERBOLT; }  // Special Electric
    PARAMETRIZE { move = MOVE_ICE_BEAM; }     // Special Ice
    PARAMETRIZE { move = MOVE_ENERGY_BALL; }  // Special Grass
    PARAMETRIZE { move = MOVE_DRAGON_PULSE; } // Special Dragon
    PARAMETRIZE { move = MOVE_DARK_PULSE; }   // Special Dark
    PARAMETRIZE { move = MOVE_FAIRY_WIND; }   // Special Fairy
    PARAMETRIZE { move = MOVE_AURA_SPHERE; }  // Special Fighting
    PARAMETRIZE { move = MOVE_SHADOW_BALL; }  // Special Ghost
    
    GIVEN {
        PLAYER(SPECIES_PETILIL) { Ability(ABILITY_RESOLVE); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.5), results[i].damage);
    }
}
