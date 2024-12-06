#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Como fazer um campo minado em c

/*
    CELULA
    eBomba 0 ou 1
    estaAberta 0 ou 1
    vizinhos 0 a 4
*/

typedef struct{
    int eBomba;
    int estaAberta;
    int vizinhos;
}Celula;

//Variáveis Globais
Celula jogo[10][10];
int l,c,tam = 10;

//Pocedimento para inicializar a matriz do jogo
void inicializarJogo(){
    for(l=0;l<tam;l++){
        for(c=0;c<tam;c++){
            jogo[l][c].eBomba = 0;
            jogo[l][c].estaAberta = 0;
            jogo[l][c].vizinhos = 0;
        }
    }
}

//Procedimento para sortear n bombas
void sortearBombas(int n){
    int i;
    srand(time(NULL));
    for(i=1;i<=n;i++){
        l = rand()%tam;
        c = rand()%tam;
        if(jogo[l][c].eBomba == 0){
            jogo[l][c].eBomba = 1;
        }
        else{
            i--;
        }
    }
}

//Função que retorna se um par de coordenadas é válido ou não
int Valido(int l, int c){
    if(l >= 0 && l<tam && c>=0 && c<tam){
        return 1;
    }  
    return 0;
}

/*
    Funcão que retorna a quantidade de bombas na vizinhança de 1 c
    n - quantidade de bombas
*/
int quantBombasVizinhas(int l, int c){
    int quantidade = 0;
    if(Valido(l-1,c) && jogo[l-1][c].eBomba){
        quantidade++;
    }
    if(Valido(l+1,c) && jogo[l+1][c].eBomba){
        quantidade++;
    }
    if(Valido(l,c-1) && jogo[l][c-1].eBomba){
        quantidade++;
    }
    if(Valido(l,c+1) && jogo[l][c+1].eBomba){
        quantidade++;
    }
    return quantidade;
}

//Procedimento para contar as bombas vizinhas
void contarBombas(){
    for(l=0;l<tam;l++){
        for(c=0;c<tam;c++){
            jogo[l][c].vizinhos = quantBombasVizinhas(l,c);
        }
    }
}

//Procedimento para imprimir o jogo
void imprimirJogo(){

    printf("\n\n\t   ");
    for(l=0;l<tam;l++){
        printf(" %d  ",l);
    }
    printf("\n\t  -----------------------------------------\n");
    for(l=0;l<tam;l++){
        printf("\t%d |",l);
        for(c=0;c<tam;c++){
            if(jogo[l][c].estaAberta){
                if(jogo[l][c].eBomba){
                    printf(" * ");
                }
                else{
                    printf(" %d ",jogo[l][c].vizinhos);
                }
            }
            else{
                printf("   ");
            }
            printf("|");
        }
        printf("\n\t  -----------------------------------------\n");
    }
}

//Procedimento para abrir a coordenada digitada
void abrirCelula(int l, int c){
    if(Valido(l,c) == 1 && jogo[l][c].estaAberta == 0){
        jogo[l][c].estaAberta = 1;
        if(jogo[l][c].vizinhos == 0){
            abrirCelula(l-1,c);
            abrirCelula(l+1,c);
            abrirCelula(l,c-1);
            abrirCelula(l,c+1);
        }
    }
}


/*
    Função para verificar vitoria
    1 - ganhou
    0 - perdeu
*/
int ganhou(){
    int quantidade = 0;
    for(l=0;l<tam;l++){
        for(c=0;c<tam;c++){
            if(jogo[l][c].estaAberta == 0 && jogo[l][c].eBomba == 0){
                quantidade++;
            }
        }
    }    
    return quantidade;
}

//Procedimento para a leitura das coordenadas
void jogar(){
    int linha,coluna;
    do{ 
        imprimirJogo();
        do{
            printf("\nInforme a coordenadas de linha e coluna:");
            scanf("%d%d", &linha, &coluna);

            if(Valido(linha,coluna) == 0){
                printf("\n Coordenada Invalida");
            }
        }while(Valido(linha,coluna) == 0 || jogo[linha][coluna].estaAberta == 1);

        abrirCelula(linha,coluna);
    }while(ganhou() != 0 && jogo[linha][coluna].eBomba == 0);
    
    if(jogo[linha][coluna].eBomba == 1){
        printf("\n\tQue pena! Voce perdeu!!\n");
    }
    else{
        printf("\n\tParabens voce ganhou!!\n");
    }
    imprimirJogo();
    
}

void main(){

    int opcao;

    do{
        inicializarJogo();
        sortearBombas(20);
        contarBombas();
        printf("\n\t\t\tCAMPO MINADO\n");
        jogar();

        printf("\nDigite 1 para jogar novamente:");
        scanf("%d", &opcao);
    }while(opcao == 1);
    printf("\nObrigado por jogar!!\n");
}