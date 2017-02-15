#ifndef ALGS_H_
#define ALGS_H_

#include <string>
#include <tuple>
#include <vector>

std::string MyDecoraterAlg(const std::tuple<int, int, int> &, char,  const std::vector<std::string> &);
std::string SpaceDecoraterAlg(const std::tuple<int, int, int> &, char, const std::vector<std::string> &);

/*
  A struct to hash specific cubie orientations.
*/
struct CubieHash {
  std::size_t operator()(const std::tuple<std::tuple<int, int, int>, char> &) const;
  std::size_t operator()(const char &) const;
};
#endif // ALGS_H_