// Rain Drop Simulation by Abthahi Ahmed Rifat

#include <iostream>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;
// Random number generator
float random(float low, float high){
	return low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX;
}
// Create a window
SDL_Window *win = SDL_CreateWindow("Rain Drop | Abthahi & Programming", 10,10,1000,600, 0);
// Create a renderer for window
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
// Event handler object
SDL_Event event;

// Drop Class
class Drop{
    
private:
    float x,y,g,ac;
    int a, w;
    
public:
    // Contructor for initialization
    Drop(float x, float y){
        
        this->x = x;
        this->y = y;
        
        this->g = 0;
        this->ac = random(0.08, 0.15);
        
        this->a = random(100, 255);
        this->w = random(2, 5);
        
    }
    // Update the data 
    void update(){
        
        this->y += this->g;
        
        this->g += this->ac;
        
    }
    // Draw the drop on screen
    void draw(){
        SDL_Rect rect = {(int)this->x, (int)this->y, this->w, 10};
        SDL_SetRenderDrawColor(ren, 255, 255, 255, this->a);
        SDL_RenderFillRect(ren, &rect);
    }
    
};
// Draw the cloud on screen
void drawCloud(SDL_Texture *texture, int x){
    SDL_Rect cloud_geometry = {x, -30, 150, 72};
    SDL_RenderCopy(ren, texture, NULL, &cloud_geometry);
}


int main(int argc, char *argv[]){
    // Seting Blendmode
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    
    bool isRunning = true;
    
    vector<Drop> drops;
    // Loading Cloud texture from PNG file
    SDL_Texture *cloud = IMG_LoadTexture(ren, "cloud.png");
    // Checking the texture
    if (!cloud){
        cout<<"Cloud Texture not loaded yet!!!"<<endl;
        exit(1);
    }
   // Main loop     
    while(isRunning){
	// Set Background Color
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);       
        // Draw the cloud
        for (int i = -1; i < 10; i++){
            drawCloud(cloud, i * 100);
        }
        
        

    
        // Draw & update every drops
        for(unsigned i = 0; i < drops.size(); i++){
            
            drops[i].update();
            drops[i].draw();
            
        }
        // Create new drops in every frame
        drops.push_back(Drop(random(0, 990), 30));
        
        // Handle the event
        if (SDL_PollEvent(&event)){
	    // Close the program if close button is pressed!!!
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }       
	// The Renderer
        SDL_RenderPresent(ren);
    }
    
    
    
        
    return 0;
}

// End
