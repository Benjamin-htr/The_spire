#include "entity.h"
#include "../misc/stat/stat.h"
#include <stdio.h>
#include <stdlib.h>

// CONSTRUCTORS
entity_t *initEntity(char *name, int stats[][2], int cards[][2], int diffCardSize)
// for cards param first int is the card id 2nd one is the number of card
// for diffCardSize param is just the size of the array
{
    entity_t *res = malloc(sizeof(entity_t));
    res->name = name;
    res->stats = initEntityStatFromArray(stats);
    res->effects = initEffectBar();
    res->cardDeck = createDeckFromArray(cards, diffCardSize);
    return res;
}

entity_t *importCaracter(entity_import entitySkel)
{
    return initEntity(
        entitySkel.name,
        entitySkel.stats,
        entitySkel.cardDeck,
        entitySkel.diffCardSize);
}

entity_t *importCaracterFromId(CARACTER_ID id)
{
    return importCaracter(CARATER_ENCYCLOPEDIA[id]);
}

entity_t *importEnemy(enemy_import enemySkel)
{
    int hp =
        enemySkel.hpRange[0] + (rand() %
                                (enemySkel.hpRange[1] -
                                 enemySkel.hpRange[0]));
    int stats[5][2] = {
        {hp, false},
        {999, true},
        {999, false},
        {999, false},
    };
    return initEntity(
        enemySkel.name,
        stats,
        enemySkel.cardDeck,
        enemySkel.diffCardSize);
}

entity_t *importEnemyPhase1FromId(ENEMY_PHASE_1_ID id)
{
    return importEnemy(ENEMY_PHASE_1_ENCYCLOPEDIA[id]);
}

entity_t *getRandomEnemyPhase1()
{
    return importEnemyPhase1FromId(rand() % ENEMY_PHASE_1_ID_SIZE);
}

entity_t *importEnemyPhase2FromId(ENEMY_PHASE_2_ID id)
{
    return importEnemy(ENEMY_PHASE_2_ENCYCLOPEDIA[id]);
}

entity_t *getRandomEnemyPhase2()
{
    return importEnemyPhase2FromId(rand() % ENEMY_PHASE_2_ID_SIZE);
}

entity_t *importMiniBossFromId(MINIBOSS_ID id)
{
    return importEnemy(MINIBOSS_ENCYCLOPEDIA[id]);
}

entity_t *getRandomMiniBoss()
{
    return importMiniBossFromId(rand() % MINIBOSS_ID_SIZE);
}

entity_t *importBOSSFromId(BOSS_ID id)
{
    return importEnemy(BOSS_ENCYCLOPEDIA[id]);
}

// DISPLAY FUNCTION

void displayEntity(entity_t *entity)
{
    printf("\nNAME:\n_____\n%s\n", entity->name);
    printf("\nSTATS: \n______\n");
    for (size_t stats_ID = 0; stats_ID < 4; stats_ID++)
    {
        displayStat(entity->stats[stats_ID]);
    };
    printf("\nEFFECTS: \n________\n");
    for (size_t effects_ID = 0; effects_ID < 5; effects_ID++)
    {
        displayEffect(entity->effects[effects_ID]);
    };
    printf("\nDECK: \n_____\n");
    displayDeck(entity->cardDeck);

    printf("============================================\n");
}

// METHODS

void applyCardEffect(card_t *card, entity_t *launcher, entity_t *receiver)
{
    for (size_t launcherEffectID = 0; launcherEffectID < card->launcherEffectsSize; launcherEffectID++)
    {
        mergeEffect(launcher, card->launcherEffects[launcherEffectID]);
    }
    for (size_t receiverEffectID = 0; receiverEffectID < card->receiverEffectsSize; receiverEffectID++)
    {
        mergeEffect(receiver, card->receiverEffects[receiverEffectID]);
    }
}

// GETTER / SETTER

//      GETTER

stat_t *getStat(entity_t *entity, stat_ID statId)
{
    return &entity->stats[statId - 1];
}

effect_t *getEffect(entity_t *entity, effect_ID id)
{
    if (id < 3)
    {
        return NULL;
    }
    return &entity->effects[id - 4];
}

//      SETTER

void mergeEffect(entity_t *entity, effect_t effect)
{
    if (effect.id < 4)
    {
        stat_t *currentStat = getStat(entity, effect.id + 1);
        updateStat(currentStat, effect.value, CURR, PERCISTANT);
    }
    else
    {
        effect_t *currentEffect = getEffect(entity, effect.id);
        currentEffect->value += effect.value;
    }
}

// TEST

void testGetterSetter(entity_t *testCar)
{
    // GETTER TESTS

    printf("TEST GETTER/SETTER\n==================\n");
    printf("TEST getStat\n____________");
    stat_t *testStatGetter = getStat(testCar, DODGE);
    displayStat(*testStatGetter);

    printf("TEST getEffect\n______________");
    effect_t *testEffectGetter = getEffect(testCar, FIRE_E);
    displayEffect(*testEffectGetter);

    effect_t *testEffect = initEffect(STR_E, 10);
    mergeEffect(testCar, *testEffect);
}

void testApplyCardEffect(entity_t *testCar, entity_t *testEnemy)
{
    printf("\nTEST applyCard\n==============");

    card_t *test = createCard(
        "Strike",
        BASIC,
        0,
        1,
        false,
        (int[][2]){{STR_E, 6}, {DODGE_E, 10}},
        2,
        (int[][2]){{HP_E, -6}},
        1,
        "Inflige 6 dégats",
        "Attaque de base");
    displayEntity(testCar);
    displayEntity(testEnemy);
    applyCardEffect(test, testCar, testEnemy);
    printf("\napply effect\n");
    displayEntity(testCar);
    displayEntity(testEnemy);
}

void testEntity()
{
    // entity_t *testCar = initEntity("peter", testStat, (int[][2]){{DODGE_A, 1}, {PULVERIZE, 2}, {DEFENSE, 3}}, 3);
    entity_t *testEnemy = getRandomMiniBoss();
    displayEntity(testEnemy);

    // testGetterSetter(testCar);
    // testApplyCardEffect(testCar, testEnemy);
}

entity_import CARATER_ENCYCLOPEDIA[] = {
    {
        .name = "Peter",
        .stats = {
            {75, false},
            {999, true},
            {3, true},
            {100, true},
        },
        .cardDeck = {
            {STRIKE, 5},
            {DODGE_A, 5},
            {SPECTRUM, 1},
        },
        .diffCardSize = 3,
    },
};
enemy_import ENEMY_PHASE_1_ENCYCLOPEDIA[] = {
    {
        .name = "Jawurm",
        .hpRange = {40, 44},
        .cardDeck = {
            {JAWURM_BACKSTAB, 1},
            {JAWURM_FIST, 1},
            {JAWURM_CROUCH, 1},
        },
        .diffCardSize = 3,
    },
    {
        .name = "Blouni",
        .hpRange = {46, 50},
        .cardDeck = {
            {BLOUNI_JAB, 1},
            {BLOUNI_KICK, 1},
        },
        .diffCardSize = 2,
    },
    {
        .name = "Keliko",
        .hpRange = {60, 70},
        .cardDeck = {
            {KELIKO_NUDGE, 1},
            {KELIKO_PINCH, 1},
        },
        .diffCardSize = 2,
    },
};
enemy_import ENEMY_PHASE_2_ENCYCLOPEDIA[] = {
    {
        .name = "Jawurm2",
        .hpRange = {55, 62},
        .cardDeck = {
            {JAWURM2_HAIRPULLING, 1},
            {JAWURM2_SPIT, 1},
        },
        .diffCardSize = 2,
    },
    {
        .name = "Redoni",
        .hpRange = {50, 54},
        .cardDeck = {
            {REDONI_SLAP, 1},
            {REDONI_SPANKING, 1},
        },
        .diffCardSize = 2,
    },
    {
        .name = "Mangoustine",
        .hpRange = {70, 80},
        .cardDeck = {
            {MANGOUSTINE_SNARE, 1},
        },
        .diffCardSize = 1,
    },
};
enemy_import MINIBOSS_ENCYCLOPEDIA[] = {
    {
        .name = "Eldan",
        .hpRange = {80, 81},
        .cardDeck = {
            {ELDAN_BANANAPEEL, 1},
            {HEADBUTT, 1},
            {ELDAN_TOTAL, 1},
        },
        .diffCardSize = 3,
    },
    {
        .name = "Pyrox",
        .hpRange = {120, 121},
        .cardDeck = {
            {PYROX_FIRESPIT, 1},
            {PYROX_FIRESTORM, 1},
        },
        .diffCardSize = 2,
    },
};
enemy_import BOSS_ENCYCLOPEDIA[] = {
    {
        .name = "Gardien de la plume",
        .hpRange = {150, 151},
        .cardDeck = {
            {SPECTRUM, 1},
            {PULVERIZE, 1},
            {CLAW_COMBO, 1},
            {SLEEP, 1},
        },
        .diffCardSize = 4,
    },
};
