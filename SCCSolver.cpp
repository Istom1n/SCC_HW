//
// Created by Ivan Istomin on 15/11/16.
//

#include "SCCSolver.h"

Vertice::Vertice(int id)
{
    this->id = id;
}

void Vertice::refresh()
{
    // Nullable values of Vertice
    discovered_step = -1;
    finished_step = -1;
    passed = false;
}

bool Vertice::compare(Vertice *v1, Vertice *v2)
{
    return v1->finished_step > v2->finished_step;
}

void SCCSolver::initialize(std::vector<int> *adjList, int n)
{
    if (adjList == nullptr) {
        throw std::invalid_argument("nullptr in argument");
    }

    nVertices = n;

    if (adjacencyList != nullptr) {
        delete[] adjacencyList;
    }

    adjacencyList = new std::vector<int>[nVertices];

    for (int i = 0; i < nVertices; i++) {
        adjacencyList[i] = adjList[i];
    }

    buildPool();

    solved = false;
    initialized = true;
}

void SCCSolver::solve()
{
    if (isInitialized()) {

        // The first run DFS does not need a tree
        runDFS();

        // Sort Vertices by finished step
        sortPool();

        // Refresh properties of Vertices
        refreshPool();

        // Transpose the data graph
        adjacencyList = reverseAdjacencyList(adjacencyList, nVertices);

        // Take result trees
        result = runDFS();

        // Change state
        solved = true;
    } else {
        throw std::logic_error("Called before initialization");
    }
}

std::vector<int>* SCCSolver::reverseAdjacencyList(std::vector<int> *adjList, int n)
{
    // Make new adjacency list
    std::vector<int>* newAdjList = new std::vector<int>[n];

    // Transpose the data graph
    for (int i = 0; i < n; ++i) {
        for (int j : adjList[i]) {
            newAdjList[j].push_back(i);
        }
    }

    return newAdjList;
}

std::vector<std::vector<int>> SCCSolver::getResult()
{
    if (isSolved()) {
        return result;
    } else {
        std::logic_error("Called before initialization");
    }
}

bool SCCSolver::isSolved()
{
    return solved;
}

bool SCCSolver::isInitialized()
{
    return initialized;
}

/*
 * You need to remove the curly braces from
 * the header!!!
 */
SCCSolver::~SCCSolver()
{
    delete[] adjacencyList;

    for(Vertice* v : vertPool) {
        delete v;
    }
}

void SCCSolver::buildPool()
{
    // If we run program for more then one graph
    vertPool.clear();

    // Build pool of Vertices
    for (int i = 0; i < nVertices; ++i) {
        vertPool.push_back(new Vertice(i));
    }
}

std::vector<std::vector<int>> SCCSolver::runDFS() {
    // Steps of DFS walking
    int step = 1;

    // Iteration variable for tree
    int i = 0;

    std::vector<std::vector<int>> tree;

    for (Vertice* v : vertPool) {
        if (!v->passed) {
            tree.push_back(std::vector<int>());

            DFSVisit(v, step, tree[i]);

            ++i; // new branch
        }
    }

    return tree;
}

void SCCSolver::DFSVisit(Vertice *v, int &step, std::vector<int> &tree) {

    // Check visited state
    v->passed = true;

    v->discovered_step = step;
    ++step;

    tree.push_back(v->id);

    // Iterate walking at all edges
    for (int i : adjacencyList[v->id]) {
        Vertice* vertice = getVertice(i);

        if (!vertice->passed) {
            DFSVisit(vertice, step, tree);
        }
    }

    v->finished_step = step;
    ++step;
}

void SCCSolver::sortPool() {
    std::sort(vertPool.begin(), vertPool.end(), Vertice::compare);
}

void SCCSolver::refreshPool() {

    // Nullable values of all Vertices
    for (Vertice* v : vertPool) {
        v->refresh();
    }
}

Vertice* SCCSolver::getVertice(int id) {
    for (Vertice* v : vertPool) {
        if (v->id == id) return v;
    }
}
