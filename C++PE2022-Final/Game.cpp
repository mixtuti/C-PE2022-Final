//
//  Game.cpp
//  C++PE2022-Final
//
//  Created by hw20a086 on 2022/12/16.
//

#include "Game.hpp"

#include <algorithm>
#include <sys/syslimits.h>
#include <filesystem>
#include <mach-o/dyld.h>

using namespace std;

Game::Game()
  : mRenderer(nullptr),
    mInputSystem(nullptr),
    mPhysWorld(nullptr),
    mAudioSystem(nullptr),
    mGameState(GamePlay),
    mUpdatingActors(false)
{
}

// ゲームの初期化処理
bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
        return false;
    }

    // 実行ファイルが置かれているディレクトリの絶対パスを取得する
    // ※ mac限定のAPIを利用
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0)
    {
        filesystem::path ps = path;
        mExecutableDirPath = ps.remove_filename();
    }
    else
    {
        SDL_Log("The absolute path of the executable file is too long.");
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

// ゲーム開始処理
void Game::StartGame()
{
    // 終了状態じゃ無い時に繰り返す
    while (mGameState != Quit)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

// ゲーム終了処理
void Game::Shutdown()
{
    UnloadData();

    SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::PushUI(UIScreen* screen)
{
    mUIStack.emplace_back(screen);
}

void Game::ProcessInput()
{
    
}

void Game::UpdateGame()
{
    // 前回のフレームから16ms経過するまで待機
    // つまり、目標のフレームレートは60FPS
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    // ゲームがポーズ中でなければシーン中のアクターの更新をする
    if (!(mGameState == Paused))
    {
        mUpdatingActors = true;
        
        mPendingActors.clear();

        std::vector<Actor*> deadActors;
        for (auto actor : mActors)
        {
            
        }

        for (auto actor : deadActors)
        {
            delete actor;
        }
    }

    // 閉じられたUIの破棄
    auto iter = mUIStack.begin();
}

void Game::GenerateOutput()
{
    
}

void Game::UnloadData()
{
    // 全アクターの破棄
    UnloadAllActors();

    // UIScreen はデストラクタで mUIStack から自分自身を取り除く処理を行わないので
    // このような形で削除を行う
    auto iter = mUIStack.begin();
    while (iter != mUIStack.end())
    {
        // イテレータが指す要素のオブジェクトを破棄
        delete *iter;
        // erase の戻り値は配列から除去した要素の次の要素を指すイテレータ!
        iter = mUIStack.erase(iter);
    }

    if (mRenderer)
    {
        
    }
}

void Game::UnloadAllActors()
{
    // デストラクタで mActors から自分自身を取り除く処理を行うので
    // このような形で削除を行う
    while (!mActors.empty())
    {
        delete mActors.back();
    }
}
