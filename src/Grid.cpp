#include "Grid.hpp"
#include <cstddef>
#include <stdexcept>

Collum::Collum(const size_t rows) : rows_(rows) { }

[[nodiscard]] Node& Collum::operator[](const size_t row) {
  if(row >= rows_.size()) {
    throw std::logic_error("Out of Index");
    }
    return rows_.at(row);
  }

[[nodiscard]] size_t Collum::GetRows() {
    return rows_.size();
  }

Grid::Grid(const size_t side, const float pixelSize) : Grid(side, side, pixelSize) {}

Grid::Grid(const size_t collums, const size_t rows, const float pixelSize) : collums_(collums, Collum(rows)) {
  for(auto collum{0uz}; collum < GetCollums(); collum++) {
    for(auto row{0uz}; row < collums_.at(collum).GetRows(); row++) {
      collums_.at(collum)[row].x_ = collum,
      collums_.at(collum)[row].y_ = row;
      collums_.at(collum)[row].pixelSize_ = pixelSize;
    }
  }
}

[[nodiscard]] Collum& Grid::operator[](const size_t collum) {
    if(collum >= collums_.size()) {
      throw std::logic_error("Out of Index");
    }
    return collums_.at(collum);
  }

[[nodiscard]] size_t Grid::GetCollums() {
    return collums_.size(); 
  }