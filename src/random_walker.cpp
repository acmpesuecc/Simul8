#include <raylib.h>
#include <vector>

struct trailInfo {
    int x, y;
    float opacity; // store previous positions' opacity
};

class Walker {
private:
    int x, y;
    std::vector<trailInfo> trail;
    int maxTrailLen = 4; // setting the max trail length

public:
    Walker(int width, int height) {
        x = width / 2;
        y = height / 2;
    }

    void render() {
        DrawPixel(x, y, WHITE);

        // draw the white fading trail
        for (auto& segment : trail) {
            Color trailColor = {255, 255, 255, (unsigned char)segment.opacity};
            DrawPixel(segment.x, segment.y, trailColor);
        }
    }

    void step() {
        // current position has full opacity
        trail.push_back({x, y, 255.0f});

        // remove the oldest segment to limit the trail size
        if (trail.size() > maxTrailLen) trail.erase(trail.begin());

        // reduce opacity over time
        for (auto& segment : trail) {
            segment.opacity -= 40.0f;
            if (segment.opacity < 0.0f) segment.opacity = 0.0f;
        }

        int choice = GetRandomValue(0, 3);

        if (choice == 0){
            x++;
        }
        else if (choice == 1){
            x--;
        }
        else if (choice == 2){
            y++;
        }
        else{ 
            y--;
        }
    }
};

int main(void) {
    const int width = 800;
    const int height = 600;
    InitWindow(width, height, "Random Walker with Fading Trail");
    SetTargetFPS(60);

    Walker w(width, height);

    while (!WindowShouldClose()) {
        w.step();
        BeginDrawing();
        ClearBackground(BLACK); // clear the screen each frame
        w.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;



}




