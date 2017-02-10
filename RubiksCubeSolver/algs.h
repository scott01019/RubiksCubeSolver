#ifndef ALGS_H_
#define ALGS_H_

#include <string>
#include <tuple>
#include <vector>

std::string MyDecoraterAlg(const std::tuple<int, int, int> &, char,  const std::vector<std::string> &);
std::string SpaceDecoraterAlg(const std::tuple<int, int, int> &, char, const std::vector<std::string> &);

#endif // ALGS_H_