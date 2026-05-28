/* ENUNCIADO:
    Modifique a estrutura de dados do nó, removendo o campo que guarda a
    altura da sub-árvore que tem raiz no nó.

    No lugar da altura, você deve guardar na estrutura de dados do nó o fator
    de balanceamento do nó, que é um valor inteiro no intervalo [-1,+1].

    Você deve alterar as funções da biblioteca para funcionarem com o fator
    de balanceamento no lugar da altura
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct no {
    int chave;
    int fb;
    struct no *pai;
    struct no *esq;
    struct no *dir;
} no;


typedef struct {
    no *raiz;
} arvore;


no* tree_insert(arvore *t, no *z) 
{
    no *x, *y;

    x = t->raiz;
    y = NULL;

    while(x != NULL) 
    {
        y = x;

        if(z->chave < x->chave)
            x = x->esq;

        else
            x = x->dir;
    }
    z->pai = y;

    if(y == NULL)
        t->raiz = z;

    else if(z->chave < y->chave)
        y->esq = z;

    else
        y->dir = z;

    return y;
}


void transplant(arvore *t, no *u, no *v) 
{
    if(u->pai == NULL)
        t->raiz = v;

    else if(u == u->pai->esq)
        u->pai->esq = v;

    else
        u->pai->dir = v;

    if(v != NULL)
        v->pai = u->pai;
}


no* tree_minimum(no *x) 
{
    while(x->esq != NULL)
        x = x->esq;

    return x;
}


no* tree_delete(arvore *t, no *z) 
{
    no *x, *y;

    x = z->pai;

    if(z->esq == NULL)
        transplant(t, z, z->dir);

    else if(z->dir == NULL)
        transplant(t, z, z->esq);

    else 
    {
        y = tree_minimum(z->dir); //sucessor
        x = y->pai;

        if(y != z->dir) 
        {
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }

    return x;
}


no* rot_esq(no *p) 
{
    no *q;

    q = p->dir;

    p->dir = q->esq;
    if(p->dir != NULL)
        p->dir->pai = p;
    
    q->esq = p;
    q->pai = p->pai;
    p->pai = q;    

    //atualiza fatores de balanceamento
    //p->fb == +2
    if (q->fb == 0)
    {
        p->fb = +1;
        q->fb = -1;
    } 
    else //q->fb == +1
    {
        p->fb = 0;
        q->fb = 0;
    }

    return q;
}


no* rot_dir(no *p) 
{
    no *q;

    q = p->esq;

    p->esq = q->dir;
    if(p->esq != NULL)
        p->esq->pai = p;

    q->dir = p;
    q->pai = p->pai;
    p->pai = q;  

    //atualiza fatores de balanceamento
    //p->fb == -2
    if (q->fb == 0) 
    {
        p->fb = -1;
        q->fb = +1;
    } 
    else //q->gb == -1
    {
        p->fb = 0;
        q->fb = 0;
    }

    return q;
}


no* rot_esqdir(no *p) {
    no *q, *r;
    int fb_r;

    q = p->esq;
    r = q->dir; //neto
    fb_r = r->fb; //guarda fb antigo do neto

    p->esq = r->dir;
    if(p->esq)
        p->esq->pai = p;
    q->dir = r->esq;
    if(q->dir)
        q->dir->pai = q;
    r->esq = q;
    r->dir = p;

    r->pai = p->pai;
    p->pai = r;
    q->pai = r;

    //atualiza fb com base em fb antigo do neto (r)
    //p->fb == -2 e q->fb == +1
    r->fb = 0;
    if (fb_r == 0) 
    {
        p->fb = 0;
        q->fb = 0;
    }
    else if (fb_r == +1) 
    {
        p->fb = 0;
        q->fb = -1;
    } 
    else //fb_r == -1 
    { 
        p->fb = +1;
        q->fb = 0;
    }

    return r;
}


no* rot_diresq(no *p) {
    no *q, *r;
    int fb_r;

    q = p->dir;
    r = q->esq; //neto
    fb_r = r->fb; //guarda fb antigo do neto

    p->dir = r->esq;
    if(p->dir)
        p->dir->pai = p;
    q->esq = r->dir;
    if(q->esq)
        q->esq->pai = q;
    r->dir = q;
    r->esq = p;

    r->pai = p->pai;
    p->pai = r;
    q->pai = r;

    //p->fb == +2 e q->fb == -1
    r->fb = 0;
    if (fb_r == 0) 
    {
        p->fb = 0;
        q->fb = 0;
    } 
    else if (fb_r == -1) 
    {
        p->fb = 0;
        q->fb = +1;
    } 
    else //fb_r == +1 
    { 
        p->fb = -1;
        q->fb = 0;
    }

    return r;
}


void troca_filho(arvore *t, no *u, no *v) 
{
    if(v->pai == NULL)
        t->raiz = v;

    else if(u == v->pai->esq)
        v->pai->esq = v;

    else
        v->pai->dir = v;
}


no* avl_balance(no *x) 
{
    no* y;

    if (x->fb < -1) 
    {
        //Verificar alinahmento de raiz e raiz_sub
        if (x->esq->fb <= 0) //Sinais de raiz e raiz_sub iguais -> rotação simples
            y = rot_dir(x);
        else                    //Sinais contrários -> rotação dupla
            y = rot_esqdir(x);
    } 
    else //x->fb > 1
    {         
        if (x->dir->fb >= 0)
            y = rot_esq(x);
        else
            y = rot_diresq(x);
    }

    return y;
}


void avl_insert(arvore *t, no *z) 
{
    no *raiz, *raiz_sub, *nova_raiz;
    int aumentou_subarvore;

    raiz = tree_insert(t, z); //x é o pai de z, após inserção 
    raiz_sub = z;

    z->fb = 0;
    z->esq = NULL;
    z->dir = NULL;
    
    aumentou_subarvore = 1;

    while (raiz != NULL && aumentou_subarvore)
    {
        //Atualiza fb
        if (raiz_sub == raiz->esq)
            raiz->fb--;
        else 
            raiz->fb++;
        
        //Decide o que fazer
        if (raiz->fb == 0) //se inserção balanceou árvore, então termina
        {
            aumentou_subarvore = 0;
            break;
        }

        else if (abs(raiz->fb) == 1) //Desbalanceou árvore de um lado, então a altura subiu
            aumentou_subarvore = 1;

        else //desbalanceou mais que o permitido -> rotação
        {
            nova_raiz = avl_balance(raiz);

            troca_filho(t, raiz, nova_raiz);
            raiz = nova_raiz;

            aumentou_subarvore = 0;
            break;
        }

        //Sobe um nível
        raiz_sub = raiz;
        raiz = raiz->pai;
    } 
}

void avl_delete(arvore *t, no *z) 
{
    no *y;
    no *raiz, *raiz_sub, *nova_raiz;
    int diminuiu_subarvore;

    //Quem é a subarvore que vai diminuir de altura?
    if (z->esq == NULL) 
        raiz_sub = z->dir;

    else if (z->dir == NULL)
        raiz_sub = z->esq;

    else 
    {
        y = tree_minimum(z->dir);
        raiz_sub = y->dir; 
    }
    
    raiz = tree_delete(t, z); //"raiz" é pai daonde ocorreu alteração
    
    diminuiu_subarvore = 1;
    
    while (raiz != NULL && diminuiu_subarvore)
    {
        //Atualiza fb - (Lógica inversa da inserção)
        if (raiz_sub == raiz->esq)
            raiz->fb++;
        else 
            raiz->fb--;

        //Decide o que deve ser feito
        if (raiz->fb == 0)
            diminuiu_subarvore = 1;
        
        else if (abs(raiz->fb) == 1)
            diminuiu_subarvore = 0;

        else //Desbalanceou mais que o permitido -> rotação
        {
            nova_raiz = avl_balance(raiz);

            troca_filho(t, raiz, nova_raiz);
            raiz = nova_raiz;

            if (raiz->fb == 0)
                diminuiu_subarvore = 1;
            else
                diminuiu_subarvore = 0;
        }

        //Sobe um nível
        raiz_sub = raiz;
        raiz = raiz->pai;
    }
}