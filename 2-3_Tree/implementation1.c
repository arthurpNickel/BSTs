#include <stdlib.h>
#include <stdio.h>

typedef struct node2 {
    int n;
    int key;
    Node *left;
    Node *right;
} Node2;

typedef struct node3 {
    int n;
    int key1, key2;
    Node *left;
    Node *middle;
    Node *right;
} Node3;

typedef struct node {
    int type;

    union {
        Node2 node2;
        Node3 node3;
    };
} Node;

typedef struct tree{
    Node *root;
} Tree;


split_2_3 ()
{

}

//Q: Tem alguma lógica errada com o retorno do pai ou filho
Node *search_2_3 ( Tree t, Node *y, int wanted )
{                
    Node *x;
    int key;

    y = NULL;
    x = t.root;

    /* Verify first key */
    if ( x != NULL )
    {
        if ( x->type == 2 )
            key = x->node2.key;
        else
            key = x->node3.key1;
    }

    /* Search the node wanted */
    while ( x != NULL && key != wanted )
    {        
        /* Choice the next node */
        if ( x->type == 2 ) 
        {
            if ( x->node2.key != wanted)
                y = x;
            
            if ( x->node2.key < wanted )
                x = x->node2.left;

            else if ( x->node2.key > wanted )
                x = x->node2.right;
        }
        else //x->type == 5
        {
            if ( x->node3.key1 != wanted && x->node3.key2 != wanted)
                y = x;

            if ( x->node3.key1 < wanted )
                x = x->node3.left;
            else //chave é maior
            {
                if ( x->node3.key2 < wanted )
                    x = x->node3.middle;
                
                else  //x->node3.key2 > wanted
                    x = x->node3.right;
            }
        }

        /* Store the key of next node */
        if ( x != NULL )
            if ( x->type == 2 )
                key = x->node2.key;
            else
                key = x->node3.key1;
    }

    return x;
}

insertion_2_3 ()
{
    //busca pai do nó que vai ser inserido

    //se inserção for em um lugar vazio ou com 1 nó, apenas insere

    //enquanto inserção em 2 nos, split e insere em cima
}