#include "cube.h"
#include "cube_alg_search.h"
#include "cube_driver.h"
#include "cube_printer.h"
#include "cube_solver.h"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

/*
  Executes command for the program.
*/
void CubeDriver::ExecuteCommand(const std::string &command) {
  if (command == "1") {
    cube_ = Cube();
  } else if (command == "2") {
    cube_.Scramble();
  } else if (command == "3") {
    std::vector<std::string> solution = CubeSolver::Solve(cube_);
    std::cout << "Solution: ";
    for (auto move : solution) std::cout << move << " ";
  } else if (command == "4") {
    std::vector<std::string> solution = CubeSolver::Solve(cube_);
    std::cout << "Solution: ";
    for (auto move : solution) std::cout << move << " ";
    std::cout << "\n\n";
    for (auto move : solution) {
      std::cout << "Move: " << move << "\n\n";
      cube_.Move(move);
      CubePrinter::PrintCube(cube_);
    }
  } else if (command == "5") {
    if (!thread_running_) {
      thread_running_ = true;
      std::string filename;
      std::cout << "Please enter a filename: ";
      std::cin >> filename;
      thread_ = std::make_unique<std::thread>(std::thread(CubeAlgSearch::GenerateCubieAlgorithms, filename));
      thread_->detach();
    } else {
      std::cout << "\n\nAlgorithm file is already being generated!\n\n";
    }
  } else if (command == "6") {
    std::cout << "\n\nGood Bye\n\n";
  } else {
    for (auto move : Cube::MOVES)
      if (command == move) {
        std::cout << "\nMove: " << move << "\n\n";
        cube_.Move(move);
      }
  }
}

/*
  Runs the interface for the program.
*/
void CubeDriver::Run() {
  std::string input;
  while (input != "6") {
    CubePrinter::PrintCube(cube_);
    std::cout << "Main Menu\n";
    std::cout << "1 - Reset Cube\n";
    std::cout << "2 - Scramble Cube\n";
    std::cout << "3 - Generate Solution for Cube\n";
    std::cout << "4 - Generate Solution and Solve Cube\n";
    std::cout << "5 - Generate Algorithm File\n";
    std::cout << "6 - Exit\n\n";
    std::cout << "Enter any of these valid moves: ";
    for (auto move : Cube::MOVES) { std::cout << move << " "; }
    std::cout << "\n\nInput: ";

    std::cin >> input;
    ExecuteCommand(input);
  }
}