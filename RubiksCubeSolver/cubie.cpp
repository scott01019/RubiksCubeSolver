#include "cubie.h"

#include <tuple>
#include <utility>
#include <vector>

#include <iostream>

/*
  Constructor for Cubie class given the solved position of the cubie (x, y, z).
*/
Cubie::Cubie(const std::tuple<int, int, int> &solved_position) 
  : position_(solved_position), solved_position_(solved_position) {
  if (std::get<0>(position_) == 1) values_.push_back(std::make_tuple('R', 'R', 'R'));
  else if (std::get<0>(position_) == -1) values_.push_back(std::make_tuple('L', 'L', 'L'));
  if (std::get<1>(position_) == 1) values_.push_back(std::make_tuple('U', 'U', 'U'));
  else if (std::get<1>(position_) == -1) values_.push_back(std::make_tuple('D', 'D', 'D'));
  if (std::get<2>(position_) == 1) values_.push_back(std::make_tuple('B', 'B', 'B'));
  else if (std::get<2>(position_) == -1) values_.push_back(std::make_tuple('F', 'F', 'F'));
}

/*
  Copy Constructor for Cubie class.
*/
Cubie::Cubie(const Cubie &cubie) : position_(cubie.position_), 
solved_position_(cubie.solved_position_), values_(cubie.values_) { }

/*
  Returns true if the cubie is a center cubie.
*/
bool Cubie::IsCenter() const { return values_.size() == 1; }

/*
  Returns true if the cubie is a corner cubie.
*/
bool Cubie::IsCorner() const { return values_.size() == 3; }

/*
  Returns true if the cubie is an edge cubie.
*/
bool Cubie::IsEdge() const { return values_.size() == 2; }

/*
  Returns true if the cubie has equal position and orientation as input cubie.
*/
bool Cubie::Equals(const Cubie &cubie) const {
  if (position_ != cubie.position_) return false;
  for (auto i = 0; i < values_.size(); ++i) {
    if (std::get<0>(values_[i]) != std::get<0>(cubie.values_[i])
      || std::get<1>(values_[i]) != std::get<1>(cubie.values_[i])) return false;
  }
  return true;
}

/*
  Returns true if the cubie value for the given axis is equal to the given layer.
*/
bool Cubie::IsInAxisLayer(char axis, int layer) const {
  switch (axis) {
  case 'x': {
    return std::get<0>(position_) == layer;
  } break;
  case 'y': {
    return std::get<1>(position_) == layer;
  } break;
  case 'z': {
    return std::get<2>(position_) == layer;
  } break;
  }
  return false;
}

/*
  Returns true if the cubie is correctly oriented, ie, if face value is currently on
  equals to the solved face for the value.
*/
bool Cubie::IsOriented() const {
  for (auto value : values_)
    if (std::get<1>(value) != std::get<2>(value)) return false;
  return true;
}

/*
  Returns true if cubie is correctly positioned (position is equal to solved position).
*/
bool Cubie::IsPositioned() const { return position_ == solved_position_; }

/*
  Returns true if the cubie is sovled (position and orientation solved).
*/
bool Cubie::IsSolved() const { return IsOriented() && IsPositioned(); }

/*
  Sets the current face for the given value.
*/
void Cubie::SetFaceForValue(char val, char face) {
  for (std::tuple<char, char, const char> &value : values_)
    if (std::get<0>(value) == val)
      std::get<1>(value) = face;
}