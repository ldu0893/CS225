<<<<<<< HEAD
/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;
    private:
        class Sticker {
            public:
                Sticker(unsigned i, unsigned x, unsigned y, Image* im);
                unsigned index;
                unsigned x;
                unsigned y;
                Image* image;
        };
        Image* base;
        unsigned capacity;
        std::vector<Sticker> sheet;
        bool checkCapacity();
        Sticker* findSticker(unsigned index);
};
=======
/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
>>>>>>> release/main
