#include "Player.hpp"
#include "Grid.hpp"
#include <algorithm>
#include <raylib.h>

Player::Player(Grid& grid, Node* start) : grid_(grid) {
  pos_ = {(start->x_ + 0.5f) * start->pixelSize_,
          (start->y_ + 0.5f) * start->pixelSize_};
}

void Player::Update() {
  float dt {GetFrameTime()};
  Vector2 dir {0, 0};

  if (IsKeyDown(KEY_W)) { dir.y -= 1; }
  if (IsKeyDown(KEY_S)) { dir.y += 1; }
  if (IsKeyDown(KEY_A)) { dir.x -= 1; }
  if (IsKeyDown(KEY_D)) { dir.x += 1; }

  // X und Y getrennt prüfen, so rutscht man an Wänden entlang
  Vector2 newX = {pos_.x + dir.x * speed_ * dt, pos_.y};
  if (!IsWallAt(newX)) { pos_ = newX; }

  Vector2 newY = {pos_.x, pos_.y + dir.y * speed_ * dt};
  if (!IsWallAt(newY)) { pos_ = newY; }
}

Node* Player::CellAt(Vector2 posPixel) const {
  float size = grid_[0][0].pixelSize_;
  int posX = std::clamp(static_cast<int>(posPixel.x / size), 0, static_cast<int>(grid_.GetCollums()) - 1);
  int posY = std::clamp(static_cast<int>(posPixel.y / size), 0, static_cast<int>(grid_[0].GetRows()) - 1);
  return &grid_[posX][posY];
}

bool Player::IsWallAt(Vector2 posPixel) const {
  return CellAt(posPixel)->isWall_;
}

Node* Player::GetPlayer() const {
  return CellAt(pos_);
}

Vector2 Player::GetPos() const {
  return pos_;
}