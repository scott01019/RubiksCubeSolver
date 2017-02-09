#include "cube.h"
#include "cube_printer.h"
#include "cubie.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <Windows.h>

/*
  Executes the print process.
*/
void CubePrinter::PrintCube(const Cube &cube) {
  int size = Cube::SIZE;
  std::vector<std::vector<char>> cb[6];
  for (auto i = 0; i < 6; ++i) {
    for (auto j = 0; j < size; ++j) {
      cb[i].resize(size);
      for (auto k = 0; k < size; ++k) {
        cb[i][j].resize(size);
      }
    }
  }

  SetFaces(cb, cube);
  Print(cb);
}

/*
  Gets the appropriate color value for the given face value.
*/
int CubePrinter::GetColor(char face) {
  switch (face) {
  case 'L': return 5;
  case 'U': return 14;
  case 'F': return 9;
  case 'R': return 12;
  case 'D': return 15;
  case 'B': return 10;
  }
  return 6;
}

/*
  Prints the cube to the console.
*/
void CubePrinter::Print(std::vector<std::vector<char>> cube[]) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  std::cout << "\n";

  int size = Cube::SIZE;

  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size; ++j) std::cout << " ";
    for (auto j = 0; j < size; ++j) {
      SetConsoleTextAttribute(hConsole, CubePrinter::GetColor(cube[0][i][j]));
      std::cout << (char)254u;
    }
    std::cout << "\n";
  }
  for (auto i = 0; i < size; ++i) {
    for (auto j = 1; j < 5; ++j) {
      for (auto k = 0; k < size; ++k) {
        SetConsoleTextAttribute(hConsole, GetColor(cube[j][i][k]));
        std::cout << (char)254u;
      }
    }
    std::cout << "\n";
  }

  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size; ++j) std::cout << " ";
    for (auto j = 0; j < size; ++j) {
      SetConsoleTextAttribute(hConsole, GetColor(cube[5][i][j]));
      std::cout << (char)254u;
    }
    std::cout << "\n";
  }

  std::cout << "\n";
  SetConsoleTextAttribute(hConsole, 15);
}

/*
  Builds the printable cube from the Cube object.
*/
void CubePrinter::SetFaces(std::vector<std::vector<char>> print_cube[], const Cube &cube) {
  std::vector<Cubie> cubies = cube.cubies();
  for (auto cubie : cubies) {
    std::tuple<int, int, int> position = cubie.position();
    std::vector<std::tuple<char, char, const char>> values = cubie.values();
    for (auto value : values) {
      switch (std::get<1>(value)) {
      case 'R': {
        print_cube[3][std::get<1>(position) * -1 + 1][std::get<2>(position) + 1] = std::get<0>(value);
      } break;
      case 'L': {
        print_cube[1][std::get<1>(position) * -1 + 1][std::get<2>(position) * -1 + 1] = std::get<0>(value);
      } break;
      case 'F': {
        print_cube[2][std::get<1>(position) * -1 + 1][std::get<0>(position) + 1] = std::get<0>(value);
      } break;
      case 'B': {
        print_cube[4][std::get<1>(position) * -1 + 1][std::get<0>(position) * -1 + 1] = std::get<0>(value);
      } break;
      case 'U': {
        print_cube[0][std::get<2>(position) * -1 + 1][std::get<0>(position) +1] = std::get<0>(value);
      } break;
      case 'D': {
        print_cube[5][std::get<2>(position) +1][std::get<0>(position) +1] = std::get<0>(value);
      } break;
      }
    }
  }
}