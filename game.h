
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_WIDTH][BOARD_HEIGHT];
  Tetromino randomT[7] = {Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::S, Tetromino::Z, Tetromino::J, Tetromino::L};
  int tick;
  int lineCount;
  long long startTime;
  bool finish;
  Tetromino tetromino = Tetromino::I;
  Tetromino tetromino_next = Tetromino::I;
  int tetroPos[2] = { 0, };  //인덱스 0는 x축의 좌표, 인덱스 1은 y축의 좌표
  Tetromino RandTetromino(); //OOOOOOOOOOOOOOO
  std::string getElapsedTime();
  void NextTetromino(); //00000000000000000
  void stopTetromino(); //00000000000000000000000
  bool checkTetrominoPosition(Tetromino tetromino, int x, int y); //0000000000000000000000
  void pressKey(); //0000000000000000000000000
  void createTetromino(); //00000000000000000000000000
  bool Win(); //0000000000000000000000000000
  void Line(); //000000000000000000000000
  void printNextTetromino(); //00000000000000000000000000000
  void printWin(); //000000000000000000000000000
  void drawGround(); //00000000000000000000000000000000
  void drawNextBox(); //0000000000000000000000000000000000
  void drawHoldBox(); //0000000000000000000000000000000000


public:
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  Game();
};
#endif