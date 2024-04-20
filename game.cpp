#include "game.h"
#include "tetromino.h"
#include "console/console.h"
#include<cstdlib>
#include<ctime>
#include <iostream>

using namespace std;

// 게임의 한 프레임을 처리한다.
void Game::update(){
  curtime=clock();
  min=curtime/60000;
  sec=curtime/1000;
  msec=curtime%100;

  moveTime--;
  if(moveTime==0){
    moveTime=DROP_DELAY;
    cur_y++;

    if(console::key(console::K_LEFT)){
      if(cur_x>1){
        cur_x--;
        shad_x--;
        shadow();
      }
    }
    if(console::key(console::K_RIGHT)){
      if(cur_x+t.size()-1<BOARD_WIDTH){
        cur_x++;
        shad_x++;
        shadow();
      }
    }
    if(console::key(console::K_UP))
      cur_y=BOARD_HEIGHT+1-t.size();
    if(console::key(console::K_DOWN))
      cur_y++;
    if(console::key(console::K_SPACE)){
      if(hold_t.size()==0){
        hold_t=*t.original();
        t=newtet();
        shadow();
        shad_t=t;
      }
      else{
        Tetromino tmp=t;
        t=hold_t;
        hold_t=tmp;
      }
    }
    if(console::key(console::K_X))
      t.rotatedCW();
    if(console::key(console::K_Z))
      t.rotatedCCW();
    if(console::key(console::K_NONE))
      moveTime=DROP_DELAY;

    if(cur_y+t.size()==BOARD_HEIGHT){//끝에 도착
      for(int y=cur_y; y<cur_y+t.size(); y++){
        for(int x=cur_x; x<cur_x+t.size(); x++){
          if(t.check(x,y))
            board[x][y]=true;
        }
      }
      t=next_t;
      initial();
    }

    for(int y=BOARD_HEIGHT,count=0; ;){//라인 지우기
      for(int x=1; x<=BOARD_WIDTH; x++){
        if(board[x][y])
          count++;
      }
      if(count==10){
        for(int y=BOARD_HEIGHT; y>=2; y--){
          for(int x=1; x<=BOARD_WIDTH; x++){
            board[x][y]=board[x][y-1];
          }
        }
        for(int x=1; x<=BOARD_WIDTH; x++)
          board[x][1]=false;  
        line--;          
      }
      else
        break;
      count=0;
    }
    shouldExit();
  }
}

// 게임 화면을 그린다.
void Game::draw(){
  console::drawBox(0,0,BOARD_WIDTH+1,BOARD_HEIGHT+1);
  console::drawBox(BOARD_WIDTH+3,0,BOARD_WIDTH+8,5);
  console::drawBox(BOARD_WIDTH+9,0,BOARD_WIDTH+14,5);
  console::draw(BOARD_WIDTH+4,0,"Next");
  console::draw(BOARD_WIDTH+10,0,"Hold");

  next_t.drawAt("■",BOARD_WIDTH+4,1);
  hold_t.drawAt("■",BOARD_WIDTH+10,1);

  t.drawAt("■",cur_x,cur_y);
  shad_t.drawAt("⛶",shad_x,shad_y);

  console::draw(0,BOARD_HEIGHT+2,std::to_string(line) + " lines left");
  console::draw(2,BOARD_HEIGHT+3,std::to_string(min)+":"+std::to_string(sec)+"."+std::to_string(msec));
}

// 게임 루프가 종료되어야 하는지 여부를 반환한다.
bool Game::shouldExit(){
  if(console::key(console::K_ESC) || line==0){
    console::draw(2,BOARD_HEIGHT/2,"You Lost");
    return true;
  }

  for (int x=1; x<=BOARD_WIDTH; x++){
    if(board[x][0]){
      console::draw(2,BOARD_HEIGHT/2,"You Lost");
      return true;
    }  
  }

  if(line==0){
    console::draw(3,BOARD_HEIGHT/2,"You Win");
     console::draw(2,BOARD_HEIGHT/2+1,std::to_string(min)+":"+std::to_string(sec)+"."+std::to_string(msec));
    return true;
  }

  return false;
}

//초기화
void Game::initial(){
  cur_x=BOARD_WIDTH/2-t.size()/2;
  cur_y=1;
  shad_x=cur_x;

  shadow();
  shad_t=t;

  next_t=newtet();
}

//테트로 생성
Tetromino Game::newtet(){
  int a=rand()%7;

  switch(a){
    case 0: return Tetromino::I;
    case 1: return Tetromino::J;
    case 2: return Tetromino::L;
    case 3: return Tetromino::O;
    case 4: return Tetromino::S;
    case 5: return Tetromino::T;
    case 6: return Tetromino::Z;
  }
}

void Game::shadow(){
  for(int y=cur_y,stop=0; y<=BOARD_HEIGHT+1; y++){
    for(int x=cur_x; x<cur_x+t.size(); x++){
      if(y==BOARD_HEIGHT+1 || board[x][y]){
        shad_y=y-t.size();
        stop++;
        break;
      }
    }
    if(stop==1)
      break;
  }
}

//생성자
Game::Game(){
  t=newtet();
  initial();
  line=LINES;

  srand((unsigned int)time(NULL));
  moveTime=DROP_DELAY;
}