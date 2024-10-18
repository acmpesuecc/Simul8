#include <raylib.h>

class Walker {
private:
    int x, y;
    int width, height;

public:
    Walker(int w, int h) : width(w), height(h) {
        reset();
    }

    void reset() {
        x = width / 2;
        y = height / 2;
    }

    void render() {
        DrawPixel(x, y, WHITE);
    }

    void step() {
        int choice = GetRandomValue(0, 3);
        
        if (choice == 0) {
            x++;
        } else if (choice == 1) {
            x--;
        } else if (choice == 2) {
            y++;
        } else {
            y--;
        }
    }
};

int main(void) {
    const int width = 800;
    const int height = 600;
    InitWindow(width, height, "Random walker :D");
    SetTargetFPS(60);
    
    Walker w(width, height);
    
    while (!WindowShouldClose()) {
        if (IsKey
