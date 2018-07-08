/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 #include <iostream>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] != second[curDim]) {
      return first[curDim] < second[curDim];
    } else {
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curDis = 0;
    double potDis = 0;
    for (size_t i = 0; i < Dim; i++) {
      curDis += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potDis += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if (curDis < potDis) {
      return false;
    } else if (curDis > potDis) {
      return true;
    } else {
      return potential < currentBest;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    if (points.size() > 0) {
      buildTree(0, points.size() - 1, 0);
    }
}

template <int Dim>
unsigned KDTree<Dim>::partition(unsigned left, unsigned right, unsigned pIdx, int d) {
  Point<Dim> pValue = points[pIdx];
  std::swap(points[pIdx], points[right]);
  unsigned storeIndex = left;
  for (size_t i = left; i < right; i++) {
    if (smallerDimVal(points[i], pValue, d)) {
      std::swap(points[storeIndex], points[i]);
      storeIndex++;
    }
  }
  std::swap(points[storeIndex], points[right]);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::quickselect(unsigned left, unsigned right, unsigned k, int d) {
  if (left == right) {
    return;
  }
  unsigned pivotIndex = partition(left, right, (left + right) / 2, d);
  if (pivotIndex == k) {
    return;
  } else if (k < pivotIndex) {
    quickselect(left, pivotIndex - 1, k, d);
  } else {
    quickselect(pivotIndex + 1, right, k, d);
  }
}

template <int Dim>
void KDTree<Dim>::buildTree(unsigned left, unsigned right, int d) {
  if (left == right) {
    return;
  }
  unsigned mid = (left + right) / 2;
  quickselect(left, right, mid, d);
  if (left != mid) {
    buildTree(left, mid - 1, (d + 1) % Dim);
  }
  buildTree(mid + 1, right, (d + 1) % Dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if (points.size() == 0) {
      return Point<Dim>();
    } else {
      Point<Dim> res = points[0];
      double r = 0;
      unsigned left = 0;
      unsigned right = points.size() - 1;
      findHelper(query, res, r, left, right, 0);
      return res;
    }
}

template <int Dim>
void KDTree<Dim>::findHelper(const Point<Dim>& target, Point<Dim> & best, double & radius, unsigned left, unsigned right, int d) const {
  if (left == right) {
    if (shouldReplace(target, best, points[left])) {
      best = points[left];
      radius = getRadius(target, best);
    }
    return;
  }
  unsigned root = (left + right) / 2;
  if (smallerDimVal(target, points[root], d)) {
    if (left != root) {
      findHelper(target, best, radius, left, root - 1, (d + 1) % Dim);
    }
    if (shouldReplace(target, best, points[root])) {
      best = points[root];
      radius = getRadius(target, best);
    }
    int dis = (target[d] - points[root][d]) * (target[d] - points[root][d]);
    if (dis <= radius) {
      findHelper(target, best, radius, root + 1, right, (d + 1) % Dim);
    }
  } else {
    findHelper(target, best, radius, root + 1, right, (d + 1) % Dim);
    if (shouldReplace(target, best, points[root])) {
      best = points[root];
      radius = getRadius(target, best);
    }
    int dis = (target[d] - points[root][d]) * (target[d] - points[root][d]);
    if (dis <= radius) {
      if (left != root) {
        findHelper(target, best, radius, left, root - 1, (d + 1) % Dim);
      }
    }
  }
}

template <int Dim>
double KDTree<Dim>::getRadius(const Point<Dim> & a, const Point<Dim> & b) const {
  double radius = 0;
  for (int i = 0; i < Dim; i++) {
    radius += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return radius;
}
