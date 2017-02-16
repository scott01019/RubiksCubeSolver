#include "algs.h"
#include "cube.h"
#include "cube_solver.h"

#include <algorithm>
#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>

//  Map of all algorithms to move every cubie and cubie face to their buffer position
const std::unordered_map<std::tuple<std::tuple<int, int, int>, char>, std::vector<std::string>, CubieHash> CubeSolver::ALGS = {
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, -1), 'L'), std::vector<std::string>({ "R'", "D", "R", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R'", "D'", "R" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, -1), 'D'), std::vector<std::string>({ "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, -1), 'F'), std::vector<std::string>({ "D", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, 0), 'L'), std::vector<std::string>({ "L", "U", "B'", "U'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U", "B", "U'", "L'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, 0), 'D'), std::vector<std::string>({ "L2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, 1), 'L'), std::vector<std::string>({ "D2", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, 1), 'D'), std::vector<std::string>({ "D", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "D'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, -1, 1), 'B'), std::vector<std::string>({ "R'", "D2", "R", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R'", "D2", "R" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 0, -1), 'L'), std::vector<std::string>({ "U'", "F", "U", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U'", "F'", "U" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 0, -1), 'F'), std::vector<std::string>({ "L'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 0, 1), 'L'), std::vector<std::string>({ "U", "B'", "U'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U", "B", "U'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 0, 1), 'B'), std::vector<std::string>({ "L", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, -1), 'L'), std::vector<std::string>({ "F", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, -1), 'U'), std::vector<std::string>({ "F2", "D'", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "D", "F2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, -1), 'F'), std::vector<std::string>({ "F'", "D", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D'", "F" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, 0), 'L'), std::vector<std::string>({ "L", "U'", "F", "U", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U'", "F'", "U", "L'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, 0), 'U'), std::vector<std::string>({ "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, 1), 'L'), std::vector<std::string>({ "R'", "B2", "R", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "R'", "B2", "R" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, 1), 'U'), std::vector<std::string>({ "R2", "B2", "R2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R2", "B2", "R2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(-1, 1, 1), 'B'), std::vector<std::string>({ "R'", "B", "D2", "R", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R'", "D2", "B'", "R" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, -1, -1), 'D'), std::vector<std::string>({ "D'", "L2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L2", "D" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, -1, -1), 'F'), std::vector<std::string>({ "F", "L'", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "L", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, -1, 1), 'D'), std::vector<std::string>({ "D", "L2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L2", "D'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, -1, 1), 'B'), std::vector<std::string>({ "B'", "L", "B", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "B'", "L'", "B" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, 1, -1), 'U'), std::vector<std::string>({ "R2", "U", "R2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R2", "U'", "R2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, 1, -1), 'F'), std::vector<std::string>({ "R", "F'", "R'", "L'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L", "R", "F", "R'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, 1, 1), 'U'), std::vector<std::string>({ "R2", "U'", "R2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "R2", "U", "R2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(0, 1, 1), 'B'), std::vector<std::string>({ "R'", "B", "R", "L", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L'", "R'", "B'", "R" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, -1), 'R'), std::vector<std::string>({ "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, -1), 'D'), std::vector<std::string>({ "D'", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "D" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, -1), 'F'), std::vector<std::string>({ "F", "D", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D'", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, 0), 'R'), std::vector<std::string>({ "F'", "D'", "F", "L'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L", "F'", "D", "F" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, 0), 'D'), std::vector<std::string>({ "D2", "L2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "L2", "D2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, 1), 'R'), std::vector<std::string>({ "R", "F", "R'", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "R", "F'", "R'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, 1), 'D'), std::vector<std::string>({ "D2", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "D2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, -1, 1), 'B'), std::vector<std::string>({ "D'", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 0, -1), 'R'), std::vector<std::string>({ "U'", "F'", "U", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U'", "F", "U" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 0, -1), 'F'), std::vector<std::string>({ "U2", "R", "U2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U2", "R'", "U2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 0, 1), 'R'), std::vector<std::string>({ "U", "B", "U'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U", "B'", "U'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 0, 1), 'B'), std::vector<std::string>({ "U2", "R'", "U2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "U2", "R", "U2" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 1, -1), 'R'), std::vector<std::string>({ "F", "D'", "F2", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F2", "D", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 1, -1), 'U'), std::vector<std::string>({ "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'" }) },
{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(1, 1, -1), 'F'), std::vector<std::string>({ "F2", "D", "F'", "R", "U", "R'", "U'", "R'", "F", "R2", "U'", "R'", "U'", "R", "U", "R'", "F'", "F", "D'", "F2" }) }
};

/*
  Returns the inverse of the move.
*/
std::string CubeSolver::InverseMove(const std::string &move) {
  if (move.size() == 1) return move + "'";
  else if (move.at(1) == '2') return move;
  else return std::string(1, move[0]);
}

/*
  Returns a vector of the inverse and reverse of the given moves.
*/
std::vector<std::string> CubeSolver::ReverseAndInverseAlg(const std::vector<std::string> &moves) {
  std::vector<std::string> result;
  int size = moves.size();
  for (auto i = 0; i < size; ++i) result.push_back(moves[i]);
  std::reverse(result.begin(), result.end());
  for (auto i = 0; i < size; ++i) result[i] = CubeSolver::InverseMove(result[i]);
  return result;
} 

/*
  Solves the Rubik's cube.
*/
std::vector<std::string> CubeSolver::Solve(const Cube &cube) {
  std::vector<std::string> solution = CubeSolver::SolveCorners(cube);
  Cube cube_cpy = cube;
  cube_cpy.Move(solution);
  std::vector<std::string> edges = CubeSolver::SolveEdges(cube_cpy);
  cube_cpy.Move(edges);
  solution.insert(solution.end(), edges.begin(), edges.end());
  return solution;
}

/*
  Solves the corners of the given cube.
  Returns a solution vector of all moves.
*/
std::vector<std::string> CubeSolver::SolveCorners(const Cube &cube) {
  //  copy of the cube
  Cube cube_cpy(cube);
  //  solution vector
  std::vector<std::string> solution;
  // swapping position for corner cubies
  std::tuple<int, int, int> swap_position = std::make_tuple(1, 1, 1);
  // vector of unsolved corners
  std::vector<Cubie> unsolved_corners = cube_cpy.GetUnsolvedCorners();
  
  //  while there are unsolved corners
  while (!unsolved_corners.empty()) {
    //  holds moves to solve current corner
    std::vector<std::string> alg;
    //  get the cubie to be solved
    Cubie swap = cube_cpy.GetCubieByPosition(swap_position);
    //  destination position of cubie to be solved
    std::tuple<int, int, int> solved_position = swap.solved_position();
    //  holds the value (sticker) to be solved
    char goal_face;
    
    //  if the current corner to be solved does not belong in the swap position
    if (swap_position != solved_position) {
      //  the values for tuples for the current corner to be solved
      std::vector<std::tuple<char, char, char>> values = swap.values();
      //  find the correct the goal face to be solved (the value currently mapped to the Up, or 'U' face)
      for (auto value : values) if (std::get<1>(value) == 'U') goal_face = std::get<2>(value);
      //  get the algorithm from the map based off of the position and face to be solved
      alg = CubeSolver::ALGS.at(std::tuple<std::tuple<int, int, int>, char>(solved_position, goal_face));
    } 
    
    //  the current corner to be solved belongs in the swap position
    else {
      //  get a random unsolved corner cubie which is not in the swap location
      Cubie random_unsolved_cubie;
      int size = unsolved_corners.size();
      for (auto i = 0; i < size; ++i) {
        if (unsolved_corners[i].position() != swap_position) {
          random_unsolved_cubie = unsolved_corners[i];
          break;
        }
      }
      //  pick a random value to swap with
      std::vector<std::tuple<char, char, char>> values = random_unsolved_cubie.values();
      goal_face = std::get<2>(values[0]);
      //  get algorithm for that value and position
      alg = CubeSolver::ALGS.at(std::tuple<std::tuple<int, int, int>, char>(random_unsolved_cubie.solved_position(), goal_face));
    }
    //  insert the final vector of moves into the solution vector
    solution.insert(solution.end(), alg.begin(), alg.end());
    //  execute the moves on the cube
    cube_cpy.Move(alg);
    //  get updated list of unsolved corners
    unsolved_corners = cube_cpy.GetUnsolvedCorners();
  }
  //  return the solution vector
  return solution;
}

/*
  Solves the edges of the given cube. Returns a solution vector of all moves.
*/
std::vector<std::string> CubeSolver::SolveEdges(const Cube &cube) {
  //  copy of the cube
  Cube cube_cpy(cube);
  //  solution vector
  std::vector<std::string> solution;
  // swapping position for edge cubies
  std::tuple<int, int, int> swap_position = std::make_tuple(1, 1, 0);
  // get a vector of unsolved edges
  std::vector<Cubie> unsolved_edges = cube_cpy.GetUnsolvedEdges();

  //  while there are unsolved edges
  while (!unsolved_edges.empty()) {
    //  holds moves to solve current corner
    std::vector<std::string> alg;
    //  get the cubie to be solved
    Cubie swap = cube_cpy.GetCubieByPosition(swap_position);
    //  destination position of cubie to be solved
    std::tuple<int, int, int> solved_position = swap.solved_position();
    //  holds the value (sticker) to be solved
    char goal_face;

    //  if the current edge to be solved does not belong in the swap position
    if (swap_position != solved_position) {
      //  the values for tuples for the current edge to be solved
      std::vector<std::tuple<char, char, char>> values = swap.values();
      //  find the correct the goal face to be solved (the value currently mapped to the Up, or 'U' face)
      for (auto value : values) if (std::get<1>(value) == 'U') goal_face = std::get<2>(value);
      //  get the algorithm from the map based off of the position and face to be solved
      alg = CubeSolver::ALGS.at(std::tuple<std::tuple<int, int, int>, char>(solved_position, goal_face));
    } 
    
    //  the current edge to be solved belongs in the swap position
    else {
      //  get a random unsolved edge cubie which is not in the swap location
      Cubie random_unsolved_cubie;
      auto size = unsolved_edges.size();
      for (auto i = 0; i < size; ++i) {
        if (unsolved_edges[i].position() != swap_position) {
          random_unsolved_cubie = unsolved_edges[i];
          break;
        }
      }
      //  pick a random value to swap with
      std::vector<std::tuple<char, char, char>> values = random_unsolved_cubie.values();
      goal_face = std::get<2>(values[0]);
      //  get algorithm for that value and position
      alg = CubeSolver::ALGS.at(std::tuple<std::tuple<int, int, int>, char>(random_unsolved_cubie.solved_position(), goal_face));
    }
    //  insert the final vector of moves into the solution vector
    solution.insert(solution.end(), alg.begin(), alg.end());
    //  execute the moves on the cube
    cube_cpy.Move(alg);
    //  get updated list of unsolved corners
    unsolved_edges = cube_cpy.GetUnsolvedEdges();
  }
  //  return the solution vector
  return solution;
}
