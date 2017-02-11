#include "algs.h"
#include "cube.h"
#include "cube_alg_search.h"
#include "cubie.h"

#include <fstream>
#include <queue>
#include <string>
#include <vector>

/*
  Finds simple Rubik's cube algorithms using a BFS.
  Inputs: position - the position of the cubie to be solved
  value - the value of the cubie to be solved
  new_position - the desired position of the cubie to be solved
  new_face - the new face of the for the value to be solved
  holds - a list of positions of cubies who must maintain position and orientation
*/
std::vector<std::string> CubeAlgSearch::FindAlgorithm(
  const std::tuple<int, int, int> &position,
  char value,
  const std::tuple<int, int, int> &new_position,
  char new_face,
  const std::vector<std::tuple<int, int, int>> &holds
  ) {  
  // Cubies which need to maintain position and orientation.
  // Cubies which need to be "held", or not changed.
  std::vector<Cubie> original_holds;
  
  for (auto hold : holds) {
    original_holds.push_back(Cubie(hold));
  }

  // Run BFS to find desired algorithm.
  std::queue<std::vector<std::string>> nodes;
  nodes.push(std::vector<std::string>());
  while (!nodes.empty()) {
    std::vector<std::string> current = nodes.front();
    nodes.pop();
    if (CubeAlgSearch::GoalFound(current, position, value, new_position, new_face, original_holds))
      return current;
    else {
      for (auto i = 0; i < 18; ++i) {
        std::vector<std::string> new_node = current;
        if (current.empty()) {
          new_node.push_back(Cube::MOVES[i]);
          nodes.push(new_node);
        } else if (Cube::MOVES[i].find(current.back().at(0)) == std::string::npos) {
          new_node.push_back(Cube::MOVES[i]);
          nodes.push(new_node);
        }
      }
    }
  }
  return std::vector<std::string>();
}


/*
  Generates algorithm list required to solve Rubik's cube and stores it in a text file.
*/
void CubeAlgSearch::GenerateCubieAlgorithms(const std::string &filename) {
  Cube cube;
  std::vector<Cubie> cubies = cube.cubies();

  std::tuple<int, int, int> goal_edge = std::make_tuple(-1, 1, 0);
  std::tuple<int, int, int> goal_corner = std::make_tuple(1, 1, -1);
  std::vector<std::tuple<int, int, int>> edge_holds;
  std::vector<std::tuple<int, int, int>> corner_holds;
  edge_holds.push_back(std::make_tuple(1, 1, 0));
  edge_holds.push_back(std::make_tuple(1, 1, 1));
  edge_holds.push_back(std::make_tuple(1, 1, -1));
  corner_holds.push_back(std::make_tuple(1, 1, 0));
  corner_holds.push_back(std::make_tuple(1, 1, 1));
  corner_holds.push_back(std::make_tuple(-1, 1, 0));

  std::ofstream file;
  file.open(filename);
  file.close();
  file.open(filename, std::ios::app);

  for (auto cubie : cubies) {
    std::vector<std::tuple<char, char, char>> values = cubie.values();
    std::tuple<int, int, int> p = cubie.position();
    if (p != std::make_tuple(1, 1, 1) && p != std::make_tuple(1, 1, 0)) {
      for (auto value : values) {
        std::vector<std::string> result;
        if (cubie.IsEdge())
          result = CubeAlgSearch::FindAlgorithm(p, std::get<0>(value), goal_edge, 'U', edge_holds);
        if (cubie.IsCorner())
          result = CubeAlgSearch::FindAlgorithm(p, std::get<0>(value), goal_corner, 'U', corner_holds);
        if (!cubie.IsCenter()) {
         file << MyDecoraterAlg(p, std::get<0>(value), result);
        }
      }
    }
  }

  file.close();
}

/*
  Checks whether the desired algorithm has been found.
  Inputs: potential_alg - a vector of strings representing the algorithm to be checked
  position - the position of the cubie to be solved
  value - the value of the cubie to be solved
  goal_position - the goal position for the cubie to be solved
  goal_face - the value destination for the cubie to be solved
  holds - a list of cubies which should not alter position or orientation
*/
bool CubeAlgSearch::GoalFound(
  const std::vector<std::string> &potential_alg,
  const std::tuple<int, int, int> &position,
  char value,
  const std::tuple<int, int, int> &goal_position,
  char goal_face,
  const std::vector<Cubie> &holds
  ) {
  
  Cube cube;
  Cubie *cubie = cube.GetCubiePtrByPosition(position);
  cube.Move(potential_alg);

  if (cubie == NULL) return false;
  if (cubie->position() != goal_position) return false;
  std::vector<std::tuple<char, char, char>> values = cubie->values();
  for (auto val : values) {
    if (std::get<0>(val) == value) {
      if (std::get<1>(val) != goal_face) return false;
    }
  }

  for (auto hold : holds) {
    if (!hold.Equals(cube.GetCubieByPosition(hold.position()))) return false;
  }

  return true;
}