#include "algs.h"

#include <string>
#include <tuple>
#include <vector>

/*
  A specific format for outputting algorithm data to file.
*/
std::string MyDecoraterAlg(const std::tuple<int, int, int> &position,
  char value, const std::vector<std::string> &alg) {
  std::string result;
  result = "{ std::tuple<std::tuple<int, int, int>, char>(std::tuple<int, int, int>(";
  result += std::to_string(std::get<0>(position)) + ", ";
  result += std::to_string(std::get<1>(position)) + ", " + std::to_string(std::get<2>(position));
  result += "), '" + std::string(1, value);
  result += "'), std::vector<std::string>({ ";
  int size = alg.size();
  for (auto i = 0; i < size; ++i) {
    result += "\"" + alg[i] + "\"";
    if (i + 1 < size) result += ", ";
  }
  result += " }) },\n";
  return result;
}

/*
  A common space format for outputting algorithm data to file.
*/
std::string SpaceDecoraterAlg(const std::tuple<int, int, int> &position,
  char value, const std::vector<std::string> &alg) {
  std::string result = std::to_string(std::get<0>(position)) + " ";
  result += std::to_string(std::get<1>(position)) + " " + std::to_string(std::get<2>(position));
  result += " " + value + std::string(" ");
  for (auto move : alg) {
    result += move + " ";
  } result += "\n";
  return result;
}

/*
  A hashing algorithm for cubie orientations.
*/
std::size_t CubieHash::operator()(const std::tuple<std::tuple<int, int, int>, char> &key) const {
  return std::size_t(
    std::get<1>(key) * 1000
    + (std::get<0>(std::get<0>(key)) + 2) * 100
    + (std::get<1>(std::get<0>(key)) + 2) * 10
    + (std::get<2>(std::get<0>(key)) + 2)
  );
}