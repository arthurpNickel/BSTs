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

void delete_fixup_RB (TreeRB *T, NoRB *x)
{
    NoRB *w;
    //Enquanto x não for raiz e x for preto
    while ( x != T->root && x->color == BLACK )
    {
        if ( x == x->father->left )
        {
            w = x->father->right;

            //Se o irmão for vermelho
            if ( w->color == RED )
            {
                rot_left(T, x->father); //rotaciona pai
                //pinta irmão de preto e pai de vermelho
                    //Manter alturas pretas
                w->color = BLACK; //O pai era com certeza preto -> então pinta para manter altura preta da subarvore à direita
                x->father->color = RED; //manter altura preta intacta no caminho do novo irmão de x

                //ERRO: Colocar w = x->father->right aqui (vai cair em algum caso em baixo)
            }
            //irmão preto
            //Se o irmão tem filhos pretos
            //ERRO: Aqui não é else if -> o caso 1 sempre será seguido de outro
            else if ( w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED; //pinta irmão de vermelho
                x = x->father;  //x recebe pai
            }
            else
            {
                //Se o irmão tem filho desalinhado vermelho e filho alinhado preto
                //ERRO: Não precisa da primeira verificação -> black black já foi conferido em cima
                if( w->left->color == RED && w->right->color == BLACK )
                {
                    w = rot_right(T, w);    //rotação simples no irmão
                    //irmão recebe veremlho e sobrinho preto (inverteu o parentesco)
                    w->color = BLACK;
                    w->right->color = RED;
                }
                //Se o irmão tem filho alinhado vermelho
                rot_left(x->father);    //rotação no pai

                //irmão (novo avô) recebe cor do pai -> não mudar para cima
                w->color = x->father->color;

                //pai recebe preto -> fim do duplo preto
                x->father->color = BLACK;

                //sobrinho recebe preto -> não mudar altura preta na árvore do irmão
                w->right->color = BLACK;

                x = T->root;    //para terminar o laço
            }
        }
        else
        {
            //simétrico
        }
    }
    x->color = BLACK;   //pinta x de vermelho -> pinta nó veremlho (pode ser raiz!)
}