/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <queue>
#include <map>
#include <stack>

SquareMaze::SquareMaze() {
  width_ = 0;
  height_ = 0;
}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;
  for (int i = 0; i < width * height; i++) {
    walls_.push_back(std::make_pair<bool, bool>(true, true));
  }
  DisjointSets set;
  set.addelements(width_ * height_);
  //std::srand(std::time(0)); // use current time as seed for random generator
  int i = 0;
  while (i < width_ * height_ - 1) {
    int x = rand()%width_;
    int y = rand()%height_;
    int dir = rand()%2;
    if (dir == 0 && x != (width_ - 1) && walls_[y * width_ + x].first) {
      if (set.find(y * width_ + x) != set.find(y * width_ + x + 1)) {
        walls_[y * width_ + x].first = false;
        set.setunion(y * width_ + x, y * width_ + x + 1);
        i++;
      }
    }
    if (dir == 1 && y != (height_ - 1) && walls_[y * width_ + x].second) {
      if (set.find(y * width_ + x) != set.find((y + 1) * width_ + x)) {
        walls_[y * width_ + x].second = false;
        set.setunion(y * width_ + x, (y + 1) * width_ + x);
        i++;
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  if (dir == 0) {
    if (x + 1 < width_ && !(walls_[y * width_ + x].first)) {
      return true;
    } else {
      return false;
    }
  } else if (dir == 1) {
    if (!(walls_[y * width_ + x].second)) { //exit downside
      return true;
    } else {
      return false;
    }
  } else if (dir == 2) {
    if (x > 0 && !(walls_[y * width_ + x - 1].first)) {
      return true;
    } else {
      return false;
    }
  } else if (dir == 3) {
    if (y > 0 && !(walls_[(y - 1) * width_ + x].second)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return;
  }
  if (dir == 0 && x != (width_ - 1)) {
    walls_[y * width_ + x].first = exists;
  } else if (dir == 1 && y != (height_ - 1)) {
    walls_[y * width_ + x].second = exists;
  }
}

std::vector<int> SquareMaze::solveMaze() {
  std::vector<bool> visited;
  std::vector<int> p;
  std::vector<unsigned> d;

  for (int i = 0; i < width_ * height_; i++) {
    visited.push_back(false);
    p.push_back(0);
    d.push_back(0);
  }

  std::queue<int> q;
  visited[0] = true;
  d[0] = 0;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    int x = v % width_;
    int y = v / width_;
    if (canTravel(x, y, 0) && !(visited[v + 1])) {
      visited[v + 1] = true;
      p[v + 1] = v;
      q.push(v + 1);
      d[v + 1] = d[v] + 1;
    }
    if (canTravel(x, y, 1) && !(visited[v + width_])) {
      visited[v + width_] = true;
      p[v + width_] = v;
      q.push(v + width_);
      d[v + width_] = d[v] + 1;
    }
    if (canTravel(x, y, 2) && !(visited[v - 1])) {
      visited[v - 1] = true;
      p[v - 1] = v;
      q.push(v - 1);
      d[v - 1] = d[v] + 1;
    }
    if (canTravel(x, y, 3) && !(visited[v - width_])) {
      visited[v - width_] = true;
      p[v - width_] = v;
      q.push(v - width_);
      d[v - width_] = d[v] + 1;
    }
  }

  int dest = 0;
  for (int i = 1; i < width_; i++) {
    if (d[dest + width_ * (height_ - 1)] < d[i + width_ * (height_ - 1)]) {
      dest = i;
    }
  }

  std::vector<int> res;
  int parent = p[dest + width_ * (height_ - 1)];
  int current = dest + width_ * (height_ - 1);
  while (current != 0) {
    if (current - parent == 1) {
      res.insert(res.begin(), 0);
    } else if (current - parent == width_) {
      res.insert(res.begin(), 1);
    } else if (current - parent == -1) {
      res.insert(res.begin(), 2);
    } else {
      res.insert(res.begin(), 3);
    }
    current = parent;
    parent = p[current];
  }
  return res;
}

cs225::PNG * SquareMaze::drawMaze() const {
  cs225::PNG * res = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
  cs225::HSLAPixel b(0, 0, 0);

  for (int i = 10; i < (width_ * 10 + 1); i++) {
    cs225::HSLAPixel * pixel = res->getPixel(i, 0);
    *pixel = b;
  }
  for (int i = 0; i < (height_ * 10 + 1); i++) {
    cs225::HSLAPixel * pixel = res->getPixel(0, i);
    *pixel = b;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (walls_[y * height_ + x].first) {
        for (int k = 0; k < 11; k++) {
          cs225::HSLAPixel * pixel = res->getPixel((x + 1) * 10, y * 10 + k);
          *pixel = b;
        }
      }
      if (walls_[y * height_ + x].second) {
        for (int k = 0; k < 11; k++) {
          cs225::HSLAPixel * pixel = res->getPixel(x * 10 + k, (y + 1) * 10);
          *pixel = b;
        }
      }
    }
  }
  return res;
}

cs225::PNG * SquareMaze::drawMazeWithSolution() {
  cs225::PNG * res = drawMaze();
  std::vector<int> path = solveMaze();
  cs225::HSLAPixel r(0, 1, 0.5);

  cs225::HSLAPixel * pixel = res->getPixel(5, 5);
  *pixel = r;

  int x = 0;
  int y = 0;
  for (size_t i = 0; i < path.size(); i++) {
    if (path[i] == 0) {
      x++;
      for (int k = -5; k < 6; k++) {
        cs225::HSLAPixel * pixel = res->getPixel(x * 10 + k, y * 10 + 5);
        *pixel = r;
      }
    } else if (path[i] == 1) {
      y++;
      for (int k = -5; k < 6; k++) {
        cs225::HSLAPixel * pixel = res->getPixel(x * 10 + 5, y * 10 + k);
        *pixel = r;
      }
    } else if (path[i] == 2) {
      for (int k = -5; k < 6; k++) {
        cs225::HSLAPixel * pixel = res->getPixel(x * 10 + k, y * 10 + 5);
        *pixel = r;
      }
      x--;
    } else {
      for (int k = -5; k < 6; k++) {
        cs225::HSLAPixel * pixel = res->getPixel(x * 10 + 5, y * 10 + k);
        *pixel = r;
      }
      y--;
    }
}

  cs225::HSLAPixel w(0, 0, 1);
  for (int k = 1; k < 10; k++) {
    cs225::HSLAPixel * pixel = res->getPixel(x * 10 + k, (y + 1) * 10);
    *pixel = w;
  }

  return res;
}
