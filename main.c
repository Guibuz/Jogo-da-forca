// Guilherme Buzatto Donat - 399042
// Francisco Davi de Oliveira - 499205
// Francisco Gleidson Freitas - 504355

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int categoria;
FILE* f;

void abertura() {
    strcpy(palavrasecreta, "");
    strcpy(chutes, "");
    chutesdados = 0;
    printf("                                                *****************\n");
    printf("                                                * Jogo da Forca *\n");
    printf("                                                *****************\n");
}

void menuCategoria(){
    printf("                                                \n                                                -- Categorias --\n");
    printf("                                                1 - Frutas\n                                                2 - Animais\n                                                3 - Animes\n");
    printf("                                                Escolha uma categoria: ");
    scanf("%d", &categoria);
    system("cls");
    adicionapalavra();
    system("cls");
}

void abreCategoria(){
    if(categoria == 1){
        f = fopen("fruta.txt", "r"); 
    }else if(categoria == 2){
        f = fopen("animais.txt", "r");  
    }else if(categoria == 3){
        f = fopen("animes.txt", "r");  
    }
}

int palavraValida(char palavra[TAMANHO_PALAVRA]){ 
    abreCategoria();

    char palavraArq[TAMANHO_PALAVRA];

    int qtd;
    fscanf(f ,"%d", &qtd);

    for(int i=0;i<qtd;i++){
        fscanf(f, "%s", palavraArq);
        if(!strcmp(palavraArq, palavra)){
            fclose(f);
            printf("Esta palavra ja foi cadastrada...Tente outra!\n\n");
            return 0;
        }
    }
    printf("Palavra adicionada com sucesso no banco de dados!\n\n");
    system("cls");
    fclose(f);
    return 1;
}

void chuta() {
    char chute;
    printf("Qual a letra?\n");
    scanf(" %c", &chute);

    chutes[chutesdados] = toupper(chute);
}

int jachutou(char letra) {
    int achou = 0;
    for (int i = 0; i < chutesdados; i++) {
        if(chutes[i] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();
    
    printf("                                                Tentativas: %d\n", 5 - erros);

    printf("                                                  _______      \n");
    printf("                                                 |/      |     \n");
    printf("                                                 |      %c%c%c    \n", (erros>= 1 ? '(' : ' '), (erros>= 1 ? '_' : ' '),(erros>= 1 ? ')' : ' '));
    printf("                                                 |      %c%c%c   \n",  (erros>= 2 ? '\\' : ' '), (erros>= 2 ? '|' : ' '),(erros>= 3 ? '/' : ' '));
    printf("                                                 |       %c     \n",   (erros>= 4 ? '|' : ' '));
    printf("                                                 |      %c %c   \n",   (erros>= 5 ? '/' : ' '), (erros>= 5 ? '\\' : ' '));
    printf("                                                 |             \n");
    printf("                                                _|___          \n");
    printf("                                                \n\n"); 

    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
        
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionapalavra() {
char quer;
    printf("Voce deseja adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);

    if(toupper(quer) == 'S'){
        char novapalavra[TAMANHO_PALAVRA];

        do{

            printf("Digite uma palavra relacionada a categoria escolhida: ");
            scanf("%s", novapalavra);

            
            for(int i=0; novapalavra[i] != '\0'; i++){
                novapalavra[i] = toupper(novapalavra[i]);
            }

        }while(!palavraValida(novapalavra));

        if(categoria == 1){
            f = fopen("fruta.txt", "r+");  
        }else if(categoria == 2){
            f = fopen("animais.txt", "r+");  
        }else if(categoria == 3){
            f = fopen("animes.txt", "r+");  
        }

        if(f == 0){ 
            printf("Banco de dados de palavras nao disponivel.\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0 , SEEK_SET); 
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); 
        fprintf(f, "\n%s", novapalavra);

        
        fclose(f);
        
    }
}

void escolhepalavra() {
    abreCategoria();
    
    if(f == 0){
        printf("                                                Desculpe! banco de dados nao disponivel\n\n");
        exit(1);
    }

    int qtdepalavras;
    fscanf(f, "%d", &qtdepalavras);

    srand(time(0));
    int randomico = rand() % qtdepalavras;

    for (int i = 0; i <= randomico ; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int acertou() {
    
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
           
            return  0;
        }
    }
    return 1;
}

int chuteserrados() {
    
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int jogar_de_novo() {
    char escolha;
    printf("Deseja jogar novamente? (S/N)\n");
    scanf(" %c", &escolha);
    if(toupper(escolha) == 'S'){
        return 1;
    }
    system("cls");

    printf("                                                    ************************************\n");
    printf("                                                    *      Encerrando o Programa       *\n");
    printf("                                                    ************************************\n");
   
    system("pause");
    return 0;
}

int main() {

setlocale(LC_ALL, "Portuguese_Brazil");
    
   do {

system("cls");
    abertura();
    menuCategoria();
    escolhepalavra();

    do {
        desenhaforca();
        chuta();
        chutesdados++;
        system("cls"); 
        
    } while (!acertou() && !enforcou());

    if(acertou()) {
        desenhaforca();

        printf("                                                ************************************\n");
        printf("                                                *           PARABENS!!!            *\n");
        printf("                                                *      Voce Acertou a Palavra      *\n");
        printf("                                                ************************************\n");

    } else {
        desenhaforca();
        printf("\n                                                Puxa vida! Voce foi enforcado!\n");
        printf("                                                A palavra era **%s**\n", palavrasecreta);

        printf("                                                ************************************\n");
        printf("                                                *      Numero Maximo de Erros      *\n");
        printf("                                                *           FIM DE JOGO            *\n");
        printf("                                                ************************************\n");

    }

    } while(jogar_de_novo());
    system("cls"); 
}
