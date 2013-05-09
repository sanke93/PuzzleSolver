#include <iostream>
#include <map>
#include <cmath>
#include<cstdlib>
#include <functional>
#include <iomanip>
#include "board.h"

using namespace std;

Board::Board(int size, int numInitMoves, int seed){

    srand(seed);//seeding
    _size=size;
    _tiles=new int[_size]; //dynamic allocation
    _tiles[0]=0; //empty one is denoted -2
    int temp;
    for(int i=1;i<_size;i++){  //initializes the tiles array
        _tiles[i]=i;
    }
    int num=0;
    int random;
    int rc=sqrt(_size);

    //runs as many times until the size of numInitMoves
    while(num<numInitMoves){

        for(int j=0;j<_size;j++){   //each time it enters a for loop to transverse thru the tilesand find the black tile
			if(_tiles[j]==0){
				random=rand()%4;
				//if blank tile found then create a random no between 0 and 4 depending on that perform the shuffle
				if(random==0){ //North /up
					if(j-rc>=0 && j-rc<_size){  //conditions to make sure that the move is valid and if its within the range of the array.
						temp=_tiles[j-rc]; //temp is used to help in shuffling
						_tiles[j-rc]=0;
						_tiles[j]=temp; //the move is given the empty tile and the empty tile gets the new location tile. 
					}
				}
				else if(random==2){ //south /down
					if(j+rc>=0 && j+rc<_size){ //conditions to make sure that the move is valid and if its within the range of the array.
						temp=_tiles[j+rc];
						_tiles[j+rc]=0;
						_tiles[j]=temp; //the move is given the empty tile and the empty tile gets the new location tile.
					}
				}
				else if(random==3){ //east /right
					//if statement here ensures that the tile doesn't move if its on the border
					if(j%rc==rc-1) {} 
					//conditions to make sure that the move is valid and if its within the range of the array.
					else if(j+1>=0 && j+1<_size){ 
						temp=_tiles[j+1];
						_tiles[j+1]=0;
						_tiles[j]=temp;  //the move is given the empty tile and the empty tile gets the new location tile.
					}
				}

				else if(random==1){  //west/left
				//if statement here ensures that the tile doesn't move if its on the border
					if(j%rc==0){} 
						//conditions to make sure that the move is valid and if its within the range of the array.

					else if(j-1>=0 && j-1<_size){
						temp=_tiles[j-1];
						_tiles[j-1]=0;
						_tiles[j]=temp; //the move is given the empty tile and the empty tile gets the new location tile.
					}
				}
			break;
			} //blank endings


		} //for endings

    num++;
    } //while endings
}

void Board::move(int tile){
    int empty,toMove;
	for(int i=0;i<_size;i++){ //transverse thru the tiles array

        if(_tiles[i]==0)  //if the tile is blank then the empty gets the tile number where the empty tile is
			empty=i;
        if(_tiles[i]==tile) //vice versa
			toMove=i;
    }
	_tiles[empty]=tile; //assign the appropriate tile value
	_tiles[toMove]=0;

}

Board::Board(const Board &b){
    _size=b._size; 
    _tiles=new int[_size]; //dynamic allocation
    for(int i =0;i<_size;i++){  //copies the tile. deep copy
		_tiles[i]=b._tiles[i];
	}

  // copy from rhs.dat to dat
}

Board::~Board(){
delete[] _tiles;
}
//computes the potential moves
void Board::potentialMoves(map<int, Board*> &moveMap){
    int rc=sqrt(_size);
    moveMap.clear();
	for(int j =0;j<_size;j++){ //this loop transverses and tries to find the blank tile.
	    //once found it tries to find the valid moves.
	    //if valid move is found then it goes and creates a new board object same as the current board,

        if(_tiles[j]==0){
                //top
                if(j-rc>=0 && j-rc<_size){
                    Board* b=new Board (*this); //creates a copy of the current board
                    b->move(_tiles[j-rc]); //performs the move on it 
                    moveMap[_tiles[j-rc]]=b;  //puts the moved board into a map
				}
                //south /down
                if(j+rc>=0 && j+rc<_size){
                    Board* b=new Board (*this); //creates a copy of the current board
                    b->move(_tiles[j+rc]); //performs the move on it 
                    moveMap[_tiles[j+rc]]=b; //puts the moved board into a map
                }
                //right
                if(j+1>=0 && j+1<_size && j%rc!=rc-1){
                    Board* b=new Board (*this); //creates a copy of the current board
                    b->move(_tiles[j+1]); //performs the move on it 
                    moveMap[_tiles[j+1]]=b;//puts the moved board into a map
                }
                //left
                if(j-1>=0 && j-1<_size && j%rc!=0){
                     Board* b=new Board (*this); //creates a copy of the current board
                     b->move(_tiles[j-1]);//performs the move on it 
                     moveMap[_tiles[j-1]]=b;//puts the moved board into a map
                }

            }
    }
}
bool Board::solved(){ //returns true if solved or returns false.
if(_tiles[0]!=0)
    return false;
for(int i=1;i<_size;i++){
    if(_tiles[i]!=i)
        return false;
    }
return true;
}

bool Board::operator==(const Board &rhs) const{
    for(int i=0;i<_size;i++){
        if(rhs._tiles[i]!=_tiles[i]){ //if any element is not equal then return false
            return false;
            }
		}
    return true;
}

bool Board::operator<(const Board& rhs) const{
    for(int i=0;i<_size;i++){
        if(_tiles[i]>rhs._tiles[i]){ //if an element is greater then return false
            return false;
            }
        if(_tiles[i]<rhs._tiles[i]){ //if any element is less then return true.
            return true;
            }
		}
    return false;
}
//returns tiles
int* Board::getTiles(){
    return _tiles;
}
//returns the size
  int Board::getSize(){
    return _size;
  }

//ostream operator
ostream& operator<<(ostream &os, const Board &b){

    int rc=sqrt(b._size);
    for(int i=0;i<b._size;i++){ //prints out the baord
        if(b._tiles[i]!=0){ //if its not zero then print out the tile and then a blank space
            os<<setw(3)<<b._tiles[i];
        }
        else //otherwise a two blank space
            os<<setw(3)<<"  "; //setw is used to make sure we get the appropriate spacing when its two digit number
        if(i%rc==rc-1) //if its ending then goto next line
            os<<endl;
    }
	


return os;
}
