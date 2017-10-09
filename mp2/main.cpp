#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image base;
  base.readFromFile("alma.png");
  Image pika1;
  pika1.readFromFile("pikachu.png");
  Image pika2;
  pika2.readFromFile("pikachu.png");
  StickerSheet sheit(base, 3);
  sheit.addSticker(pika1, 0,0);
  sheit.addSticker(pika2, 300,300);
  Image outcome = sheit.render();
  outcome.writeToFile("myImage.png");
  return 0;
}
