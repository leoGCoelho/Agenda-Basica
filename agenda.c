/*  Author: Leonardo Coelho - M2
*   Agenda I
*/

////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////

//=====================================
struct stack{
    void *info;
    struct stack *prox;
};
typedef struct stack STACK;
//==============================

struct var{
    int op;
    int sortOp;
    int aux;
    int i;
    int j;
    int tamBuffer;
    int n; //n = numero de contatos da agenda
    char nomeSearch[40];
    int mid; //mid = meio para quick sort
    int l; //l = esquerda para quick sort (left)
    int r; //d = direita para quick sort (right)
    int histN;
    STACK *topo;
};
typedef struct var VAR;

struct contato{
    char nome[40];
    char tel[15];
    char email[40];
};
typedef struct contato CONTATO;

////////////////////////////////////////////////////////////////////////////////////
//================ Funcoes =================
void* incluir(void *pBuffer);
void* apagar(void *pBuffer);
void buscar(void *pBuffer);
void listar(void *pBuffer);
void* mergeSort(void *pBuffer);
void* bubbleSort(void *pBuffer);
void* selectSort(void *pBuffer);
void* quickSort(void *pBuffer);
void* insertionSort(void *pBuffer);
//========
STACK* push(void *pBuffer);
STACK* pop(void *pBuffer);
int histEmpty(void *pBuffer);
int histSize(void *pBuffer);

////////////////////////////////////////////////////////////////////////////////////
//================  Main   =================
int main(){
    void *pBuffer;    VAR *x;   STACK *hist;

    if(!(pBuffer = malloc(sizeof(VAR)))){   // (!(pBuffer = ...))  == ((pBuffer = ...) == NUll)
        printf("\nEspaço de memoria indisponivel\n");
        exit(1);
    }


    x = pBuffer;    // x recebe o valor alocado de pBuffer
    x->n = 0;       // numero de contato inicial da agenda = 0
    x->topo = NULL;
    x->histN = 0;
    x->tamBuffer = sizeof(VAR);
    hist = pBuffer + sizeof(VAR);

    for(;;){
        printf(" > AGENDA >\n\n (1) Inclur\n (2) Buscar\n (3) Listar\n (4) Apagar\n (5) Ordenar\n\n (0) Sair\n\n-> ");
        scanf("%d", &x->op);

        printf("\n============================================================\n");
        switch(x->op){
            case 0:
                printf("\n > AGENDA > SAIR >\n\nSaindo do programa...\n\n");
                free(pBuffer);
                exit(1);
            break;
            case 1:
                printf(" > AGENDA > INCLUIR >\n");
                pBuffer = incluir(pBuffer);
                x->n++;
            break;
            case 2:
                printf(" > AGENDA > BUSCAR >\n");
                if(x->n == 0){
                    printf("\n(!) Inclua um primeiro contato (!)\n");   // verificaçao de existe algum contato na agenda
                    break;
                }

                buscar(pBuffer);
            break;
            case 3:
                printf(" > AGENDA > LISTAR >\n");
                if(x->n == 0){
                    printf("\n(!) Inclua um primeiro contato (!)\n");   // verificaçao de existe algum contato na agenda
                    break;
                }

                listar(pBuffer);
            break;
            case 4:
                printf(" > AGENDA > APAGAR >\n");
                if(x->n == 0){
                    printf("\n(!) Inclua um primeiro contato (!)\n");   // verificaçao de existe algum contato na agenda
                    break;
                }

                pBuffer = apagar(pBuffer);
            break;
            case 5:
                printf(" > AGENDA > ORDENAR >\n");
                if(x->n == 0){
                    printf("\n(!) Inclua alguns contatos primeiro | minimo 2 (!)\n");   // verificaçao de existe algum contato na agenda
                    break;
                }

                do{
                    printf("\n (1) Bubble Sort\n (2) Select Sort\n (3) Insertion Sort\n (4) Merge Sort\n (5) Quick Sort\n\n (6) Listar\n (0) Voltar\n\n-> ");
                    scanf("%d", &x->sortOp);

                    switch(x->sortOp){
                        case 0: break;
                        case 1:
                            printf("\n\n > AGENDA > ORDENAR > BUBBLE SORT >\n");
                            pBuffer = bubbleSort(pBuffer);
                        break;
                        case 2:
                            printf("\n\n > AGENDA > ORDENAR > SELECT SORT >\n");
                            pBuffer = selectSort(pBuffer);
                        break;
                        case 3:
                            printf("\n\n > AGENDA > ORDENAR > INSERTION SORT >\n");
                            pBuffer = insertionSort(pBuffer);
                        break;
                        case 4:
                            printf("\n\n > AGENDA > ORDENAR > MERGE SORT >\n");
                            pBuffer = mergeSort(pBuffer);
                        break;
                        case 5:
                            printf("\n\n > AGENDA > ORDENAR > QUICK SORT >\n");
                            pBuffer = quickSort(pBuffer);
                        break;
                        case 6:
                            printf("\n\n > AGENDA > ORDENAR > LISTAR >\n");
                            listar(pBuffer);
                        break;
                        default:
                            printf("\n(!) Comando incorreto! (!)\n");

                    }

                }while(x->sortOp != 0);

            break;

            default:
                printf("\n(!) Comando incorreto! (!)\n");
        }
            printf("\n============================================================\n");

    }

    free(pBuffer);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////
//================ Funcoes =================
void* incluir(void *pBuffer){ // Arrumar
    void *p;
    VAR *x1;
    CONTATO *c;

    x1 = pBuffer;

    x1->tamBuffer = x1->tamBuffer + sizeof(CONTATO);
    pBuffer = realloc(pBuffer, x1->tamBuffer);
    x1 = pBuffer;

    x1->n = x1->n + 1;

    p = pBuffer;
    p = p + sizeof(VAR);
    p = p + sizeof(CONTATO) * (x1->n-1);
    c = p;

    printf("\nNome: ");
    scanf("%s", c->nome); //&c->nome
    printf("Telefone: ");
    scanf("%s", c->tel);
    printf("Email: ");
    scanf("%s", c->email);

    return pBuffer;
}

void* apagar(void *pBuffer){
    void *p;
    VAR *x2;
    CONTATO *c;

    p = pBuffer;
    x2 = pBuffer;

    if(x2->n > 0){
        p = p + sizeof(VAR);
        c = p;

        printf("\nDigite o nome do contato: ");
        scanf("%s", x2->nomeSearch);

        for(x2->i = x2->aux; x2->i < x2->n; x2->i++)
            c[x2->i] = c[x2->i+1];

        x2->n = x2->n - 1;
        x2->tamBuffer = x2->tamBuffer - sizeof(CONTATO);
        pBuffer = realloc(pBuffer, x2->tamBuffer);
        printf("\nContato deletado com sucesso!\n");

        return pBuffer;
    }

}

void buscar(void *pBuffer){
    void *p;
    VAR *x3;
    CONTATO *c;

    p = pBuffer;
    x3 = pBuffer;

    if(x3->n > 0){
        p = p + sizeof(VAR);
        c = p;

        printf("\nDigite o nome do contato: ");
        scanf("%s", x3->nomeSearch);

        for(x3->i = 0; x3->i < x3->n; x3->i++){
            if((strcmp(x3->nomeSearch, c[x3->i].nome)) == 0){
                printf("\nContato encontrado!\n\nNome: %s\nTelefone: %s\nEmail: %s\n", c[x3->i].nome, c[x3->i].tel, c[x3->i].email);
            }
        }
    }

}

void listar(void *pBuffer){
    void *p;
    VAR *x4;
    CONTATO *c;

    p = pBuffer;
    x4 = pBuffer;

    p = p + sizeof(VAR);
    c = p;

    for(x4->i = 0; x4->i < x4->n; x4->i++){
        printf("\nNome: %s\nTelefone: %s\nEmail: %s\n", c[x4->i].nome, c[x4->i].tel, c[x4->i].email);
    }

}

void* mergeSort(void *pBuffer){
    void *p;
    VAR *x5;
    CONTATO *c, *aux;

    x5 = pBuffer;
    p = pBuffer;

    printf("\nAgenda ordenada!\n");
    return pBuffer;

}

void* bubbleSort(void *pBuffer){
    void *p;
    VAR *x6;
    CONTATO *c;

    x6 = pBuffer;

    x6->tamBuffer = x6->tamBuffer + sizeof(CONTATO);
    pBuffer = realloc(pBuffer, x6->tamBuffer);
    x6 = pBuffer;

    x6->n = x6->n + 1;

    p = pBuffer;
    p = p + sizeof(VAR);
    p = p + sizeof(CONTATO) * (x6->n-1);
    c = p;

    for(x6->i = 0; x6->i < x6->n-2; x6->i++){
        for(x6->j = 0; x6->j < x6->n-1 - x6->n-2; x6->j++){
            if(c[x6->j].nome[0] > c[x6->j + 1].nome[0]){
                c[x6->n-1] = c[x6->j];
                c[x6->j] = c[x6->j+1];
                c[x6->j+1] = c[x6->n-1];
            }
        }

    }

        
    x6->n = x6->n - 1;
    x6->tamBuffer = x6->tamBuffer - sizeof(CONTATO);
    pBuffer = realloc(pBuffer, x6->tamBuffer);

    printf("\nAgenda ordenada!\n");
    return pBuffer;
}


void* selectSort(void *pBuffer){
    void *p;
    VAR *x7;
    CONTATO *c, *aux;

    x7 = pBuffer;
    p = pBuffer;

    p = p + sizeof(VAR);
    c = p;
    aux = c + sizeof(CONTATO) * (x7->n);



    printf("\nAgenda ordenada!\n");
    return pBuffer;

}

void* quickSort(void *pBuffer){
    void *p;
    VAR *x8;
    CONTATO *c, *aux;

    x8 = pBuffer;
    p = pBuffer;

    p = p + sizeof(VAR);
    c = p;
    aux = c + sizeof(CONTATO) * (x8->n);

    printf("\nAgenda ordenada!\n");
    return pBuffer;

}

void* insertionSort(void *pBuffer){
    void *p;
    VAR *x9;
    CONTATO *c, *aux;

    x9 = pBuffer;
    p = pBuffer;

    p = p + sizeof(VAR);
    c = p;
    aux = c + sizeof(CONTATO) * (x9->n-1);

    for(x9->j =0; x9->j < x9->n; x9->j++){
        x9->i = x9->j - 1;
        aux[0] = c[x9->j];

        while((x9->i >= 0) && (aux[0].nome[0] < c[x9->i].nome[0])){
            c[x9->i+1] = c[x9->i];
            x9->i--;
        }
        c[x9->i+1] = aux[0];

    }

    printf("\nAgenda ordenada!\n");
    return pBuffer;

}

//================ Historico ==========
STACK* push(void *pBuffer){
    void *p;
    VAR *x10;
    STACK *hist, *new;

    x10 = pBuffer;
    hist = pBuffer + sizeof(STACK);

    x10->tamBuffer = x10->tamBuffer + sizeof(STACK);
    x10 = pBuffer;

    x10->histN = x10->histN + 1;

    p = pBuffer;
    p = p + sizeof(VAR);
    p = p + sizeof(STACK);

    new = p;
    new->info = pBuffer;
    new->info = hist->prox;
    hist = new;

    return hist;

}

STACK* pop(void *pBuffer){
    void *p;
    VAR *x11;

    x11 = pBuffer;
    
    x11->tamBuffer = x11->tamBuffer + sizeof(STACK);
    x11 = pBuffer;

    x11->histN = x11->histN + 1;

    p = pBuffer;
    p = p + sizeof(VAR);
    p = p + sizeof(STACK);

}

int histEmpty(void *pBuffer){
    void *p;
    VAR *x14;

    x14 = pBuffer;
    p = pBuffer;

    if(x14->topo == NULL) return 1;
    else return 0;
}

int histSize(void *pBuffer){
    void *p;
    VAR *x15;

    x15 = pBuffer;
    p = pBuffer;

    return x15->histN;
}