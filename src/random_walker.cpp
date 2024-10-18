#include <raylib.h>

class Walker{

private:
        int x,y;
        int width, height;

public:

       Walker(int windowWidth, int windowHeight) {
            width = windowWidth;
            height = windowHeight;
            x = width / 2;
            y = height / 2;
        }

        void render(){
            DrawPixel(x, y, WHITE);
        }

        void step(){
            int choice = GetRandomValue(0,3);
            
            if(choice == 0){
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

            if (x < 0) x = 0;
            if (x >= width) x = width - 1;
            if (y < 0) y = 0;
            if (y >= height) y = height - 1;

        }
        

        
};


int main(void){
    const int width = 800;
    const int height = 600;
    InitWindow(width, height, "Random walker :D");
    SetTargetFPS(60);
    
    Walker w(width,height);
    
    int i = 1;
    while(!WindowShouldClose()){
        w.step();
        BeginDrawing();
        w.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;


}




