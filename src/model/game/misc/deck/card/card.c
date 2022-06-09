#include "card.h"
#include "../../../entity/entity.h"
#include <stdlib.h>
#include <stdio.h>

// CONSTRUCTOR

card_t *createCard(
    char *name,
    enum rarityE rarity,
    int manaCost,
    int energyCost,
    boolean isAbyssal,
    int launcherEffects[][2],
    size_t launcherEffectsSize,
    int receiverEffects[][2],
    size_t receiverEffectsSize,
    char *technic,
    char *description)
{
    card_t *res = malloc(sizeof(card_t));
    res->name = name;
    res->rarity = rarity;
    res->manaCost = manaCost;
    res->energyCost = energyCost;
    res->isAbyssal = isAbyssal;
    res->launcherEffects = initEffectFromArray(launcherEffects, launcherEffectsSize);
    res->launcherEffectsSize = launcherEffectsSize;
    res->receiverEffects = initEffectFromArray(receiverEffects, receiverEffectsSize);
    res->receiverEffectsSize = receiverEffectsSize;
    res->technic = technic;
    res->description = description;
    return res;
}

card_t *importCard(card_import cardImport)
{
    return createCard(
        cardImport.name,
        cardImport.rarity,
        cardImport.manaCost,
        cardImport.energyCost,
        cardImport.isAbyssal,
        cardImport.launcherEffects,
        cardImport.launcherEffectsSize,
        cardImport.receiverEffects,
        cardImport.receiverEffectsSize,
        cardImport.technic,
        cardImport.description);
}

card_t *importCardFromId(CARD_ENCYCLOPEDIA_ID cardId)
{
    return importCard(CARD_ENCYCLOPEDIA[cardId]);
}

// DISPLAY FUNCTION

void displayCard(card_t card)
{
    printf("\nNAME:\n_____\n%s\n\nLAUNCHER EFFECT:\n________________\n", card.name);
    for (size_t launcherEffectID = 0; launcherEffectID < card.launcherEffectsSize; launcherEffectID++)
    {
        displayEffect(card.launcherEffects[launcherEffectID]);
    }
    printf("\nRECEIVER EFFECT:\n________________\n");
    for (size_t receiverEffectID = 0; receiverEffectID < card.receiverEffectsSize; receiverEffectID++)
    {
        displayEffect(card.receiverEffects[receiverEffectID]);
    }
}

// TEST FUNCTION

void testCard()
{
    // card_t *test = createCard(
    //     "Strike",
    //     BASIC,
    //     0,
    //     1,
    //     false,
    //     (int[][2]){{STR_E, 6}, {DODGE_E, 10}},
    //     2,
    //     (int[][2]){{HP_E, -6}},
    //     1,
    //     "Inflige 6 dégats",
    //     "Attaque de base");
    card_t *test = importCardFromId(ACCELERATION);
    displayCard(*test);
}

card_import CARD_ENCYCLOPEDIA[] = {
    {
        .name = "Strike",
        .rarity = BASIC,
        .manaCost = 0,
        .energyCost = 1,
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -6}},
        .receiverEffectsSize = 1,
        .technic = "Inflige 6 dégâts",
        .description = "Attaque de base",
    },
    {
        .name = "Dodge",
        .rarity = BASIC,
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 5}},
        .launcherEffectsSize = 1,
        .receiverEffectsSize = 0,
        .energyCost = 1,
        .manaCost = 0,
        .technic = "Donne 5 points d'equive",
        .description = "L'esquive de base",
    },
    {
        .name = "Double strike",
        .rarity = COMMON,
        .description = "Démultiplicateur de force",
        .energyCost = 1,
        .manaCost = 0,
        .technic = "Attaque deux fois pour 4 dégâts",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -4}, {HP_E, -4}},
        .receiverEffectsSize = 2,
    },
    {
        .name = "Boule de feu",
        .rarity = COMMON,
        .description = "Un classique des mages débutants",
        .energyCost = 0,
        .manaCost = 20,
        .technic = "Inflige 6 points de feu",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{FIRE_E, 6}},
        .receiverEffectsSize = 1,
    },
    {
        .name = "Coup affaiblissant",
        .rarity = COMMON,
        .description = "Permet d'attaquer tout en se défendant",
        .energyCost = 2,
        .manaCost = 0,
        .technic = "Inflige 3 dégâts et rends l'ennemi faible pour 2 tours",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{WEAK_E, 2}, {HP_E, -3}},
        .receiverEffectsSize = 2,
    },
    {
        .name = "Acceleration",
        .rarity = COMMON,
        .description = "Ne ralenti pas exactement les adversaires ; tout est question de perception.",
        .energyCost = 1,
        .manaCost = 10,
        .technic = "Inflige Lent pour un tour et donne 4 points d'esquive",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{SLOW_E, 1}, {DODGE_E, 4}},
        .receiverEffectsSize = 2,
    },
    {
        .name = "Surménage",
        .rarity = ATYPIC,
        .description = "Permet de frapper plus fort, mais attention aux courbatures!",
        .energyCost = 1,
        .manaCost = 20,
        .technic = "Augmente les dégâts de 2, mais vous inflige 5 dégâts",
        .isAbyssal = false,
        .launcherEffects = {{STR_E, 2}, {HP_E, -5}},
        .launcherEffectsSize = 2,
        .receiverEffectsSize = 0,
    },
    {
        .name = "Posture défensive",
        .rarity = ATYPIC,
        .description = " Permet de mieux esquiver, mais faire durer les combats plus longtemps",
        .energyCost = 0,
        .manaCost = 0,
        .technic = "Dextérité +2, mais Force -1",
        .isAbyssal = false,
        .launcherEffects = {{DEX_E, 2}, {STR_E, -1}},
        .launcherEffectsSize = 2,
        .receiverEffectsSize = 0,
    },
    {
        .name = "Concentration",
        .rarity = ATYPIC,
        .description = ": Important si les combats durent longtemps",
        .energyCost = 3,
        .manaCost = 0,
        .technic = "Recharge 50 points de mana",
        .isAbyssal = false,
        .launcherEffects = {{MANA_E, 50}},
        .launcherEffectsSize = 1,
        .receiverEffectsSize = 0,
    },
    {
        .name = "Incendie",
        .rarity = ATYPIC,
        .description = "Aidera à terminer les combats, d’une manière ou l’autre",
        .energyCost = 2,
        .manaCost = 20,
        .technic = "Inflige 10 de feu à l’adversaire et 5 de feu à soi",
        .isAbyssal = false,
        .launcherEffects = {{FIRE_E, 5}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{FIRE_E, 10}},
        .receiverEffectsSize = 1,
    },
    {
        .name = "Pulvériser",
        .rarity = RARE,
        .description = "Blam ",
        .energyCost = 3,
        .manaCost = 0,
        .technic = "Inflige 30 dégâts, Abyssal",
        .isAbyssal = true,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -30}},
        .receiverEffectsSize = 1,
    },
    {
        .name = "Spectre complet",
        .rarity = RARE,
        .description = "Un bonus pour chaque couleur de l’arc-en-ciel.",
        .energyCost = 2,
        .manaCost = 20,
        .technic = "Donne différents bonus. Abyssal.",
        .isAbyssal = false,
        .launcherEffects = {{STR_E, 1}, {DEX_E, 1}, {DODGE_E, 5}},
        .launcherEffectsSize = 3,
        .receiverEffects = {{HP_E, -6}, {FIRE_E, 3}, {SLOW_E, 1}, {WEAK_E, 1}},
        .receiverEffectsSize = 4,
    },
    {
        // 11 dégats
        .name = "Tape dans le dos",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Ca surprend !",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -11}},
        .receiverEffectsSize = 1,
    },
    {
        // 7 dégats
        .name = "Coup de poing",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Un autre classique",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -7}},
        .receiverEffectsSize = 1,
    },
    {
        // force+3, 6 points d'esquive
        .name = "Accroupissement",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Rien de mieux pour reprendre son élan",
        .isAbyssal = false,
        .launcherEffects = {{STR_E, 3}, {DODGE_E, 6}},
        .launcherEffectsSize = 2,
        .receiverEffectsSize = 0,
    },
    {
        // 13 dégâts
        .name = "Coup de pied",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Bien placé, il peut faire très mal",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -13}},
        .receiverEffectsSize = 1,
    },
    {
        // 8 dégâts
        .name = "Jab",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Un classique",
        .isAbyssal = false,
        .launcherEffects = {{WEAK_E, 2}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{HP_E, -6}},
        .receiverEffectsSize = 1,
    },
    {
        // 3 dégâts, 3 points d'esquive,force +2
        .name = "Coup de coude",
        .energyCost = 0,
        .manaCost = 0,
        .description = "De quoi refaire sa dentition..",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 3}, {STR_E, 2}},
        .launcherEffectsSize = 2,
        .receiverEffects = {{HP_E, -3}},
        .receiverEffectsSize = 1,
    },
    {
        // : 3 dégâts, 3 points d’esquive, dextérité +2
        .name = "Pincement",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Bah ?",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 3}, {DEX_E, 2}},
        .launcherEffectsSize = 2,
        .receiverEffects = {{HP_E, -3}},
        .receiverEffectsSize = 1,
    },
    {
        // 15 dégats
        .name = "Coup de boule",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Aie mon crâne",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -15}},
        .receiverEffectsSize = 1,
    },
    {
        // 12 dégats,10 points d'esquive
        .name = "Tirage de cheveux",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Un pas de plus pour la calvitie..",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 10}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{HP_E, -12}},
        .receiverEffectsSize = 1,
    },
    {
        // +3 force, 18 points d'esquive
        .name = "Crachat",
        .energyCost = 0,
        .manaCost = 0,
        .description = "On te manque de respect",
        .isAbyssal = false,
        .launcherEffects = {{STR_E, 3}, {DODGE_E, 18}},
        .launcherEffectsSize = 2,
        .receiverEffectsSize = 0,
    },
    {
        // 20 dégâts
        .name = "fessée",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Tu n'as pas été sage...",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -20}},
        .receiverEffectsSize = 1,
    },
    {
        // 15 degâts, 2 tours de faiblesse sur Peter
        .name = "Gifle",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Clac",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -15}, {WEAK_E, 2}},
        .receiverEffectsSize = 2,
    },
    {
        //  3 dégâts, 3 points d’esquive, force +2 sur lui, dextérité +2 sur lui (
        .name = "Ricannement",
        .energyCost = 0,
        .manaCost = 0,
        .description = "On se moque de toi..",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 3}, {STR_E, 2}, {DEX_E, 2}},
        .launcherEffectsSize = 3,
        .receiverEffects = {{HP_E, -3}},
        .receiverEffectsSize = 1,
    },
    {
        // : 10 dégâts, 15 points d’esquive
        .name = "Banana FLIP !",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Attention à la peau de banane",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 15}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{HP_E, -10}},
        .receiverEffectsSize = 1,
    },
    {
        // Feu 5, 10 points d’esquive
        .name = "Crachat de feu",
        .energyCost = 0,
        .manaCost = 0,
        .description = "On te crache du feu dessus",
        .isAbyssal = false,
        .launcherEffects = {{DODGE_E, 10}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{FIRE_E, 5}},
        .receiverEffectsSize = 1,
    },
    {
        // Feu 10, dextérité +2 (bonus de dextérité pour lui)
        .name = "Tempête de feu",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Une tempête de feu s'abat sur toi",
        .isAbyssal = false,
        .launcherEffects = {{DEX_E, 2}},
        .launcherEffectsSize = 1,
        .receiverEffects = {{FIRE_E, 10}},
        .receiverEffectsSize = 1,
    },
    {
        .name = "Dors..",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Le boss s'endort",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffectsSize = 0,
    },
    {
        //: Dégâts (4), Dégâts (4), Dégâts (4), Dégâts (4), Dégâts (4)
        .name = "Combo griffe",
        .energyCost = 0,
        .manaCost = 0,
        .description = "Le boss te rafale ta mère",
        .isAbyssal = false,
        .launcherEffectsSize = 0,
        .receiverEffects = {{HP_E, -4}, {HP_E, -4}, {HP_E, -4}, {HP_E, -4}, {HP_E, -4}},
        .receiverEffectsSize = 5,
    },
};
