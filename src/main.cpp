#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point (C++ conversion)
//------------------------------------------------------------------------------------


//ball class
class Ball{
    public:
    float x, y;
    int speed_x, speed_y;
    int radius;
     
    void Draw(){
        //ball
        DrawCircle(x,y,radius,BLACK);
    }
    
    void Update(){
        
        x += speed_x;
        y += speed_y;

        //Ball collision
        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth()){ //cpu wins
           // cpu_score++;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        }
    }
};

//paddle class
class Paddle{
    protected:
    void LimitMovement(){
        if(y <= 0){
            y = 0;

        }
        if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }
    public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, BLACK);

    }

    void Update(){
        //Player movement
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;

        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
};


class CpuPaddle: public Paddle{
    public:

    void Update(int ball_y){
        if(y + height / 2 > ball_y){
            y = y - speed;
        }
        if(y + height /  2 <= ball_y){
            y = y + speed;
        }
        LimitMovement();
    }
};


Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //set ball attributes
    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //Set player attributes
    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        

        // Draw
        BeginDrawing();

        //update ball 
        ball.Update();
        //Update Player
        player.Update();

        cpu.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }



        ClearBackground(RAYWHITE);

    
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, BLACK);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        
        

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
