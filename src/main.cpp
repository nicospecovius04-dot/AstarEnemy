#include "AstarAlgorithm.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Player.hpp"
#include "RaylibImplementation.hpp"
#include "raylib.h"

int main() {
  Grid grid {25, 25, 40};  // 25 * 40 = 1000 Pixel
  const char* level[25] = {
  "..#######################",
  "........................#",
  "#.#####.......#####.....#",
  "#.#...................#.#",
  "#.#...####...####.....#.#",
  "#.....#.........#.....#.#",
  "#.....#.........#.......#",
  "#...###.........###.....#",
  "#.......................#",
  "#.....##...###...##.....#",
  "#.......................#",
  "#...#...............#...#",
  "#...#......#.#......#...#",
  "#...#...............#...#",
  "#.......................#",
  "#.....##...###...##.....#",
  "#.......................#",
  "#...###.........###.....#",
  "#.....#.........#.......#",
  "#.....#.........#.....#.#",
  "#.#...####...####.....#.#",
  "#.#...................#.#",
  "#.#####.......#####.....#",
  "#.......................#",
  "#########################",
};

for (size_t y = 0; y < 25; y++) {
  for (size_t x = 0; x < 25; x++) {
    grid[x][y].isWall_ = (level[y][x] == '#');
  }
}

  Player player {grid, &grid[12][12]};
  Enemy enemy {grid, &grid[0][0]};
  AstarAlgorithm astar {grid};
  RaylibImplementation draw {grid, astar};

  InitWindow(1000, 1000, "A* Game");
  SetTargetFPS(60);

  Node* lastPlayerNode = nullptr;
  Node* lastEnemyNode = nullptr;

  while (!WindowShouldClose()) {
    player.Update();
    if (IsKeyPressed(KEY_P)) {
    draw.ToggleDebug();
}

    // Pfad nur neu berechnen, wenn sich ein Feld geändert hat
    Node* playerNode = player.GetPlayer();
    Node* enemyNode = enemy.GetEnemy();
    if (playerNode != lastPlayerNode || enemyNode != lastEnemyNode) {
      astar.Reset(enemyNode, playerNode);
      astar.Solve();
      lastPlayerNode = playerNode;
      lastEnemyNode = enemyNode;
    }

    const auto& path = astar.GetFinalPath();
    if (path.size() > 1) {
      enemy.MoveTowards(path[1]);
    }

    if (CheckCollisionCircles(player.GetPos(), 12, enemy.GetPos(), 12)) {
      break;  // später: Game-Over-Screen
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw.DrawAstar();
    DrawCircleV(player.GetPos(), 12, RED);
    DrawCircleV(enemy.GetPos(), 12, GREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}