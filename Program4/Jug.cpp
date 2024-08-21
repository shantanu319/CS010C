#include "Jug.h"
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string> //need this for to_string since normal concatentation causing problems when trying to add the final distance

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) // constructor, takes in input, builds the graph
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{
  // need to build the graph, using the algorithm provided in the starter pack
  for (int a = 0; a <= Ca; ++a)
  {
    for (int b = 0; b <= Cb; ++b)
    {
      // Compute action fill A.  A will have Ca gallons. B unchanged
      // Compute action fill B.  A unchanged, B will have Cb gallons
      unsigned fillA = state_number(Ca, b, Ca, Cb);
      unsigned fillB = state_number(a, Cb, Ca, Cb);

      // For the empties... just set the appropriate amount to zero
      unsigned emptyA = state_number(0, b, Ca, Cb);
      unsigned emptyB = state_number(a, 0, Ca, Cb);

      // For the transfers, we can only pour in as much as we have
      // in the "from" jug OR as much room as we have in the "to" jug
      unsigned transferFromA = std::min(a, Cb - b);
      unsigned AtoB = state_number(a - transferFromA, b + transferFromA, Ca, Cb);
      unsigned transferFromB = std::min(b, Ca - a);
      unsigned BtoA = state_number(a + transferFromB, b - transferFromB, Ca, Cb);
 
      // Note: We can use emplace_back here (look it up!)
      graph.push_back(State(a, b, fillA, fillB, emptyA, emptyB, AtoB, BtoA));
    }
  }
}

unsigned Jug::state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb) // returns the state number, provided in starter pack
{
  // Simple error handling.  In the program you'll never be out of
  // bounds
  if (a > Ca or b > Cb)
  {
    throw std::runtime_error("domain error");
  }

  return a * (Cb + 1) + b;
}

int Jug::solve(string &solution) // input validation for the graph and also runs dijkstra's to find the solution
{
  solution = ""; //setting it to empty for test 5

  if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpBA < 0 || cpAB < 0) // input validation 1
  {
    throw runtime_error("Invalid input");
  }
  if (!((Ca > 0 && Ca <= Cb) && (Cb <= 1000 && N <= Cb))) // input validation 2
  {
    throw runtime_error("Invalid input");
  }
  if (graph.size() == 0)
  {
    throw runtime_error("Trying to search an empty graph");
  }


  // all distances are initialized to infinity when graph is being built, so no need for that step
  dijkstraMethod(0); //call private helper 

  if (graph[N].distance == infinity)
  {
    return 0;
  }

  unsigned currNode = N; // the target node that we work backards from
  while (currNode > 0) // gets most recent traversal, adds it to the solution string, then keeps moving backwards
  {
    // appending solution seemed to fix an error where it was printing in reverse
    if (currNode == graph[graph[currNode].previous].fillA)
    {solution = "fill A\n" + solution;}
    if (currNode == graph[graph[currNode].previous].fillB)
    {solution = "fill B\n" + solution;}
    if (currNode == graph[graph[currNode].previous].emptyA)
    {solution = "empty A\n" + solution;}
    if (currNode == graph[graph[currNode].previous].emptyB)
    {solution = "empty B\n" + solution;}
    if (currNode == graph[graph[currNode].previous].AtoB)
    {solution = "pour A B\n" + solution;}
    if (currNode == graph[graph[currNode].previous].BtoA)
    {solution = "pour B A\n" + solution;}
    currNode = graph[currNode].previous; //go to previous node (spot in vector<State> graph)
  }
  solution += "success " + to_string(graph[N].distance);

  return 1;
}

void Jug::dijkstraMethod(unsigned startNode) // run's dijkstra's method to find the smalles path
{

  // starting procedure, distance = 0 since this is the first node, prev = infinity (only for the very first case)
  if (startNode == 0)
  {
    graph[startNode].distance = 0;
    graph[startNode].previous = infinity;
  }

  graph[startNode].visited = true; //sets flag for node

  unsigned fillA = graph[startNode].fillA; // fill A state
  unsigned fillA_distance = graph[startNode].distance + cfA; // The distance there is our current distance PLUS the cost of doing a fillA
  if (fillA_distance < graph[fillA].distance) // comparing distance with saved one, updating distance and previous if its shorter
  {
    graph[fillA].distance = fillA_distance;
    graph[fillA].previous = startNode;
  }
  
  //above steps are repeated for all of the five actions, logic is the same
  //this chunk is for filling B
  unsigned fillB = graph[startNode].fillB;
  unsigned fillB_distance = graph[startNode].distance + cfB;
  if (fillB_distance < graph[fillB].distance)
  {
    graph[fillB].distance = fillB_distance;
    graph[fillB].previous = startNode;
  }

  //this chunk is for emptying A
  unsigned emptyA = graph[startNode].emptyA;
  unsigned emptyA_distance = graph[startNode].distance + ceA;
  if (emptyA_distance < graph[emptyA].distance)
  {
    graph[emptyA].distance = emptyA_distance;
    graph[emptyA].previous = startNode;
  }

  //this chunk is for emptying B
  unsigned emptyB = graph[startNode].emptyB;
  unsigned emptyB_distance = graph[startNode].distance + ceB;
  if (emptyB_distance < graph[emptyB].distance)
  {
    graph[emptyB].distance = emptyB_distance;
    graph[emptyB].previous = startNode;
  }

  // this chunk is for transferring from A to B
  unsigned AtoB = graph[startNode].AtoB;
  unsigned AtoB_distance = graph[startNode].distance + cpAB;
  if (AtoB_distance < graph[AtoB].distance)
  {
    graph[AtoB].distance = AtoB_distance;
    graph[AtoB].previous = startNode;
  }

  //final chunk for transferring from B to A
  unsigned BtoA = graph[startNode].BtoA;
  unsigned BtoA_distance = graph[startNode].distance + cpBA;
  if (BtoA_distance < graph[BtoA].distance)
  {
    graph[BtoA].distance = BtoA_distance ;
    graph[BtoA].previous = startNode;
  }

  unsigned distance = infinity;
  unsigned current = infinity;
  // To do one step of Dijkstra, we look for the node with the shortest distance that we have not yet visited, already started w/ 0,0 node
  // this moves it to next node in graph
  for (unsigned i = 0; i < graph.size(); ++i)
  {
    if (graph[i].distance < distance && !graph[i].visited)
    {
      distance = graph[i].distance;
      current = i;
    }
  }

  if (distance == infinity) // infinity check means all nodes have been visited
  {
    return;
  }

  dijkstraMethod(current); // recursive call to perform the starter packs dijkstra on the next node
}