#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Snow Force boosts Ice-type moves by 30% in hail")
{
    GIVEN {
        PLAYER(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BEAM); }
    } SCENE {
        MESSAGE("Abomasnow used Ice Beam!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Snow Force boosts Ice-type moves by 30% in snow")
{
    GIVEN {
        PLAYER(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BEAM); }
    } SCENE {
        MESSAGE("Abomasnow used Ice Beam!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Snow Force doesn't boost non-Ice-type moves")
{
    GIVEN {
        PLAYER(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LEAF_STORM); }
    } SCENE {
        MESSAGE("Abomasnow used Leaf Storm!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Snow Force doesn't boost Ice-type moves outside of hail/snow")
{
    GIVEN {
        PLAYER(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BEAM); }
    } SCENE {
        MESSAGE("Abomasnow used Ice Beam!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Snow Force works with different Ice-type moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_ICE_BEAM; }
    PARAMETRIZE { move = MOVE_ICE_SHARD; }
    PARAMETRIZE { move = MOVE_ICICLE_CRASH; }
    PARAMETRIZE { move = MOVE_FREEZE_DRY; }
    PARAMETRIZE { move = MOVE_FROST_BREATH; }
    PARAMETRIZE { move = MOVE_GLACIATE; }
    PARAMETRIZE { move = MOVE_ICE_PUNCH; }
    PARAMETRIZE { move = MOVE_ICE_FANG; }
    
    GIVEN {
        PLAYER(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Abomasnow used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}
