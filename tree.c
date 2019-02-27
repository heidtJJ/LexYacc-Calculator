#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "y.tab.h"

extern int yyerror( char*);

/* Prototype */
void aux_tree_print( tree_t*, int);

/* Constructor */
tree_t* mktree(int type, tree_t* left, tree_t* right){
    tree_t* root = (tree_t*) malloc(sizeof(tree_t));
    assert(root != NULL);// No memory can be allocated.
    root->type = type;
    root->leftChild = left;
    root->rightChild = right;
    return root;
}

/* Auxiliary */
int tree_eval(tree_t* root){
    assert(root != NULL);
    
    int leftValue;
    int rightValue;
    switch(root->type){
        case '+':
            leftValue = tree_eval(root->leftChild);
            rightValue = tree_eval(root->rightChild);
            return leftValue + rightValue;
        case '-':
            leftValue = tree_eval(root->leftChild);
            if(root->rightChild){
                rightValue = tree_eval(root->rightChild);
                return leftValue - rightValue;
            }
            else 
                return -leftValue;  
        case '*':
            leftValue = tree_eval(root->leftChild);
            rightValue = tree_eval(root->rightChild);
            return leftValue * rightValue;
        case '/':
            leftValue = tree_eval(root->leftChild);
            rightValue = tree_eval(root->rightChild);
            return leftValue / rightValue;
        case NUM:
            return root->attribute;
        default:
            break;
    }

    return 42;
}

void tree_print(tree_t* root){
    aux_tree_print( root, 0 );
}

void aux_tree_print( tree_t* root, int spaces){
    if(root == NULL) return;

    for(int i = 0; i < spaces; ++i){
        fprintf(stderr, " ");
    }

    switch(root->type){
        case '+':
            fprintf(stderr, "[ADDOP]\n");
            break;
        case '-':
            fprintf(stderr, "[SUBOP]\n");
            break;    
        case '*':
            fprintf(stderr, "[MULOP]\n");
            break;
        case '/':
            fprintf(stderr, "[DIVOP]\n");
            break;    
        case NUM:
            fprintf(stderr, "[NUM:%d]\n", root->attribute);
            break;
        default:
        yyerror("Error in tree_print");
    }

    aux_tree_print(root->leftChild, spaces+4);
    aux_tree_print(root->rightChild, spaces+4);
}