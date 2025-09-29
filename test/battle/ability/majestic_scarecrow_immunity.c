#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Majestic is prevented by Oblivious")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAJESTIC); }
        OPPONENT(SPECIES_SLOWPOKE) { Ability(ABILITY_OBLIVIOUS); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Slowpoke!");
        NONE_OF {
            MESSAGE("Wobbuffet's Majestic cut Slowpoke's Special Attack!");
        }
    }
}

SINGLE_BATTLE_TEST("Majestic is prevented by Own Tempo")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAJESTIC); }
        OPPONENT(SPECIES_SPOINK) { Ability(ABILITY_OWN_TEMPO); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Spoink!");
        NONE_OF {
            MESSAGE("Wobbuffet's Majestic cut Spoink's Special Attack!");
        }
    }
}

SINGLE_BATTLE_TEST("Majestic is prevented by Inner Focus")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAJESTIC); }
        OPPONENT(SPECIES_ABRA) { Ability(ABILITY_INNER_FOCUS); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Abra!");
        NONE_OF {
            MESSAGE("Wobbuffet's Majestic cut Abra's Special Attack!");
        }
    }
}

SINGLE_BATTLE_TEST("Majestic is prevented by Scrappy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAJESTIC); }
        OPPONENT(SPECIES_KANGASKHAN) { Ability(ABILITY_SCRAPPY); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Kangaskhan!");
        NONE_OF {
            MESSAGE("Wobbuffet's Majestic cut Kangaskhan's Special Attack!");
        }
    }
}

SINGLE_BATTLE_TEST("Scarecrow is prevented by Oblivious")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_SLOWPOKE) { Ability(ABILITY_OBLIVIOUS); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Slowpoke!");
        NONE_OF {
            MESSAGE("Wobbuffet's Scarecrow cut Slowpoke's accuracy!");
        }
    }
}

SINGLE_BATTLE_TEST("Scarecrow is prevented by Own Tempo")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_SPOINK) { Ability(ABILITY_OWN_TEMPO); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Spoink!");
        NONE_OF {
            MESSAGE("Wobbuffet's Scarecrow cut Spoink's accuracy!");
        }
    }
}

SINGLE_BATTLE_TEST("Scarecrow is prevented by Inner Focus")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_ABRA) { Ability(ABILITY_INNER_FOCUS); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Abra!");
        NONE_OF {
            MESSAGE("Wobbuffet's Scarecrow cut Abra's accuracy!");
        }
    }
}

SINGLE_BATTLE_TEST("Scarecrow is prevented by Scrappy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_KANGASKHAN) { Ability(ABILITY_SCRAPPY); }
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Kangaskhan!");
        NONE_OF {
            MESSAGE("Wobbuffet's Scarecrow cut Kangaskhan's accuracy!");
        }
    }
}

SINGLE_BATTLE_TEST("Majestic works on normal targets")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MAJESTIC); }
        OPPONENT(SPECIES_RATTATA);
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Rattata!");
        MESSAGE("Wobbuffet's Majestic cut Rattata's Special Attack!");
    }
}

SINGLE_BATTLE_TEST("Scarecrow works on normal targets")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SCARECROW); }
        OPPONENT(SPECIES_RATTATA);
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        MESSAGE("Go! Rattata!");
        MESSAGE("Wobbuffet's Scarecrow cut Rattata's accuracy!");
    }
}
