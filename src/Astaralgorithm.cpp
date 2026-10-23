#include "AstarAlgorithm.hpp"
#include "Grid.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

AstarAlgorithm::AstarAlgorithm(Grid& grid) : grid_(grid) {}

void AstarAlgorithm::Reset(Node* start, Node* goal) {
  start_ = start;
  goal_ = goal;
  finalPath_.clear();
  opened_ = {};
  isFinished_ = false;

  for (auto collum {0uz}; collum < grid_.GetCollums(); collum++) {
    for (auto row {0uz}; row < grid_[collum].GetRows(); row++) {
      Node& node = grid_[collum][row];
      node.gCost_ = std::numeric_limits<float>::max();
      node.isOpen_ = false;
      node.isClosed_ = false;
      node.parent_ = nullptr;
    }
  }

  start_->gCost_ = 0;
  start_->hCost_ = Heuristic(start_, goal_);
  start_->fCost_ = start_->gCost_ + start_->hCost_;
  start_->isOpen_ = true;
  opened_.push({start_, start_->fCost_});
}

void AstarAlgorithm::Solve() {
  while (!isFinished_) {
    Update();
  }
}

float AstarAlgorithm::Heuristic(Node* a, Node* b) {
  return static_cast<float>(std::abs(a->x_ - b->x_) + std::abs(a->y_ - b->y_));
}

[[nodiscard]] std::vector<Node*> AstarAlgorithm::GetNeighbours (Node* node) const{
  std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  std::vector<Node*> output { };

  for(auto direction : directions) {
    if(node->x_ + direction.first < 0 || node->x_ + direction.first >= static_cast<int>(grid_.GetCollums())
    || node->y_ + direction.second < 0 || node->y_ + direction.second >= static_cast<int>(grid_[0].GetRows())) { continue;}
    auto neighbour = &grid_[node->x_ + direction.first][node->y_ + direction.second];
    output.push_back(neighbour);
  }
  return output;
}

void AstarAlgorithm::ExpandNode(Node* node) {
  for (auto neighbour : GetNeighbours(node)) {
    if (neighbour->isClosed_ || neighbour->isWall_) {
      continue;
    }
    if (node->gCost_ + 1 >= neighbour->gCost_) {
      continue;
    }
    neighbour->gCost_ = node->gCost_ + 1;
    neighbour->hCost_ = Heuristic(neighbour, goal_);
    neighbour->fCost_ = neighbour->gCost_ + neighbour->hCost_;
    neighbour->isOpen_ = true;
    neighbour->parent_ = node;
    opened_.push({neighbour, neighbour->fCost_});
  }
}

void AstarAlgorithm::ReconstructPath() {
  finalPath_.clear();
  for (Node* current = goal_; current != nullptr; current = current->parent_) {
    finalPath_.push_back(current);
  }
  std::reverse(finalPath_.begin(), finalPath_.end());  // path[0] = Start, path[1] = nächstes Feld
}

const std::vector<Node*>& AstarAlgorithm::GetFinalPath() const {
  return finalPath_;
}

void AstarAlgorithm::Update() {
  if (isFinished_) {
    return;
  }
  if (opened_.empty()) {  // kein Weg gefunden
    isFinished_ = true;
    return;
  }

  auto current = opened_.top();
  opened_.pop();

  if (current.node->isClosed_) {  // veralteter Doppel-Eintrag
    return;
  }
  if (current.node == goal_) {
    ReconstructPath();
    isFinished_ = true;
    return;
  }
  current.node->isClosed_ = true;
  current.node->isOpen_ = false;
  ExpandNode(current.node);
}