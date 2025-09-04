#include "body.h"
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
#include "quadtree/vector2.h"

using namespace std;

const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1200;
const int N = 20;
const double G = 6.67430e-1f; // scaled gravitational constant

struct Force {
    float fx;
    float fy;
};

void UpdateBruteForce(std::vector<Body> &bodies, double dt) {
    int bodyCount = bodies.size();
    std::vector<quadtree::PVector<double>> accelerations(bodyCount, {0, 0});

    for (int i = 0; i < bodyCount; i++) {
        quadtree::PVector<double> acc(0, 0);

        for (int j = 0; j < bodyCount; j++) {
            if (i == j)
                continue;

            auto diff = bodies[j].position - bodies[i].position;
            double r2 = diff.x * diff.x + diff.y * diff.y + 1e-2; // softening
            double invR = 1.0 / std::sqrt(r2);
            double invR3 = invR * invR * invR;

            acc += diff * (G * bodies[j].center_of_mass * invR3);
        }
        accelerations[i] = acc;
    }

    // integrate
    for (int i = 0; i < bodyCount; i++) {
        bodies[i].velocity += accelerations[i] * dt;
        bodies[i].position += bodies[i].velocity * dt;
    }
}

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "N-Body Problem");
    SetTargetFPS(60);

    std::srand(std::time(nullptr)); // Seed random generator

    // Create 1000 bodies
    std::vector<Body> bodies(N);

    for (size_t i = 0; i < bodies.size(); i++) {
        bodies[i].radius = std::rand() % 10 + 1; // radius 2..11
        bodies[i].position.x = bodies[i].radius + std::rand() % (SCREEN_WIDTH - (int)bodies[i].radius * 2);
        bodies[i].position.y = bodies[i].radius + std::rand() % (SCREEN_HEIGHT - (int)bodies[i].radius * 2);
        bodies[i].center_of_mass = bodies[i].radius;
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
        UpdateBruteForce(bodies, 1);
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Body &b : bodies) {
            DrawCircle((int)b.position.x, (int)b.position.y, b.radius, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}
