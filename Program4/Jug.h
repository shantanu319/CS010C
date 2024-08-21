#pragma once
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

const unsigned infinity = std::numeric_limits<unsigned>::max();

struct State
{
  int a; // Amount in jug A
  int b; // Amount in jug B

  // Where to go on each of the six actions
  unsigned fillA; // I would assume this is the adjancency list, ie if fill A is
  unsigned fillB;
  unsigned emptyA;
  unsigned emptyB;
  unsigned AtoB;
  unsigned BtoA;

  // These fields are useful when we do Dijkstra's method
  unsigned previous;
  unsigned distance;
  bool visited;

  State(unsigned a = infinity,
        unsigned b = infinity,
        unsigned fillA = infinity,
        unsigned fillB = infinity,
        unsigned emptyA = infinity,
        unsigned emptyB = infinity,
        unsigned AtoB = infinity,
        unsigned BtoA = infinity)
      : a(a),
        b(b),
        fillA(fillA),
        fillB(fillB),
        emptyA(emptyA),
        emptyB(emptyB),
        AtoB(AtoB),
        BtoA(BtoA),
        previous(infinity),
        distance(infinity),
        visited(false)
  {
  }
};

class Jug
{
public:
  Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
  
  // default destructor sufficient, no new pointers allocated
  Jug(const Jug&) = delete;
  Jug& operator=(const Jug&) = delete;

  // solve is used to check input and find the solution if one exists
  // returns -1 if invalid inputs. solution set to empty string.
  // returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
  // returns 1 if solution is found and stores solution steps in solution string.
  int solve(string &solution);

private:
  // anything else you need
  int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
  vector<State> graph;

  unsigned state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb);
  void dijkstraMethod(unsigned startNode);
};