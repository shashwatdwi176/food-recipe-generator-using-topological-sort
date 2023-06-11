
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 9

char recipe_items[9][50] = {"3/4_cup_milk", "1_egg", "1_Tbls_oil", "1_cup_mix", "Heat_syrup", "heat_griddle", "pour_1/4_cup", "turn_when_bubly", "eat"};

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

typedef struct graph {
    int vertices;
    int adj_matrix[MAX_SIZE][MAX_SIZE];
} Graph;

void initialize_stack(Stack* s) {
    s->top = -1;
}

bool is_stack_empty(Stack* s) {
    return s->top == -1;
}

bool is_stack_full(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack* s, int value) {
    if (is_stack_full(s)) {
        printf("Stack is full.\n");
    } else {
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(Stack* s) {
    int item;
    if (is_stack_empty(s)) {
        printf("Stack is empty.\n");
        item = -1;
    } else {
        item = s->items[s->top];
        s->top--;
    }
    return item;
}

void create_graph(Graph* g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj_matrix[i][j] = 0;
        }
    }
}

void add_edge(Graph* g, int src, int dest) {
    if (src >= 0 && dest >= 0 && src < g->vertices && dest < g->vertices) {
        g->adj_matrix[src][dest] = 1;
    } else {
        printf("\nInvalid Edge!!!");
    }
}

void print_graph(Graph* g) {
    printf("Graph:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("Step %d", i);
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj_matrix[i][j] == 1) {
                printf(" -> %d", j);
            }
        }
        printf("\n");
    }
}

void dfs(Graph* g, int vertex, bool visited[], Stack* s) {
    visited[vertex] = true;

    for (int i = 0; i < g->vertices; i++) {
        if (g->adj_matrix[vertex][i] == 1 && !visited[i]) {
            dfs(g, i, visited, s);
        }
    }

    push(s, vertex);
}

void topological_sort(Graph* g) {
    bool visited[MAX_SIZE] = { false };
    Stack s;
    initialize_stack(&s);

    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i]) {
            dfs(g, i, visited, &s);
        }
    }
    printf("\n------------------------------------\n");
    printf("\n   Recipe For Your Pancake: \n\n");
    printf("------------------------------------\n");
    while (!is_stack_empty(&s)) {
        printf(" %s \n", recipe_items[pop(&s)]);
        printf("\n");
        printf("  | \n");
        printf("  v \n");
        
    }
}

int main() {

    
    printf("\n\n \t     Food Recipe Generator\n\n");

    Graph graph;
    create_graph(&graph, 9);

    add_edge(&graph, 0, 3);
    add_edge(&graph, 1, 3);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 3, 6);
    add_edge(&graph, 5, 6);
    add_edge(&graph, 6, 7);
    add_edge(&graph, 7, 8);
    add_edge(&graph, 4, 8);

    printf("\n");
    printf("-----------------------------------\n");
    printf("\n\tGraph Formed\n\n");
    printf("-----------------------------------\n");
    print_graph(&graph);
    printf("\n");

    topological_sort(&graph);

    printf("\n----- Enjoy PANCAKE!!! ----------");
    printf("\n\n---- Thankyou ----");
    return 0;
}


