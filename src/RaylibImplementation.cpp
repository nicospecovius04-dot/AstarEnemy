#include "RaylibImplementation.hpp"
#include "AstarAlgorithm.hpp"
#include "Grid.hpp"
#include "raylib.h"

RaylibImplementation::RaylibImplementation(Grid& grid, AstarAlgorithm& astar) : grid_(grid), astar_(astar) {}

/*void RaylibImplementation::DrawGrid() {

  while(!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    BeginDrawing();

  for( auto collum{0uz}; collum < grid_.GetCollums(); collum++){
    for(auto row {0uz}; row < grid_[collum].GetRows(); row++) {

      Color color {GRAY};

      if((collum + row) % 2) {
        color = BLACK;
      }
      DrawRectangle(collum * grid_[collum][row].pixelSize_, row * grid_[collum][row].pixelSize_, grid_[collum][row].pixelSize_, grid_[collum][row].pixelSize_, color);
    }
  }
    EndDrawing();
  }
  CloseWindow();
}*/

void RaylibImplementation::DrawAstar() {
  for (auto collum {0uz}; collum < grid_.GetCollums(); collum++) {
    for (auto row {0uz}; row < grid_[collum].GetRows(); row++) {
      Node& current = grid_[collum][row];

      Color color {LIGHTGRAY};
      if (showDebug_) {
        if (current.isOpen_)   { color = YELLOW; }
        if (current.isClosed_) { color = SKYBLUE; }
      }
      if (current.isWall_) { color = DARKGRAY; }

      DrawRectangle(collum * current.pixelSize_, row * current.pixelSize_,
                    current.pixelSize_, current.pixelSize_, color);
    }
  }

  if (showDebug_) {
    for (auto node : astar_.GetFinalPath()) {
      DrawRectangle(node->x_ * node->pixelSize_, node->y_ * node->pixelSize_,
                    node->pixelSize_, node->pixelSize_, LIME);
    }
  }
}
