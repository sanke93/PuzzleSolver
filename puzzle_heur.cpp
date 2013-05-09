#include <iostream>
#include <cmath>
#include <cstdlib>
#include "puzzle_heur.h"
using namespace std;

int PuzzleHeuristic::compute(int *tiles, int size){
//finds the manhattan distance between the tiles
    int heur=0;
    int width=sqrt(size);
	int fx,fy,ix,iy,xd,yd;
    for(int i=0;i<size;i++){ //going thru the entire tile array
        if(tiles[i]!=i){ //tries to find if any tile is not in its place i.e if tile 1 is not at _tiles[1] then only it gives back true

                for(int k=0;k<size;k++){ //this for loop tries to find the tile no. that is
                    if(tiles[k]==i){ //tries to find the tile place where the number that doesn't match is located so this can be used to find the distance the tile is away from its original place.
                        iy=static_cast<int>(i/width); //y cor
                        ix=i-(iy*3); //x cor
                        fy=static_cast<int>(k/width); //y cordinate
                        fx=k-(fy*width); //x cor
                        xd=abs(fx-ix); //finds the abs value so we get a positive distance in x direction
                        yd=abs(fy-iy);//finds the abs value so we get a positive distance in y direction
                        heur+=xd+yd; //keeps adding them for every tile out of place
                    }
                }
        }

    }

return heur;
}
