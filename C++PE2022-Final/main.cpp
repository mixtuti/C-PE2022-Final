//
//  main.cpp
//  C++PE2022-Final
//
//  Created by hw20a086 on 2022/12/16.
//

//#include <iostream>
#include "Game.hpp"

int main() {
    Game game;
    
    bool isGameReady = game.Initialize();
    
    // ゲームが起動できた時の処理
    if(isGameReady == true){
        game.StartGame();
    }
    // ゲームを終了
    game.Shutdown();
    
    return 0;
}
