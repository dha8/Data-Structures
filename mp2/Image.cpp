#include "Image.h"
using namespace cs225;

void Image::lighten(){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            cs225::HSLAPixel* curr = getPixel(x,y);
            curr->l+=0.1;
            if(curr->l > 1.0) curr->l = 1.0;
        }
    }
}

void Image::lighten(double amount){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            cs225::HSLAPixel* curr = getPixel(x,y);
            curr->l+=amount;
            if(curr->l > 1.0) curr->l = 1.0;
        }
    }
}

void Image::darken(){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->l-=0.1;
            if(curr->l < 0.0) curr->l = 0.0;
        }
    }
}

void Image::darken(double amount){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->l-=amount;
            if(curr->l < 0.0) curr->l = 0.0;
        }
    }
}

void Image::saturate(){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->s+=0.1;
            if(curr->s > 1.0) curr->s = 1.0;
        }
    }
}

void Image::saturate(double amount){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->s+=amount;
            if(curr->s > 1.0) curr->s = 1.0;
        }
    }
}

void Image::desaturate(){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->s-=0.1;
            if(curr->s < 0.0) curr->s = 0.0;
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->s-=amount;
            if(curr->s < 0.0) curr->s = 0.0;
        }
    }
}

void Image::grayscale(){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->s-=0;
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            HSLAPixel* curr = getPixel(x,y);
            curr->h += degrees;
            while(curr->h < 0 || curr->h > 360){
                if(curr->h < 0) curr->h += 360;
                if(curr->h > 360) curr->h -= 360;
            }
            // why doesn't this work?
            // curr->h = (double)(int(curr->h) % 360);
        }
    } 
}

void Image::illinify(){
    double temp;
    for(unsigned x=0;x<width();++x){
        for(unsigned y=0;y<height();++y){
            temp = getPixel(x,y)->h;
            getPixel(x,y)->h = (temp > 288 || temp < 114) ? 11 : 216;
        }
    }
}

void Image::scale(double factor){
    scale(width()*factor, height()*factor); 
}

void Image::copyPxl(Image * newImg, int x, int y, int orig_x, int orig_y){
    newImg->getPixel(x,y)->h = getPixel(orig_x,orig_y)->h;
    newImg->getPixel(x,y)->s = getPixel(orig_x,orig_y)->s;
    newImg->getPixel(x,y)->l = getPixel(orig_x,orig_y)->l;
    newImg->getPixel(x,y)->a = getPixel(orig_x,orig_y)->a;
}

void Image::scale(unsigned w, unsigned h){
    //create new Img
    Image newImg;
    newImg.resize(w,h);
    //traverse new Img, map each point back to orig. pxl. copy values.
    double w_ratio = double(width()) / newImg.width();
    double h_ratio = double(height()) / newImg.height();
    for(unsigned x=0;x<newImg.width();++x){
       for(unsigned y=0;y<newImg.height();++y){
           copyPxl(&newImg,x,y,int(x*w_ratio),int(y*h_ratio));
       }
    } 
    //copy over new one to original img
    *this = newImg;
}


