#pragma once
#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

struct Node {
  int x_{ };
  int y_{ };
  float pixelSize_{ };

  bool isPlayer_{ };
  bool isOpen_{ };
  bool isClosed_{ };
  bool isWall_ { };

  float fCost_{ };
  float gCost_{ std::numeric_limits<float>::max() };
  float hCost_{ };
  Node* parent_;

  bool operator==(Node node) {
    return (this->x_ == node.x_ && this->y_ == node.y_);
  }
};

using Rows = std::vector<Node>;

class Collum {
public:
  Collum(const size_t rows);
  ~Collum() = default;
  Collum(const Collum& other) = default;
  Collum& operator=(const Collum& other) = delete;
  Collum(Collum&& other) = delete;
  Collum& operator=(Collum&&) = delete;

[[nodiscard]] Node& operator[](const size_t position);

[[nodiscard]] size_t GetRows();

private:
  Rows rows_;
};

using Collums = std::vector<Collum>;

class Grid {
public:
  Grid(const size_t side, const float pixelSize);
  Grid(const size_t collums, const size_t rows, const float pixelSize);
  ~Grid() = default;
  Grid(const Grid& grid) = default;
  Grid& operator=(const Grid& grid) = delete; //returnval nicht teil der signatur lol aber lasse ich mal aus
  Grid(Grid&& grid) = delete;
  Grid& operator=(Grid&&) = delete;

[[nodiscard]] Collum& operator[](const size_t position);

[[nodiscard]] size_t GetCollums();

private:
  Collums collums_;
};