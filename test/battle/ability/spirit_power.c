#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Spirit Power doubles Special Attack for special moves")
{
    GIVEN {
        PLAYER(SPECIES_MEDITITE) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        MESSAGE("Meditite used Psychic!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(2.0), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Spirit Power doesn't affect physical moves")
{
    GIVEN {
        PLAYER(SPECIES_MEDITITE) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ZEN_HEADBUTT); }
    } SCENE {
        MESSAGE("Meditite used Zen Headbutt!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Spirit Power works with various special moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_PSYCHIC; }
    PARAMETRIZE { move = MOVE_PSYBEAM; }
    PARAMETRIZE { move = MOVE_CONFUSION; }
    PARAMETRIZE { move = MOVE_FUTURE_SIGHT; }
    PARAMETRIZE { move = MOVE_PSYSHOCK; }
    PARAMETRIZE { move = MOVE_PSYCHIC_FANGS; }
    PARAMETRIZE { move = MOVE_PSYCHIC_TERRAIN; }
    PARAMETRIZE { move = MOVE_PSYCHIC_NOISE; }
    
    GIVEN {
        PLAYER(SPECIES_MEDITITE) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Meditite used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(2.0), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Spirit Power works with non-Psychic special moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_FIRE_BLAST; }
    PARAMETRIZE { move = MOVE_THUNDERBOLT; }
    PARAMETRIZE { move = MOVE_ICE_BEAM; }
    PARAMETRIZE { move = MOVE_ENERGY_BALL; }
    PARAMETRIZE { move = MOVE_DARK_PULSE; }
    PARAMETRIZE { move = MOVE_FLASH_CANNON; }
    PARAMETRIZE { move = MOVE_DRAGON_PULSE; }
    PARAMETRIZE { move = MOVE_SHADOW_BALL; }
    
    GIVEN {
        PLAYER(SPECIES_MEDITITE) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Meditite used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(2.0), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Spirit Power doesn't affect status moves")
{
    GIVEN {
        PLAYER(SPECIES_MEDITITE) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MEDITATE); }
    } SCENE {
        MESSAGE("Meditite used Meditate!");
        MESSAGE("Meditite's Attack rose!");
    } THEN {
        // Status moves don't deal damage, so no damage boost expected
    }
}

SINGLE_BATTLE_TEST("Spirit Power works with Medicham")
{
    GIVEN {
        PLAYER(SPECIES_MEDICHAM) { Ability(ABILITY_SPIRIT_POWER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        MESSAGE("Medicham used Psychic!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(2.0), results[0].damage);
    }
}
