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
using namespace std;


string fileBase = "/Users/Kelvin/Desktop/Game_Programming/PlatformGameDemo/PlatformGameDemo";
string fileEx = ".png";
vector<SDL_Texture*> playerTexture;


int main(int argc, const char * argv[]) {
   
    for (int i = 1; i <= 8; ++i)
    {
        string fileName;
        fileName = "" + fileBase;
        fileName = fileName + "/player/" + i + fileEx;
        
        
        // Finally, load the filename that we generated.
        healerTexture.push_back(IMG_LoadTexture(fileName.c_str()));
    }

    
    
    
    
    
    
    
    return 0;
}
