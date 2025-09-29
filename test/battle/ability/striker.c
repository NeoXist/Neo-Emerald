#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Striker boosts kicking moves by 30%")
{
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLAZE_KICK); }
    } SCENE {
        MESSAGE("Blaziken used Blaze Kick!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Striker doesn't boost non-kicking moves")
{
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FIRE_PUNCH); }
    } SCENE {
        MESSAGE("Blaziken used Fire Punch!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}

SINGLE_BATTLE_TEST("Striker works with various kicking moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_HIGH_JUMP_KICK; }
    PARAMETRIZE { move = MOVE_JUMP_KICK; }
    PARAMETRIZE { move = MOVE_MEGA_KICK; }
    PARAMETRIZE { move = MOVE_DOUBLE_KICK; }
    PARAMETRIZE { move = MOVE_TRIPLE_KICK; }
    PARAMETRIZE { move = MOVE_BLAZE_KICK; }
    PARAMETRIZE { move = MOVE_LOW_KICK; }
    PARAMETRIZE { move = MOVE_LOW_SWEEP; }
    PARAMETRIZE { move = MOVE_TRIPLE_AXEL; }
    PARAMETRIZE { move = MOVE_TROP_KICK; }
    PARAMETRIZE { move = MOVE_HIGH_HORSEPOWER; }
    PARAMETRIZE { move = MOVE_ROLLING_KICK; }
    PARAMETRIZE { move = MOVE_PYRO_BALL; }
    PARAMETRIZE { move = MOVE_THUNDEROUS_KICK; }
    
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Blaziken used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Striker works with stomping moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_STOMP; }
    PARAMETRIZE { move = MOVE_STOMPING_TANTRUM; }
    
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Blaziken used %s!", move);
        HP_BAR(opponent, captureDamage: results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Striker works with Cinderace")
{
    GIVEN {
        PLAYER(SPECIES_CINDERACE) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLAZE_KICK); }
    } SCENE {
        MESSAGE("Cinderace used Blaze Kick!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Striker works with Lopunny")
{
    GIVEN {
        PLAYER(SPECIES_LOPUNNY) { Ability(ABILITY_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HIGH_JUMP_KICK); }
    } SCENE {
        MESSAGE("Lopunny used High Jump Kick!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[0].damage);
    }
}
