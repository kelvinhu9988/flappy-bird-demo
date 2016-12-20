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
    
    
    Star(int x, int y);
    void move();
    bool isOffScreen ();
};



#endif /* Star_hpp */
