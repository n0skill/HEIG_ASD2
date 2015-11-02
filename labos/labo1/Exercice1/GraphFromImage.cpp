#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
    
    
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    /* A IMPLEMENTER */
    
    
//     get_pixel(const unsigned int x, const unsigned int y,
//                         unsigned char& red,
//                         unsigned char& green,
//                         unsigned char& blue) const
    
    Iterable List;
    
    unsigned char red,
                  green,
                  blue,
                  redTmp,
                  greenTmp,
                  blueTmp;
    
     int x_, 
         y_,
         xTmp,
         yTmp;
     
    x_ = x(v);
    y_ = y(v);
    
    image.get_pixel(x_, y_, red, green, blue);
    
    // Je determine les voisin du sommet "V"
    const int xMin = 0,
              xMax = image.width(),
              yMin = 0,
              yMax = image.height();
    
    // Je determine le voisin de gauche
    if((x_ - 1)>= xMin && (x_ - 1) <= xMax )
    {
        xTmp = x_ - 1;
        yTmp = y_;
        image.get_pixel(xTmp, yTmp, redTmp, greenTmp, blueTmp);
        if( red == redTmp && green == greenTmp && blue == blueTmp)
            List.push_back(idx(xTmp, yTmp));
    }
    
    // Je determine le voisin de droite
    if((x_ + 1)>= xMin && (x_ + 1) <= xMax )
    {
        xTmp = x_ + 1;
        yTmp = y_;
        image.get_pixel(xTmp, yTmp, redTmp, greenTmp, blueTmp);
        if( red == redTmp && green == greenTmp && blue == blueTmp)
            List.push_back(idx(xTmp, yTmp));
        
    }
    
    // Je determine le voisin du dessous
    if((y_ - 1) >= yMin && (y_ - 1) <= yMax)
    {
        xTmp = x_ ;
        yTmp = y_ - 1;
        image.get_pixel(xTmp, yTmp, redTmp, greenTmp, blueTmp);
        if( red == redTmp && green == greenTmp && blue == blueTmp)
            List.push_back(idx(xTmp, yTmp));
    }
    
    // Je determine le voisin du dessus
    if((y_ + 1) >= yMin && (y_ + 1) <= yMax)
    {
        xTmp = x_;
        yTmp = y_ + 1;
        image.get_pixel(xTmp, yTmp, redTmp, greenTmp, blueTmp);
        if( red == redTmp && green == greenTmp && blue == blueTmp)
            List.push_back(idx(xTmp, yTmp));
    }
    
    return List;
}

int GraphFromImage::idx(int x, int y) const {
    /* A IMPLEMENTER */
    return(x + image.width()*y);
}

int GraphFromImage::x(int idx) const {
    /* A IMPLEMENTER */
    return(idx % image.width());
    
}

int GraphFromImage::y(int idx) const {
    /* A IMPLEMENTER */
    return(idx / image.width());
}

int GraphFromImage::V() const {
    /* A IMPLEMENTER */
    return image.pixel_count();
}
