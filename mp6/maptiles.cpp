/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "point.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    map<Point<3>, size_t> colorToTile;
    vector<Point<3>> colors;
    for (size_t i = 0; i < theTiles.size(); i++) {
      HSLAPixel tileColor = theTiles[i].getAverageColor();
      //colorToTile[tileColor] = theTiles[i];//need modify
      Point<3> p(tileColor.h / 360, tileColor.s, tileColor.l);
      colors.push_back(p);
      colorToTile[p] = i;
    }
    KDTree<3> theColor(colors);
    MosaicCanvas* res = new MosaicCanvas(theSource.getRows(), theSource.getColumns(), &theTiles);
    for (int row = 0; row < theSource.getRows(); row++) {
      for (int col = 0; col < theSource.getColumns(); col++) {
        HSLAPixel oldColor(theSource.getRegionColor(row, col));
        Point<3> tmp(oldColor.h / 360, oldColor.s, oldColor.l);
        Point<3> newColor = theColor.findNearestNeighbor(tmp);
        size_t img = colorToTile[newColor];
        res->setTile(row, col, img);
      }
    }

    return res;
}
