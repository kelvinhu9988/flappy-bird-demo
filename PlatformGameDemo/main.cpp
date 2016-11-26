//
//  main.cpp
//  Super Mario Demo
//
//  Created by Kelvin Hu on 11/26/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Background.hpp"
#include "Star.hpp"
using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const int FRAMES_PER_SECOND = 60;
const Uint8 *KEYS = SDL_GetKeyboardState(NULL);
const string PATH_BACKGROUND = "/Users/Kelvin/Desktop/Game_Programming/PlatformGameDemo/PlatformGameDemo/scroll_background.png";
const string PATH_STAR = "/Users/Kelvin/Desktop/Game_Programming/PlatformGameDemo/PlatformGameDemo/star.png";
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 600

vector<Star*> stars;

bool init();
void enable2D(int width, int height);


int main(int argc, const char * argv[]) {
    
    
    Player p(WINDOW_WIDTH/10, WINDOW_HEIGHT/5, WINDOW_HEIGHT);
    Background b;
    

    
    if (!init())
    {
        printf("Failed to initialize!\n");
    } else
    {
        SDL_Event event;
        b.loadFromFile(PATH_BACKGROUND, renderer);
        bool done = false;
        int player_prev_ticks = 0;
        int frame_prev_ticks = 0;
        int framePlayer = 0;
        
        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                {
                    done = true;
                }
            }
            
            
            b.render(b.xPos, b.yPos, NULL, renderer);
            b.move();

            int current_ticks = SDL_GetTicks();
            int player_elapsed_ticks = current_ticks - player_prev_ticks;
            int frame_elapsed_ticks = current_ticks - frame_prev_ticks;
            frame_prev_ticks = SDL_GetTicks();
            
            if (player_elapsed_ticks > 125)
            {
                player_prev_ticks = current_ticks;
                framePlayer++;
                if (framePlayer >= 8)
                {
                    framePlayer = 0;
                }
            }

            
            p.loadTextures(renderer);
            p.playerTexture[framePlayer]->render(p.xPos, p.yPos, NULL, renderer);
            p.fall();
            
            if (KEYS[SDL_SCANCODE_SPACE]) {
                p.jump(WINDOW_HEIGHT);
            }
            
            if (KEYS[SDL_SCANCODE_LEFT]) {
                p.updateXPos(-1, WINDOW_WIDTH);
            }
            
            if (KEYS[SDL_SCANCODE_RIGHT]) {
                p.updateXPos(1, WINDOW_WIDTH);
            }
            
            if (rand() % 30 == 0 && stars.size() < 3)
            {
                int xPos = WINDOW_WIDTH;
                int yPos = (int) WINDOW_HEIGHT * (rand() / (float) RAND_MAX);
                Star *s = new Star(xPos, yPos);
                s->loadFromFile(PATH_STAR, renderer);
                stars.push_back(s);
            }
            
            for (vector<Star*>::iterator it = stars.begin(); it != stars.end();) {
                Star* s = *it;
                if (p.detectCollision(s->xPos, s->yPos, s->getTextureWidth(), s->getTextureHeight()))
                {
                    p.yPos = p.groundHeight;
                    stars.erase(it);
                }
                else if (s->isOffScreen())
                {
                    stars.erase(it);
                } else {
                    it++;
                }
            }
            
            for (Star* s : stars)
            {
                s->move();
                s->render(s->xPos, s->yPos, NULL, renderer);
            }
                        
            
            if (frame_elapsed_ticks < 1000 / FRAMES_PER_SECOND)
            {
                SDL_Delay((1000 / FRAMES_PER_SECOND) - frame_elapsed_ticks);
            }
            
            SDL_RenderPresent(renderer);

        }
        
    }
    


    
    return 0;
}


bool init()
{
    // Initialization flag
    bool success = true;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        
        // Create window
        window = SDL_CreateWindow("Kelvin's Platform Game Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else
        {
            // Create an OpenGL context for use with an OpenGL window
            SDL_GLContext context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, context);
            
            // Create vsynced renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else
            {
                
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void enable2D(int width, int height)
{
    // Set the viewport within the window in pixels
    glViewport(0, 0, width, height);
    
    // Specify which matrix stack is the target for subsequent matrix operations
    // GL_PROJECTION matrix defines the properties of camera that views the objects in the
    // world coordinate frame, which typically include the zoom factor, aspect ratio,
    // and the near and far clipping planes
    glMatrixMode(GL_PROJECTION);
    
    // Replace the current matrix with the identity matrix
    glLoadIdentity();
    
    // Multiply the current matrix (M) by an orthographic matrix (O),
    // so M is replaced by M • O
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    
    // GL_MODELVIEW matrix defines how objects are transformed, which typically
    // include translation, rotation and scaling in the world coordinate frame
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Specify clear values for the color buffers
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void close()
{
    
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    
    // Quit SDL environment
    IMG_Quit();
    SDL_Quit();
}

