#ifndef GUI_COMBAT
#define GUI_COMBAT

#include "./../../../include/raylib.h"
#include "./../../model/game/combat/combat.h"
#include "./../../model/game/misc/effect/effect.h"
#include "./../utils/utils.h"

// Tableau contenant les noms des effets :
extern char *EFFECT_NAME[13];

void drawStatBoard();
void drawEffect(effect_t *effect, Vector2 position, float scaleFactor, boolean alignLeft, int forcedState);
int GuiCardHand(card_t *card, Vector2 position, float scaleFactor, int forcedState);
void InitCombatScreen(void);
void UpdateCombatScreen(void);
void DrawCombatScreen(void);
void UnloadCombatScreen(void);
int FinishCombatScreen(void);

#endif