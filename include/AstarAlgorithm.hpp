#pragma once
#include "Grid.hpp"
#include <queue>
#include <vector>

class AstarAlgorithm {
 public:
  explicit AstarAlgorithm(Grid& grid);

  void Reset(Node* start, Node* goal);
  
  void Solve();

  void Update();

  bool IsFinished() const { return isFinished_; }

  const std::vector<Node*>& GetFinalPath() const;

 private:
  struct OpenNode {
    Node* node;
    float fCost;
    bool operator<(const OpenNode& other) const { return fCost > other.fCost; }
  };

  static float Heuristic(Node* a, Node* b);

  std::vector<Node*> GetNeighbours(Node* node) const;

  void ExpandNode(Node* node);

  void ReconstructPath();

  Grid& grid_;
  Node* start_ {nullptr};
  Node* goal_ {nullptr};
  std::vector<Node*> finalPath_;
  bool isFinished_ {false};
  std::priority_queue<OpenNode> opened_;
};