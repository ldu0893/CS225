#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base=new Image(picture);
    capacity=max;
}

StickerSheet::~StickerSheet() {
    delete base;
    sheet.clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    base=new Image(*other.base);
    sheet=other.sheet;
    capacity=other.capacity;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    delete base;
    base=new Image(*other.base);
    sheet=other.sheet;
    capacity=other.capacity;
    return other;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max<sheet.size()) {
        for (std::vector<Sticker>::iterator it=sheet.begin(); it!=sheet.end();) {
            if (it->index>=max) {
                it=sheet.erase(it);
            } else {
                it++;
            }
        }
    }
    capacity=max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (!checkCapacity()) return -1;
    unsigned index=0;
    for (int i=0; i<(int)sheet.size(); i++) {
        if (sheet[i].index==index) {
            index++;
        } else {
            sheet.insert(sheet.begin()+index, Sticker(index, x, y, &sticker));
            return index;
        }
    }
    sheet.push_back(Sticker(index, x, y, &sticker));
    return index;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    Sticker* s=findSticker(index);
    if (s==NULL) return false;
    s->x=x;
    s->y=y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    sheet.erase(sheet.begin()+index);
}

Image* StickerSheet::getSticker(unsigned index) {
    Sticker* s=findSticker(index);
    if (s!=NULL) return s->image;
    return NULL;
}

Image StickerSheet::render () const {
    Image out(*base);
    for (Sticker s : sheet) {
        Image* img=s.image;
        if (img->width()+s.x > out.width()) {
            out.resize(img->width()+s.x, out.height());
        }
        if (img->height()+s.y > out.height()) {
            out.resize(out.width(), img->height()+s.y);
        }
        for (unsigned i=0;i<img->width();i++) {
            for (unsigned j=0;j<img->height();j++) {
                cs225::HSLAPixel *p=&(img->getPixel(i,j));
                if (p->a!=0) out.getPixel(i+s.x, j+s.y)=*p;
            }
        }
    }
    return out;
}

StickerSheet::Sticker::Sticker(unsigned i, unsigned x, unsigned y, Image* im) {
    index=i;
    this->x=x;
    this->y=y;
    image=im;
}

bool StickerSheet::checkCapacity() {
    if (sheet.size()>=capacity) {
        std::cout << "No more capacity" << std::endl;
        return false;
    }
    return true;
}

StickerSheet::Sticker* StickerSheet::findSticker(unsigned index) {
    for (std::vector<Sticker>::iterator it=sheet.begin(); it!=sheet.end() && it->index<=index; it++) {
        if (it->index==index) return &(*it);
    }
    return NULL;
}