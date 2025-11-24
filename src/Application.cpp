#include "Application.h"
#include "Ant.h"
#include <iostream>
#include <random>

const char* TITLE = "Langton";
const int GRID_SIZE = 5;
const int GRID_CNT_X  = 200;
const int GRID_CNT_Y  = 200;
const int SCREEN_H  = GRID_CNT_Y * GRID_SIZE;
const int SCREEN_W  = GRID_CNT_X * GRID_SIZE;
const int NUM_ANTS  = 20;

Application::Application()
: mActive(true)
{
    // SDL初期化
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL_Init(): " << SDL_GetError() << std::endl;
    }
        
    // ウインドウ生成
    mWin = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if(mWin == nullptr)
    {
        std::cout << "Can not create window" << std::endl;
        return;
    }
    // レンダラー生成
    mRend = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_ACCELERATED);
    if(mRend == nullptr)
    {
        std::cout << "Can not create renderer" << std::endl;
        return;
    }
    
    // 乱数をつかってCellを初期化
    std::random_device rd;  // 非決定的な乱数生成器
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,10);


    mLangtonMap.resize(GRID_CNT_Y);
    for (int i = 0; i < GRID_CNT_Y; i++)
    {
        mLangtonMap[i].resize(GRID_CNT_X);
        for (int j = 0; j < GRID_CNT_X; j++)
        {
            if (dist(gen) == 2)
            {
                mLangtonMap[i][j] = 0;
            }
            else
            {
                mLangtonMap[i][j] = 0;
            }
        }
    }
    
    
    
    int minX = GRID_CNT_X / 4;
    int maxX = GRID_CNT_X / 4 * 3;
    int minY = GRID_CNT_Y / 4;
    int maxY = GRID_CNT_Y / 4 * 3;
    std::uniform_int_distribution<int> distX(minX,maxX);
    std::uniform_int_distribution<int> distY(minY,maxY);
    std::uniform_int_distribution<int> distDir(0,3);
    
    for (int i = 0; i < NUM_ANTS; i++)
    {

        int x = distX(gen);
        int y = distY(gen);
        AntDir dir = (AntDir)distDir(gen);
        Ant a(x, y, dir);
        mAnts.push_back(a);
    }
    
}

Application::~Application()
{
    mLangtonMap.clear();
    mAnts.clear();
    
    // リリース処理
    if(mRend) SDL_DestroyRenderer(mRend);
    if(mWin) SDL_DestroyWindow(mWin);

    SDL_Quit();
}

// 描画
void Application::Draw()
{
    // FPS60固定
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    mTicksCount = SDL_GetTicks();
    // 背景クリア
    SDL_SetRenderDrawColor(mRend, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRend);

    
    for (int i = 0; i < GRID_CNT_Y; i++)
    {
        for (int j = 0; j < GRID_CNT_X; j++)
        {
            if (mLangtonMap[i][j] == 1)
            {
                SDL_SetRenderDrawColor(mRend, 255, 0, 0, 255);
                // 矩形
                SDL_Rect rect = { j*GRID_SIZE, i*GRID_SIZE, GRID_SIZE, GRID_SIZE };
                SDL_RenderFillRect(mRend, &rect);
            }
        }
    }
    
    for (auto a : mAnts)
    {
        int x = a.GetX();
        int y = a.GetY();
        // 矩形
        SDL_SetRenderDrawColor(mRend, 0, 255, 0, 255);
        SDL_Rect rect = { x*GRID_SIZE, y*GRID_SIZE, GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(mRend, &rect);
    }


    SDL_RenderPresent(mRend);

}

void Application::Update()
{
    for (int i = 0; i < NUM_ANTS; i++)
    {
        mAnts[i].Update(mLangtonMap);
    }

}

void Application::Execute()
{
    // メインループ
    while(mActive)
    {

        
        Update();
        // 画面描画
        Draw();
                
        // アプリ終了条件
        while(SDL_PollEvent(&mEvent))
        {
            switch(mEvent.type)
            {
                case SDL_KEYDOWN:
                    switch(mEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            mActive = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    mActive = false;
                    break;
                default:
                    break;
            }
        }
    }
}
