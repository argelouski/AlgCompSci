/* We will explore the tree until every leaf, in each leaf we will encode the corresponding symbol. The distinguishing characteristic of each leaf is that it doesn't have right or left childern; because it is a leaf. We will use a string of fixed length (8) to codify everything, hoping that it is enough.(It would be enough for the ascii symbols because 2**8 = 128 and there are 127 ascii symbols) */
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void code_generator(int base,tree_t tree, int *out_table,int dist){ /* missing allocation and deallocation */
  int out = base;
  int val;
  if (tree->right){
    code_generator(out*2+1,tree->right,out_table,dist+1);
    code_generator(out*2,tree->left,out_table,dist+1);
  }
  else{
  val =  tree->symbol;
  out_table[val] = out;
  printf("Símbolo: %c, Distancia: %d, código: %i \n",val,dist,out);
  }
}


  /* Muy incipiente, pensar con calma SIN ALCOHOL */
tree_t tree_generator(bamboo_t bamboo){
  tree_t tree;
  /* int i=1; */
  /* bamboo_t aux_bamboo; */
  tree = append_to_tree((bamboo->tree),(bamboo->next)->tree);
  bamboo = bamboo->next;
    while((((bamboo->next)->tree)->freq)!=1){
      bamboo = bamboo->next;
      tree = append_to_tree(tree,bamboo->tree);
      /* printf("Appended tree\n"); */
      /* i++; */
  }
    /* printf("Appended %d trees \n",i); */
    return tree;
}

tree_t append_to_tree(tree_t tree1, tree_t tree2){
  tree_t result;
  result = (tree_t) malloc(sizeof(struct tree_s));
  /* result->right = (tree_t) malloc(sizeof(struct tree_s)); */
  /* result->left = (tree_t) malloc(sizeof(struct tree_s)); */
  if ((tree1->freq) < (tree2->freq)){
      result->right = tree1;
      result->left = tree2;
      printf("Árbol grande pegado a la derecha\n");
  }
  else {
    result->right = tree2;
    result->left = tree1;
    printf("Árbol grande pegado a la izquierda\n");
  }
  result->freq = (tree1->freq) + (tree2->freq);
  return result;
}

void free_bamboo(bamboo_t bamboo){
  if(bamboo->next != NULL){
    free_bamboo(bamboo->next);
  }
  /* free(bamboo->tree); /\* Not used because we are using the same memory for the big tree *\/ */
  free(bamboo);

}

