#include <iostream>
#include <cassert>
#include "SCCSolver.h"

int main() {
    SCCSolver* sccSolver = new SCCSolver();

    int const n = 8;

    std::vector<int>* adjList = new std::vector<int>[n];

    // First Graph
    adjList[0] = {4, 1}; // Node 0
    adjList[1] = {3, 2}; // Node 1
    adjList[2] = {1};    // Node 2
    adjList[3] = {3};    // Node 3
    adjList[4] = {0, 3}; // Node 4
    adjList[5] = {6, 2}; // Node 5
    adjList[6] = {2, 7}; // Node 6
    adjList[7] = {5};    // Node 7

    sccSolver->initialize(adjList, n);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 4);


    // Second Graph
    for (int i = 0; i < n; ++i) {
        adjList[i].clear();
    }

    adjList[0] = {5, 1}; // Node 0
    adjList[1] = {2, 5}; // Node 1
    adjList[2] = {3, 6}; // Node 2
    adjList[4] = {0};    // Node 4
    adjList[5] = {4, 6}; // Node 5
    adjList[6] = {2};    // Node 6
    adjList[7] = {6};    // Node 7

    sccSolver->initialize(adjList, n);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 4);


    // Third Graph
    for (int i = 0; i < n; ++i) {
        adjList[i].clear();
    }

    int const k = 2;

    adjList[0] = {1}; // Node 0
    adjList[1] = {0}; // Node 1

    sccSolver->initialize(adjList, k);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 1);


    // Fourth Graph
    for (int i = 0; i < n; ++i) {
        adjList[i].clear();
    }

    int const l = 1;

    sccSolver->initialize(adjList, l);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 1);

    return 0;
}