#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"

void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG png;
  
  png.readFromFile(inputFile);
  unsigned int w = png.width();
  unsigned int h = png.height();
  cs225::PNG result(w, h);
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      cs225::HSLAPixel *inPixel = png.getPixel(x, y);
      cs225::HSLAPixel *outPixel = result.getPixel(w - x - 1, h - y - 1);
      *outPixel = *inPixel;
      }
  }
  result.writeToFile(outputFile);
}
