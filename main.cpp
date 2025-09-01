#include "point.h"
#include <ctime> // for time()
#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

int main() {

    const int SCREEN_WIDTH = 1800;
    const int SCREEN_HEIGHT = 1200;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "N-Body Problem");
    SetTargetFPS(60);

    std::srand(std::time(nullptr)); // Seed random generator

    // Create 1000 bodies
    std::vector<Body> bodies(1000);

    for (size_t i = 0; i < bodies.size(); i++) {
        bodies[i].radius = 5; // radius 2..11
        bodies[i].x = bodies[i].radius + std::rand() % (SCREEN_WIDTH - (int)bodies[i].radius * 2);
        bodies[i].y = bodies[i].radius + std::rand() % (SCREEN_HEIGHT - (int)bodies[i].radius * 2);
    }

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Body &b : bodies) {
            DrawCircle((int)b.x, (int)b.y, b.radius, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}
