#include "Image.h"
#include <iostream>

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->l+=amount;
            if (p->l > 1) p->l=1;
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->l-=amount;
            if (p->l < 0) p->l=0;
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->s+=amount;
            if (p->s > 1) p->s=1;
        }
    }
}

void Image::desaturate() {
    desaturate(-0.1);
}

void Image::desaturate(double amount) {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->s-=amount;
            if (p->s < 0) p->s=0;
        }
    }
}

void Image::grayscale() {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->s=0;
        }
    }
}

void Image::rotateColor(double degrees) {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            p->h=(p->h+degrees);
            while(p->h>360) p->h-=360;
            while(p->h<0) p->h+=360;
        }
    }
}

void Image::illinify() {
    unsigned int w = width();
    unsigned int h = height();
    unsigned int i, j;
    for (i=0;i<w;i++) {
        for (j=0;j<h;j++) {
            cs225::HSLAPixel* p=&getPixel(i, j);
            if (p->h > 293.5 || p->h < 113.5) {
                p->h = 11;
            } else {
                p->h = 216;
            }
        }
    }
}

void Image::scale(double factor) {
    scale(width()*factor, height()*factor);
}

void Image::scale(unsigned w, unsigned h) {
    unsigned int wp=width();
    unsigned int hp=height();
    double max=(double)w/(double)wp>(double)h/(double)hp?(double)h/(double)hp:(double)w/(double)wp;
    max>1.0?up(max):down(max);
    
}

void Image::up(double max) {
    unsigned int wp=width();
    unsigned int hp=height();
    resize(max*wp, max*hp);
    for (int i=wp-1;i>=0;i--) {
        for (int j=hp-1;j>=0;j--) {
            fill(&getPixel(i,j), i*max, j*max, max, max);
        }
    }
}

void Image::down(double max) {
    unsigned int wp=width();
    unsigned int hp=height();
    for (unsigned int i=0;i<wp;i++) {
        for (unsigned int j=0;j<hp;j++) {
            fill(&getPixel(i,j), i*max, j*max, max, max);
        }
    }
    resize(max*wp, max*hp);
}

void Image::fill(cs225::HSLAPixel* p, int a, int b, double w, double h) {
    for (unsigned i=a;i<a+w;i++) {
        for (unsigned j=b;j<b+h;j++) {
            getPixel(i,j)=*p;
        }
    }
}