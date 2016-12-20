//
//  Star.cpp
//  PlatformGameDemo
//
//  Created by Kelvin Hu on 11/26/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "Star.hpp"

Star::Star(int x, int y) : LTexture(1) {
    this->xPos = x;
    this->yPos = y;
    this->xSpeed = 10;
}

void Star::move() {
    xPos -= xSpeed;
    angle += 1;
}

bool Star::isOffScreen () {
    if (xPos <= -10) {
        return true;
    } else {
        return false;
    }
}


