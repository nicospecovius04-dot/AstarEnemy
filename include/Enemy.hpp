//strategy design pattern für verschiedene movements angriffe etc
#pragma once
#include "Grid.hpp"
#include "raylib.h"


class Enemy {
public:
Enemy(Grid& grid, Node* start);

[[nodiscard]] Vector2 Center(Node* node) const;

void MoveTowards(Node* target);

Node* GetEnemy(); 

Vector2 GetPos() const;
private:
Grid& grid_;
Vector2 pos_;
float speed_ {100.0f};
};