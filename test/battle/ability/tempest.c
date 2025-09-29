#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Tempest boosts wing moves by 25%")
{
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WING_ATTACK); }
    } SCENE {
        MESSAGE("Pidgeot used Wing Attack!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.25), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest boosts wind moves by 25%")
{
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAZOR_WIND); }
    } SCENE {
        MESSAGE("Pidgeot used Razor Wind!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.25), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest boosts air moves by 25%")
{
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AIR_SLASH); }
    } SCENE {
        MESSAGE("Pidgeot used Air Slash!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.25), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest doesn't boost non-wing non-wind non-air moves")
{
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Pidgeot used Tackle!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Tempest works with various wing moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_WING_ATTACK; }
    PARAMETRIZE { move = MOVE_BRAVE_BIRD; }
    PARAMETRIZE { move = MOVE_ACROBATICS; }
    PARAMETRIZE { move = MOVE_AERIAL_ACE; }
    PARAMETRIZE { move = MOVE_DRILL_PECK; }
    PARAMETRIZE { move = MOVE_PECK; }
    PARAMETRIZE { move = MOVE_SKY_ATTACK; }
    PARAMETRIZE { move = MOVE_FLY; }
    
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Pidgeot used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.25), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest works with various wind moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_RAZOR_WIND; }
    PARAMETRIZE { move = MOVE_ICY_WIND; }
    PARAMETRIZE { move = MOVE_LEAF_STORM; }
    PARAMETRIZE { move = MOVE_TAILWIND; }
    
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Pidgeot used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.25), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest works with various air moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_AIR_CUTTER; }
    PARAMETRIZE { move = MOVE_AIR_SLASH; }
    PARAMETRIZE { move = MOVE_AERIAL_ACE; }
    PARAMETRIZE { move = MOVE_GUST; }
    PARAMETRIZE { move = MOVE_HURRICANE; }
    PARAMETRIZE { move = MOVE_WHIRLWIND; }
    PARAMETRIZE { move = MOVE_TWISTER; }
    PARAMETRIZE { move = MOVE_DEFOG; }
    
    GIVEN {
        PLAYER(SPECIES_PIDGEOT) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Pidgeot used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.25), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest works with Swanna")
{
    GIVEN {
        PLAYER(SPECIES_SWANNA) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AIR_SLASH); }
    } SCENE {
        MESSAGE("Swanna used Air Slash!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.25), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Tempest works with Talonflame")
{
    GIVEN {
        PLAYER(SPECIES_TALONFLAME) { Ability(ABILITY_TEMPEST); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BRAVE_BIRD); }
    } SCENE {
        MESSAGE("Talonflame used Brave Bird!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.25), results[0].damage);
    }
}
