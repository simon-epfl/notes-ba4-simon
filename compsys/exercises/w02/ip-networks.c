#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char Address;

typedef struct
{
    unsigned char address[4];
    Address **neighbors;
    int neighborsCount;
} Node;

Node *create_node(Address parts[4])
{
    Node *node = malloc(sizeof(Node));
    for (int i = 0; i < 4; i++)
    {
        node->address[i] = parts[i];
    }
    node->neighbors = calloc(256, sizeof(Address *));
    node->neighborsCount = 0;
    return node;
}

void link_neighbors(Node *nodeA, Node *nodeB)
{
    // nodeA->neighbors[nodeA->neighborsCount] = *nodeB->address;
    // nodeA->neighborsCount += 1;
    // nodeB->neighbors[nodeB->neighborsCount] = *nodeA->address;
    // nodeB->neighborsCount += 1;
    nodeA->neighbors[nodeA->neighborsCount] = calloc(4, sizeof(Address));
    for (int i = 0; i < 4; i++) {
        nodeA->neighbors[nodeA->neighborsCount][i] = nodeB->address[i];
    }
    nodeA->neighborsCount++;

    nodeB->neighbors[nodeB->neighborsCount] = calloc(4, sizeof(Address));
    for (int i = 0; i < 4; i++) {
        nodeB->neighbors[nodeB->neighborsCount][i] = nodeA->address[i];
    }
    nodeB->neighborsCount++;
}

Address **common_neighbors(Node *nodeA, Node *nodeB)
{
    Address **commonNeighbors = calloc(128, sizeof(Address *));
    int currentNumberOfNeighbors = 0;
    for (int i = 0; i < nodeA->neighborsCount; i++)
    {
        for (int j = 0; j < nodeB->neighborsCount; j++)
        {
            bool isSame = true;
            for (int k = 0; k < 4; k++) {
                if (nodeA->neighbors[i][k] != nodeB->neighbors[j][k]) isSame = false;
                break;
            }
            if (isSame) {
                commonNeighbors[currentNumberOfNeighbors] = calloc(4, sizeof(Address));
                for (int k = 0; k < 4; k++) {
                    commonNeighbors[currentNumberOfNeighbors][k] = nodeA->neighbors[i][k];
                }
                currentNumberOfNeighbors += 1;
                if (currentNumberOfNeighbors >= 128)
                {
                    printf("unhandled, need vector enlarge");
                    return commonNeighbors;
                }
            }
        }
    }
    return commonNeighbors;
}

void node_print(Node const *node)
{
    printf("Node %d.%d.%d.%d has %d neighbors ", node->address[0], node->address[1], node->address[2], node->address[3], node->neighborsCount);
    for (int i = 0; i < node->neighborsCount; i++)
    {
        printf("%d.%d.%d.%d ",
               node->neighbors[i][0],
               node->neighbors[i][1],
               node->neighbors[i][2],
               node->neighbors[i][3]);
    }
    puts("");
}

int main()
{

    unsigned char nodeAParts[4] = {192, 168, 1, 1};
    Node *nodeAPtr = create_node(nodeAParts);

    unsigned char nodeBParts[4] = {192, 168, 1, 2};
    Node *nodeBPtr = create_node(nodeBParts);

    unsigned char nodeCParts[4] = {192, 168, 1, 3};
    Node *nodeCPtr = create_node(nodeCParts);

    link_neighbors(nodeAPtr, nodeBPtr);
    link_neighbors(nodeAPtr, nodeCPtr);

    node_print(nodeAPtr);
    node_print(nodeBPtr);

    Address **common = common_neighbors(nodeBPtr, nodeCPtr);
    printf("Common neighbors between B and C: ");
    for (int i = 0; common[i] != NULL; i++)
    {
        printf("%d.%d.%d.%d ", common[i][0], common[i][1], common[i][2], common[i][3]);
        free(common[i]);
    }
    puts("");

    return 0;
}
