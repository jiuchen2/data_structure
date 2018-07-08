/* Your code here! */
#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num) {
  if (num > 0) {
    data_.insert(data_.end(), num, -1);
  }
}

int DisjointSets::find(int elem) {
  if (data_[elem] < 0) {
    return elem;
  } else {
    return (data_[elem] = find(data_[elem]));
  }
}

void DisjointSets::setunion(int a, int b) {
  int root1 = find(a), root2 = find(b);

  int newSize = data_[root1] + data_[root2];

  if (data_[root1] <= data_[root2]) {
    data_[root2] = root1;
    data_[root1] = newSize;
  } else {
    data_[root1] = root2;
    data_[root2] = newSize;
  }

}
