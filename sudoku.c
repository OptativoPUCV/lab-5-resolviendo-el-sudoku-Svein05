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

/*
2.Cree la función int is_valid(Node * n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

No se repitan números en las filas
No se repitan números en las columnas
No se repitan números en las submatrices de 3x3
Si el estado es válido la función retorna 1, si no lo es retorna 0.

Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.
*/
int is_valid(Node* n)
{
    int filas[10], colu[10], sub[10];

    int i, j, k, l;
    for (i = 0 ; i < 9 ; i++)
    {
        for (j = 0 ; j < 9 ; j++)
        {
            filas[j] = 0;
            colu[j] = 0;
            sub[j] = 0;
        }

        for (j = 0 ; j < 0 ; j++)
        {
            if (n->sudo[i][j] != 0)
            {
                if (filas[n->sudo[i][j]] == 1) return 0;
                filas[n->sudo[i][j]] = 1;
            }
            if (n->sudo[j][i] != 0)
            {
                if (filas[n->sudo[j][i]] == 1) return 0;
                filas[n->sudo[j][i]] = 1;
            }
        }

        for (k = 0 ; k < 3 ; k++)
        {
            for (l = 0 ; l < 3 ; l++)
            {
                if (sub[n->sudo[k + i / 3 * 3][l + i % 3 * 3]] == 1) return 0;
                sub[n->sudo[k + i / 3 * 3][l + i % 3 * 3]] = 1;
            }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n)
{
    List* lista = createList();
    if (n == NULL) return lista;
    //if (is_final(n)) return lista;

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


int is_final(Node* n){
    return 0;
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