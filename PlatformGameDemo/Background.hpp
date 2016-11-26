//
//  Background.hpp
//  PlatformGameDemo
//
//  Created by Kelvin Hu on 11/26/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include "LTexture.hpp"



class Background : public LTexture {
    
public:
    
    int xPos, yPos;
    float xSpeed;
    
    Background() : LTexture(1) {
        this->xPos = 0;
        this->yPos = 0;
        this->xSpeed = 5.0;
    }
    
    void move()
    {
        xPos -= xSpeed;
        
        if (xPos <= -getTextureWidth()/2)
        {
            xPos = 0;
        }
    }
    
    
    
};



#endif /* Background_hpp */
