//
//  Star.hpp
//  PlatformGameDemo
//
//  Created by Kelvin Hu on 11/26/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Star_hpp
#define Star_hpp

#include <stdio.h>
#include "LTexture.hpp"

class Star : public LTexture {
    
public:
    int xPos;
    int yPos;
    int xSpeed;
    
    
    
    Star(int x, int y) : LTexture(1) {
        this->xPos = x;
        this->yPos = y;
        this->xSpeed = 10;
    }
    
    void move() {
        xPos -= xSpeed;
        angle += 1;
    }
    
    bool isOffScreen () {
        if (xPos <= -10) {
            return true;
        } else {
            return false;
        }
    }
    
    
    
};



#endif /* Star_hpp */
