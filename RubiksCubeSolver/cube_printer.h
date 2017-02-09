#ifndef CUBE_PRINTER_H_
#define CUBE_PRINTER_H_

#include "cube.h"

#include <vector>

/*
  A class of static methods to print Cube's to console using std::cout.
*/
class CubePrinter {
public:
  static void PrintCube(const Cube &);
private:
  static void Print(std::vector<std::vector<char>>[]);
  static int GetColor(char);
  static void SetFaces(std::vector<std::vector<char>>[], const Cube &);
};

#endif // CUBE_PRINTER_H_