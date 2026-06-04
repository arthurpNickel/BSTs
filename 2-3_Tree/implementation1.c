#include <stdlib.h>
#include <stdio.h>

typedef struct node2 {
    int key;
    Node *left;
    Node *right;
} Node2;

typedef struct node3 {
    int key1, key2;
    Node *left;
    Node *middle;
    Node *right;
} Node3;

typedef struct node {
    int type;
    Node *dad;

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


Node *search_2_3 ( Tree *t, int wanted )
{                
    Node *x, *y;
    int key;

    y = NULL;
    x = t->root;

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

    if ( x != NULL )
        return x;
    else /* Not found - return father */
        return y;
}

void node_2_to_3 (Node *x, int biggest_key, int smallest_key)
{
    int aux = x->node2.key;
    Node *son_left = x->node2.left;
    Node *son_right = x->node2.right;

    x->type = 3;
    x->node3.key1 = smallest_key;
    x->node3.key2 = biggest_key;
    
    //if...
    x->node3.left = son_left;
    x->node3.middle = NULL;
    x->node3.right = son_right;
}

void node_3_to_2 (Node *x, int is_left)
{
    Node *son_left, *son_right;
    if (is_left)
    {
        son_left = x->node3.left;
        son_right = x->node3.middle;
        //....
    }

    x->type = 2;
    x->node2.key = key;
    x->node2.
}

insertion_2_3 (Tree *t, int key)
{
    Node *x, *y;

    //busca pai do nó que vai ser inserido
    y = search_2_3(t, key);

    //Q: caso de ser raiz?

    //se inserção for em um lugar vazio ou com 1 nó, apenas insere
    if (y->type == 2)
    {
        if (y->node2.key > key)           
            node_2_to_3(y, y->node2.key, key);
        
        else 
            node_2_to_3(y, key, y->node2.key);
    }

    //enquanto inserção em 2 nos, split e insere em cima
    while ( 1 && y->type == 3 )
    {
        if ( y->dad->type == 2 )
        {
            if ( y->dad->node2.left = y ) //Se y for filho a esquerda
            {
                node_2_to_3(y->dad, y->dad->node2.key, y->node3.key2); //então y é menor que o pai
                
                node_3_to_2()

                if ( )
            }
                
            else 
                node_2_to_3(y->dad, y->dad->node2.key, y->node3.key1);
            
        }
    }
}