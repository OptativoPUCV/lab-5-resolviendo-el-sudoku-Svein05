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

    // Revisar filas y columnas
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

    for (i = 0 ; i < 3 ; i++)
        for (j = 0 ; j < 3 ; j++)
        {
            int sub[10] = {0};
            for (k = 0 ; k < 3 ; k++)
                for (l = 0 ; l < 3 ; l++)
                {
                    int num = n->sudo[i * 3 + k][j * 3 + l];
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

/*
4.Implemente la función int is_final(Node * n). Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.
*/
int is_final(Node* n)
{
    int i, j;
    for (i = 0 ; i < 9 ; i++)
        for (j = 0 ; j < 9 ; j++)
            if (n->sudo[i][j] == 0) return 0;
    return 1;
}

Node* DFS(Node* initial, int* cont){
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