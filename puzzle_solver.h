#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"

using namespace std;

class PuzzleSolver
{
 public:
  typedef priority_queue<PuzzleMove*, vector<PuzzleMove*>, PuzzleMoveGreater > PuzzleMoveHeap;
  typedef set<Board *, BoardLessThan> BoardSet;

  // Constructor (makes a copy of the Board and stores it in _b
  PuzzleSolver(const Board &b);

  // Destructor
  ~PuzzleSolver(){;}

  // Run the A* search returning -1 if no solution exists or
  //  the number of moves in the solution
  int run(PuzzleHeuristic *ph);

  // Return the solution deque
  deque<int> getSolution();

  // Return how many expansions were performed in the search
  int getNumExpansions();
 private:
  Board _b;
  deque<int> _solution;
  int _expansions;
  //  PuzzleHeuristic *_ph;
};

#endif
