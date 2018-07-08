#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"

class StickerSheet{
public:
  StickerSheet(const Image &picture, unsigned max);
  StickerSheet(const StickerSheet &other);
  ~StickerSheet();
  const StickerSheet & operator=(const StickerSheet &other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image * getSticker(unsigned index) const;
  Image render() const;
private:
  Image* base_;
  unsigned max_;
  Image ** stickers_;
  unsigned * x_;
  unsigned * y_;
  void clear();
  void copy(const StickerSheet & other);

};

#endif
