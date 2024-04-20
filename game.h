
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include <string.h>
#include <ctime>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  clock_t curtime;
  
  bool board[BOARD_WIDTH+2][BOARD_HEIGHT+2];
  int moveTime,cur_x,cur_y,shad_x,shad_y,min,sec,msec,line;
  Tetromino t=Tetromino("",0,"");
  Tetromino shad_t=Tetromino("",0,"");
  Tetromino next_t=Tetromino("",0,"");
  Tetromino hold_t=Tetromino("",0,"");

  void initial();
  void shadow();
  Tetromino newtet();

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