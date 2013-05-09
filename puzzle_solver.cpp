#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "puzzle_solver.h"
using namespace std;

//constructor for the puzzle solved
PuzzleSolver::PuzzleSolver(const Board &b): _b(b){}


//run function which implements the a* alogrithm
int PuzzleSolver::run(PuzzleHeuristic *ph){

    PuzzleMoveHeap pq; //creates a priority queue - open list - heap
    BoardSet bs; //creates a boardset which is the closed list to put in the objects already explored
    map <int,Board*> pmoves; //map of board* which is used for potential moves
    PuzzleMove *pm=new PuzzleMove(_b); //creates a new puzzlemove pointer object using the current given board so that we can pass that to our priority queue
    pq.push(pm); //adds the pm to pq
    int runed=0;
    _expansions=0;

    while(!pq.empty()){ //runs until pq is empty
        PuzzleMove * pm=pq.top(); //removes the min f value state from the open list
        pm->_b->potentialMoves(pmoves); //perform potential moves
        bs.insert(pm->_b); //inserts the board into the boardset set
        pq.pop(); //pops the top of the pq as we dont need it anymore

		if(pm->_b->solved()){ //if a solution is found
			//if it is solved then it foes in here and tries to recontruct
			while(true){ //pushes each solution i.e tile move into the solution deque
				_solution.push_front(pm->_tileMove); //keep pusing the solution
				if(pm->_prev==NULL){ //if the prev pointer is null i.e if the original board that the function started with is found then break the function
					break; //break out so that we can move on as we got the soltuon
				}
				PuzzleMove *temp=new PuzzleMove(pm->_tileMove,pm->_b,pm); //creating a temporary pointer so we can equate it to pm, so that way we dont have to worry about deleting pm
				temp=pm;
				pm = temp->_prev; //helps in pointing to the parent. so this way we keep pointing each pm from where it came from and thus we can reconstruct
				delete temp; //dynamically allocated so we delete it once we used it.
				runed++;
			}
            break; //break out as we are done
        }
	//iterates over the pmoves board - for each successor
		for(map<int,Board*>::iterator it2 = pmoves.begin(); it2!= pmoves.end(); it2++){
			if( bs.find(it2->second) == bs.end()){ //tries to find if the board already exists in the boardset. it does thru using the end function of a map
				PuzzleMove * newmove = new PuzzleMove(it2->first, it2->second, pm); //dynamically alllocated
				newmove->score(ph); //perfroms the heuristics
				bs.insert(it2->second); //inserts new boards into the boardset
				pq.push(newmove); //moves the new moves the he priorty queue.
				_expansions++; //increment number of expansions

            }
        }



    }
//cleanup and return appropirate values
//deletes the open list.

    while(!pq.empty()){
		/*//tries to find if the board in the current pq.top exists in the boardset.
		//if it doesn't then we put the board that the pq is pointing at into the boardset so we
		get only ONE data structure that holds all the daata pointers and then way we can just delete the whole boardset.
		//This way we can ensure to only delete each value once and not try deleting twice which can be a probelm
		*/
		if( bs.find((pq.top())->_b) == bs.end()){
            bs.insert(pq.top()->_b);
		}
		//and then it pops out aftger putting it in the bs.
		//if the board isn't found in that would mean we dont have any problem with double deletion so we can just simply popp out.
    pq.pop();
    }
    bs.clear(); //tries to clean the boardset

    for (set<Board *, BoardLessThan>::iterator it = bs.begin(); it != bs.end(); it++) { //iterates over the boardset and tries to delete all its element
            delete *it;
    }

return runed; //returns the approiate value.
}


//returns the solution deque
deque<int> PuzzleSolver::getSolution(){
    return _solution;
}

  // Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions(){
    return _expansions;
}
