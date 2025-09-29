#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Scarecrow lowers foe's accuracy by one stage when switching in")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Wobbuffet's accuracy fell!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Scarecrow affects all opposing Pokemon in double battle")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_SCARECROW);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        MESSAGE("Wobbuffet's accuracy fell!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("Wobbuffet's accuracy fell!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, playerLeft);
    } THEN {
        EXPECT_EQ(opponentLeft->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(opponentRight->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Scarecrow does not affect ally Pokemon")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_SCARECROW);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Wobbuffet's accuracy fell!");
        NONE_OF {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
            MESSAGE("Wobbuffet's accuracy fell!");
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, playerLeft);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(playerRight->statStages[STAT_ACC], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Scarecrow does not affect Pokemon behind Substitute")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_WOBBUFFET) { Status2(STATUS2_SUBSTITUTE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        NONE_OF {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("Wobbuffet's accuracy fell!");
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Scarecrow does not affect absent Pokemon")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); SEND_OUT(opponent, 1); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet fainted!");
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Wobbuffet's accuracy fell!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Scarecrow works with Contrary ability")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_SPIRITOMB) { Ability(ABILITY_CONTRARY); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        ABILITY_POPUP(opponent, ABILITY_CONTRARY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Spiritomb's accuracy rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Scarecrow shows won't decrease message when accuracy is already at minimum")
{
    GIVEN {
        PLAYER(SPECIES_CACTURNE) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_WOBBUFFET) { StatStages(STAT_ACC, MIN_STAT_STAGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        MESSAGE("Wobbuffet's accuracy won't go lower!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], MIN_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Scarecrow works with different Pokemon")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_CACTURNE; }
    PARAMETRIZE { species = SPECIES_CACNEA; }
    
    GIVEN {
        PLAYER(species) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SCARECROW);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Wobbuffet's accuracy fell!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}
