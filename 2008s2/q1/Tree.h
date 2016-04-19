// Tree.h ... binary tree interface

#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct node *Tree;

// Standard interface functions
Tree newTree();                 // create new Tree
Tree insert(Tree t, char it);   // insert item into Tree
int  isBST(Tree t);             // is Tree a binary search tree?
Tree scan(FILE *inf);           // read values, build tree
void show(Tree t);              // display a Tree (inorder)

#endif
