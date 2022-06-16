#include "effect.h"
#include <stdlib.h>
#include <stdio.h>

// GLOBAL VARIABLES

char *const EFFECT_NAME[13] = {
    "VIE",
    "ESQUIVE",
    "MANA",
    "ENERGIE",
    "VIE MAX",
    "ESQUIVE MAX",
    "MANA MAX",
    "ENERGIE MAX",
    "FORCE",
    "DEXTERITE",
    "FEU",
    "FAIBLESSE",
    "LENTEUR",
};

// CONSTRUCTORS

effect_t *initEffect(effect_ID id, int value)
{
    effect_t *res = malloc(sizeof(effect_t));
    res->id = id;
    res->value = value;
    return res;
}

// effects : [[effectID, value]]
effect_t **initEffectFromArray(int size, int effects[size][2])
{
    effect_t **res = malloc(size * sizeof(effect_t *));
    for (int effects_ID = 0; effects_ID < size; effects_ID++)
    {
        res[effects_ID] = initEffect(effects[effects_ID][0], effects[effects_ID][1]);
    };
    return res;
}

// used in entity
effect_t **initEntityEffectArray()
{
    return initEffectFromArray(9, (int[9][2]){
                                      {HP_MAX_E, 0},
                                      {DODGE_MAX_E, 0},
                                      {MANA_MAX_E, 0},
                                      {ENERGY_MAX_E, 0},
                                      {STR_E, 0},
                                      {DEX_E, 0},
                                      {FIRE_E, 0},
                                      {WEAK_E, 0},
                                      {SLOW_E, 0},
                                  });
}

// DECONSTRUCTOR

void freeEffect(effect_t *effect)
{
    free(effect);
}

void freeEffectArray(effect_t **effectArray, int size)
{
    for (int effectIdx = 0; effectIdx < size; effectIdx++)
    {
        freeEffect(effectArray[effectIdx]);
    }
    free(effectArray);
}

void freeEntityEffectArray(effect_t **effectArray)
{
    freeEffectArray(effectArray, 9);
}

// DISPLAY FUNCTION

void displayEffect(effect_t *effect)
{
    printf(
        "\nnom: %s\nvaleur: %d\n",
        EFFECT_NAME[effect->id],
        effect->value);
}

void displayEffectArray(effect_t **effectArray, int size)
{
    for (int effectIdx = 0; effectIdx < size; effectIdx++)
    {
        displayEffect(effectArray[effectIdx]);
    }
}

void displayEntityEffectArray(effect_t **effectArray)
{
    displayEffectArray(effectArray, 9);
}

// TEST FUNCTION
void testEffect()
{
    printf("\n==============================\n\tTEST DE EFFECT\n==============================\n");
    effect_t **test = initEntityEffectArray();
    displayEntityEffectArray(test);
    freeEntityEffectArray(test);
}