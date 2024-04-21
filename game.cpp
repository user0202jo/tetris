#include "game.h"
#include "console/console.h"

#include <random>
#include <chrono>
using namespace std::chrono;

Tetromino Game::RandTetromino() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 6);
    return randomT[dis(gen)];
}

Game::Game() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            board_[i][j] = false;
        }
    }
    tick = 0;
    lineCount = LINES;

    tetromino = Game::RandTetromino();
    tetromino_next = Game::RandTetromino();
    tetroPos[0] = (BOARD_WIDTH/2-tetromino.size()/2)+1;
    tetroPos[1] = 1;
    startTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Game::NextTetromino() {
    tetromino = tetromino_next;
    tetromino_next = Game::RandTetromino();
    tetroPos[0] = (BOARD_WIDTH/2-tetromino.size()/2)+1;
    tetroPos[1] = 1;
}


bool Game::checkTetrominoPosition(Tetromino tetromino, int x, int y) {
    for(int i = 0; i < tetromino.size(); i++) {
        for(int j = 0; j < tetromino.size(); j++) {
            if(!(x+i >= 1 && x+i <= BOARD_WIDTH && y+j >= 1 && y+j <= BOARD_HEIGHT) && tetromino.check(x,y)) {
                return false;
            }
        }
    }
    return true;
}

void Game::pressKey() {
    if(console::key(console::K_LEFT)) {
        if(Game::checkTetrominoPosition(tetromino, tetroPos[0]-1, tetroPos[1])) {
            tetroPos[0]--;
        }
    } 
    else if(console::key(console::K_RIGHT)) {
        if(Game::checkTetrominoPosition(tetromino, tetroPos[0]+1, tetroPos[1])) {
            tetroPos[0]++;
        }
    } 
    else if(console::key(console::K_DOWN)) {
        if(Game::checkTetrominoPosition(tetromino, tetroPos[0], tetroPos[1]+1)) {
            tetroPos[1]++;
        }
    } 
    else if(console::key(console::K_Z)) {
        Tetromino tmp = tetromino.rotatedCCW();
        if(Game::checkTetrominoPosition(tmp, tetroPos[0], tetroPos[1])) {
            tetromino = tmp;
        }
    } 
    else if(console::key(console::K_X)) {
        Tetromino tmp = tetromino.rotatedCW();
        if(Game::checkTetrominoPosition(tmp, tetroPos[0], tetroPos[1])) {
            tetromino = tmp;
        }
    }
    else if(console::key(console::K_ESC)) {
        finish = true;
    }
}

void Game::Line() {
    std::string result = std::to_string(lineCount) + " lines left";
    console::draw(0, BOARD_HEIGHT+2, result);
}

void Game::createTetromino() {
    tetromino.drawAt(BLOCK_STRING, tetroPos[0], tetroPos[1]);
}

void Game::FinishedTetromino() {
    for(int i = 0; i < tetromino.size(); i++) {
        for(int j = 0; j < tetromino.size(); j++) {
            if(tetromino.check(i, j)) {
                board_[tetroPos[0]+i-1][tetroPos[1]+j-1] = true;
            }
        }
    }
}

void Game::RemoveLine(int y) {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        if(!board_[i][y]) {
            return;
        }
    }

    for(int i = y; i > 0; i--) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            board_[j][i] = board_[j][i-1];
        }
    }
    for(int i = 0; i < BOARD_WIDTH; i++) {
        board_[i][0] = false;
    }
    lineCount--;
}

void Game::printNextTetromino() {
    int nextBoxPos = (BOARD_WIDTH+1)+3;
    int boxSize = 5;
    if(tetromino_next.name().compare("I") == 0){
        tetromino_next.drawAt(BLOCK_STRING, (nextBoxPos + (boxSize-tetromino_next.size())/2), 1);
    }

    else{
        tetromino_next.drawAt(BLOCK_STRING, (nextBoxPos + (boxSize-tetromino_next.size())/2), 2);
    }
    
}

void Game::stopTetromino() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            if(board_[i][j]) {
                console::draw(i+1, j+1, BLOCK_STRING);
            }
        }
    }
}

bool Game::Win(){
    if(lineCount == 0){
        return true;
    }

    else{
        return false;
    }
}

void Game::printWin() {
    std::string message = "You Win";
    console::draw(BOARD_WIDTH/2-message.length()/2+1, BOARD_HEIGHT/2, message);
}

void Game::drawGround() {
    console::drawBox(0, 0, BOARD_WIDTH+1, BOARD_HEIGHT+1);
}

void Game::drawNextBox() {
    int startPosX = (BOARD_WIDTH+1)+2;
    int startPosY = 0;
    int boxSize = 5;
    console::drawBox(startPosX, startPosY, startPosX+boxSize, startPosY+boxSize);
    console::draw(startPosX+1, startPosY, "Next");
}

void Game::drawHoldBox() {
    int startPosX = ((BOARD_WIDTH+1)+2+5)+1;
    int startPosY = 0;
    int boxSize = 5;
    console::drawBox(startPosX, startPosY, startPosX+boxSize, startPosY+boxSize);
    console::draw(startPosX+1, startPosY, "Hold");
}

void Game::draw() {
    Game::drawGround();
    Game::drawNextBox();
    Game::drawHoldBox();
}

void Game::update() {
    Game::Line();
    Game::createTetromino();
    Game::printNextTetromino();
    Game::stopTetromino();

    if(Game::Win()) {
        Game::printWin();
        Game::Line();
        finish = true;
    }

    Game::pressKey();
}

bool Game::shouldExit(){
    return finish;
}