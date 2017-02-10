#ifndef CUBE_ALG_SEARCH_H_
#define CUBE_ALG_SEARCH_H_

#include "cubie.h"

#include <string>
#include <vector>

/*
  A class used to search for simple Rubik's cube algorithms.
*/
class CubeAlgSearch {
public:
  static std::vector<std::string> FindAlgorithm(
    const std::tuple<int, int, int> &, 
    char, 
    const std::tuple<int, int, int> &, 
    char,
    const std::vector<std::tuple<int, int, int>> &
  );

  static void GenerateCubieAlgorithms(const std::string &);

  static bool GoalFound(
    const std::vector<std::string> &,
    const std::tuple<int, int, int> &,
    char,
    const std::tuple<int, int, int> &,
    char,
    const std::vector<Cubie> &
  );
};

#endif  // CUBE_ALG_SEARCH_H_