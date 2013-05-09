#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "puzzle_move.h"
using namespace std;

PuzzleMove::PuzzleMove(Board &b){
    _g=0;  //g value is null as this is the first board
    _tileMove=-1; 
    _b=&b; 
    _prev=NULL; //the first board is pointing to null
}

  // Constructor for subsequent search boards
  // (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent){

    _tileMove=tile;
    _b=b;
    _prev=parent; //points to the board passed
    _g=parent->_g + 1; //everytime this is called g value increseas

}

  // Compare to PuzzleMoves based on f distance
  //  (needed for priority queue maintainenance)
bool PuzzleMove::operator<(const PuzzleMove& p) const{
    if((_g+_h)==((p._h)+(p._g))) //if they are equal then it returns the one wiht the higher g value
        return (_g<p._g);
    else   //otherwise return which one is true
        return ((_g+_h)<((p._h)+(p._g)));
}

//greater then operator
bool PuzzleMove::operator>(const PuzzleMove& p) const{
    if((_g+_h)==((p._h)+(p._g)))//if they are equal then it returns the one wiht the higher g value
        return (_g<p._g);
    else   //otherwise return which one is true
        return ((_g+_h)>((p._h)+(p._g)));
}


void PuzzleMove::score(PuzzleHeuristic *ph){
//computes the heuristic score here 
_h=ph->compute(_b->getTiles(),_b->getSize());
}



