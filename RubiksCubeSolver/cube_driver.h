#ifndef CUBE_DRIVER_H_
#define CUBE_DRIVER_H_

#include "cube.h"

#include <memory>
#include <thread>

/*
  A driver class to run the program.
*/
class CubeDriver {
public:
  CubeDriver() : thread_running_(false) { }
  void ExecuteCommand(const std::string &);
  void Run();
private:
  Cube cube_;
  std::unique_ptr<std::thread> thread_;
  bool thread_running_;
};

#endif // CUBE_DRIVER_H_