#ifndef EFFECT
#define EFFECT

#include <stdlib.h>

typedef enum
{
    HP_E,
    DODGE_E,
    MANA_E,
    ENERGY_E,
    STR_E,
    DEX_E,
    FIRE_E,
    WEAK_E,
    SLOW_E,
} effect_ID;

typedef struct
{
    effect_ID id;
    int value;
} effect_t;

// CONSTRUCTOR
effect_t *initEffect(effect_ID id, int value);
effect_t *initEffectBar();
effect_t *initEffectFromArray(int effects[][2], size_t size);

// DISPLAY FUNCTION
void displayEffect(effect_t effect);

// TEST FUNCTION
void testEffect();

#endif