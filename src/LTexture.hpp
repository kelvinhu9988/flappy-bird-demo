//
//  LTexture.h
//  SpaceInvader
//
//  Created by Siyuan Hu on 10/14/16.
//  Copyright © 2016 Siyuan Hu. All rights reserved.
//

#ifndef LTexture_h
#define LTexture_h

#include <string>
#include <assert.h>
#include <iostream>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>



class LTexture {
public:
    
    float angle;
    
    LTexture(int nframes);
    
    ~LTexture();
    
    bool loadFromFile(std::string path, SDL_Renderer* renderer);
    void free();
   
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setRenderer(SDL_Renderer* renderer);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    
    void render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    int getTextureWidth();
    int getTextureHeight();
    SDL_Texture* getTexture();
    int getFrames();
    
private:
    SDL_Texture* texture;
    int textureWidth;
    int textureHeight;
    int nframes;
};




#endif /* LTexture_h */
