#ifndef SWEEP_H_
#define SWEEP_H_

#include "src/solvers/block_diagonal/mcmath.h"
#include <math.h>
class Sweep
{
private: 
  int MZ;                                  // number of equations
  int NX;                                  // number of points in grid
  int BZ_I_DIM;
  int BZ_J_DIM; 

public:
  MCMatrix A;                 // Block matrices
  MCMatrix B;
  MCMatrix C;
  MCMatrix RightSide;
  double ** bz;                             // aux array
  double ** fz; 
  
  Sweep        ();                           // default constructor
  Sweep        (int PointNum, int EqNum);
  ~Sweep       ();

  void Initialize (int PointNum, int EqNum);
  virtual void Solve   (int, int, int );                               
  void construction_bz(int num_eq, int flag);
  virtual void construction_from_fz(int N, int m,int key) = 0;

  // array for results
private:
  virtual void LeftBoundAppr  (int,int) = 0;         // left boundary approximation
  virtual void MiddleAppr     (int, int,int) = 0;   // approximation in the middle node
  virtual void RightBoundAppr (int,int) = 0;        // right boundary approximation

private:
  Sweep(const Sweep&);
  //void operator=(const Sweep&);
  
protected:
  void Clear ();

};

#endif /* SWEEP_H_ */



