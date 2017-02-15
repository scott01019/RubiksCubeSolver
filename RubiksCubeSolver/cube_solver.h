#ifndef CUBE_SOLVER_H_
#define CUBE_SOLVER_H_

#include "algs.h"
#include "cube.h"

#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>

/*
  A class to run the cube solver algorithm.
*/
class CubeSolver {
public:
  static const std::unordered_map<std::tuple<std::tuple<int, int, int>, char>, std::vector<std::string>, CubieHash> ALGS;

  static std::string InverseMove(const std::string &);
  static std::vector<std::string> ReverseAndInverseAlg(const std::vector<std::string> &);
  static std::vector<std::string> Solve(const Cube &);
  static std::vector<std::string> SolveCorners(const Cube &cube);
  static std::vector<std::string> SolveEdges(const Cube &cube);
};

#endif // CUBE_SOLVER_H_