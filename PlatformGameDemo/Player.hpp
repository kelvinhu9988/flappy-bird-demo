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
    
    Player(int xPos, int yPos, int screenHeight)
    {
        this->xPos = xPos;
        this->yPos = yPos;
        this->xSpeed = 5.0;
        this->fallSpeed = 2.5;
        this->jumpSpeed = 6.0;
        this->groundHeight = 0.6 * screenHeight;
    }
    
    
    ~Player()
    {
        for (LTexture* t: playerTexture)
        {
            delete t;
            t = nullptr;
        }
    }
    

    
    
    bool loadTextures(SDL_Renderer* renderer) {
        std::string fileBase = "/Users/Kelvin/Desktop/Game_Programming/HW6PlatformGameDemo/PlatformGameDemo";
        std::string fileEx = ".png";
        bool success = true;
        
        for (int i = 1; i <= 8; ++i)
        {
            std::string fileName;
            fileName = "" + fileBase;
            fileName += "/player/" + std::to_string(i) + fileEx;
            
            LTexture* newTexture = new LTexture(1);
            newTexture->loadFromFile(fileName, renderer);
            this->width = newTexture->getTextureWidth();
            this->height = newTexture->getTextureHeight();
            
            if (newTexture->getTexture() == NULL)
            {
                printf("Unable to create texture from %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError());
                success = false;
            } else
            {
                playerTexture.push_back(newTexture);
                
            }
            
        }
        return success;
    }
    
    void jump(int screenHeight)
    {
        if (yPos >= 0)
        {
            yPos -= jumpSpeed;
        }
    }
    
    void fall() {
        
        if (yPos <= groundHeight)
        {
            yPos += fallSpeed;
        }
    }
    
    void updateXPos(int xDir, int screenWidth)
    {
        
        if (xDir == 1) {
            if (xPos + width <= screenWidth)
            {
                xPos += xDir * xSpeed;
            }
        } else if (xDir == -1)
        {
            if (xPos >= 0)
            {
                xPos += xDir * xSpeed;
            }
        }
        
    }
    
    
    bool detectCollision(int _xPos, int _yPos, int _width, int _height)  {
        int lowerBound = _yPos;
        int upperBound = _yPos + _height;
        int leftBound  = _xPos;
        int rightBound = _xPos + _width;
        
        if (xPos + width > leftBound
            && xPos  < rightBound
            && yPos < upperBound
            && yPos + height > lowerBound) {
            return true;
        }
        return false;
    }
    
    
};








#endif /* Player_hpp */
