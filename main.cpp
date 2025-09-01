#include "point.h"
#include <ctime> // for time()
#include <iostream>
#include <raylib.h>
#include <vector>
#include <ctime>    // for time()
#include<math.h>

#include <chrono>   // for timing


//BRUTE FORCE 50 seconds for 50,000 bodies 


using namespace std;

int main() {

    const int SCREEN_WIDTH = 1800;
    const int SCREEN_HEIGHT = 1200;
    const int N =10000;
    const float G = 6.67430e-1f; // scaled gravitational constant

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "N-Body Problem");
    SetTargetFPS(60);

    std::srand(std::time(nullptr)); // Seed random generator

    // Create 1000 bodies
    std::vector<Body> bodies(N);

    for (size_t i = 0; i < bodies.size(); i++) {
        bodies[i].radius = 5;              // radius 2..11
        bodies[i].x = bodies[i].radius + std::rand() % (SCREEN_WIDTH - (int)bodies[i].radius*2);
        bodies[i].y = bodies[i].radius + std::rand() % (SCREEN_HEIGHT - (int)bodies[i].radius*2);
        bodies[i].center_of_mass = 5;
    }

    // Start timer

    #define RUN_BRUTE_FORCE_METHOD
    #ifdef RUN_BRUTE_FORCE_METHOD
    auto start = chrono::high_resolution_clock::now();

           // Calculate forces
    for (int i = 0; i < N; i++) {
        float fx = 0, fy = 0;

        for (int j = 0; j < N; j++) {
            if (i == j) continue;

            float dx = bodies[j].x - bodies[i].x;
            float dy = bodies[j].y - bodies[i].y;
            float distSqr = dx*dx + dy*dy + 1e-5f; // prevent division by zero
            float dist = sqrt(distSqr);
            float force = G * bodies[i].center_of_mass * bodies[j].center_of_mass/ distSqr;

            fx += force * dx / dist; // x-component
            fy += force * dy / dist; // y-component
        }

        //cout << "Body " << i << ": Fx = " << fx << ", Fy = " << fy << endl;
    }

     // End timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Force calculation time for " << N 
         << " bodies: " << elapsed.count() << " seconds" << endl;
    return 0;
    #endif

   

    while (WindowShouldClose() == false){
   
   
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Body &b : bodies) {
            DrawCircle((int)b.x, (int)b.y, b.radius, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}
