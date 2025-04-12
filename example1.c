#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;            // număr de noduri (restaurante)
    int *vis;         // vector de vizitat
    NODE **alst;      // liste de adiacență
} GPH;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);  // pentru graf neorientat
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("Adauga %d muchii (indexare de la 0 la %d):\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        if (src >= 0 && src < nrv && dest >= 0 && dest < nrv)
            add_edge(g, src, dest);
        else
            printf("Muchie invalida: %d - %d\n", src, dest);
    }
}

// Verifică dacă există drum direct (adică muchie directă) între două noduri
int has_direct_path(GPH *g, int from, int to) {
    NODE *temp = g->alst[from];
    while (temp != NULL) {
        if (temp->data == to)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    int nrv;       // nr de restaurante
    int edg_nr;    // nr de muchii

    printf("Cate restaurante are reteaua? ");
    scanf("%d", &nrv);

    printf("Cate legaturi directe sunt intre restaurante? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr, nrv);

    int r1, r2;
    printf("Verificare drum direct intre doua restaurante (indexate de la 0):\n");
    printf("Restaurant 1: ");
    scanf("%d", &r1);
    printf("Restaurant 2: ");
    scanf("%d", &r2);

    if (r1 >= 0 && r1 < nrv && r2 >= 0 && r2 < nrv) {
        if (has_direct_path(g, r1, r2))
            printf("Exista drum direct intre restaurantul %d si %d.\n", r1, r2);
        else
            printf("NU exista drum direct intre restaurantul %d si %d.\n", r1, r2);
    } else {
        printf("Restaurante invalide.\n");
    }

    return 0;
}
