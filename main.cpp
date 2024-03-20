#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int SCREEN_WIDTH = 861;
const int SCREEN_HEIGHT = 517;
const char* WINDOW_TITLE = "SDL_GuessIt";

int generateRandomNum();
int guessInput();
void displayStatus(int guess, int secretNum, int guessCount);
void playAgame();

void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* tex);
void waitUntilKeyPressed();
SDL_Surface* loadMedia(const char* path);
void drawSomething(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc,char** argv)
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* render = createRenderer(window);
    SDL_Surface* background = SDL_GetWindowSurface(window);
    SDL_Surface* tex = loadMedia("images/game.bmp");
    SDL_BlitSurface(tex, NULL, background, NULL);
    SDL_UpdateWindowSurface(window);
    srand(time(0));
    //playAgame();
    waitUntilKeyPressed();
    quitSDL(window, render, tex);
    return 0;
}




int guessInput()
{
    int input;
    cout << "Guess a number (1..100) !\n";
    while (!(cin >> input))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input; please re-enter.\n";
    }
    return input;
}


void displayStatus(int guess, int secretNum, int guessCount)
{
    if(guess == secretNum)
        cout << "Correct!\n" << (100 - guessCount);
    else if (guess < secretNum)
        cout << "Too small!\n";
    else
        cout << "Too big!\n";
}

int generateRandomNum()
{
   int random = rand() % 100;
   return random + 1;
}

void playAgame()
{
    int secretNum = generateRandomNum();
    int guessCount = 0;
    bool correct;
    do{
        int guess = guessInput();
        correct = (guess == secretNum);
        guessCount++;
        displayStatus(guess, secretNum, guessCount);
    }while(!correct);
}

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* tex)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(tex);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void drawSomething(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}

SDL_Surface* loadMedia(const char* path)
{
    SDL_Surface* tex = SDL_LoadBMP(path);
    if (tex == nullptr) logErrorAndExit("Create texture", SDL_GetError());
    return tex;
}
