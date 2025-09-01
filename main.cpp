#include "point.h"
#include "quadtree/quadtree.h"
#include <ctime>
#include <ctime> // for time()
#include <iostream>
#include <math.h>
#include <raylib.h>
#include <vector>

#include <chrono> // for timing

// BRUTE FORCE 50 seconds for 50,000 bodies

#include "quadtree/quadtree.h"

using namespace std;

const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1200;
const int N = 20;
const float G = 6.67430e-1f; // scaled gravitational constant

struct Force {
    float fx;
    float fy;
};

void UpdateBruteForce(std::vector<Body> &bodies) {
    auto start = chrono::high_resolution_clock::now();

    int bodyCount = bodies.size();
    std::vector<Force> forces(bodyCount, {0.0f, 0.0f});
    // Calculate forces
    for (int i = 0; i < bodyCount; i++) {
        float fx = 0, fy = 0;

        for (int j = 0; j < bodyCount; j++) {
            if (i == j)
                continue;

            float dx = bodies[j].x - bodies[i].x;
            float dy = bodies[j].y - bodies[i].y;
            float distSqr = dx * dx + dy * dy + 1e-1f; // prevent division by zero
            float dist = sqrt(distSqr);
            float force = G * bodies[i].center_of_mass * bodies[j].center_of_mass / distSqr;

            fx += force * dx / dist; // x-component
            fy += force * dy / dist; // y-component
        }

        forces[i].fx = fx;
        forces[i].fy = fy;
        // cout << "Body " << i << ": Fx = " << fx << ", Fy = " << fy << endl;
    }

    for (int i = 0; i < bodyCount; i++) {
        // Update positions based on forces (simple Euler integration)
        bodies[i].x += forces[i].fx / bodies[i].center_of_mass;
        bodies[i].y += forces[i].fy / bodies[i].center_of_mass;
    }

    // End timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // cout << "Force calculation time for " << N << " bodies: " << elapsed.count() << " seconds" << endl;
}

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "N-Body Problem");
    SetTargetFPS(60);

    std::srand(std::time(nullptr)); // Seed random generator

    // Create 1000 bodies
    std::vector<Body> bodies(N);

    for (size_t i = 0; i < bodies.size(); i++) {
        bodies[i].radius = std::rand() % 10 + 1; // radius 2..11
        bodies[i].x = bodies[i].radius + std::rand() % (SCREEN_WIDTH - (int)bodies[i].radius * 2);
        bodies[i].y = bodies[i].radius + std::rand() % (SCREEN_HEIGHT - (int)bodies[i].radius * 2);
        bodies[i].center_of_mass = bodies[i].radius * bodies[i].radius * 100;
    }

    // Start timer

// #define RUN_BRUTE_FORCE_METHOD
#ifdef RUN_BRUTE_FORCE_METHOD
    auto start = chrono::high_resolution_clock::now();

    // Calculate forces
    for (int i = 0; i < N; i++) {
        float fx = 0, fy = 0;

        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;

            float dx = bodies[j].x - bodies[i].x;
            float dy = bodies[j].y - bodies[i].y;
            float distSqr = dx * dx + dy * dy + 1e-5f; // prevent division by zero
            float dist = sqrt(distSqr);
            float force = G * bodies[i].center_of_mass * bodies[j].center_of_mass / distSqr;

            fx += force * dx / dist; // x-component
            fy += force * dy / dist; // y-component
        }

        // cout << "Body " << i << ": Fx = " << fx << ", Fy = " << fy << endl;
    }

    // End timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Force calculation time for " << N << " bodies: " << elapsed.count() << " seconds" << endl;
    return 0;
#endif

    while (WindowShouldClose() == false) {
        UpdateBruteForce(bodies);
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Body &b : bodies) {
            DrawCircle((int)b.x, (int)b.y, b.radius, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}
