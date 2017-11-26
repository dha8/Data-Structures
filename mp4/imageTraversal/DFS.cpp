#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
    // initialize 2d arr to keep of visited coordinates
    bool ** visited = new bool*[png.width()];
    for(unsigned x=0;x<png.width();++x) visited[x] = new bool[png.height()];
    for(unsigned x=0;x<png.width();++x){
        for(unsigned y=0;y<png.height();++y){
            visited[x][y] = false;
        }
    }
    DFSHelper(png,start,start,tolerance,visited);
    // clean up memory after
    for(unsigned x=0;x<png.width();++x) delete[] visited[x];
    delete[] visited;
}

// helper fxn for DFS.
void DFS::DFSHelper(const PNG & png, const Point & curr, 
        const Point & start, double tolerance, bool ** visited){
    // base case : point is outside of the picture
    if(curr.x>=png.width() || curr.y>=png.height()) return;
    // base case : point has already been visited
    if(visited[curr.x][curr.y]==1) return;
    // base case : point outsideof tolerance
    double delta = calculateDelta
        (*(png.getPixel(start.x,start.y)),*(png.getPixel(curr.x,curr.y)));
    if(delta >= tolerance) return;
    // regular case : add points to the stack, and mark visited
    add(curr);
    visited[curr.x][curr.y] = true;

    // recursively add other points
    if(curr.y!=0) 
        DFSHelper(png, Point(curr.x,curr.y-1), start, tolerance, visited);
    if(curr.x!=0) 
        DFSHelper(png, Point(curr.x-1,curr.y), start, tolerance, visited);
    DFSHelper(png, Point(curr.x,curr.y+1), start, tolerance, visited);
    DFSHelper(png, Point(curr.x+1,curr.y), start, tolerance, visited);
}

double DFS::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
      double h = fabs(p1.h - p2.h);
      double s = p1.s - p2.s;
      double l = p1.l - p2.l;
      // Handle the case where we found the bigger angle between two hues:
      if (h > 180) { h = 360 - h; } 
      h /= 360;
      return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return Iterator(&(q.front()),&q);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
    return Iterator(NULL,&q);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
    q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
    Point p = q.front();
    q.pop();
    return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}
