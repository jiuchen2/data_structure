#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

int main() {
  Image totoro;
  totoro.readFromFile("totoro.png");

  Image neighbor;
  neighbor.readFromFile("MyNeighborTotoro.png");

  Image black;
  black.readFromFile("black.png");

  Image watercolor;
  watercolor.readFromFile("watercolor_totoro.png");

  StickerSheet sheet(watercolor, 5);
  sheet.addSticker(totoro, 220, 200);
  sheet.addSticker(black, 100, 500);
  sheet.addSticker(neighbor, 70, 600);

  sheet.changeMaxStickers(6);
  Image * black1 = sheet.getSticker(1);
  StickerSheet result(black, 2);
  result = sheet;
  result.removeSticker(0);
  Image * black2 = result.getSticker(1);
  result.changeMaxStickers(5);
  Image scene0(result.render());
  black1->writeToFile("black1.png");
  black2->writeToFile("black2.png");
  
  Image scene(sheet.render());
  scene.writeToFile("myImage.png");
  //scene0.writeToFile("test.png");

  return 0;
}
