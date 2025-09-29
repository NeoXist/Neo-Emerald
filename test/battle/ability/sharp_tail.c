#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Sharp Tail boosts the power of tail moves by 30%")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TAIL_WHIP; }
    PARAMETRIZE { move = MOVE_IRON_TAIL; }
    PARAMETRIZE { move = MOVE_DRAGON_TAIL; }
    PARAMETRIZE { move = MOVE_POISON_TAIL; }
    PARAMETRIZE { move = MOVE_TAIL_SLAP; }
    PARAMETRIZE { move = MOVE_TAIL_GLOW; }
    PARAMETRIZE { move = MOVE_TAIL_WIND; }
    PARAMETRIZE { move = MOVE_AQUA_TAIL; }
    
    GIVEN {
        PLAYER(SPECIES_DRAGONAIR) { Ability(ABILITY_SHARP_TAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Sharp Tail does not boost non-tail moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TACKLE; }
    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_QUICK_ATTACK; }
    PARAMETRIZE { move = MOVE_BITE; }
    PARAMETRIZE { move = MOVE_HEADBUTT; }
    PARAMETRIZE { move = MOVE_PSYCHIC; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; }
    PARAMETRIZE { move = MOVE_THUNDERBOLT; }
    PARAMETRIZE { move = MOVE_ICE_BEAM; }
    PARAMETRIZE { move = MOVE_ENERGY_BALL; }
    
    GIVEN {
        PLAYER(SPECIES_DRAGONAIR) { Ability(ABILITY_SHARP_TAIL); }
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

SINGLE_BATTLE_TEST("Sharp Tail works with different Pokemon")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_DRAGONAIR; }
    PARAMETRIZE { species = SPECIES_DRAGONITE; }
    PARAMETRIZE { species = SPECIES_DRATINI; }
    
    GIVEN {
        PLAYER(species) { Ability(ABILITY_SHARP_TAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_IRON_TAIL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_IRON_TAIL, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Sharp Tail works with all tail move types")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TAIL_WHIP; }    // Normal
    PARAMETRIZE { move = MOVE_IRON_TAIL; }    // Steel
    PARAMETRIZE { move = MOVE_DRAGON_TAIL; }  // Dragon
    PARAMETRIZE { move = MOVE_POISON_TAIL; }  // Poison
    PARAMETRIZE { move = MOVE_TAIL_SLAP; }    // Normal
    PARAMETRIZE { move = MOVE_TAIL_GLOW; }    // Bug
    PARAMETRIZE { move = MOVE_TAIL_WIND; }    // Flying
    PARAMETRIZE { move = MOVE_AQUA_TAIL; }    // Water
    
    GIVEN {
        PLAYER(SPECIES_DRAGONAIR) { Ability(ABILITY_SHARP_TAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.3), results[i].damage);
    }
}

SINGLE_BATTLE_TEST("Sharp Tail stacks with other damage modifiers")
{
    GIVEN {
        PLAYER(SPECIES_DRAGONAIR) { Ability(ABILITY_SHARP_TAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_TAIL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_TAIL, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        // Should get 1.3x from Sharp Tail + 1.5x from STAB = 1.95x total
        EXPECT_MUL_EQ(results[i].damage, UQ_4_12(1.95), results[i].damage);
    }
}
