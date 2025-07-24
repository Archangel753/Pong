#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    // Ball
    Vector2 ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 10;

    // Paddles
    Rectangle player = { 20, screenHeight / 2.0f - 50, 10, 100 };
    Rectangle enemy = { screenWidth - 30, screenHeight / 2.0f - 50, 10, 100 };
    float paddleSpeed = 5.0f;

    // Scores
    int playerScore = 0;
    int enemyScore = 0;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyDown(KEY_W)) player.y -= paddleSpeed;
        if (IsKeyDown(KEY_S)) player.y += paddleSpeed;

        // Player AI
        //if (player.y + player.height / 2 < ballPos.y) player.y += paddleSpeed;
        //if (player.y + player.height / 2 > ballPos.y) player.y -= paddleSpeed;

        // Enemy AI
        if (enemy.y + enemy.height / 2 < ballPos.y) enemy.y += paddleSpeed;
        if (enemy.y + enemy.height / 2 > ballPos.y) enemy.y -= paddleSpeed;

        // Ball Movement
        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;

        // Wall Collision
        if (ballPos.y - ballRadius <= 0 || ballPos.y + ballRadius >= screenHeight)
            ballSpeed.y *= -1;

        // Paddle Collision
        if (CheckCollisionCircleRec(ballPos, ballRadius, player) ||
            CheckCollisionCircleRec(ballPos, ballRadius, enemy)) {
            ballSpeed.x *= -1.1f; // Bounce and increase speed
        }

        // Scoring
        if (ballPos.x < 0) {
            enemyScore++;
            ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { 5.0f, 4.0f };
        }
        if (ballPos.x > screenWidth) {
            playerScore++;
            ballPos = { screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = { -5.0f, -4.0f };
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(TextFormat("%d", playerScore), screenWidth / 4, 20, 40, WHITE);
        DrawText(TextFormat("%d", enemyScore), screenWidth * 3 / 4, 20, 40, WHITE);

        DrawCircleV(ballPos, ballRadius, WHITE);
        DrawRectangleRec(player, WHITE);
        DrawRectangleRec(enemy, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
