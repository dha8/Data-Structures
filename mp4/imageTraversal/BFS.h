#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  queue<Point> q;
  void BFSHelper(const PNG & png, const Point & curr, const Point & start,
         double tolerance, bool ** visited, queue<Point> & tempQueue);
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);
};

#endif
