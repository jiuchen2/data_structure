#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(PNG png);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  PNG png_;

};

#endif
