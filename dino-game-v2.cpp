#include<stdio.h>
#include <stdlib.h> 
#include<conio.h>    // getche e kbhit
#include <windows.h> // função gotoxy, sleep

int menu(){
	
	int opcao;
	
	do {
		printf("--------------------------------\n");
		printf("            DINO GAME           \n");
		printf("--------------------------------\n");
		printf("Selecione uma opcao:\n");
		printf("1 - Iniciar jogo \n");
		printf("2 - Tutorial \n");
		printf("3 - Sair \n");
		scanf("%d", &opcao);
		
		if (opcao < 1 || opcao > 3) {
            printf("Opcao invalida, redigite!\n");
        }
	} while(opcao < 1 || opcao > 3);
	
	system("cls");
	return opcao;
}

// usada para posicionar o cursor em uma posição específica da tela
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// variavel global que controla a altura do dinossauro
int pos_vertical;
int dino(int pulo){
	
	static int pernasDino=1;	
	
	// correndo
	if(pulo == 0){
		pos_vertical = 0;
	}
	
	// descendo
	else if(pulo == 2){
		pos_vertical--;
	}
	
	//pulando
	else {
		pos_vertical++;
	}
	
	// organiza o dino na tela 
	gotoxy(2,14-pos_vertical);
    printf("                  ");
    
    gotoxy(2,15-pos_vertical);
    printf("           0    0 ");
    
    gotoxy(2,16-pos_vertical);
    printf("         ########");
    
    gotoxy(2,17-pos_vertical);
    printf("         ########");
    
    gotoxy(2,18-pos_vertical);
    printf("         ########");
    
    gotoxy(2,19-pos_vertical);
    printf(" #      ######## ");
    
    gotoxy(2,20-pos_vertical);
    printf(" ###  ########## ");
    
    gotoxy(2,21-pos_vertical);
    printf(" ############  # ");
    
    gotoxy(2,22-pos_vertical);
    printf("   #########     ");
    gotoxy(2,23-pos_vertical);
    
    // movimentação das pernas na subida e descida
    if(pulo==1 || pulo==2){
	    printf("    ### ##       ");
	    gotoxy(2,24-pos_vertical);
	    printf("    ##   ##      ");

	// alternança da posição das pernas ao correr
    }else if(pernasDino==1){
	    printf("    ####  ###    ");
	    gotoxy(2,24-pos_vertical);
	    printf("      ##         ");
	    pernasDino=2;
	
    }else if(pernasDino==2){
	    printf("     ### ##      ");
	    gotoxy(2,24-pos_vertical);
	    printf("          ##     ");
	    pernasDino=1;
    }
    
    // imprime abaixo do dino
    gotoxy(2,25-pos_vertical);
    
    // no ar imprime vazio
    if(pulo !=0){
        printf("                ");
    }
    
    else{
    	printf("=================");
    }
    
	//é usada para pausar a execução do programa, para 
	//controlar o ritmo de animações ou dar uma "pausa" entre ações.
    Sleep(50);
}

int obstaculo(){
	
	static int pos_obst=0, pontuacao=0;
	char opcao;
	
	// verifica a colisão
	if(pos_obst==56 && pos_vertical<4) {
		pontuacao=0;
		opcao = getch();
		if (opcao == 'v'|| opcao == 'V'){
			system("cls");
			return 1;
		}
	}
	
	//organiza o obstaculo na tela
	gotoxy(74-pos_obst,20);
	printf("#    # ");
	
	gotoxy(74-pos_obst,21);
	printf("#    # ");
	
	gotoxy(74-pos_obst,22);
	printf("###### ");
	
	gotoxy(74-pos_obst,23);
	printf("  #    ");
	
	gotoxy(74-pos_obst,24);
	printf("  #  " );
	
	// movimetação do obstaculo
	pos_obst++;
	
	if(pos_obst==73) {
		pos_obst=0;
		pontuacao++;
		gotoxy(70,2);
		printf("%d", pontuacao);
	}
	
	return 0;
}

int iniciar() {
	
	char opcao;
	int pulo = 0, i;
	
	printf("\nPressione 'V' para sair \nPressione 'P' para pular");
	gotoxy(62,2);
	
	printf("Score: ");
	gotoxy(1,25);
	
	for(int x=0;x<80;x++){
		printf("=");
	}
	
	 while (1) {
	 	// enquanto nenhuma tecla é pressionada
        if (!kbhit()) {
            dino(0); 
            if (obstaculo() == 1) {  //volta ao menu
                return 1;
            }
        } else {
        	
            opcao = getche();

            if (opcao == 'P' || opcao == 'p') {
            	
            	// os laços são responsáveis por fazer subir/descer 10 linhas
                for (i = 0; i < 10; i++) {
                    dino(1); 
                    if (obstaculo() == 1) {  
                	return 1;
            		}
                }
                for (i = 0; i < 10; i++) {
                    dino(2); 
                    if (obstaculo() == 1) { 
                	return 1;
            		}
                }
                pulo = 0; 
            } else if (opcao == 'V' || opcao == 'v') {
            	system("cls");
                return 1;
            }
        }
    }
}

int tutorial(){
	
	char voltar;
	
	do {
    	printf("--------------------------------\n");
    	printf("            DINO GAME           \n");
    	printf("--------------------------------\n");

    	FILE *arquivo = fopen("tutorialjogo.txt", "r");
    	if (arquivo == NULL) {
        	printf("Erro ao abrir o arquivo, verifique se o arquivo esta no diretorio correto.\n");
    	}

    	char texto[200];
    	while (fgets(texto, sizeof(texto), arquivo)) {
        	printf("%s", texto);
    	}

    	fclose(arquivo);
    
    	printf("\n\nV - Voltar para o menu \n");
    	scanf(" %c", &voltar);
    
    	if(voltar == 'v' || voltar == 'V'){
    		system("cls");
    		return 1;
		}
			else {
				printf("\nOpcao invalida! Digite 'v' para voltar.\n\n");
			}
	} while(voltar != 'v' || voltar != 'V');	
}

void sair(){
	
	printf("--------------------------------\n");
	printf("            DINO GAME           \n");
	printf("--------------------------------\n");
	printf("\n Obrigado por jogar! Encerrando o programa...\n");
    exit(0);
}

int main(){
	
	while (1){
		
		int opcao = menu();
	
		switch(opcao){
			case 1:
				iniciar();
				break;
	
			case 2:
				tutorial();
				break;
	
			case 3:
				sair();
				break;
		}
	}
	return 0;
}
