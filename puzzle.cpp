#include <iostream>
#include <cstdlib>
#include "puzzle_heur.h"
#include "board.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

using namespace std;

int main(int argc, char *argv[])
{
    int tile; //tile to be moved
    if(argc < 4){ //to make sure user enters the correct number of arguments
    cout << "Usage: " << argv[0] << " size initMoves seed" << endl;
    return 1;
    }
    int size=atoi(argv[1]); //convert the command line argument into an integer
    PuzzleHeuristic *ph=new PuzzleHeuristic; //a new ph object
	int numInitMoves = atoi(argv[2]); //command line arguments
	int seedv=atoi(argv[3]); //gets the seed info
	Board b(size,numInitMoves,seedv); //Calls in the appropriate board constructor to allocate the board.
    cout<<b; //prints the shuffled board.

    int numsteps;
    while(!b.solved()){ //game runs until the program is solved.
        cout<<endl<<"Enter tile number to move or -1 for a cheat: ";
        cin>>tile;
        if(tile==-1){  //if -1 is entered then cheat is invoked.
            PuzzleSolver psobject(b); //passes the current board to a puzzlesolved object
            numsteps=psobject.run(ph); //calls the run function
            deque<int>solutions=psobject.getSolution(); //creates a new deque of solutions and then getSolution returns the solved deque.
            int sized=solutions.size(); //finds the size of the solution
            cout<<endl<<"Try this sequence: ";
            for(int i=1;i<sized;i++){  //prints out the solutions in the deque. the first one is ommited as its -1
                cout<<solutions[i]<<" ";
            }
            cout<<endl<<"(Expansions = "<<psobject.getNumExpansions()<<" )";  //gets the number of expansions
            cout<<endl<<endl;
        }
        else{ //if no cheat is entered then the entered tile is moved using the move function
        	b.move(tile);
        }
        cout<<b;
    }
    //puzzle is solved!
    cout<<endl<<"The puzzle is solved. You WIN!"<<endl<<endl;
    return 0;
}
