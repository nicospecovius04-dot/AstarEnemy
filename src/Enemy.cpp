#include "Enemy.hpp"
#include "Grid.hpp"
#include <cmath>
#include <raylib.h>

Enemy::Enemy(Grid& grid, Node* node) : grid_(grid), pos_(Center(node)) {}

[[nodiscard]] Vector2 Enemy::Center(Node* node) const{
  return {node->pixelSize_ / 2 + node->x_ * node->pixelSize_, node->y_ * node->pixelSize_ + node->pixelSize_ / 2};
}

void Enemy::MoveTowards(Node* target) {
  float dt{ GetFrameTime()};
  auto goal = Center(target);
  Vector2 d {goal.x - pos_.x, goal.y - pos_.y};
  float luftlinie = std::sqrt(d.x * d.x + d.y * d.y);
  float step = speed_ * dt;

  if (luftlinie <= step) {
    pos_ = goal;                 // angekommen
  } else {
    pos_.x += d.x / luftlinie * step;  // proz anteil der luftlinie in Richtung Ziel auf x & y pro frame
    pos_.y += d.y / luftlinie * step;
  }
}

Vector2 Enemy::GetPos() const {
  return pos_;
}

Node* Enemy::GetEnemy() {
  auto pixelSize = grid_[0][0].pixelSize_;
  return &grid_[static_cast<int>(pos_.x/ pixelSize)][static_cast<int>(pos_.y / pixelSize)];
}

