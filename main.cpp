#include <SDL3/SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include "database/database.h"
#include <algorithm>
#include <thread>
#include "graphics/display.h"


// over arching architecture:
// tasks - > stored in database
// focus/time management 30-5 or 60-10 alarms (can be changed based on user input
// optionally alarms can be modified to change to a 2-30-2-5 or 2-60-2-10; providing 2 mins to note dump
// settings (font size color, account etc...) icon top right change action assignment
// on plus version AI is added and setting becomes
// swipe from left to right to progress task, swipe right to left to mark task complete
// triple dot : archive task, or pin task,
// top left filters : category based and/or tag based.

static void myprint(std::string sd) {
    std::cout << "Hello " << sd << "\n";
}

SDL_Window* applicationWindow = nullptr;
SDL_Renderer* graphicsRenderer = nullptr;
SDL_Texture* bitmapTexture = nullptr;
SDL_Surface* bitmapSurface = nullptr;
/*taskunit myButton(myprint, 0, 480);
taskunit myButton2(myprint, 1, 480);
taskunit myButton3(myprint, 2, 480);
taskunit myButton4(myprint, 3, 480);
taskunit myButton5(myprint, 4, 480);
taskunit myButton6(myprint, 5, 480);
taskunit myButton7(myprint, 6, 480);*/
//taskdisplay tdisplay("tasksdb.db");
TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
TTF_Font* font3 = nullptr;
SDL_FRect blankBox = {0, 0, 480, 30};

//circledraw myCircle(440, 680, 20, {0, 0, 0, 255});

//void processArguments(int argc, char* argv[]) {
//    // check for arguments and process them (not implemented yet)
//    return;
//}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    // logger logs errors.
    std::ofstream logger("calendar_logs.txt");
    SDL_Init(SDL_INIT_VIDEO);
    applicationWindow = SDL_CreateWindow("Calendar", 480, STARTING_WIN_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    graphicsRenderer = SDL_CreateRenderer(applicationWindow, NULL);
    bitmapSurface = SDL_LoadBMP("img/testing.bmp");
    bitmapTexture = SDL_CreateTextureFromSurface(graphicsRenderer, bitmapSurface);
    SDL_DestroySurface(bitmapSurface);

    TTF_Init();
    float fontSize = 36;
    float font2Size = 18;
    float scrollSpeed = 5;
    float font3Size = 10;
    //std::cin >> data;
    font = TTF_OpenFont("Times.ttf", fontSize); 
    font2 = TTF_OpenFont("Times.ttf", font2Size);
    font3 = TTF_OpenFont("Times.ttf", font3Size);
    SDL_Color fontColor = {255, 0, 0, 255};
    if (!font) {
        std::cout << SDL_GetError();
        return EXIT_FAILURE;
    }
    if (!font2) {
        std::cout << SDL_GetError();
        return EXIT_FAILURE;
    }

    bool closeApplication = false;

    if (applicationWindow == nullptr) {
        logger << "window creation failed (window == nullptr)\n";
        logger.close();
        return EXIT_FAILURE;
    }
    float texW = 10, texH = 10;
    //SDL_FRect texRect = { 8, 8, 0 , 0 };
    /*if (SDL_GetTextureSize(texture, &texW, &texH)) {
        texRect.h = texH;
        texRect.w = texW;
    }*/
    display myDisplay(graphicsRenderer, font, font2, font3);
    SDL_FRect mouse = {0, 0, 1, 1};
    SDL_FRect initMouse = { 0, 0, 1, 1 };
    std::string textdata = "hello! from here!";
    //uint32_t mouseClick = 0;
    const int holdNotClick = 150;
    bool heldToSwipe = false;

    while (!closeApplication) {
        auto start = std::chrono::steady_clock::now();
        std::chrono::microseconds oneTwentyHertz(8333);
        auto end = start + oneTwentyHertz;
        SDL_Event event;
        uint64_t buttonDownTimeStamp = 0;
        SDL_RenderClear(graphicsRenderer);
        myDisplay.draw();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_MOUSE_WHEEL:
                if (event.wheel.y > 0) {
                    myDisplay.scroll(scrollSpeed);
                }
                else {
                    myDisplay.scroll(-scrollSpeed);
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                SDL_GetMouseState(&mouse.x, &mouse.y);
                if (event.button.button == SDL_BUTTON_LMASK) {
                   if (!heldToSwipe){
                        //tdisplay.checkClick(&mouse);
                       myDisplay.checkClicks(&mouse);
                   }
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                SDL_GetMouseState(&initMouse.x, &initMouse.y);
                buttonDownTimeStamp = SDL_GetTicks();
                heldToSwipe = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                int w, h;
                if (SDL_GetWindowSize(applicationWindow, &w, &h)) {
                    //tdisplay.updateWindowSize(w, h);
                }
                break;
            case SDL_EVENT_QUIT:
                closeApplication = true;
                break;
            default:
                break;
            }
            if (event.button.button == SDL_BUTTON_LMASK) {
                if (!heldToSwipe) {
                    if (SDL_GetTicks() - buttonDownTimeStamp) {
                        heldToSwipe = true;
                    }
                }
                else {
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    //tdisplay.checkSwipe(&mouse, &initMouse);
                }
            }
        }
        SDL_RenderFillRect(graphicsRenderer, &blankBox);
        SDL_RenderPresent(graphicsRenderer);
        //auto end2 = std::chrono::steady_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start);
        //std::cout << duration.count() << "us\n";
        std::this_thread::sleep_until(end);
    }
    // delete SDL obejects
    SDL_DestroyTexture(bitmapTexture);
    SDL_DestroyRenderer(graphicsRenderer);
    SDL_DestroyWindow(applicationWindow);
    SDL_Quit();

    logger.close();
} // return 0 implied