#include "./../../../include/raylib.h"
#include "credits.h"
#include "./../utils/utils.h"
#include <stdio.h>

#define TAB_SIZE 4*2

static float creditsScrollingPosY = 0;
static Texture2D raylibLogo;

void InitCreditsScreen(void)
{
    printf("Credits Screen Init\n");

    creditsScrollingPosY = (float)GetScreenHeight() + 20.0f;
    raylibLogo = LoadTexture("./asset/Misc/raylib_logo.png");
    
}
void UpdateCreditsScreen(void)
{
    creditsScrollingPosY -= 1.5f;
    if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_DOWN))
    {
        creditsScrollingPosY -= 3.0f;
    }
    if (creditsScrollingPosY < (-GetScreenHeight() -400)) creditsScrollingPosY = -GetScreenHeight() - 400;
    
}
void DrawCreditsScreen(void)
{
    float scaleBackground = (float)(GetScreenWidth() / (float)background.width);
    DrawTextureEx(background, (Vector2){0, 0}, 0, scaleBackground, WHITE);

    int fontSize = 50;

    char *creditsData[TAB_SIZE] = { "DESIGN DU JEU",
                        "Dutoit Hugo\nHautier Benjamin",
                        "DEVELOPPEMENT DU JEU",
                        "Corre Léonard\nMille Martin\nDutoit Hugo\nHautier Benjamin",
                        "CREATION D'ASSETS",
                        "Dutoit Hugo\nHautier Benjamin",
                        "MUSIQUE PAR",
                        "Dar Golan" };

    float padding = 40.0f; 
    float sizeQueue = 0.0f;
    Color color = GetColor(0x8a9696ff);
    for (int i = 0; i < TAB_SIZE-1; i+=2) {
        int factorPos = i != 0 ? i : 1;
        Vector2 sectionTitleSize = MeasureTextEx(font, creditsData[i], fontSize, 2);
        Vector2 sectionDataSize = MeasureTextEx(font, creditsData[i+1], fontSize, 2);
        sizeQueue += 20.0f;
        DrawTextEx(font, creditsData[i], (Vector2){ GetScreenWidth()/2 - sectionTitleSize.x/2, creditsScrollingPosY + sizeQueue }, fontSize, 2, color);
        sizeQueue += sectionTitleSize.y;
        DrawTextEx(font, creditsData[i+1], (Vector2){ GetScreenWidth()/2 - sectionDataSize.x/2, creditsScrollingPosY + sizeQueue }, fontSize, 2, WHITE);
        sizeQueue += sectionDataSize.y;
    }

    Vector2 sectionTitleSize = MeasureTextEx(font, "Crée avec", fontSize, 2);
    DrawTextEx(font, "Crée avec", (Vector2){ GetScreenWidth()/2 - sectionTitleSize.x/2, creditsScrollingPosY + sizeQueue + 20 }, fontSize, 2, color);
    sizeQueue += sectionTitleSize.y;
    DrawTexture(raylibLogo, GetScreenWidth()/2 - 64, creditsScrollingPosY + sizeQueue + 40, WHITE);

    int buttonWitdth = 200;
    int buttonHeight = 80;
    if (GuiButton((Rectangle){ GetScreenWidth() - (buttonWitdth+20), GetScreenHeight()-(buttonHeight+20), buttonWitdth, buttonHeight }, "RETOUR", -1)) TransitionToScreen(MENU);

}
void UnloadCreditsScreen(void)
{
    UnloadTexture(raylibLogo);
}
int FinishCreditsScreen(void) 
{
    return 0;
}