/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pts;
    map<Point<3>, TileImage> map;
    for(unsigned i=0;i<theTiles.size();++i){   
        HSLAPixel avg = theTiles[i].getAverageColor();
        Point<3> temp;
        temp[0] = avg.h;
        temp[1] = avg.s;
        temp[2] = avg.l;
        map[temp] = theTiles[i];
        pts.push_back(temp);
    }
    KDTree<3> tree(pts);
    for(int i=0;i<theSource.getRows();i+=theTiles[0].getResolution()){   
        for(int j=0;j<theSource.getColumns();j+=theTiles[0].getResolution()){   
            HSLAPixel avg = theSource.getRegionColor(i,j); 
            Point<3> temp;
            temp[0] = avg.h;
            temp[1] = avg.s;
            temp[2] = avg.l;
            canvas->setTile(i,j,map[tree.findNearestNeighbor(temp)]);
        }
    }
    return canvas;
}

