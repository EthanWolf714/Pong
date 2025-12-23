#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point (C++ conversion)
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    int playerPosition = screenHeight / 2 - 40;
    int moveSpeed = 10;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsKeyDown(KEY_UP))
        {
            playerPosition -= 2 * moveSpeed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            playerPosition += 2 * moveSpeed;
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(screenWidth / 2 - 40, playerPosition, 30, 150, BLACK);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
