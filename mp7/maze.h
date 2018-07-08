/* Your code here! */
#ifndef MAZE_H
#define  MAZE_H

#include <vector>
#include "./cs225/PNG.h"

class SquareMaze {
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze();
  cs225::PNG * drawMaze() const;
  cs225::PNG * drawMazeWithSolution();
private:
  int width_;
  int height_;
  std::vector<std::pair<bool, bool>> walls_;
};



#endif
