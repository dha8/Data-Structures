
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
    //initialize visited arr
    bool ** visited = new bool*[png.width()];
    for(unsigned x=0;x<png.width();++x) visited[x] = new bool[png.height()];
    for(unsigned x=0;x<png.width();++x){
        for(unsigned y=0;y<png.height();++y){
            visited[x][y] = false;
        }
    }

    queue<Point> tempQueue;
    tempQueue.push(start);
    visited[start.x][start.y]=true;

    while(!tempQueue.empty()){
        Point curr = tempQueue.front();
        tempQueue.pop();
        q.push(curr); // add to actual traversal queue

        // add neighbors
    BFSHelper(png,Point(curr.x+1,curr.y),start,tolerance,visited,tempQueue);
    BFSHelper(png,Point(curr.x,curr.y+1),start,tolerance,visited,tempQueue);
    BFSHelper(png,Point(curr.x-1,curr.y),start,tolerance,visited,tempQueue);
    BFSHelper(png,Point(curr.x,curr.y-1),start,tolerance,visited,tempQueue);
    }

    if(!tempQueue.empty()) cout << "BFS tempqueue not empty? wtf?" << endl;
    // clean up memory after
    for(unsigned x=0;x<png.width();++x) delete[] visited[x];
    delete[] visited;
}

//helper fxn for BFS.
void BFS::BFSHelper(const PNG & png, const Point & curr,const Point & start,
        double tolerance, bool ** visited, queue<Point> & tempQueue){
    // base case : point is outside of the picture
    if(curr.x>=png.width() || curr.y>=png.height()) return;
    // base case : point has already been visited
    if(visited[curr.x][curr.y]==1) return;
    // base case : point outside of tolereance
    double delta = calculateDelta
        (*(png.getPixel(start.x,start.y)),*(png.getPixel(curr.x,curr.y)));
    if(delta >= tolerance) return;

    // regular case : add point to the stack, and mark visited
    tempQueue.push(curr);
    visited[curr.x][curr.y]=true;
}

double BFS::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return Iterator(&(q.front()), &q);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return Iterator(NULL, &q);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  return q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
    Point p = q.front();
    q.pop();
    return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
    return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}
