#include "Node.h"
#include <cmath>

Node::Node(int x, int y) : x(x), y(y), gCost(INFINITY), hCost(INFINITY), fCost(INFINITY), parent(nullptr) {}

float Node::calculateFCost() {
    fCost = gCost + hCost;
    return fCost;
}

float Node::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}