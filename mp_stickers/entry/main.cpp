<<<<<<< HEAD
#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../field.png");
  Image i; i.readFromFile("../small.png");
  Image il; il.readFromFile("../tests/i.png");
  Image a; a.readFromFile("../altgeld.png");
  il.scale(0.1);
  i.scale(0.25);
  a.scale(0.25);
  StickerSheet sheet(alma, 5);
  sheet.addSticker(il, 420, 160);
  sheet.addSticker(i, 480, 200);
  sheet.addSticker(a, 900, 250);
  sheet.render().writeToFile("../myImage.png");
  return 0;
}
=======
#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
>>>>>>> release/main
