//
//  Player.hpp
//  PlatformGameDemo
//
//  Created by Kelvin Hu on 11/26/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include "LTexture.hpp"


class Player {
public:
    std::vector<LTexture*> playerTexture;
    int xPos, yPos;
    float xSpeed, fallSpeed, jumpSpeed;
    int width, height;
    int groundHeight;
  
    
    Player(int xPos, int yPos, int screenHeight);
    ~Player();
    bool loadTextures(SDL_Renderer* renderer);
    void jump(int screenHeight);
    void fall();
    void updateXPos(int xDir, int screenWidth);
    bool detectCollision(int _xPos, int _yPos, int _width, int _height);
};








#endif /* Player_hpp */
