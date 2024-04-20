#include "tetromino.h"
#include "console/console.h"

Tetromino Tetromino::I("I",4,"XXXXOOOOXXXXXXXX");
Tetromino Tetromino::J("J",3,"OXXOOOXXX");
Tetromino Tetromino::L("L",3,"XXOOOOXXX");
Tetromino Tetromino::O("O",2,"OOOO");
Tetromino Tetromino::S("S",3,"XOOOOXXXX");
Tetromino Tetromino::T("T",3,"XOXOOOXXX");
Tetromino Tetromino::Z("Z",3,"OOXXOOXXX");

Tetromino::Tetromino(std::string name, int size, std::string shape){
    this->name_=name;
    size_=size;
    original_=this;
    
    for(int i=0; i<shape.length(); i++){
        if(shape[i]=='O')
            shape_[i/size][i%size]=true;
    }
}

Tetromino Tetromino::rotatedCW(){//오른쪽X
    std::string rotCW="";

    for(int x=0; x<size_; x++){
        for (int y=size_-1; y>=0; y--)
            rotCW+=shape_[y][x] ? "O":"X";
    }

    Tetromino rottet(name_,size_,rotCW);
    rottet.original_=original_;
    
    return rottet;
}

Tetromino Tetromino::rotatedCCW(){//왼쪽Z
    std::string rotCW="";

    for(int x=size_-1; x>=0; x--){
        for (int y=0; y<size_; y++)
            rotCW+=shape_[y][x] ? "O":"X";
    }

    Tetromino rottet(name_,size_,rotCW);
    rottet.original_=original_;
    
    return rottet;
}
// 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
void Tetromino::drawAt(std::string s, int x, int y){
    for(int y1=0; y1<size_; y1++){
        for(int x1=0; x1<size_; x1++)
            if(check(x1,y1))
                console::draw(x+x1,y+y1,s);
    }
}
