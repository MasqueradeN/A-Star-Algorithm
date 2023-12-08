#include "AStar.h"
#include <algorithm>
#include "../raylib/raymath.h"
#include <iostream>

//solucion guarra a un error que estaba teniendo
bool IsEqual(const VectorInt2& a, const VectorInt2& b)
{
    return a.x == b.x && a.y == b.y;
}

// Busca un camino desde un nodo de inicio a un nodo objetivo en un grid
std::vector<Node*> AStar::AStarSearch(Node* start, Node* goal, 
    const std::vector<std::vector<sCell>>& grid, const VectorInt2& agentPos, 
    const std::vector<VectorInt2>& orbs) {
    // Lista de nodos aún no procesados.
    std::vector<Node*> openList;
    // Lista de nodos ya procesados.
    std::vector<Node*> closedList;

    openList.push_back(start);
    // Inicializa los costos de inicio: gCost es 0, y hCost es calculado usando la heurística.
    start->gCost = 0;
    start->hCost = Node::heuristic(start->x, start->y, goal->x, goal->y);
    start->calculateFCost();

    // Continúa mientras haya nodos en la lista abierta.
    while (!openList.empty()) {
        Node* currentNode = getLowestFCostNode(openList);

        // Si el nodo actual es el objetivo, reconstruye y devuelve el camino encontrado.
        if (currentNode->x == goal->x && currentNode->y == goal->y) {
            return reconstructPath(currentNode);
        }

        openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
        closedList.push_back(currentNode);

        for (Node* neighbor : getNeighbors(currentNode, grid, agentPos, orbs)) {
            // Si el vecino ya está en la lista cerrada, ignóralo.
            if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) {
                continue;
            }

            float tentativeGCost = currentNode->gCost + Node::heuristic(currentNode->x, currentNode->y, neighbor->x, neighbor->y);
            // Si el gCost tentativo es menor al gCost actual del vecino, actualiza su información.
            if (tentativeGCost < neighbor->gCost) {
                neighbor->parent = currentNode;
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = Node::heuristic(neighbor->x, neighbor->y, goal->x, goal->y);
                neighbor->calculateFCost();

                if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                    openList.push_back(neighbor);
                }
            }
        }
        std::cout << "Oh nooooooooooo\n";
    }

    std::cout << "AAAAAAAAAAAAA\n";
    return std::vector<Node*>(); // Devuelve un vector vacío si no se encuentra un camino.
}

std::vector<Node*> AStar::reconstructPath(Node* currentNode) {
    std::vector<Node*> path;
    while (currentNode->parent != nullptr) {
        path.push_back(currentNode->parent);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// getNeighbors: Encuentra todos los nodos vecinos válidos del nodo actual.
// node: El nodo actual del que se buscan vecinos.
// grid: El grid que representa el entorno del juego.
// agentPos: Posición del agente en el grid.
// orbs: Posiciones de los orbes en el grid.
std::vector<Node*> AStar::getNeighbors(Node* node, const std::vector<std::vector<sCell>>& grid,
    const VectorInt2& agentPos, const std::vector<VectorInt2>& orbs) {
    std::vector<Node*> neighbors;

    // Revisa todas las posiciones alrededor del nodo actual.
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Ignorar el nodo actual.

            int newX = node->x + dx;
            int newY = node->y + dy;

            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
                sCell cell = grid[newX][newY];

                if (cell.object != eObjType::barrier && cell.object != eObjType::borde) {
                    bool isAgentPos = IsEqual(VectorInt2{ newX, newY }, agentPos);
                    bool isOrbPos = false;

                    for (const auto& orb : orbs) {
                        if (IsEqual(VectorInt2{ newX, newY }, orb)) {
                            isOrbPos = true;
                            
                            break;
                        }
                    }

                    //if (isAgentPos || isOrbPos)
                        //neighbors.push_back(new Node(newX, newY));

                    if (!isAgentPos && !isOrbPos)
                        neighbors.push_back(new Node(newX, newY));

                    
                }
            }
        }
    }
    return neighbors;
}


Node* AStar::getLowestFCostNode(std::vector<Node*>& openList) {
    Node* lowestFCostNode = openList[0];
    for (Node* node : openList) {
        if (node->fCost < lowestFCostNode->fCost) 
            lowestFCostNode = node;
        
    }
    return lowestFCostNode;
}
