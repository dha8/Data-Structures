#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

// read file, rotate img 180 degrees, write rotated img as outfile
void rotate(std::string inputFile, std::string outputFile) {

    // read new img
    PNG * origImg = new PNG();
    origImg->readFromFile(inputFile);
    int width = origImg->width();
    int height = origImg->height();

    // make output img
    PNG * outImg = new PNG(width,height); 

    // rotate img
    for(int row=0;row<height;++row){
        for(int col=0;col<width;++col){
            *(outImg->getPixel(width-col-1,height-row-1))
                =*(origImg->getPixel(col,row));
        }
    }

    // make output img
    outImg->writeToFile(outputFile);
    
/*
    // free assigned memory
    for(int y=0;y<height;++y){
        for(int x=0;x<width;++x){
           delete(origImg->getPixel(x,y));
           delete(outImg->getPixel(x,y));
        }
    }
    delete(origImg);
    delete(outImg);
*/
}
