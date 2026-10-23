#pragma once
#include "AstarAlgorithm.hpp"
#include "Grid.hpp"

class RaylibImplementation {
public:
  RaylibImplementation(Grid& grid, AstarAlgorithm& astar);
  ~RaylibImplementation() = default;
  RaylibImplementation(const RaylibImplementation& raylibImplementation) = delete;
  RaylibImplementation& operator=(const RaylibImplementation& raylibImplementation) = delete;
  RaylibImplementation(RaylibImplementation&& raylibImplementation) = delete;
  [[nodiscard]] RaylibImplementation& operator=(RaylibImplementation&&) = delete;

void DrawGrid();

void DrawAstar();

 void ToggleDebug() { showDebug_ = !showDebug_; }

private:
  Grid& grid_;
  AstarAlgorithm& astar_;
  bool showDebug_{true};
};