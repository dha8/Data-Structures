#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"

class StickerSheet{

    private:
        Image ** images;
        Image * base;
        int * x;
        int * y;
        unsigned size;

    public:
        StickerSheet(const Image & picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet & other);
        const StickerSheet & operator=(const StickerSheet & other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image & sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index) const;
        Image render() const;

        //helper fxns
        void copy(const StickerSheet & other);
        void delete_();       

};

#endif
