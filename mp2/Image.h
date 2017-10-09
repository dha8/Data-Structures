#ifndef IMAGE_H
#define IMAGE_H

#include "cs225/PNG.h"

class Image : public cs225::PNG{
    
    public:

    // note: no-arg cstor is pointless, since it is automatically called
    // with parent's no-arg cstor first.
    

    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    // helper fxn for copying each values of pixel
    void copyPxl(Image * newImg, int x, int y, int orig_x, int orig_y);
    void scale(unsigned w, unsigned h);
};

#endif
