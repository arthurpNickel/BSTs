#define RED 1
#define BLACK 0

typedef struct tree
{
    NoRB *root;
    NoRB *nil;
} TreeRB;

typedef struct noRB
{
    int color;
    int key;
    NoRB *father;
    NoRB *left;
    NoRB *right;
} NoRB;

//coloca v no lugar de u
void transplant_RB (TreeRB *T, NoRB *u, NoRB *v);

void delete_RB (TreeRB *T, NoRB *z)
{
    NoRB *x;
    NoRB *y = z;

    //grava cor de y (z)
    int y_original_color = z->color;

    //remove y
    //verifica se filho esquerda é nil
    if ( z->left == T->nil )
    {   
        x = z->left;    //ERRO: INVERTI A LEFT E RIGHT DENTRO DESSES 2 IFS
        transplant_RB(T, z, z->left);
    }
    //verifica se filho direita é nmil
    else if ( z->right == T->nil )
    {
        x = z->right;
        transplant_RB(T, z, z->right);
    }
    //nó interno
    else
    {
        y = z->right;
        
        //se sucessor não é filho direito, então procura na subárvore
        if ( y->left != T->nil ) //ERRO: não precisava do if -> executa minimum de qualquer jeito
        {
            y = minimum_treeRB(T, y);
        }

        y_original_color = y->color;     //grava cor de y

        x = y->right;

        //troca de ponteiros -> coloca x no lugar de y
        //ERRO: isso só precisa acontecer se sucessor não for filho direita de z
            //Se for, então não precisa fazer isso-> só deslocar y para cima
        transplant_RB(T, y, y->right);

        //ERRO: se y é filho direita de z, então existe um caso especial
            //Nesse caso, x, que é filho direita de y, pode ser nil
                //Se ele for nil e chamarem delete-fixup para ele? Se ele for o duplo-preto?
                //Como o pai será acessado?
                    //Por isso, é preciso atribuir y ao T.nil

        //troca de ponteiros -> coloca y no lugar de z
        //isso daqui está certo ->tem que colocar y no lugar de z e o filho esquerda de z em y
            //independente do caso
        transplant_RB(T, z, y);
        y->left = z->left;
        y->left->father = y;

        //ERRO: isso daqui só acontece só acontece se sucessor não é filho direita de z
            //se for, isso aqui está atribuindo ponteiros erroneamente
        y->right = z->right;
        y->right->father = y;

        y->color = z->color;    //pinta de y de antiga cor de z
    }

    //se y antigo era preto -> delete fixup
    if (y_original_color == BLACK)
        delete_fixup_RB(T, x);
}

void delete_fixup_RB ()
{
    
}