#include <SDL3/SDL.h>
#include <fstream>
#include <string>



SDL_Window* applicationWindow = nullptr;
SDL_Renderer* graphicsRenderer = nullptr;
SDL_Texture* bitmapTexture = nullptr;
SDL_Surface* bitmapSurface = nullptr;


void processArguments(int argc, char* argv[]){
    // check for arguments and process them (not implemented yet)
    return;
}

int main(int argc, char* argv[]){
    
    // logger logs errors.
    std::ofstream logger("calendar_logs.txt");
	
    SDL_Init(SDL_INIT_VIDEO);
    applicationWindow =  SDL_CreateWindow("Calendar", 1280, 720, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    graphicsRenderer = SDL_CreateRenderer(applicationWindow, NULL);
    bitmapSurface = SDL_LoadBMP("img/testing.bmp");
    bitmapTexture = SDL_CreateTextureFromSurface(graphicsRenderer, bitmapSurface);
    SDL_DestroySurface(bitmapSurface);

    bool closeApplication = false;
    
    if(applicationWindow == nullptr){
        logger << "window creating failed (window == nullptr)\n";
        logger.close();
        return EXIT_FAILURE;
    }

    while(!closeApplication){
        SDL_Event event;
        SDL_RenderClear(graphicsRenderer);
        SDL_RenderTexture(graphicsRenderer, bitmapTexture, NULL, NULL);
        
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_EVENT_QUIT:
                    closeApplication = true;
                    //prepare for quititng the application.
                break;
                default:
                break;
            }
        }
        SDL_RenderPresent(graphicsRenderer);
    }
    
    // delete SDL obejects
    SDL_DestroyTexture(bitmapTexture);
    SDL_DestroyRenderer(graphicsRenderer);
    SDL_DestroyWindow(applicationWindow);
    SDL_Quit();

    logger.close();
} // return 0 implied
