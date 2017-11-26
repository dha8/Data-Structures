#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);

private:

};

#endif
