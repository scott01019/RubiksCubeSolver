#ifndef CUBE_SOLVER_H_
#define CUBE_SOLVER_H_

#include "cube.h"

#include <map>
#include <string>
#include <tuple>
#include <vector>

/*
  A class to run the cube solver algorithm.
*/
class CubeSolver {
public:
  static const std::map<std::tuple<std::tuple<int, int, int>, char>, const std::string> ALGS;

  static std::string InverseMove(const std::string &);
  static std::vector<std::string> ReverseAndInverseAlg(const std::vector<std::string> &);
  static std::vector<std::string> Solve(const Cube &);
  static std::vector<std::string> SolveCorners(const Cube &cube);
  static std::vector<std::string> SolveEdges(const Cube &cube);
};

#endif // CUBE_SOLVER_H_