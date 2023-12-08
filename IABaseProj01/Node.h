#pragma once

class Node {
public:

    int x, y;
    float gCost, hCost, fCost;
    Node* parent;

    Node(int x, int y);

    float calculateFCost();
    
    static float heuristic(int x1, int y1, int x2, int y2);

};