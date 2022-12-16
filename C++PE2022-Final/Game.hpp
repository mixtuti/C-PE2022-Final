//
//  Game.hpp
//  C++PE2022-Final
//
//  Created by hw20a086 on 2022/12/16.
//

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef Game_h
#define Game_h

using namespace std;

class Game{
public:
    Game();
    bool Initialize();
    void StartGame();
    void Shutdown();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    class Renderer* GetRenderer() const { return mRenderer; }
    class PhysWorld* GetPhysWorld() const { return mPhysWorld; }
    class AudioSystem* GetAudioSystem() const { return mAudioSystem; }
    
    // ゲームの状態リスト
    enum GameState
    {
        TitleScene, // タイトル
        GamePlay, // プレイ画面
        Paused, // ポーズ画面
        ResultScene, // リザルト画面
        Quit, // 終了画面
    };
    
    GameState GetState() const { return mGameState; }
    void SetState(GameState state) { mGameState = state; }

    // モードの状態リスト
    enum InputMode
    {
        GamePlaying,
        UIWindow,
    };

    void SetInputMode(InputMode inputMode) { mInputMode = inputMode; }

    class Font* GetFont(const string& fileName);
    const vector<class UIScreen*>& GetUIStack() { return mUIStack; }
    void PushUI(class UIScreen* screen);

    // アクターを全部破棄する
    void UnloadAllActors();

    const string& GetExecutableDirPath () const { return mExecutableDirPath; }

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // ゲームのリソースのアンロードを行う
    // ゲームを終了する前に呼ぶ
    void UnloadData();

    vector<class Actor*> mActors;
    vector<class Actor*> mPendingActors;

    class Renderer* mRenderer;
    class InputSystem* mInputSystem;
    class PhysWorld* mPhysWorld;
    class AudioSystem* mAudioSystem;

    Uint32 mTicksCount;
    GameState mGameState;
    bool mUpdatingActors;
    InputMode mInputMode;
    // 実行ファイルが属するディレクトリ
    string mExecutableDirPath;

    unordered_map<string, class Font*> mFonts;
    vector<class UIScreen*> mUIStack;
};

#endif /* Game_h */
