#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned char Address;

typedef struct
{
    unsigned char address[4];
    Address *neighbors;
    int neighborsCount;
} Node;

Node *create_node(Address parts[4])
{
    Node *node = malloc(sizeof(Node));
    //*(node->address) = *parts;

    for (int i = 0; i < 4; i++)
    {
        node->address[i] = parts[i];
    }

    node->neighbors = calloc(128, sizeof(Address));
    node->neighborsCount = 0;
    return node;
}

void link_neighbors(Node *nodeA, Node *nodeB)
{
    nodeA->neighbors[nodeA->neighborsCount] = *nodeB->address;
    nodeA->neighborsCount += 1;
    nodeB->neighbors[nodeB->neighborsCount] = *nodeB->address;
    nodeB->neighborsCount += 1;
}

Address **common_neighbors(Node *nodeA, Node *nodeB)
{
    Address **commonNeighbors = calloc(128, sizeof(Address *));
    int currentNumberOfNeighbors = 0;
    for (int i = nodeA->neighborsCount; i < nodeA->neighborsCount; i++)
    {
        Address currentNeighborAPtr = (Address)nodeA->neighbors[i];
        for (int j = nodeB->neighborsCount; j < nodeB->neighborsCount; j++)
        {
            Address currentNeighborBPtr = (Address)nodeB->neighbors[j];
            if (currentNeighborAPtr == currentNeighborBPtr)
            {
                commonNeighbors[currentNumberOfNeighbors] = &currentNeighborAPtr;
                currentNumberOfNeighbors += 1;
                if (currentNumberOfNeighbors)
                {
                    printf("unhandled, need vector enlarge");
                }
            }
        }
    }
    return commonNeighbors;
};

void node_print(Node const *node)
{
    printf("Node %d.%d.%d.%d has %d neighbors ", node->address[0], node->address[1], node->address[2], node->address[3], node->neighborsCount);
    for (int i = 0; i < node->neighborsCount; i++)
    {
        printf("%d.%d.%d.%d",
               (node->neighbors[i] >> 24) & 0xf,
               (node->neighbors[i] >> 16) & 0xf,
               (node->neighbors[i] >> 8) & 0xf,
               (node->neighbors[i] >> 0) & 0xf);
    }
    puts("");
};

int main()
{

    unsigned char nodeAParts[4] = {192, 168, 1, 1};
    Node *nodeAPtr = create_node(nodeAParts);

    unsigned char nodeBParts[4] = {192, 168, 1, 2};
    Node *nodeBPtr = create_node(nodeBParts);

    link_neighbors(nodeAPtr, nodeBPtr);

    node_print(nodeAPtr);
    node_print(nodeBPtr);
}
