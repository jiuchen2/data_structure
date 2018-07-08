#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

void Image::lighten(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double newl = pixel->l + 0.1;
      if (newl<=1){
        pixel->l = newl;
      }else
      {
        pixel->l = 1;
      }
    }
  }
}

void Image::lighten(double amount){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double newl = pixel->l + amount;
      if (newl<=1){
        pixel->l = newl;
      }else
      {
        pixel->l = 1;
      }
    }
  }
}

void Image::darken(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double newl = pixel->l - 0.1;
      if (newl>=0){
        pixel->l = newl;
      }else
      {
        pixel->l = 0;
      }
    }
  }
}

void Image::darken(double amount){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double newl = pixel->l - amount;
      if (newl>=0){
        pixel->l = newl;
      }else
      {
        pixel->l = 0;
      }
    }
  }
}

void Image::saturate(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double news = pixel->s + 0.1;
      if (news<=1){
        pixel->s = news;
      }else
      {
        pixel->s = 1;
      }
    }
  }
}

void Image::saturate(double amount){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double news = pixel->s + amount;
      if (news<=1){
        pixel->s = news;
      }else
      {
        pixel->s = 1;
      }
    }
  }
}

void Image::desaturate(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double news = pixel->s - 0.1;
      if (news>=0){
        pixel->s = news;
      }else
      {
        pixel->s = 0;
      }
    }
  }
}

void Image::desaturate (double amount){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double news = pixel->s - amount;
      if (news>=0){
        pixel->s = news;
      }else
      {
        pixel->s = 0;
      }
    }
  }
}

void Image::grayscale(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      pixel->s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      double newh = pixel->h + degrees;
      if (newh < 0){
        pixel->h = 360 + newh;
      }else if (newh > 360)
      {
        pixel->h = newh - 360;
      }else
      {
        pixel->h = newh;
      }
    }
  }
}

void Image::illinify(){
  unsigned int w = this->width();
  unsigned int h = this->height();
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel* pixel = this->getPixel(i, j);
      if (pixel->h >= 114 && pixel->h <= 293) {
      pixel->h = 216;
      }else
      {
      pixel->h = 11;
      }
    }
  }
}
void Image::scale(double factor){
  unsigned int w = this->width();
  unsigned int h = this->height();
  unsigned newWidth = static_cast<unsigned int>((double) this->width()*factor);
  unsigned newHeight = static_cast<unsigned int>((double)this->height()*factor);
  // Create a new vector to store the image data for the new (resized) image
  HSLAPixel *oldImageData = new HSLAPixel[(w* h)];
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel *pixel = this->getPixel(x, y);
      oldImageData[ (x + (y * w))] = *pixel;
    }
  }

  this->resize(newWidth, newHeight);
  for (unsigned x = 0; x < newWidth; x++) {
    for (unsigned y = 0; y < newHeight; y++) {
      unsigned int oldx = static_cast<unsigned int>(x/factor);
      unsigned int oldy = static_cast<unsigned int>(y/factor);
      HSLAPixel &oldPixel = oldImageData[(oldx + (oldy * w))];
      HSLAPixel *newPixel = this->getPixel(x, y);
      *newPixel = oldPixel;
    }
  }
  delete[] oldImageData;
}

void Image::scale(unsigned w, unsigned h){
  unsigned int w0 = this->width();
  unsigned int h0 = this->height();
  if ((double)w0/(double)h0 >= (double)w/(double)h) {
    scale((double)w/(double)w0);
  }else
  {
    scale((double)h/(double)h0);
  }
}
