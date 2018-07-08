#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  location_ = Point();
  size_ = 0;
  v_ = new bool[size_];
  imagetraversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* trav) {
  /** @todo [Part 1] */
  imagetraversal_ = trav;
  size_ = trav->png_->width() * trav->png_->height();
  v_ = new bool[size_];
  for( unsigned i = 0; i < size_; ++i ){
    v_[ i ] = false;
  }
  location_ = trav->begin_;
  v_[trav->begin_.y * trav->png_->width() + trav->begin_.x] = true;
  trav->pop();
  Point nextPoint = location_;
  Point temp = Point(nextPoint.x + 1, nextPoint.y);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x, nextPoint.y + 1);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x - 1, nextPoint.y);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x, nextPoint.y - 1);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
}

ImageTraversal::Iterator::~Iterator() {
  delete[] v_;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned w = imagetraversal_->png_->width();
  v_[location_.y * w + location_.x] = true;
  Point nextPoint;
  bool visited = true;
  while (visited) {
    nextPoint = imagetraversal_->pop();
    visited = v_[nextPoint.y * w + nextPoint.x];
    if (nextPoint == imagetraversal_->begin_ && imagetraversal_->empty()) {
      location_ = Point();
      imagetraversal_ = NULL;
      return *this;
    }
  }
  location_ = nextPoint;
  Point temp = Point(nextPoint.x + 1, nextPoint.y);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x, nextPoint.y + 1);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x - 1, nextPoint.y);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }
  temp = Point(nextPoint.x, nextPoint.y - 1);
  if (imagetraversal_->checkTolerance(temp)) {
    imagetraversal_->add(temp);
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return location_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (location_ == other.location_ && imagetraversal_ == other.imagetraversal_) {
    return false;
  } else {
    return true;
  }
  /*
  bool res = true;
  for (unsigned i = 0; i < v_.size(); i++) {
    if (i >= other.v_.size() || !(v_[i] == other.v_[i])) {
      res = false;
      break;
    }
  }
  if (res) {
    return false;
  }*/
}

bool ImageTraversal::Iterator::checkAdd(Point p) {
  bool res = imagetraversal_->checkTolerance(p);
  return res;
}

bool ImageTraversal::checkTolerance(Point p) {
  if (p.x >= png_->width() || p.y >= png_->height()) {
    return false;
  }
  HSLAPixel * p1 = png_->getPixel(p.x, p.y);
  HSLAPixel * p2 = png_->getPixel(begin_.x, begin_.y);
  return (calculateDelta(*p1, *p2) < tolerance_);
}
