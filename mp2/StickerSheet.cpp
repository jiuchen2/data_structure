#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  base_ = new Image(picture);
  max_ = max;
  stickers_ = new Image* [max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  for(unsigned i = 0; i < max_; i++){
    stickers_[i] = NULL;
    x_[i] = 0;
    y_[i] = 0;
  }
}

void StickerSheet::clear(){
  for(unsigned i = 0; i < max_; i++){
    if(stickers_[i] != NULL){
      delete stickers_[i];
      stickers_[i] = NULL;
    }
  }
  delete []stickers_;
  delete []x_;
  delete []y_;
  delete base_;
  stickers_ = NULL;
  x_ = NULL;
  y_ = NULL;
  base_ = NULL;
}

void StickerSheet::copy(const StickerSheet &other){
  base_ = new Image(*other.base_);
  max_ = other.max_;
  stickers_ = new Image* [max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  for(unsigned i = 0; i < max_; i++){
    if(other.stickers_[i] != NULL){
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
      stickers_[i] = new Image(*other.stickers_[i]);
    }
    else{
      x_[i] = 0;
      y_[i] = 0;
      stickers_[i] = NULL;
    }
  }
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}

StickerSheet::~StickerSheet(){
  clear();
}



const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
  if (this != &other) {
    clear();
    copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
  if (max == max_){
    return;
  }
  unsigned * newx = new unsigned[max];
  unsigned * newy = new unsigned[max];
  Image ** newstickers = new Image*[max];
  for (unsigned i = 0; i < max; i++) {
    if (i < max_) {
      if (stickers_[i] != NULL) {
        newx[i] = x_[i];
        newy[i] = y_[i];
        newstickers[i] = stickers_[i];
        //newstickers[i] = new Image(*stickers_[i]);
      }else{
        newx[i] = 0;
        newy[i] = 0;
        newstickers[i] = NULL;
      }
    }
    else{
      newx[i] = 0;
      newy[i] = 0;
      newstickers[i] = NULL;
    }
  }
  //Image * newbase = new Image(*base_);
  //clear();
  for(unsigned i = max; i < max_; i++){
    if (stickers_[i] != NULL){
      delete stickers_[i];
      stickers_[i] = NULL;
    }
  }
  delete []stickers_;
  delete []x_;
  delete []y_;

  //base_ = newbase;
  max_ = max;
  x_ = newx;
  y_ = newy;
  stickers_ = newstickers;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  for (unsigned i = 0; i < max_; i++){
    if (stickers_[i] == NULL) {
      stickers_[i] = new Image(sticker);
      x_[i] = x;
      y_[i] = y;
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index < max_ && stickers_[index] != NULL) {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker(unsigned index) {
  if (index < max_) {
    x_[index] = 0;
    y_[index] = 0;
    delete stickers_[index];
    stickers_[index] = NULL;
  }
}

Image * StickerSheet::getSticker(unsigned index) const {
  if (index < max_) {
    return stickers_[index];
  }
  return NULL;
}

Image StickerSheet::render() const {
  unsigned w = base_->width();
  unsigned h = base_->height();
  for (unsigned i = 0; i < max_; i++){
    if(stickers_[i] != NULL) {
      if ((x_[i] + stickers_[i]->width())> w) {
        w = x_[i] + stickers_[i]->width();
      }
      if ((y_[i] + stickers_[i]->height())> h) {
        h = y_[i] + stickers_[i]->height();
      }
    }
  }
  Image scene(*base_);
  scene.resize(w, h);
  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i] != NULL) {
      Image* s = stickers_[i];
      for (unsigned x = 0; x < s->width(); x++) {
        for (unsigned y = 0; y < s->height(); y++){
          cs225::HSLAPixel * data = s->getPixel(x, y);
          if (data->a != 0) {
            cs225::HSLAPixel * pixel = scene.getPixel(x_[i] + x, y_[i] + y);
            *pixel = *data;
          }
        }
      }
    }
  }
  return scene;
}
