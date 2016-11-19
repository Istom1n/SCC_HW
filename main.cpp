#include <iostream>
#include <cassert>
#include "SCCSolver.h"

int main() {
    SCCSolver* sccSolver = new SCCSolver();

    int const n = 8;

    std::vector<int>* adjList = new std::vector<int>[n];

    // First Graph
    // Node 0
    adjList[0].push_back(4);
    adjList[0].push_back(1);

    // Node 1
    adjList[1].push_back(3);
    adjList[1].push_back(2);

    // Node 2
    adjList[2].push_back(1);

    // Node 3
    adjList[3].push_back(3);

    // Node 4
    adjList[4].push_back(0);
    adjList[4].push_back(3);

    // Node 5
    adjList[5].push_back(6);
    adjList[5].push_back(2);

    // Node 6
    adjList[6].push_back(2);
    adjList[6].push_back(7);

    // Node 7
    adjList[7].push_back(5);

    sccSolver->initialize(adjList, n);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 4);


    // Second Graph
    for (int i = 0; i < n; ++i) {
        adjList[i].clear();
    }

    // Node 0
    adjList[0].push_back(5);
    adjList[0].push_back(1);

    // Node 1
    adjList[1].push_back(2);
    adjList[1].push_back(5);

    // Node 2
    adjList[2].push_back(3);
    adjList[2].push_back(6);

    // Node 4
    adjList[4].push_back(0);

    // Node 5
    adjList[5].push_back(4);
    adjList[5].push_back(6);

    // Node 6
    adjList[6].push_back(2);

    // Node 7
    adjList[7].push_back(6);

    sccSolver->initialize(adjList, n);
    sccSolver->solve();

    assert(sccSolver->getResult().size() == 4);


    // Third Graph
    for (int i = 0; i < n; ++i) {
        adjList[i].clear();
    }

    int const k = 2;

    // Node 0
    adjList[0].push_back(1);

    // Node 1
    adjList[1].push_back(0);

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