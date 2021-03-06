#include "functions.h"
#include<string.h>


int computeOutDegree(int x) {
    int length = 0;
    struct node *p = adjList[x];
    while(p != NULL) {
        length++;
        p = p -> next;
    }
    return length;
}

int valueAlreadyExists(int nodInitial, int nodFinal) {
    struct node *p = adjList[nodInitial];
    while(p != NULL) {
        if(p -> vertex == nodFinal) {
            return 1;
        } else {
            p = p -> next;
        }
    }
    return 0;
}

void createGraph ( struct node *adjList[MAX_NODES], int nodes, int vertices) {

    int x, y;
    struct node *p, *c;
    int k = 0;

    while(k != vertices) {
        x = rand() % (nodes + 1);
        while(x == 0) {
            x = rand() % (nodes + 1);
        }
        //printf("x = ");
        //scanf("%d", &x);
        if(computeOutDegree(x) < nodes - 1) {
            y = rand() % (nodes + 1);
            while(y == 0 || x == y || valueAlreadyExists(x,y) == 1) {
                y = rand() % (nodes + 1);
            }

            //printf("y = ");
            //scanf("%d", &y);

            //inserarea elementelor arcului
            c = new_node;
            c -> vertex = y;
            c -> next = NULL;
            if ( adjList[x] == NULL ) {
                adjList[x] = c;
            } else {
                p = adjList[x];
                while ( p -> next != NULL )
                    p = p -> next;
                p -> next = c;
            }
            //printf("%d %d\n" , x, y);

            //verificam daca graful ramane aciclic
            if(isGraphAcyclic(nodes, x) == 1) {
                if(adjList[x] -> next == NULL) {
                    adjList[x] = NULL;
                } else {
                    p -> next = NULL;
                }
                //printf("Erase %d %d\n" , x, y);
            } else  {
                k++;
            }
        }
    }
}

void createFileName(char filename[20]) {
    char aux[10];
    strcpy(filename, "dg_");
    itoa(nodes, aux, 10);
    strcat(filename, aux);
    strcat(filename, "n_%");
    itoa(percent, aux, 10);
    strcat(filename, aux);
    strcat(filename, "v");
    strcat(filename, ".txt");
}

void printGraph(struct node *adjList[MAX_NODES], int nodes) {
    char filename[10];
    createFileName(filename);
    //printf("%s ", filename);

    FILE *out = fopen(filename, "w");

    fprintf(out, "%d %d\n", nodes, vertices);
    int i;
    struct node *p;
    for(i = 1; i <= nodes; i++) {
        p = adjList[i];
        while(p != NULL) {
            fprintf(out, "%d %d \n", i, p->vertex);
            p = p->next;
        }
    }
}


void DFS(int startNode) {
    struct node *p;
    p = adjList[startNode];
    visited[startNode] = 1;
    while(p != NULL) {
        if(visited[p->vertex] == 0) {
            DFS(p->vertex);
        }
        p = p->next;
    }
    //printf("\n");
}

int isGraphAcyclic(int nodes, int startNode) {
    int i;
    for(i = 1; i <= nodes; i++) {
        visited[i] = 0;
    }
    DFS(startNode);
    for(i = 1; i <= nodes; i++) {
        if(visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

