#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct tree
{
    NoRB *root;
    //nil?
} Tree;

typedef struct noRB
{
    int color;
    int key;
    NoRB *father;
    NoRB *left;
    NoRB *right;
} NoRB;

//não sei se é NoRB
NoRB *insert_RB (Tree *T, NoRB *z)
{
    NoRB *father, *uncle, *grandfather;
    NoRB *x, *y;

    z->color = RED;
    
    //busca onde inserir
    x = T->root;
    y = NULL;
    while ( x != NULL )
    {
        y = x;
        if ( x->key < z->key )
            x = x->right;
        else
            x = x->left;
    }
    //insere
    z->father = y;      //Tinha esquecido!!
    if ( y == T->nil )  //Tinha esquecido!!
        T->root = z;
    else if (y->key < z->key)
        y->right = z;
    else
        y->left = z;
    
    z->left = T->nil;       //Tinha esquecido!!
    z->right = T->nil;

    //TODA ESSA PARTE DE BAIXO "FAZ PARTE" DO "INSERT-FIXUP"
        //Esqueci completamente que a coloração errada pode se espalhar

    //Define pai e tio -> facilita acesso
        //Não tinha sacado essa parte!!
    
    father = z->father;
    grandfather = father->father;
    if (father == grandfather->right) //Onde está o tio?
        uncle = grandfather->left;      //Nesse momento eu poderia resolver questão de alinhamento, o que seria o ideal?
    else
        uncle = grandfather->right;

    //Arruma propriedades

    if ( z == T->root )
    {
        z->color = BLACK;
        return;
    }
    
    if ( uncle->color == RED )
    {
        //troca cores
        uncle->color = BLACK;
        grandfather->color = RED;
        father->color = BLACK; 
        return;
    }

    //Senão (tio preto)
    //Verifica alinhamento
    if ( grandfather->right == father && father->right == z )       //alinhamento à direita
        rot_left(T, grandfather);
    else if ( grandfather->left == father && father->left == z )    //alinhamento à esquerda
        rot_right(T, grandfather);
    else if ( grandfather->right == father && father->left == z )    //triangulo à direita
    {
        rot_right(T, father);
        rot_left(T, grandfather);
    }
    else                                                            // triangulo à esquerda
    {
        rot_left(T, father);
        rot_right(T, grandfather);
    }

    //Q: tem que fazer pinturas aqui?
}

NoRB *insert_fixup()
{
    
}