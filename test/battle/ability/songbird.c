#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Songbird boosts sound-based moves by 20%")
{
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BUZZ); }
    } SCENE {
        MESSAGE("Swellow used Bug Buzz!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Songbird boosts wing-based moves by 20%")
{
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WING_ATTACK); }
    } SCENE {
        MESSAGE("Swellow used Wing Attack!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Songbird doesn't boost non-sound non-wing moves")
{
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Swellow used Tackle!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Songbird works with various sound moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_BUG_BUZZ; }
    PARAMETRIZE { move = MOVE_BOOMBURST; }
    PARAMETRIZE { move = MOVE_CHATTER; }
    PARAMETRIZE { move = MOVE_DISARMING_VOICE; }
    PARAMETRIZE { move = MOVE_ECHOED_VOICE; }
    PARAMETRIZE { move = MOVE_HYPER_VOICE; }
    PARAMETRIZE { move = MOVE_ROUND; }
    PARAMETRIZE { move = MOVE_SING; }
    
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Swellow used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.2), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Songbird works with various wing moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_WING_ATTACK; }
    PARAMETRIZE { move = MOVE_BRAVE_BIRD; }
    PARAMETRIZE { move = MOVE_ACROBATICS; }
    PARAMETRIZE { move = MOVE_AERIAL_ACE; }
    PARAMETRIZE { move = MOVE_AIR_SLASH; }
    PARAMETRIZE { move = MOVE_DRILL_PECK; }
    PARAMETRIZE { move = MOVE_PECK; }
    PARAMETRIZE { move = MOVE_SKY_ATTACK; }
    
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Swellow used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.2), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Songbird boosts both sound and wing moves")
{
    GIVEN {
        PLAYER(SPECIES_SWELLOW) { Ability(ABILITY_SONGBIRD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BUZZ); }
        TURN { MOVE(player, MOVE_WING_ATTACK); }
    } SCENE {
        MESSAGE("Swellow used Bug Buzz!");
        HP_BAR(opponent, captureDamage: results[0].damage);
        MESSAGE("Swellow used Wing Attack!");
        HP_BAR(opponent, captureDamage: results[1].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
        EXPECT_MUL_EQ(results[1].damage, UQ_4_12(1.2), results[1].damage);
    }
}
