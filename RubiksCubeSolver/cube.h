#ifndef CUBE_H_
#define CUBE_H_

#include "cubie.h"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

/*
 A class representing a generic Cube.
*/
class Cube {
public:
  static const std::string MOVES[18];
  static const std::map<std::string, void(Cube::*)(void)> MOVES_MAP; // Move -> Move Method
  static const std::map<std::tuple<char, char>, char> ROTATIONS_MAP; // Current Face and Axis -> new Face
  static const int SIZE = 3;
  static const std::vector<std::string> T_PERM;

  Cube() { init(); }

  void Move(char, int, int);
  void Move(const std::string &);
  void Move(const std::vector<std::string> &);
  void Rotate(char, Cubie &);
  void RotateX(Cubie &);
  void RotateY(Cubie &);
  void RotateZ(Cubie &);
  const Cubie &GetCubieByPosition(const std::tuple<int, int, int> &) const;
  std::vector<Cubie> GetUnsolvedCorners() const;
  std::vector<Cubie> GetUnsolvedCubies() const;
  std::vector<Cubie> GetUnsolvedEdges() const;
  void Scramble();
  bool Solved() const;

  // Move Methods
  void R() { Cube::Move('x', 1, 1); }
  void Ri() { Cube::Move('x', 1, 3); }
  void R2() { Cube::Move('x', 1, 2); }

  void L() { Cube::Move('x', -1, 3); }
  void Li() { Cube::Move('x', -1, 1); }
  void L2() { Cube::Move('x', -1, 2); }

  void F() { Cube::Move('z', -1, 3); }
  void Fi() { Cube::Move('z', -1, 1); }
  void F2() { Cube::Move('z', -1, 2); }

  void B() { Cube::Move('z', 1, 1); }
  void Bi() { Cube::Move('z', 1, 3); }
  void B2() { Cube::Move('z', 1, 2); }

  void U() { Cube::Move('y', 1, 1); }
  void Ui() { Cube::Move('y', 1, 3); }
  void U2() { Cube::Move('y', 1, 2); }

  void D() { Cube::Move('y', -1, 3); }
  void Di() { Cube::Move('y', -1, 1); }
  void D2() { Cube::Move('y', -1, 2); }

  void T() { Move(T_PERM); }

  const std::vector<Cubie> &cubies() const { return cubies_; }
  int size() const { return SIZE; }

private:
  void init();

  std::vector<Cubie> cubies_; // A vector of the cubies.
};

#endif // CUBE_H_