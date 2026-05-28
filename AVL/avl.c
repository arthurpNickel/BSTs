/* Implementação das funções da árvore AVL */

#include <stdio.h>

typedef struct no
{
    int chave;
    int altura;
    int fb;
    no *pai;
    no *esq;
    no *dir;
} no;

typedef struct raiz
{
    no *raiz;
} raiz;

void transplant(raiz *T, no *u, no *v)
{
    //acertar ponteiro pai -> filho
    if (u->pai == NULL)
        T->raiz = v;
    
    else if (u->pai->esq = u)
        u->pai->esq = v;

    else if (u->pai->dir = u)
        u->pai->dir = v;

    //acerta ponteiro filho -> pai
    if (v != NULL) //FALTOU ESSA VERIFICAÇÃO!!!!!!!!!!!!!!
        v->pai = u->pai
}

no *rot_esq(no *b); 

no *rot_dir(no *b)
{
    no *d;

    d = b->esq; //nomear d

    //trocar sub arvore (só uma conexão)
    b->esq = d->dir;
    if (b->esq != NULL) 
        b->esq->pai = b;

    //conexao da nova subraiz
    d->dir = b;
    b->pai = d;

    d->pai = b->pai; //FALTOU ESSA!!!!!!!!!! -> Não precisa de verdade verdadeira

    b->altura = MAX(ALT(b->esq), ALT(b->dir)) + 1;
    d->altura = MAX(ALT(d->esq), ALT(d->dir)) + 1;

    return d; //retorna nova raiz da sub arvore
}

no *rot_esq_dir();

no *rot_dir_esq();

no *tree_min();

no *tree_max();

no *sucessor();

no *antecessor();

no *avl_search();

no *avl_balance(raiz T, no *x)
{
    no *r = x;

    int fb;
    
    fb = ALT(x->dir) - ALT(x->esq);

    if (fb < 1) //esquerda é maior que direita
    {
        if (ALT(x->esq->esq) > ALT(x->esq->dir)) //se estiver "alinhado" o desbalanceamento
            r = rot_dir();
        else                                    //se o desbalanceamento estiver "no meio"
            r = rot_esq_dir();
    }
    else if (fb > 1)
    {
        if (ALT(x->dir->dir) > ALT(x->dir->esq))
            r = rot_esq();
        else
            r = rot_dir_esq();
    }

    return r;
}

no *tree_delete(raiz *T,no *z)
{
    no *p, *y;

    p = z->pai;

    if (z->esq == NULL)
        transplant(T, z, z->dir);       //sobe filho a direita do removido
    
    else if (z->dir == NULL)
        transplant(T, z, z->esq);       //sobe filho a esquerda do removido

    else
    {
        y = sucessor(T, y);             //!!!!!!!!! minimo, não sucessor

        p = y->pai;                     //!!!!!!!!! Estrutura que muda é o pai do sucessor -> mesmo podendo ser o sucessor depois que alocado corretamente

        if (y != z->dir)
        {
            transplant(T, y, y->dir);   // Sobe filho do sucessor
            //Conecta sucessor no filho a direita do removido
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(T, z, y);            //Conecta sucessor ao pai do removido

        //Conecta sucessor no filho a esquerda do removido
        y->esq = z->esq;
        y->esq->pai = y;
    }

    return p;
}

//ERRADO   
no *avl_delete(raiz *T,no *z)
{
    int alt_antiga;
    no *p;

    p = tree_delete(T, z);

    while (p != NULL) //!!!!! ou p->pai????
    {
        alt_antiga = p->altura;

        p->altura = MAX(ALT(p->esq), ALT(p->dir)) + 1; //Não tem isso!!!!!!!!!!!!!!!

        //comparar se altura continua igual
        if (alt_antiga == p->altura)
            break;

        p = avl_balance(T, p);

        //avaliar se rotacionou -> muda subraiz

        //comparação de altura vem aqui
            //Q: onde a altura é atualizada???

        //aqui que anda na árvore -> entender  oque rotação retorna
    }

    return p;
}

void avl_delete(raiz *T,no *z)
{
    int h;
    no *x, *y;

    x = tree_delete(T, z);

    while (x != NULL) //!!!!! ou p->pai????
    {
        h = MAX(ALT(x->esq), ALT(x->dir)) + 1;

        y = avl_balance(T, x);

        if (x != y) //avl_balance rotacionou
        {
            transplant (T, x, y) //ponteiros do pai de x passam para y
            x = y;
        }

        //comparar se altura continua igual
        //na rotação, a altura de x é atualizada
        if (h == x->altura)
            break;
        
        x->altura = h; //PQ?????

        //aqui que anda na árvore -> entender  oque rotação retorna
        x = x->pai
    }
}

no *tree_insert()

no *avl_insert()
{

}

void avl_delete(arvore *t, no *z) {
    int fb, a;
    no *x, *y, *p;
    
    x = tree_delete(t, z);
    while(x != NULL) {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));
        y = avl_balance(x);
        if(y != x) {
            transplant(t, x, y);
            x = y;
        }
        if(x->altura == a)
            break;
        x->altura = a; //??????????????ww
        x = x->pai;
    }        
}

void avl_insert(arvore *t, no *z) 
{
    int a;
    no *x, *y;

    z->altura = 0;
    x = tree_insert(t, z);

    while(x != NULL) 
    {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));

        y = avl_balance(x);

        if(y != x) //Se transplantou
        {
            transplant(t, x, y);
            break;
        }

        if(x->altura == a)
            break;

        x->altura = a;

        x = x->pai;
    }        
}
