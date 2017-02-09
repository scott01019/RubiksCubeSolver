#ifndef CUBIE_H_
#define CUBIE_H_

#include <tuple>
#include <utility>
#include <vector>

/*
  A class representing a cubie (edge, center, or corner) of the cube.
*/
class Cubie {
public:
  Cubie(const std::tuple<int, int, int> &);
  Cubie(const Cubie &);

  bool IsCorner() const;
  bool IsEdge() const;
  bool IsCenter() const;
  bool IsSolved() const;
  bool IsOriented() const;
  bool IsInAxisLayer(char, int) const;

  const std::tuple<int, int, int> &position() const { return position_; }
  const std::tuple<int, int, int> &solved_position() const { return solved_position_; }
  const std::vector<std::tuple<char, char, char>> &values() const { return values_;  }

  void set_position(const std::tuple<int, int, int> &pos) { position_ = pos; }
  void SetFaceForValue(char value, char face);

private:
  std::tuple<int, int, int> positon_; // x, y, z
  const std::tuple<int, int, int> solved_position_; // x, y, z
  std::vector<std::tuple<char, char, char>> values_; // value, face value is currently on, face value is solved on
}

#endif // CUBIE_H_