#include <SDL3/SDL_video.h>
#include <fstream>



SDL_Window* applicationWindow = nullptr;
SDL_Renderer* graphicsRenderer = nullptr;
SDL_Texture* bitmapTexture = nullptr;
SDL_Surface* bitmapSurface = nullptr;

sdlInit(char* name, int width, int  length, SDL_WINDOW_FLAGS flags){
    SDL_Init(SDL_INIT_VIDEO);
    applicationWindow =  SDL_CreateWindow(name, width, length, flags);
    graphicsRenderer = SDL_CreateRenderer(applicationWindow, NULL);
    bitmapSurface = SDL_LoadBMP("img/hello.bmp");
    bitmapTexture = SDL_CreateTextureFromSurface(graphicsRenderer, bitmapSurface);
    SDL_DestroySurface(bitmapSurface);

}

void sdlClose(SDL_Window* &window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void processArguments(int argc, char* argv[]){
    // check for arguments and process them (not implemented yet)
    return;
}

int main(int argc, char* argv[]){
    
    // logger logs errors.
    ofstream logger("calendar_logs.txt");

    bool closeApplication = false;


    //possible names: techno calendar?
    SDL_Window* applicationWindow = sdlInit("Calendar", 1280, 720, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    
    if(window == nullptr){
        logger << "window creating failed (window == nullptr)\n";
        logger.close();
        return EXIT_FAILURE;
    }

    while(!closeApplication){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case event.type == SDL_EVENT_QUIT;
                    closeApplication = true;
                    //prepare for quititng the application.
                break;
                default:
                break;
            }
        }
    }
    

    logger.close();
} // return 0 implied
