#include <stdio.h>
#include <stdint.h>

typedef struct {
    unsigned char address[4];
    int* neighbors;
    int neighborsCount;
} Node;

Node* create_node(unsigned char parts[4]) {
    Node* node = malloc(sizeof(Node));
    *(node->address) = parts;
    node->neighborsCount = 0;
    return node;
}

Node* link_neighbors(Node* nodeA, Node* nodeB) {
    nodeA->neighbors[nodeA->neighborsCount-1] = nodeB->address;
    nodeA->neighborsCount += 1;
    nodeB->neighbors[nodeB->neighborsCount-1] = nodeB->address;
    nodeB->neighborsCount += 1;
}

Node* common_neighbors(Node* nodeA, Node* nodeB) {
    Node commonNeighbors[nodeA->neighborsCount];
    int currentNumberOfNeighbors = 0;
    for (int i = nodeA->neighborsCount; i < nodeA->neighborsCount; i++) {
        Node* currentNeighborA = nodeA->neighbors[i];
        for (int j = nodeB->neighborsCount; j < nodeB->neighborsCount; j++) {
            Node* currentNeighborB = nodeB->neighbors[j];
            if (currentNeighborA == currentNeighborB) {
                commonNeighbors[currentNumberOfNeighbors] = currentNeighborA;
                currentNumberOfNeighbors += 1;
            }
        }
    }
}
