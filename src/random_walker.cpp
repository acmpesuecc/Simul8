#include <raylib.h>

class Walker{

private:
        int x,y;
        int xChanged, yChanged;
        int increased, decreased;

public:

        Walker(int width,int height){
            x = width/2;
            y = height/2;
            xChanged = 0;
            yChanged = 0;
            increased = 0;
            decreased = 0;
        }

        void render(){
            Color currentPixel = WHITE;
            Color prevOnePixel = {255, 255, 255, 215};
            Color prevTwoPixel = {255, 255, 255, 175};
            Color prevThreePixel = {255, 255, 255, 135};
            Color prevFourPixel = {255, 255, 255, 95};
            Color prevFivePixel = {255, 255, 255, 55};
            Color prevSixPixel = {255, 255, 255, 15};

            DrawPixel(x, y, currentPixel); // to color the current pixel solid white
            
            // if x coord changes, create a fading white trail in a direction depending on
            // whether x increased or decreased
            if(xChanged) {
                if(increased) {
                    DrawPixel(x - 1, y, prevOnePixel);
                    DrawPixel(x - 2, y, prevTwoPixel);
                    DrawPixel(x - 3, y, prevThreePixel);
                    DrawPixel(x - 4, y, prevFourPixel);
                    DrawPixel(x - 5, y, prevFivePixel);
                    DrawPixel(x - 6, y, prevSixPixel);
                    increased = 0;
                }
                else if(decreased) {
                    DrawPixel(x + 1, y, prevOnePixel);
                    DrawPixel(x + 2, y, prevTwoPixel);
                    DrawPixel(x + 3, y, prevThreePixel);
                    DrawPixel(x + 4, y, prevFourPixel);
                    DrawPixel(x + 5, y, prevFivePixel);
                    DrawPixel(x + 6, y, prevSixPixel);
                    decreased = 0;
                }
                xChanged = 0;
            }
            // if y coord changes, create a fading white trail in a direction depending on
            // whether y increased or decreased
            else if(yChanged) {
                if(increased) {
                    DrawPixel(x, y - 1, prevOnePixel);
                    DrawPixel(x, y - 2, prevTwoPixel);
                    DrawPixel(x, y - 3, prevThreePixel);
                    DrawPixel(x, y - 4, prevFourPixel);
                    DrawPixel(x, y - 5, prevFivePixel);
                    DrawPixel(x, y - 6, prevSixPixel);
                    increased = 0;
                }
                else if(decreased) {
                    DrawPixel(x, y + 1, prevOnePixel);
                    DrawPixel(x, y + 2, prevTwoPixel);
                    DrawPixel(x, y + 3, prevThreePixel);
                    DrawPixel(x, y + 4, prevFourPixel);
                    DrawPixel(x, y + 5, prevFivePixel);
                    DrawPixel(x, y + 6, prevSixPixel);
                    decreased = 0;
                }
                yChanged = 0;
            }
        }

        void step(){
            int choice = GetRandomValue(0,3);
            
            if(choice == 0){
                x++;
                xChanged = 1;
                increased = 1;
            }
            else if (choice == 1){
                x--;
                xChanged = 1;
                decreased = 1;
            }
            else if (choice == 2){
                y++;
                yChanged = 1;
                increased = 1;
            }
            else{
                y--;
                yChanged = 1;
                decreased = 1;
            }
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




