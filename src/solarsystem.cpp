#include <raylib.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <rlgl.h>

using namespace std;

class Planet {
private:
    float radius;                  
    float distance;               
    float angle;                   
    float orbitSpeed;     
    vector<Planet> moons;
    Texture2D texture;  // Texture for the planet
    Color color;        // Color for the planet

public:
    Planet(float r, float d, float o, Texture2D tex, Color col) 
        : radius(r), distance(d), orbitSpeed(o), texture(tex), color(col) {
        angle = GetRandomValue(0, 2 * PI);
    }

    void orbit() {
        angle += orbitSpeed; 
        for (auto& moon : moons) {
            moon.orbit();
        }
    }

    void spawnMoons(int total, int level, Texture2D tex, vector<Color>& colors) {
        moons.reserve(total);
        for (int i = 0; i < total; i++) {
            float r = radius / (level * 2);
            float d = GetRandomValue(75, 200);   
            float o = static_cast<float>(rand()) / RAND_MAX * 0.2f - 0.1f; 
            Color moonColor = colors[GetRandomValue(0, colors.size() - 1)];
            moons.emplace_back(r, d / level, o, tex, moonColor); 

            if (level < 3) {
                int num = GetRandomValue(0, 4);
                moons.back().spawnMoons(num, level + 1, tex, colors);
            }
        }
    }

    void show(Vector2 center) {
        Vector2 pos = { center.x + distance * cos(angle), center.y + distance * sin(angle) };

        // Draw the texture if available, otherwise draw a colored circle
        if (texture.id > 0) {
            DrawTexture(texture, pos.x - radius, pos.y - radius, WHITE);  // Texture as the planet
        } else {
            DrawCircleV(pos, radius, color);  // Color if no texture
        }

        for (auto& moon : moons) {
            moon.show(pos);
        }
    }
};

int main(void) {
    const int width = 800;
    const int height = 600;
    const int numStars = 100;

    InitWindow(width, height, "My Solar System :D");

    // Load textures for planets
    Texture2D sunTexture = LoadTexture("sun.png");       // Texture for the sun
    Texture2D planetTexture = LoadTexture("earth.png");  // Placeholder texture for planets (you can load more if needed)

    // Create a list of stars with random positions
    vector<Vector2> stars;
    for (int i = 0; i < numStars; i++) {
        stars.push_back({ static_cast<float>(GetRandomValue(0, width)), static_cast<float>(GetRandomValue(0, height)) });
    }

    // Define colors for the planets
    vector<Color> planetColors = {RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW, PINK};

    // Create the solar system
    Planet sun(50, 0, 0, sunTexture, YELLOW);  // Sun with texture
    sun.spawnMoons(4, 1, planetTexture, planetColors);  // Spawn planets with different colors

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        sun.orbit(); 

        BeginDrawing();
        ClearBackground(BLACK);  // Black background

        // Draw the stars
        for (const auto& star : stars) {
            DrawCircleV(star, 1, WHITE);  // Small white dots for stars
        }

        // Draw the sun and planets
        sun.show({ width / 2, height / 2 });

        EndDrawing();
    }

    // Unload textures when finished
    UnloadTexture(sunTexture);
    UnloadTexture(planetTexture);

    CloseWindow();
    return 0;
}
