#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point (C++ conversion)
//------------------------------------------------------------------------------------

Color Blue = Color{0,0,255, 255};
Color Dark_Blue = Color{0,0,139, 255};

Color Light_Blue = Color{173,216,230,255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int cpu_score = 0;

//ball class
class Ball{
    public:
    float x, y;
    int speed_x, speed_y;
    int radius;
     
    void Draw(){
        //ball
        DrawCircle(x,y,radius,Yellow);
    }
    
    void Update(){
        
        x += speed_x;
        y += speed_y;

        //Ball collision
        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }

        //scoreing
        if(x + radius >= GetScreenWidth()){ //cpu wins
           cpu_score++;
           ResetBall();
        }
        if(x -radius <= 0){
            player_score++;
            ResetBall();
        }
    }
    
    //Resets the ball to the center after scoreing
    void ResetBall(){
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[2] = {-1,1};

        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }
};

//paddle class
class Paddle{
    protected:
    //limits the movement when the paddle hits the edge of the screen
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
        //rounds the edges of the rectangle
        DrawRectangleRounded(Rectangle{x,y, width, height}, 0.8, 0, WHITE);

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



        ClearBackground(Dark_Blue);
        DrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight, Blue);
        DrawCircle(screenWidth/2, screenHeight/2, 150, Light_Blue);
    
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, BLACK);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i",cpu_score), screenWidth/4 - 20, 20,80,BLACK);
        DrawText(TextFormat("%i",player_score), 3*screenWidth/4 - 20, 20,80,BLACK);
        

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
