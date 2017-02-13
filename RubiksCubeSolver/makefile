CXX = g++
CXXFLAGS = -Wall -g -pthread -std=c++11

RunCube: main.o cube_driver.o cube_solver.o cube_alg_search.o cube_printer.o cube.o cubie.o algs.o
	$(CXX) $(CXXFLAGS) -o RunCube main.o cube_driver.o cube_solver.o cube_alg_search.o cube_printer.o cube.o cubie.o algs.o

main.o: main.cpp cube_driver.h
	$(CXX) $(CXXFLAGS) -c main.cpp

cube_driver.o: cube_driver.h cube_solver.h cube_alg_search.h cube_printer.h cube.h cube_solver.h
	$(CXX) $(CXXFLAGS) -c cube_driver.cpp

cube_solver.o: cube_solver.h cube.h
	$(CXX) $(CXXFLAGS) -c cube_solver.cpp

cube_alg_search.o: cube_alg_search.h algs.h cube.h cubie.h
	$(CXX) $(CXXFLAGS) -c cube_alg_search.cpp

cube_printer.o: cube_printer.h cube.h cubie.h
	$(CXX) $(CXXFLAGS) -c cube_printer.cpp

cube.o: cube.h cubie.h
	$(CXX) $(CXXFLAGS) -c cube.cpp

algs.o: algs.h
	$(CXX) $(CXXFLAGS) -c algs.cpp

cubie.o: cubie.h
	$(CXX) $(CXXFLAGS) -c cubie.cpp
