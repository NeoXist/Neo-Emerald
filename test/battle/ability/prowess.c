#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Prowess raises Special Attack by one stage after directly causing a Pokemon to faint")
{
    u32 species = 0, ability = 0, abilityPopUp = 0;
    PARAMETRIZE { species = SPECIES_VOLCARONA;         ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_PYROAR;            ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_FROSLASS;          ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_SURF) == MOVE_TARGET_FOES_AND_ALLY);
        PLAYER(species) { Ability(ability); }
        PLAYER(SPECIES_SNORUNT) { HP(1); }
        OPPONENT(SPECIES_GLALIE) { HP(1); }
        OPPONENT(SPECIES_ABRA) { HP(1); }
        OPPONENT(SPECIES_ABRA);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); SEND_OUT(opponentLeft, 2);  }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, playerLeft);
        MESSAGE("The opposing Glalie fainted!");
        MESSAGE("Snorunt fainted!");
        MESSAGE("The opposing Abra fainted!");
        ABILITY_POPUP(playerLeft, abilityPopUp);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        if (species == SPECIES_VOLCARONA)
            MESSAGE("Volcarona's Special Attack drastically rose!");
        else if (species == SPECIES_PYROAR)
            MESSAGE("Pyroar's Special Attack drastically rose!");
        else
            MESSAGE("Froslass's Special Attack drastically rose!");
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 3);
    }
}

DOUBLE_BATTLE_TEST("Prowess does not trigger if Pokemon faint to indirect damage or damage from other Pokemon")
{
    u32 species = 0, ability = 0, abilityPopUp = 0;
    PARAMETRIZE { species = SPECIES_VOLCARONA;         ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_PYROAR;            ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_FROSLASS;          ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    GIVEN {
        PLAYER(species) { Ability(ability); }
        PLAYER(SPECIES_SNORUNT) { HP(1); Status1(STATUS1_POISON); }
        OPPONENT(SPECIES_GLALIE) { HP(1); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_ABRA) { HP(1); }
        OPPONENT(SPECIES_ABRA);
    } WHEN {
        TURN { MOVE(playerRight, MOVE_QUICK_ATTACK, target: opponentRight); SEND_OUT(opponentLeft, 2);  }
    } SCENE {
        int i;

        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, playerRight);
        for (i = 0; i < 3; i++) {
            ONE_OF {
                MESSAGE("Snorunt fainted!");
                MESSAGE("The opposing Glalie fainted!");
                MESSAGE("The opposing Abra fainted!");
            }
            NONE_OF {
                ABILITY_POPUP(playerLeft, abilityPopUp);
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
                MESSAGE("Volcarona's Prowess raised its Special Attack!");
                MESSAGE("Pyroar's Prowess raised its Special Attack!");
                MESSAGE("Froslass's Prowess raised its Special Attack!");
            }
        }
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Prowess does not trigger when already at maximum Special Attack stage")
{
    u32 species = 0, ability = 0, abilityPopUp = 0;
    PARAMETRIZE { species = SPECIES_VOLCARONA;         ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_PYROAR;            ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_FROSLASS;          ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_NASTY_PLOT) == EFFECT_NASTY_PLOT);
        PLAYER(species) { Ability(ability); }
        OPPONENT(SPECIES_SNORUNT) { HP(1); }
        OPPONENT(SPECIES_SNORUNT);
    } WHEN {
        TURN { MOVE(player, MOVE_NASTY_PLOT); }
        TURN { MOVE(player, MOVE_PSYCHIC); SEND_OUT(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_NASTY_PLOT, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        if (species == SPECIES_VOLCARONA)
            MESSAGE("Volcarona's Special Attack sharply rose!");
        else if (species == SPECIES_PYROAR)
            MESSAGE("Pyroar's Special Attack sharply rose!");
        else
            MESSAGE("Froslass's Special Attack sharply rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, player);
        MESSAGE("The opposing Snorunt fainted!");
        NONE_OF {
            ABILITY_POPUP(player, abilityPopUp);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Volcarona's Prowess raised its Special Attack!");
            MESSAGE("Pyroar's Prowess raised its Special Attack!");
            MESSAGE("Froslass's Prowess raised its Special Attack!");
        }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPATK], MAX_STAT_STAGE);
    }
}

DOUBLE_BATTLE_TEST("Prowess does not increase damage done by the same move that causes another Pokemon to faint")
{
    s16 damage[2];
    u32 species = 0, ability = 0, abilityPopUp = 0;
    PARAMETRIZE { species = SPECIES_VOLCARONA;         ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_PYROAR;            ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }
    PARAMETRIZE { species = SPECIES_FROSLASS;          ability = ABILITY_PROWESS;            abilityPopUp = ABILITY_PROWESS;          }

    GIVEN {
        ASSUME(GetMoveTarget(MOVE_SURF) == MOVE_TARGET_FOES_AND_ALLY);
        PLAYER(species) { Ability(ability); }
        PLAYER(SPECIES_ABRA) { HP(1); }
        OPPONENT(SPECIES_GLALIE);
        OPPONENT(SPECIES_GLALIE);
        OPPONENT(SPECIES_ABRA);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, playerLeft);
        HP_BAR(opponentLeft, captureDamage: &damage[0]);
        HP_BAR(playerRight);
        HP_BAR(opponentRight, captureDamage: &damage[1]);
        MESSAGE("Abra fainted!");
        ABILITY_POPUP(playerLeft, abilityPopUp);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        if (species == SPECIES_VOLCARONA)
            MESSAGE("Volcarona's Special Attack rose!");
        else if (species == SPECIES_PYROAR)
            MESSAGE("Pyroar's Special Attack rose!");
        else
            MESSAGE("Froslass's Special Attack rose!");
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(damage[0], damage[1]);
    }
}
