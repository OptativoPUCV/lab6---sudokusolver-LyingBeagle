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

int is_valid(Node* n){

    //Filas
    for(int fila = 0; fila < 9; fila++){

      int nFila[10] = {0};
      
        for(int columna = 0; columna < 9; columna++){

        if(n->sudo[fila][columna] != 0){
              if(nFila[n->sudo[fila][columna]] == 1) return 0;
              else nFila[n->sudo[fila][columna]] = 1;
          }
        }
    }

    
    //Columna
    for(int columna = 0; columna < 9; columna++){

      int nColumna[10] = {0};
      
        for(int fila = 0; fila < 9; fila++){

        if(n->sudo[fila][columna] != 0){
              if(nColumna[n->sudo[fila][columna]] == 1) return 0;
              else nColumna[n->sudo[fila][columna]] = 1;
          }
        }
    }


    
    //SubMatriz
    for(int cicloSubMatriz = 0; cicloSubMatriz < 9; cicloSubMatriz++){

      int subMatriz[10] = {0};
      
      for(int p = 0; p < 9; p++){
        
          int i = 3 * (cicloSubMatriz/3) + (p/3);
          int j = 3 * (cicloSubMatriz%3) + (p%3);

          if(n->sudo[i][j] != 0){

              if(subMatriz[n->sudo[i][j]] == 1) return 0;
              else subMatriz[n->sudo[i][j]] = 1;
          }
      }
      
    }
    

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            if(n->sudo[i][j] == 0){

                for(int k = 1; k < 10; k++){
                    Node* aux = copy(n);

                    aux->sudo[i][j] = k;

                    if(is_valid(aux)){
                        push(list,aux);
                    }
  
                }
              return list;
            }
          
        }
    }
  
    return list;
}


int is_final(Node* n){

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
           if(n->sudo[i][j] == 0) return 0; 
        }
    }
  
    return 1;
}

Node* DFS(Node* initial, int* cont){
  
  Stack* pila =createStack();
  
  push(pila, initial);
  
  while(is_empty(pila) == 0){
    
      Node *n = top(pila); 
    
      pop(pila);
    
      if(is_final(n)){
        return n;
      }
    
      List *lista = get_adj_nodes(n);
    
      Node *primer=first(lista);
    
      while(primer != NULL){
        
        push(pila, primer);
        primer=next(lista); 
        
      }
      (*cont)++;
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