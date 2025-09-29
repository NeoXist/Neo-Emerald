#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Swarm boosts Bug moves by 20% above 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_SCYTHER) { Ability(ABILITY_SWARM); HP(100); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BUZZ); }
    } SCENE {
        MESSAGE("Scyther used Bug Buzz!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Swarm boosts Bug moves by 50% below 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_SCYTHER) { Ability(ABILITY_SWARM); HP(30); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BUZZ); }
    } SCENE {
        MESSAGE("Scyther used Bug Buzz!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Torrent boosts Water moves by 20% above 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_SQUIRTLE) { Ability(ABILITY_TORRENT); HP(100); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        MESSAGE("Squirtle used Water Gun!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Torrent boosts Water moves by 50% below 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_SQUIRTLE) { Ability(ABILITY_TORRENT); HP(30); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        MESSAGE("Squirtle used Water Gun!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Blaze boosts Fire moves by 20% above 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_CHARMANDER) { Ability(ABILITY_BLAZE); HP(100); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        MESSAGE("Charmander used Ember!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Blaze boosts Fire moves by 50% below 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_CHARMANDER) { Ability(ABILITY_BLAZE); HP(30); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        MESSAGE("Charmander used Ember!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Overgrow boosts Grass moves by 20% above 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_OVERGROW); HP(100); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_VINE_WHIP); }
    } SCENE {
        MESSAGE("Bulbasaur used Vine Whip!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Overgrow boosts Grass moves by 50% below 1/3 HP")
{
    GIVEN {
        PLAYER(SPECIES_BULBASAUR) { Ability(ABILITY_OVERGROW); HP(30); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_VINE_WHIP); }
    } SCENE {
        MESSAGE("Bulbasaur used Vine Whip!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Type boost abilities don't affect other types")
{
    GIVEN {
        PLAYER(SPECIES_CHARMANDER) { Ability(ABILITY_BLAZE); HP(30); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Charmander used Tackle!");
        HP_BAR(opponent, captureDamage: results[0].damage);
    } THEN {
        EXPECT_EQ(results[0].damage, results[0].damage); // No boost
    }
}
