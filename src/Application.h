#pragma once
#include <SDL2/SDL.h>
#include <vector>


class Application
{
private:
    SDL_Event mEvent;
    SDL_Window* mWin = nullptr;
    SDL_Renderer* mRend = nullptr;
    bool mActive;
    unsigned int mLoopCount;
    unsigned int mTicksCount;
    
    std::vector< std::vector<int> > mLangtonMap;
    
    std::vector<class Ant> mAnts;
    
    // 描画
    void Draw();
    void Update();
public:
    Application();
    ~Application();
    
    void Execute();
};
