#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
    int i, j, k, l;

    for (i = 0 ; i < 9 ; i++)
    {
        int filas[10] = {0};
        int colu[10] = {0};
        for (j = 0 ; j < 9 ; j++)
        {
            int num_fila = n->sudo[i][j];
            int num_colu = n->sudo[j][i];
            if (num_fila != 0)
            {
                if (filas[num_fila]) return 0;
                filas[num_fila] = 1;
            }
            if (num_colu != 0)
            {
                if (colu[num_colu]) return 0;
                colu[num_colu] = 1;
            }
        }
    }

    for (int k = 0; k < 9; k++) 
    {
        int sub[10] = {0};
        for (int p = 0; p < 9; p++) 
        {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];
            
            if (num != 0) 
            {
                if (sub[num]) return 0;
                sub[num] = 1;
            }
        }
    }
        
    return 1;
}


List* get_adj_nodes(Node* n)
{
    List* lista = createList();
    if (n == NULL) return lista;

    int i, j, k;
    for (i = 0 ; i < 9 ; i++)
       for (j = 0 ; j < 9 ; j++)
          if (n->sudo[i][j] == 0)
          {
             for (k = 1 ; k <= 9 ; k++)
             {
                Node* new = copy(n);
                new->sudo[i][j] = k;
                if (is_valid(new)) pushBack(lista, new);
             }
             return lista;
          }

    return lista;
}

int is_final(Node* n)
{
    int i, j;
    for (i = 0 ; i < 9 ; i++)
        for (j = 0 ; j < 9 ; j++)
            if (n->sudo[i][j] == 0) return 0;
    return 1;
}

Node* DFS(Node* initial, int* cont)
{
    Stack *pila = createStack();
    push(pila, initial);

    Node *nodo = top(pila);
    while (nodo != NULL)
    {
        pop(pila);
        if (is_final(nodo)) return nodo;

        List *nodos_ady = get_adj_nodes(nodo);
        
        Node* nodo_lista = first(nodos_ady);
        while (nodo_lista != NULL)
        {
            push(pila, nodo_lista);
            nodo_lista = next(nodos_ady);
        }

        free(nodo);

        (*cont)++;
        nodo = top(pila);
    }

    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/