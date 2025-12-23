#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point (C++ conversion)
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 800;

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



        //player
        DrawCircle(screenWidth / 2, screenHeight / 2, 20, BLACK);
        DrawRectangle(0, screenHeight / 2 - 60, 30, 120, BLACK);
        DrawRectangle(screenWidth - 35, screenHeight / 2 - 60, 30, 120, BLACK);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
