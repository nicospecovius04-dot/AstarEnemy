#pragma once 
#include "Grid.hpp"
#include <raylib.h>

class Player {
public:
Player(Grid& grid, Node* start);

void Update();

Node* CellAt(Vector2 posPixel) const;

Vector2 GetPos() const;

Node* GetPlayer() const;

Node* CellAt(Vector2 pos);

bool IsWallAt(Vector2 pos) const;

private:
Grid& grid_;
Vector2 pos_{};
float speed_{200.0f};
};