#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

bool dfsCycle(Graph* graph, int vertex, bool* recStack) {
    graph->visited[vertex] = true;
    recStack[vertex] = true;

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;

        if (!graph->visited[adjVertex]) {
            if (dfsCycle(graph, adjVertex, recStack)) {
                return true;
            }
        } else if (recStack[adjVertex]) {
            return true;
        }

        temp = temp->next;
    }

    recStack[vertex] = false;
    return false;
}

bool isCyclic(Graph* graph) {
    bool* recStack = malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++) {
        recStack[i] = false;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            if (dfsCycle(graph, i, recStack)) {
                free(recStack);
                return true;
            }
        }
    }

    free(recStack);
    return false;
}

int main() {
    int vertices, edges;
    printf("Nhap so dinh: ");
    scanf("%d", &vertices);

    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Nhap danh sach canh:\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    if (isCyclic(graph)) {
        printf("Do thi co chu trinh\n");
    } else {
        printf("Do thi khong co chu trinh\n");
    }

    return 0;
}

