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

  bool IsCenter() const;
  bool IsCorner() const;
  bool IsEdge() const;
  bool Equals(const Cubie &) const;
  bool IsInAxisLayer(char, int) const;
  bool IsOriented() const;
  bool IsPositioned() const;
  bool IsSolved() const;
  void SetFaceForValue(char, char);

  const std::tuple<int, int, int> &position() const { return position_; }
  const std::tuple<int, int, int> &solved_position() const { return solved_position_; }
  const std::vector<std::tuple<char, char, const char>> &values() const { return values_;  }

  void set_position(const std::tuple<int, int, int> &pos) { position_ = pos; }

private:
  std::tuple<int, int, int> position_; // x, y, z
  const std::tuple<const int, const int, const int> solved_position_; // x, y, z
  std::vector<std::tuple<char, char, const char>> values_; // value, face value is currently on, face value is solved on
};

#endif // CUBIE_H_