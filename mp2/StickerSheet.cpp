#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    images = new Image*[max]; // initialize array of image ptrs
    base = new Image(picture);
    x = new int[max];
    y = new int[max];
    size = max;
    for(unsigned i=0;i<max;++i){
        images[i] = NULL;
        x[i] = 0;
        y[i] = 0;
    }
}

void StickerSheet::delete_(){
    /*
    for(unsigned i=0;i<size;++i){
        if(images[i] != NULL){
            delete images[i];
            images[i] = NULL;
        }
    }*/
    delete[] images;
    delete base;
    delete[] x;
    delete[] y;
    images = NULL;
    base = NULL;
    x = NULL;
    y = NULL;
    size = 0;
}

StickerSheet::~StickerSheet(){
    delete_();
}

void StickerSheet::copy(const StickerSheet & other){
    this->size = other.size;
    this->images = new Image*[size];
    x = new int[other.size];
    y = new int[other.size];
    for(unsigned i=0;i<size;++i){
        if(other.images[i]!=NULL)
            images[i] = new Image(*(other.images[i])); // changed here
        else images[i] = NULL;
        x[i] = other.x[i];
        y[i] = other.y[i];
    } 
    this->base = new Image(*(other.base));
}

StickerSheet::StickerSheet(const StickerSheet & other){
    copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    if(this != &other){ //prevent against self-assignment
        delete_();
        copy(other); 
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max == 0){
        delete_();
        return; 
    }
    if(max!=size){ // prevents against calling w/ same size
        Image ** new_images = new Image*[max]; //allocate new array of img ptrs
        int * new_x = new int[max];
        int * new_y = new int[max];
        for(unsigned i=0;i<max;++i){
            if(i<size){
                new_images[i] = images[i]; //img ptrs get copied over
                new_x[i] = x[i];
                new_y[i] = y[i];
            }
            else if(i>=size){
                new_images[i] = NULL;
                new_x[i] = 0;
                new_y[i] = 0; 
            }
        } 
        Image ** temp = images; // get ptr to orig. images
        images = new_images; // copy ptr over
        delete[] temp; // could be just delete. delete upper lvl ptr, not 
                       // img ptrs inside it
        int* temp_xy = x;
        x = new_x;
        delete[] temp_xy;
        temp_xy = y;
        y = new_y;
        delete[] temp_xy;
        size = max;
        
    }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
    for(unsigned i=0;i<size;++i){
        if(images[i] == NULL){
            images[i] = &sticker; 
            this->x[i] = x;
            this->y[i] = y;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if((index < size) && (images[index]!=NULL)){
        this->x[index] = x; 
        this->y[index] = y;
        return true;
    }
    return false; 
}

void StickerSheet::removeSticker(unsigned index){
    if((index < size) && (images[index]!=NULL)){ // prevent against IndexOutOfBoundsError
        // UNCOMMENT BELOW LINE TO FIX MMR LEAKAGE
       // delete images[index];
        images[index] = NULL;
        x[index] = 0;
        y[index] = 0;
    }
    return;
}

Image * StickerSheet::getSticker(unsigned index) const{
    if(index >= size) return NULL;
    return images[index];
}

Image StickerSheet::render() const{
    // find dimensions of the canvas
    unsigned w = 0;
    unsigned h = 0;
    for(unsigned i=0;i<size;++i){
        if(images[i] != NULL){
            w = (w < x[i]+(images[i]->width())) ? 
                    x[i]+images[i]->width() : w;
            h = (h < y[i]+(images[i]->height())) ? 
                    y[i]+images[i]->height() : h;
        }
    }
    w = (w < base->width()) ? base->width() : w;
    h = (h < base->height()) ? base->height() : h;
    //create new canvas
    Image background;
    background.resize(w,h);
    //draw base img
    for(unsigned x_=0;x_< base->width();++x_){
        for(unsigned y_=0;y_< base->height();++y_){
            background.getPixel(x_,y_)->h = base->getPixel(x_,y_)->h;
            background.getPixel(x_,y_)->s = base->getPixel(x_,y_)->s;
            background.getPixel(x_,y_)->l = base->getPixel(x_,y_)->l;
            background.getPixel(x_,y_)->a = base->getPixel(x_,y_)->a;
        }
    }
    //slap on those stickers
    for(unsigned i=0;i<size;++i){ //traversing through stickers
        if(images[i] != NULL){
            for(unsigned x_=x[i];x_<x[i]+images[i]->width();++x_){
                for(unsigned y_=y[i];y_<y[i]+images[i]->height();++y_){
                   // alpha check first
                   if(images[i]->getPixel(x_-x[i],y_-y[i])->a==0) continue;
                   background.getPixel(x_,y_)->h = 
                       images[i]->getPixel(x_-x[i],y_-y[i])->h;
                   background.getPixel(x_,y_)->s = 
                       images[i]->getPixel(x_-x[i],y_-y[i])->s;
                   background.getPixel(x_,y_)->l = 
                       images[i]->getPixel(x_-x[i],y_-y[i])->l;
                   background.getPixel(x_,y_)->a = 
                       images[i]->getPixel(x_-x[i],y_-y[i])->a;
                }
            }
        }
    }
    return background;
}

