#include "raylib.h"
#include <time.h>
#include <cstdlib>
#include <string>
#include <vector>

// Window Size

const int screenWidth = 800;
const int screenHeight = 450;

// Background Colour

const Color BACKGROUND_COLOUR = { 28, 28, 28, 255 };

// Bar Structure

struct Bar{
  Vector2 size;
  Vector2 position;
};

// Bubble Sort Class

class Bubble{
public:
  Bar arr[80];
  Bar store[2];

  unsigned int comparisons = 0;
  unsigned int swaps = 0;

  // Rearrange The arr For The Next Value

  bool next(){

    int arrSize = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < arrSize; i++){
      if (i >= arrSize-1) return true;

      comparisons++;

      if (arr[i].size.y > arr[i+1].size.y){
        store[0] = arr[i];
        store[1] = arr[i+1];

        arr[i] = store[1];
        arr[i+1] = store[0];

        swaps++;

        break;
      }

    }

    return false;

  }

};

int main(){

  // Randomise Numbers

  srand( time(NULL) );

  // Init Window

  InitWindow(screenWidth, screenHeight, "Window");
  SetTargetFPS(60);

  // Add Random Bars To Sorter

  Bubble sorter;
  bool sorted = false;

  for (int i = 0; i < 80; i++){
    Vector2 size = {(float)5, (float)(rand() % (1 + 450))};
    Vector2 pos = {0, (float)450-size.y};

    sorter.arr[i] = {size, pos};
  }

  // Main Program Loop

  while (!WindowShouldClose()){
    BeginDrawing();

    // Clear Background

    ClearBackground(BACKGROUND_COLOUR);

    // Draw Comparisons

    std::string cpp_swaps_string = std::to_string(sorter.swaps) + " Swaps - " + std::to_string(sorter.comparisons) + " Comparisons";
    char *cstr = &cpp_swaps_string[0];

    DrawText(cstr, 0, 0, 20, RAYWHITE);

    // Draw New Bars

    for (int i = 0; i < sizeof(sorter.arr)/sizeof(sorter.arr[0]); i++){
        DrawRectangleV(Vector2{(float)i*10, sorter.arr[i].position.y}, Vector2{sorter.arr[i].size.x, sorter.arr[i].size.y}, RAYWHITE);
    }

    // Check If arr Is Sorted

    if (!sorted){
      sorted = sorter.next();
    }

    else if (sorted){
      DrawText("Sorted!", (screenWidth/2)-60, 50, 40, RAYWHITE);
    }

    EndDrawing();

  }

  CloseWindow();

  return 0;
}
