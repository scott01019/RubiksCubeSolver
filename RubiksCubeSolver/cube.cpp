#include "cube.h"

#include <chrono>
#include <functional>
#include <random>
#include <string>
#include <tuple>
#include <map>
#include <utility>
#include <vector>

// Possible moves for the cube.
const std::string Cube::MOVES[18] = { "R", "R'", "R2", "L", "L'", "L2", "F", "F'", "F2",
"B", "B'", "B2", "U", "U'", "U2", "D", "D'", "D2" };

// Moves mapped to their respective methods.
const std::map<std::string, void(Cube::*)(void)> Cube::MOVES_MAP = { { "R", &Cube::R }, { "R'", &Cube::Ri },
{ "R2", &Cube::R2 }, { "L", &Cube::L }, { "L'", &Cube::Li }, { "L2", &Cube::L2 }, { "F", &Cube::F },
{ "F'", &Cube::Fi }, { "F2", &Cube::F2 }, { "B", &Cube::B }, { "B'", &Cube::Bi }, { "B2", &Cube::B2 },
{ "U", &Cube::U }, { "U'", &Cube::Ui }, { "U2", &Cube::U2 }, { "D", &Cube::D }, { "D'", &Cube::Di },
{ "D2", &Cube::D2 }, { "T", &Cube::T } };

// Current face rotated around an axis mapped to their new face.
const std::map<std::tuple<char, char>, char> Cube::ROTATIONS_MAP = {
  { std::tuple<char, char>('F', 'x'), 'U' }, { std::tuple<char, char>('U', 'x'), 'B' },
  { std::tuple<char, char>('B', 'x'), 'D' }, { std::tuple<char, char>('D', 'x'), 'F' },
  { std::tuple<char, char>('R', 'x'), 'R' }, { std::tuple<char, char>('L', 'x'), 'L' },
  { std::tuple<char, char>('F', 'y'), 'L' }, { std::tuple<char, char>('U', 'y'), 'U' },
  { std::tuple<char, char>('B', 'y'), 'R' }, { std::tuple<char, char>('D', 'y'), 'D' },
  { std::tuple<char, char>('R', 'y'), 'F' }, { std::tuple<char, char>('L', 'y'), 'B' },
  { std::tuple<char, char>('F', 'z'), 'F' }, { std::tuple<char, char>('U', 'z'), 'L' },
  { std::tuple<char, char>('B', 'z'), 'B' }, { std::tuple<char, char>('D', 'z'), 'R' },
  { std::tuple<char, char>('R', 'z'), 'U' }, { std::tuple<char, char>('L', 'z'), 'D' }
};

// T-perm
const std::vector<std::string> Cube::T_PERM = { "R", "U", "R'", "U'", "R'",
"F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'" };

/*
  Initializes the cube and the moves map.
*/
void Cube::init() {
  for (auto x = -1; x < 2; ++x) {
    for (auto y = -1; y < 2; ++y) {
      for (auto z = -1; z < 2; ++z) {
        if (!(x == 0 && y == 0 && z == 0))
          cubies_.push_back(Cubie(std::make_tuple(x, y, z)));
      }
    }
  }
}

/*
  A copy constructor for the Cube class.
*/
Cube::Cube(const Cube &cube) {
  for (auto cubie : cube.cubies_) cubies_.push_back(cubie);
}

/*
  Rotates the given layer from the given axis clockwise 90 degrees 
  the given number of times.
*/
void Cube::Move(char axis, int layer, int turns) {
  for (auto i = 0; i < turns; ++i) {
    for (Cubie &cubie : cubies_) {
      if (cubie.IsInAxisLayer(axis, layer)) {
        std::vector<std::tuple<char, char, char>> values = cubie.values();
        for (auto value : values) {
          cubie.SetFaceForValue(
            std::get<0>(value),
            ROTATIONS_MAP.at(std::make_tuple(std::get<1>(value), axis))
          );
        }
        Rotate(axis, cubie);
      }
    }
  }
}

/*
  Executes the given move.
*/
void Cube::Move(const std::string &move) { (this->*MOVES_MAP.at(move))(); }

/*
  Executes the given moves.
*/
void Cube::Move(const std::vector<std::string> &moves) {
  for (auto move : moves) Move(move);
}

/*
  Rotates the given cubie around the given axis 90 degrees clockwise 
  (oriented by the positive axis).
*/
void Cube::Rotate(char axis, Cubie &cubie) {
  switch (axis) {
  case 'x': RotateX(cubie); break;
  case 'y': RotateY(cubie); break;
  case 'z': RotateZ(cubie); break;
  }
}

/*
  Rotates the given cubie 90 degrees around the x-axis.
*/
void Cube::RotateX(Cubie &cubie) {
  std::tuple<int, int, int> current = cubie.position();
  cubie.set_position(
    std::make_tuple(
      std::get<0>(current),
      std::get<2>(current) * -1,
      std::get<1>(current)
    )
  );
}

/*
  Rotates the given cubie 90 degrees around the y-axis.
*/
void Cube::RotateY(Cubie &cubie) {
  std::tuple<int, int, int> current = cubie.position();
  cubie.set_position(
    std::make_tuple(
      std::get<2>(current),
      std::get<1>(current),
      std::get<0>(current) * -1
    )
  );
}

/*
  Rotates the given cubie 90 degrees around the z-axis.
*/
void Cube::RotateZ(Cubie &cubie) {
  std::tuple<int, int, int> current = cubie.position();
  cubie.set_position(
    std::make_tuple(
      std::get<1>(current) * -1,
      std::get<0>(current),
      std::get<2>(current)
    )
  );
}

/*
  Returns the cubie at the given position.
*/
const Cubie &Cube::GetCubieByPosition(const std::tuple<int, int, int> &position) const {
  int size = cubies_.size();
  for (auto i = 0; i < size; ++i) {
    if (cubies_[i].position() == position) return cubies_[i];
  }
}

/*
  Returns a ptr cubie at the given position.
*/
Cubie *Cube::GetCubiePtrByPosition(const std::tuple<int, int, int> &position) {
  int size = cubies_.size();
  for (auto i = 0; i < size; ++i)
    if (cubies_[i].position() == position) return &cubies_[i];
  return NULL;
}


/*
  Returns a vector of the unsolved corners.
*/
std::vector<Cubie> Cube::GetUnsolvedCorners() const {
  std::vector<Cubie> unsolved_corners;
  int size = cubies_.size();
  for (auto i = 0; i < size; ++i)
    if (cubies_[i].IsCorner() && !cubies_[i].IsSolved()) unsolved_corners.push_back(cubies_[i]);
  return unsolved_corners;
}

/*
  Returns a vector of all unsolved cubies.
*/
std::vector<Cubie> Cube::GetUnsolvedCubies() const {
  std::vector<Cubie> unsolved_cubies;
  int size = cubies_.size();
  for (auto i = 0; i < size; ++i)
    if (!cubies_[i].IsSolved()) unsolved_cubies.push_back(cubies_[i]);
  return unsolved_cubies;
}

/*
  Returns a vector of all unsolved edges.
*/
std::vector<Cubie> Cube::GetUnsolvedEdges() const {
  std::vector<Cubie> unsolved_edges;
  int size = cubies_.size();
  for (auto i = 0; i < size; ++i)
    if (cubies_[i].IsEdge() && !cubies_[i].IsSolved()) unsolved_edges.push_back(cubies_[i]);
  return unsolved_edges;
}


/*
  Scrambles the cube.
*/
void Cube::Scramble() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, 17);
  auto rand = std::bind(distribution, generator);
  for (auto i = 0; i < 100; ++i)
    Move(MOVES[rand()]);
}

/*
  Returns true if all cubies in the cube are solved.
*/
bool Cube::Solved() const {
  for (auto cubie : cubies_)
    if (!cubie.IsSolved()) return false;
  return true;
}