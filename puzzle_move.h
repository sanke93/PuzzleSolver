#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "board.h"
#include "puzzle_heur.h"

using namespace std;

class PuzzleMove
{
 public:
  // Constructor for starting Board
  PuzzleMove(Board &b);

  // Constructor for subsequent search boards
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board *b, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove(){;}

  // Compare to PuzzleMoves based on f distance
  //  (needed for priority queue maintainenance)
  bool operator<(const PuzzleMove& p) const;
  bool operator>(const PuzzleMove& p) const;

  // Call ph->compute() on the board associated with this move
  // and storing the result in the _h value
  void score(PuzzleHeuristic *ph);

  // Data members can be public
 public:
  int _tileMove;  // tile moved to reach the Board b
  Board *_b;      // Pointer to a board representing the updated state
  int _g;         // distance from the start board
  int _h;         // heuristic distance to the goal
  PuzzleMove *_prev;  // Pointer to parent PuzzleMove
};


// Leave this alone and don't touch it!
struct PuzzleMoveGreater :
  public binary_function<const PuzzleMove*, const PuzzleMove*,bool>
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    return *m1 > *m2;
  }
};

#endif
