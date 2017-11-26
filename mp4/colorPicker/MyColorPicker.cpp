#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  srand(time(NULL));
  double h = rand()/RAND_MAX * 360.0;
  double s = rand()/RAND_MAX;
  double l = rand()/RAND_MAX;
  double a = rand()/RAND_MAX;

  HSLAPixel rand(h,s,l,a);
  return HSLAPixel();
}
