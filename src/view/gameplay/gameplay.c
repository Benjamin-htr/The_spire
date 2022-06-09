#include "./../../../include/raylib.h"
#include "gameplay.h"
#include "./../utils/utils.h"

#include <stdio.h>

static int finishScreen = 0;

static Texture2D arrowButtonBack = {0};
static Texture2D arrow = {0};

static Sprite roomSprite = {0};

static int roomGapX = -200;

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
bool ArrowButton(Rectangle bounds, float rotation, int forcedState)
{
    NPatchInfo buttonArrowInfo = {0};

    int state = (forcedState >= 0)? forcedState : 0;                // NORMAL
    bool pressed = false;

    int arrowPosAdd = 0;

    // Update control
    //--------------------------------------------------------------------
    if ((state < 3) && (forcedState < 0))
    {
        Vector2 mousePoint = GetMousePosition();

        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            // PRESSED
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                state = 2;
                arrowPosAdd = 10;
            }    
            else state = 1;                                         // FOCUSED

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsGestureDetected(GESTURE_TAP))
            {
                pressed = true;
                PlaySound(buttonSound);
            }
        }
    }

    buttonArrowInfo.source = (Rectangle){0, 0, 66, arrowButtonBack.height},
    buttonArrowInfo.left = 30;
    buttonArrowInfo.top = 30;
    buttonArrowInfo.right = 30;
    buttonArrowInfo.bottom = 30;
    buttonArrowInfo.source.x = 66*state;

    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    //DrawRectangleRec(bounds, GREEN);
    //DrawRectangleLinesEx(bounds, 4, DARKGREEN);
    DrawTextureNPatch(arrowButtonBack, buttonArrowInfo, bounds, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);

    Vector2 posArrow = { 0 };
    //DrawTextEx(font, text, (Vector2){ bounds.x + bounds.width/2 - arrow.width/2, bounds.y + bounds.height/2 - arrow.height/2 - 4 + arrowPosAdd }, font.baseSize, 1, GetColor(textColor[state]));
    if(rotation == -180) posArrow = (Vector2){ bounds.x + bounds.width/2 + arrow.width/2, bounds.y + bounds.height/2 + arrow.height/2 - 4 + arrowPosAdd };
    else if (rotation == -90) posArrow = (Vector2){ bounds.x + bounds.width/2 - arrow.height/2, bounds.y + bounds.height/2 + arrow.width/2 - 6 + arrowPosAdd };
    else if (rotation == 90) posArrow = (Vector2){ bounds.x + bounds.width/2 + arrow.height/2, bounds.y + bounds.height/2 - arrow.width/2 - 6 + arrowPosAdd };
    else posArrow = (Vector2){ bounds.x + bounds.width/2 - arrow.width/2, bounds.y + bounds.height/2 - arrow.height/2 - 4 + arrowPosAdd };
    

    DrawTextureEx(arrow, posArrow, rotation, 1.0f, WHITE);
    //------------------------------------------------------------------

    return pressed;
}

//----------------------------------------------------------------------------------
// Screen functions :
//----------------------------------------------------------------------------------
void InitGameplayScreen(void)
{
    printf("Gameplay Screen Init\n");  

    arrow = LoadTexture("./asset/UI_assets/arrow.png");
    arrowButtonBack = LoadTexture("./asset/UI_assets/button-arrow.png");

    constructSprite(&roomSprite, "./asset/map/room_start.png", 3, 1, (Vector2){GetScreenWidth()/2-roomGapX, GetScreenHeight() / 2});
}
void UpdateGameplayScreen(void)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        showInGameMenu = !showInGameMenu;
    }

    updateSprite(&roomSprite);
}
void DrawGameplayScreen(void)
{
    ClearBackground(BLACK);

    Vector2 textSize = MeasureTextEx(font, "ETAGE 1", 20, 1);
    DrawTextEx(font, "ETAGE 1", (Vector2){GetScreenWidth()- (textSize.x+10), GetScreenHeight()-(textSize.y+10)}, 20, 1, LIGHTGRAY);

    float scaleFactor = 4.0f;
    //DrawTextureEx(arrowButton, (Vector2){GetScreenWidth() / 2 - arrowButton.width * scaleFactor / 2, GetScreenHeight() / 2 - arrowButton.height * scaleFactor / 2}, 0, scaleFactor, WHITE);

    scaleFactor = 1.2f;
    float roomWidth = (roomSprite.frameRec.width * scaleFactor);
    float roomHeight = (roomSprite.frameRec.height * scaleFactor);
    const Vector2 position = {GetScreenWidth() / 2 - roomWidth/2 +roomGapX, GetScreenHeight() / 2 - roomHeight / 2};
    drawSprite(&roomSprite, position, 0.0f, scaleFactor, WHITE);

    int arrowButtonWidth = 72;
    int padding = 4;
    if (ArrowButton((Rectangle){ GetScreenWidth()/2 + (roomWidth/ 2)+padding +roomGapX, GetScreenHeight()/2 - arrowButtonWidth/2, arrowButtonWidth, arrowButtonWidth }, 0, -1))
    {
        printf("ArrowButton RIGHT\n");
    }
    if (ArrowButton((Rectangle){ GetScreenWidth()/2 - (roomWidth/ 2)-arrowButtonWidth-padding +roomGapX, GetScreenHeight()/2 - arrowButtonWidth/2, arrowButtonWidth, arrowButtonWidth }, -180, -1))
    {
        printf("ArrowButton LEFT\n");
    }
    if (ArrowButton((Rectangle){ GetScreenWidth()/2 - arrowButtonWidth/2 +roomGapX, GetScreenHeight()/2 - (roomHeight/2)-arrowButtonWidth-padding, arrowButtonWidth, arrowButtonWidth }, -90, -1))
    {
        printf("ArrowButton TOP\n");
    }
    if (ArrowButton((Rectangle){ GetScreenWidth()/2 - arrowButtonWidth/2 +roomGapX, GetScreenHeight()/2 + (roomHeight/2)+padding, arrowButtonWidth, arrowButtonWidth }, 90, -1))
    {
        printf("ArrowButton BOTTOM\n");
    }



}
void UnloadGameplayScreen(void)
{
    UnloadTexture(arrow);
    UnloadTexture(arrowButtonBack);
    UnloadTexture(roomSprite.texture);
}
int FinishGameplayScreen(void)
{
    return finishScreen;
}
