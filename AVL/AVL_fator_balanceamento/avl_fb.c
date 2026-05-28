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
#define ALT(a) ((a == NULL)?(-1):(a->altura))

typedef struct no {
    int chave;
    int altura;
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

    p->altura = 1 + MAX(ALT(p->esq), ALT(p->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));

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

    p->altura = 1 + MAX(ALT(p->esq), ALT(p->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));

    return q;
}


no* rot_esqdir(no *p) 
{
    p->esq = rot_esq(p->esq);

    p->esq->pai = p;

    return rot_dir(p);
}


no* rot_diresq(no *p) 
{
    p->dir = rot_dir(p->esq);

    p->dir->pai = p;

    return rot_esq(p);
}


no* avl_balance(no *x) 
{
    int fb;
    no *y;

    y = x;

    fb = ALT(x->dir) - ALT(x->esq);

    if(fb < -1)
        if(ALT(x->esq->esq) < ALT(x->esq->dir))
            y = rot_esqdir(x);
        else
            y = rot_dir(x);

    else if(fb > 1)
        if(ALT(x->dir->dir) < ALT(x->dir->esq))
            y = rot_diresq(x);
        else
            y = rot_esq(x);

    return y;
}

//?????
void troca_filho(arvore *t, no *u, no *v) 
{
    if(v->pai == NULL)
        t->raiz = v;

    else if(u == v->pai->esq)
        v->pai->esq = v;

    else
        v->pai->dir = v;
}


void avl_insert(arvore *t, no *z) {
    int a;
    no *x, *y;

    z->altura = 0;

    x = tree_insert(t, z); //x é o pai de z, após inserção

    //vai subindo, atualizando as alturas e rotacionando
    while(x != NULL) 
    {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));

        y = avl_balance(x);

        if(y != x) //Se houve rotação
        {
            troca_filho(t, x, y);
            break;
        }

        if(x->altura == a) //Se altura continuar igual, termina
            break;

        x->altura = a; //atualiza altura

        x = x->pai; //vai subindo
    }        
}

void avl_delete(arvore *t, no *z) 
{
    int fb, a;
    no *x, *y, *p;
    
    x = tree_delete(t, z);

    while(x != NULL) 
    {
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));

        y = avl_balance(x);

        if(y != x) 
        {
            troca_filho(t, x, y);
            x = y;
        }

        if(x->altura == a)
            break;

        x->altura = a;

        x = x->pai;
    }        
}

/*------------ Funções alteradas ----------------*/
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
    int aux = q->fb;
    q->fb = q->fb - 1;
    p->fb = aux - p->fb - 1; //não sei se tá certo!!!!!!!!!1

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
    int aux = q->fb;
    q->fb = q->fb + 1;
    p->fb = aux - p->fb + 1;

    return q;
}


no* rot_esqdir(no *p) 
{
    p->esq = rot_esq(p->esq);

    p->esq->pai = p;

    return rot_dir(p);
}


no* rot_diresq(no *p) 
{
    p->dir = rot_dir(p->esq);

    p->dir->pai = p;

    return rot_esq(p);
}

no* avl_balance(no *x) 
{
    /* Faltou juntar insert e delete aqui */
}


void avl_insert(arvore *t, no *z) 
{
    no *raiz, *raiz_sub;

    raiz = tree_insert(t, z); //x é o pai de z, após inserção 
    raiz_sub = z;

    int aumentou_subarvore = 1;

    while (raiz != NULL && aumentou_subarvore)
    {
        /*-----------------avl_balance--------------------*/
        //Atualiza fb
        if (raiz_sub == raiz->esq)
            raiz->fb--;
        else 
            raiz->fb++;
        
        //Decide o que fazer
        aumentou_subarvore = 0;

        if (raiz->fb == 0) //se inserção balanceou árvore, então termina
            break;
        
        else if (abs(raiz->fb) == 1) //Desbalanceou árvore de um lado, então a altura subiu
            aumentou_subarvore = 1;

        else //desbalanceou mais que o permitido -> rotação
        {
            //Verificar alinahmento de raiz sub e raiz sub sub
                //Sinais de raiz e raiz_sub iguais -> rotação simples
                //Sinais contrários -> rotação dupla
        }
        /*-----------------avl_balance--------------------*/

        //Sobe um nível
        raiz_sub = raiz;
        raiz = raiz->pai;
    } 
}

void avl_delete(arvore *t, no *z) 
{
  
    int diminuiu_subarvore;
    no *x, *y;
    no *raiz, *raiz_sub;

    y = z->pai;

    //Marca subarvore "irmã" de z em x
    if (z == y->esq)
        x = y->dir;
    else //z == y->dir
        x = y->esq;

    raiz = tree_delete(t, z); //raiz é pai daonde ocorreu alteração

    //Quem é a subarvore que diminui de altura? está na esquerda ou direita?
    if (raiz == y) //"Subiu" uma subarvore
        if (x == raiz->dir)
            raiz_sub = raiz->esq;
        else
            raiz_sub = raiz->dir;
    else //então, o sucessor foi colocado no lugar
        raiz_sub = raiz->esq;
    
    diminuiu_subarvore = 1;
    
    while (raiz != NULL && diminuiu_subarvore)
    {
        /*-----------------avl_balance--------------------*/

        //Atualiza fb - (Lógica inversa da inserção)
        if (raiz_sub == raiz->esq)
            raiz->fb++;
        else 
            raiz->fb++;

        if (raiz->fb == 0)
            diminuiu_subarvore = 1;
        
        else if (abs(raiz->fb) == 1)
            diminuiu_subarvore = 0;

        else //desbalanceou mais que o permitido -> rotação
        {
            //Verificar alinahmento de raiz sub e raiz sub sub
                //Sinais de raiz e raiz_sub iguais -> rotação simples
                //Sinais contrários -> rotação dupla
            //diminui subarvore????
        }

        /*-----------------avl_balance--------------------*/

        //Sobe um nível
        raiz_sub = raiz;
        raiz = raiz->pai;
    }
}