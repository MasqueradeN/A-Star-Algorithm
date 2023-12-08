#include "../raylib/raylib.h"
#include "../entorno/Grid.h"
#include "../Node.h"
#include <vector>
#include <limits>
#include <cmath>

class AStar {
public:
    AStar() = default;

    std::vector<Node*> AStarSearch(Node* start, Node* goal, 
        const std::vector<std::vector<sCell>>& grid, const VectorInt2& agentPos, 
        const std::vector<VectorInt2>& orbs);

    std::vector<Node*> reconstructPath(Node* currentNode);
    
    std::vector<Node*> getNeighbors(Node* node, const std::vector<std::vector<sCell>>& grid, 
        const VectorInt2& agentPos, const std::vector<VectorInt2>& orbs);
    
    Node* getLowestFCostNode(std::vector<Node*>& openList);
};


