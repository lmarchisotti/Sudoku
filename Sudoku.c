#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
int i = 0, j = 0, k = 0;
int MATp[9][9] = {0};				// Matriz do programa com a solucao do sudoku
int MATu[9][9] = {0};				// Matriz do usuario, que é modificada toda hora
char player[30], nomeJog[30];					// String com o nome do usuario
FILE *pontREAD;						// Ponteiro para ser usado em leitura de arquivos
FILE *pontWRITE;					// Ponteiro para ser usado em escrita de arquivos

struct timespec start, finish, now;
float tempo;

struct class{
	char podium[30];
	int hora;
	int min;
	int sec;
	int T;
} jogadores[20]={0};

int Novo();		  					// Main - Contem o Menu principal
int inserirN();   					// Funcao para gerar um jogo aleatoriamente
int removerN();   					// Funcao para inserir valores na matriz
int verifica();   					// Funcao para verificacao / Correcao
int vet_check();  					// Funcao para verificar cada quadrante da matriz 9x9	  					// Funcao para remover um valor
void Continuar(); 					// Funcao para carregar jogo do usuario
void imprime();   					// Funcao para imprimir a matriz quando solicitado
void salvar();						// Funcao para salvar o jogo no arquivo asism que solicitado
void ranking();   					// Funcao para gerar o ranking dos melhores jogadores
void finaliza();  					// Funcao para inserir o jogador quando terminar o jogo

int main(){
	system ("clear");
	int num, num2;
	int tempo=0, horas=0, horas_seg=3600, minutos=0, segundos=0;
	int entrada;
	printf ("\n-------------------------------------- SUDOKU --------------------------------------\n\n");
	printf ("\t\t\t\t Bem vindo ao SUDOKU:\n");
	printf ("\n\t\t\t\t REGRAS DO JOGO \n\n");
	printf (" * O objetivo do jogo é preencher todas as casas da matriz com números de 1 a 9.\n");
	printf (" * Nenhum número pode ser repetido na linha respectiva.\n");
	printf (" * Nenhum número pode ser repetido na coluna respectiva.\n");
	printf (" * A matriz 9x9 possui 9 quadrantes 3x3, estes quadrantes devem ter números de 1 a 9 sem repetição.\n\n");
	printf ("\n\n------------------------------------------------------------------------------------\n");
	printf ("\n\n");
	printf ("\t\t\t\t1. Novo Jogo\n");
	printf ("\t\t\t\t2. Continuar Jogo\n");
	printf ("\t\t\t\t3. Pontuações\n");
	printf ("\t\t\t\t4. Sair\n");
	scanf ("%d", &entrada);

	if (entrada == 4){
		return 0;
		}else if ((entrada > 4) || (entrada < 1)){
			printf ("ERRO\n");
			return main();
		}

	while ( entrada != 4){
		switch(entrada){
			case 1:
				clock_gettime(CLOCK_MONOTONIC, &start); // Funcao para pegar o tempo inicial.
				Novo();
				num = -1;
				while ( num != 5){
				salvar();						
				imprime();
				printf("\n------------------------------------- Novo Jogo ------------------------------------\n\n");
				printf("1 - Inserir Número:\n");
				printf("2 - Remover Número:\n");
				printf("3 - Verificar tempo:\n");
				printf("4 - Verificação / Correção:\n");
				printf("5 - Voltar ao Menu Principal:\n\n");
				printf("Escolha uma opcao: ");
				printf("\n\n------------------------------------------------------------------------------------\n");
					scanf ("%d", &num);
						switch(num){
							case 1:
								inserirN();
								break;
							case 2:
								removerN();
								break;
							case 3:
								clock_gettime(CLOCK_MONOTONIC, &now);
								tempo = (now.tv_sec - start.tv_sec);
								tempo += (now.tv_nsec - start.tv_nsec) / 1000000000.0;
								horas = (tempo / horas_seg);
								minutos = (tempo - (horas_seg * horas)) / 60;
								segundos = (tempo - (horas_seg * horas) - (minutos * 60));
								printf("\n\nSeu tempo neste momento é %dh:%dmin:%dseg.\n", horas, minutos, segundos);
								sleep(3);
								break;
							case 4:
								printf("\n-------------------------------- Verificacao / Correcao ------------------------------\n\n");
								verifica();
								printf("1 - Voltar ao Menu Principal:\n");
								printf("2 - Sair do jogo:\n\n");
								printf("Escolha uma opcao: ");
								printf("\n\n------------------------------------------------------------------------------------\n");
								scanf ("%d", &num);
								switch(num){
									case 1:
										return main();
										break;
									case 2:
										return 0;
										break;
								}	
								break;
							case 5:
								return main();
								break;
						}
				}
				break;
			case 2:
				clock_gettime(CLOCK_MONOTONIC, &start); // Funcao para pegar o tempo inicial.
				Continuar();
				num = -1;
					while ( num != 5){
					salvar();						
					imprime();
					printf("\n------------------------------------- Carregar jogo ------------------------------------\n\n");
					printf("1 - Inserir Número:\n");
					printf("2 - Remover Número:\n");
					printf("3 - Verificar tempo:\n");
					printf("4 - Verificação/Correção:\n");
					printf("5 - Voltar ao Menu Principal:\n\n");
					printf("Escolha uma opcao: ");
					printf("\n\n------------------------------------------------------------------------------------\n");
					scanf ("%d", &num);
						switch(num){
							case 1:
								printf("\n-------------------------------- Inserir numeros ------------------------------\n\n");
								printf("Digite 0 em qualquer momento para voltar:\n\n");
								printf("\n\n------------------------------------------------------------------------------------\n");
								inserirN();
								break;
							case 2:
								removerN();
								break;
							case 3:
								clock_gettime(CLOCK_MONOTONIC, &now);
								tempo = (now.tv_sec - start.tv_sec);
								tempo += (now.tv_nsec - start.tv_nsec) / 1000000000.0;
								horas = (tempo / horas_seg);
								minutos = (tempo - (horas_seg * horas)) / 60;
								segundos = (tempo - (horas_seg * horas) - (minutos * 60));
								printf("\n\nSeu tempo neste momento é %dh:%dmin:%dseg.\n", horas, minutos, segundos);
								sleep(3);
								break;
							case 4:
								printf("\n-------------------------------- Verificacao / Correcao ------------------------------\n\n");
								printf("1 - Voltar ao Menu Principal:\n");
								printf("2 - Sair do jogo:\n\n");
								printf("Escolha uma opcao: ");
								printf("\n\n------------------------------------------------------------------------------------\n");
								verifica();
								scanf ("%d", &num);
								switch(num){
									case 1:
										return main();
										break;
									case 2:
										return inserirN();
										break;
								}	
								break;
							case 5:
								return main();
								break;
						}
					}
				break;
			case 3:
				printf("\n--------------------------------------- Ranking -------------------------------------\n\n");
				ranking();
				printf("\n\n");
				printf("1 - Voltar ao Menu Principal:\n");
				printf("2 - Sair do jogo:\n\n");
				printf("Escolha uma opcao: ");
				printf("\n\n------------------------------------------------------------------------------------\n");
				scanf ("%d", &num);
				switch(num){
					case 1:
						return main();
						break;
					case 2:
						return 0;
						break;
				}
				break;		
			case 4:
				return 0;
				break;
		}
	}
	return 0;
}

int Novo(){
	srand(time(NULL));
	char nome[40];
	char nome2[40];
	FILE *fp;
	FILE *in;
	int opt;
	int x;
	
		opt = 1+rand()%10;							// Sorteia o numero - Sintaxe - sprintf(str, "%d", someInt);
		sprintf(nome, "BD/%d.txt", opt);			// Coloca uma entrada formatada na string nome
		printf("%d %s\n", opt, nome);				// Imprime para verificar se deu certo
		pontREAD = fopen(nome, "r");				// Abre o arquivo sorteado
    		for ( i = 0; i < 9; i++){				// Pega o que ta dentro dele
				for ( j = 0; j < 9; j++){
					fscanf(pontREAD, "%d %d %d", &i, &j, &MATp[i][j]);
				}
			}

			for ( i = 0; i < 9; i++){			
				for ( j = 0; j < 9; j++){
					MATu[i][j] = MATp[i][j];
				}
			}

			for (i = 0; i < 9; i++){
				x = 2 +rand () %8;
				for (x; x > 0; x--){
					j = rand() % 9;
					MATu[i][j] = 0;
				}
			}
	fgets (nome2,30,stdin);
	printf ("Digite um nome para o arquivo:\n");
	fgets (player,30,stdin);
	player[strlen(player)-1]='\0';
	strcpy(player,nomeJog);
	strcat(player,".txt");
	if (!fopen(player, "r")){
		fopen (player, "w");
		}
	printf ("Arquivo criado: %s\n",player);
	fp = fopen (player, "r+");
	for (i = 0; i < 9; i++){
		for ( j = 0; j < 9; j++){
			fprintf (fp,"%d %d %d ",i,j,MATu[i][j]);
		}
	}
	fclose(fp);
}

int inserirN(){
	i = -2;
	while ( i != -1){
		system ("clear");
		salvar();
		imprime();
	
		printf ("Digite um valor para a casa (nesta ordem: 'Linha' 'Coluna' e 'Valor'):\n");
		printf ("Para voltar ao menu anterior, digite 0.\n");
		printf ("Digite:\n");
		scanf ("%d", &i);
		if(i == 0){
		return 0;
		}else{
		scanf ("%d", &j);
			if ( MATu[i-1][j-1] != 0){
			printf ("Já existe um valor nessa casa.\n");
			sleep(2);
			return inserirN();
			}else{
			scanf ("%d", &MATu[i-1][j-1]);
			}
		}
	}
}

int removerN(){
	system ("clear");
	imprime();
	printf ("Digite nessa ordem: 'Linha' e 'Coluna':\n");
	scanf ("%d", &i);
	scanf ("%d", &j);
	i = i-1;
	j = j-1;
	MATu[i][j] = 0;
	system ("clear");
}

int verifica(){						// Funcao de Verificação
	system ("clear");
	int vet1[9];
	int vet2[9];
	int vet3[9];
	int vet4[9];
	int vet5[9];
	int vet6[9];
	int vet7[9];
	int vet8[9];
	int vet9[9];
	int cont = 0;
	int m;

	for (i = 0; i < 9; i++){
		for (j = 0; j < 9; j++){
			for (k = 0; k < j; k++){
				if (MATu[i][j] == MATu[i][k]){
					i++;
					j++;
					k++;
					printf ("Opa! Deu ruim lek\n");
					printf ("As casas [%d][%d] e [%d][%d] estão repetindo.\n",i,k,i,j);
					cont++;
				}
			}
		}
	}
	
	for (j = 0; j < 9; j++){
		for (i = 0; i < 9; i++){
			for (k = 0; k < i; k++){
				if (MATu[k][j] == MATu[i][j]){
					i++;
					j++;
					k++;
					printf ("Opa! Deu ruim lek\n");
					printf ("As casas [%d][%d] e [%d][%d] estão repetindo.\n",j,k,j,i);
					cont++;
					
				}
			}
		}
	}

	//vetor1	
		m = 0;
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				vet1[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet1[i] == vet1[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 1ª tabela(3x3) está repetindo o valor %d.\n",vet1[i]);
					cont++;
				}
			}
		}
		
	//vetor2
		m = 0;
		for (i = 3; i < 6; i++){
			for (j = 0; j < 3; j++){
				vet2[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet2[i] == vet2[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 2ª tabela(3x3) está repetindo o valor %d.\n",vet2[i]);
					cont++;
				}
			}
		}

	//vetor3
		m = 0;
		for (i = 6; i < 9; i++){
			for (j = 0; j < 3; j++){
				vet3[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet3[i] == vet3[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 3ª tabela(3x3) está repetindo o valor %d.\n",vet3[i]);
				cont++;
				}
			}
		}

	//vetor4
		m = 0;
		for (i = 0; i < 3; i++){
			for (j = 3; j < 6; j++){
				vet4[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet4[i] == vet4[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 4ª tabela(3x3) está repetindo o valor %d.\n",vet4[i]);
				cont++;
				}
			}
		}

	//vetor5
		m = 0;
		for (i = 3; i < 6; i++){
			for (j = 3; j < 6; j++){
				vet5[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet5[i] == vet5[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 5ª tabela(3x3) está repetindo o valor %d.\n",vet5[i]);
					cont++;
				}
			}
		}

	//vetor6
		m = 0;
		for (i = 6; i < 9; i++){
			for (j = 3; j < 6; j++){
				vet6[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet6[i] == vet6[j]){
					printf ("Opa! Deu ruim lek\n");
					printf ("Na 6ª tabela(3x3) está repetindo o valor %d.\n",vet6[i]);
					cont++;
				}
			}
		}

	//vetor7
		m = 0;
		for (i = 0; i < 3; i++){
			for (j = 6; j < 9; j++){
				vet7[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet7[i] == vet7[j]){
				printf ("Opa! Deu ruim lek\n");
				printf ("Na 7ª tabela(3x3) está repetindo o valor %d.\n",vet7[i]);
				cont++;
				}
			}
		}
		
	//vetor8
		m = 0;
		for (i = 3; i < 6; i++){
			for (j = 6; j < 9; j++){
				vet8[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet8[i] == vet8[j]){
				printf ("Opa! Deu ruim lek\n");
				printf ("Na 8ª tabela(3x3) está repetindo o valor %d.\n",vet8[i]);
				cont++;
				}
			}
		}

	//vetor9
		m = 0;
		for (i = 6; i < 9; i++){
			for (j = 6; j < 9; j++){
				vet9[m] = MATu[i][j];
				m++;
			}
		}
		for (i = 0; i < 9; i++){
			for (j = 0; j < i; j++){
				if (vet9[i] == vet9[j]){
				printf ("Opa! Deu ruim lek\n");
				printf ("Na 9ª tabela(3x3) está repetindo o valor %d.\n",vet9[i]);
				cont++;
				}
			}
		}
	if ( cont == 0){
		printf ("PARABÉNS VOCÊ GANHOU!\n");
		finaliza();
		sleep(2);
		return main();
	}
	else{
		printf ("Tente refazer novamente.\n");
		sleep(2);
		return inserirN();
	}
}

int vet_check (int vet[], int a, int b, int c, int d, int e){

	int cont = 0;
	int m = 0;
	
	for (i = a; i < b; i++){
		for (j = c; j < d; j++){
		vet[m] = MATu[i][j];
		m++;
		}
	}
	for (i = 0; i < 9; i++){
		for (j = 0; j < i; j++){
			if (vet[i] == vet[j]){
				printf ("Opa! Deu ruim lek\n");
				printf ("Na %dª tabela(3x3) está repetindo o valor %d.\n",e,vet[i]);
				cont++;
			}
		}
	}
	return (cont);		

}

void Continuar(){
	system ("clear");
	char nome[40];
	printf("Digite o nome do arquivo:\n");
	fgets (nome,29,stdin);
	fgets (player,29,stdin);
	player[strlen(player)-1]='\0';
	strcat(player,".txt");
	pontREAD = fopen (player, "r");
	for ( i = 0; i < 9; i++){
		for ( j = 0; j < 9; j++){
			fscanf(pontREAD, "%d\t%d\t%d ", &i, &j, &MATu[i][j]);
		}
	}
	fclose(pontREAD);
}

void imprime(){
	system("clear");
	printf("\n");
	printf("  1  2  3   4  5  6   7  8  9  \n");
	printf("+---------+---------+---------+\n");
	for (i = 0; i < 9; i++){
		printf("|");
		for (j = 0; j < 9; j++){
			if (MATu[i][j] != 0)
				printf(" %d ", MATu[i][j]);
			else
				printf("   ");
			if (j % 3 == 2)
				printf("|");
		}
		if (i % 3 == 2)
			printf("\n+---------+---------+---------+");
		printf("\n");
	}
	printf("\n");
}

void salvar(){
	pontWRITE = fopen (player,"r+");
	for (i = 0; i < 9; i++){
		for ( j = 0; j < 9; j++){
			fprintf (pontWRITE,"%d %d %d \n",i,j,MATu[i][j]);
		}
	}
	fclose(pontWRITE);

}
 
void ranking(){
	int aux=0, ord=0, horas_seg=3600;
	int pri=500, seg=600, ter=700;
	int P1=0, P2=0, P3=0;
	pontREAD = fopen("Jogadores.txt","r");
	for( i = 0 ; i < 20 ; i++ ){
		fscanf(pontREAD,"%s %d\n", &jogadores[i].podium[0], &jogadores[i].T);
	}
	fclose(pontREAD);
	
	// 1 Colocado
	for (i = 0; i < 20; i++){
		if ( jogadores[i].T < pri && jogadores[i].T > 0){
			pri = jogadores[i].T;
			P1 = i;
		}
	}

	// 2 Colocado
	for (i = 0; i < 20; i++){
		if ( jogadores[i].T > pri && jogadores[i].T < seg && jogadores[i].T > 0){
			seg = jogadores[i].T;
			P2 = i;
		}
	}

	// 3 Colocado
	for (i = 0; i < 20; i++){
		if ( jogadores[i].T > pri && jogadores[i].T > seg && jogadores[i].T < ter && jogadores[i].T > 0){
			ter = jogadores[i].T;
			P3 = i;
		}
	}

	for (i = 0; i < 20; i++){
		jogadores[i].hora = (jogadores[i].T / horas_seg);
		jogadores[i].min = (jogadores[i].T - (horas_seg * jogadores[i].hora)) / 60;
		jogadores[i].sec = (jogadores[i].T - (horas_seg * jogadores[i].hora) - (jogadores[i].min * 60));
	}

	printf("1 Posição: %s - Tempo - %dh:%dm:%ds.\n", jogadores[P1].podium, jogadores[P1].hora, jogadores[P1].min, jogadores[P1].sec);
	printf("2 Posição: %s - Tempo - %dh:%dm:%ds.\n", jogadores[P2].podium, jogadores[P2].hora, jogadores[P2].min, jogadores[P2].sec);
	printf("3 Posição: %s - Tempo - %dh:%dm:%ds.\n", jogadores[P3].podium, jogadores[P3].hora, jogadores[P3].min, jogadores[P3].sec);
}

void finaliza(){
	int tempo = 0;
	clock_gettime(CLOCK_MONOTONIC, &finish);
	tempo = (finish.tv_sec - start.tv_sec);
	tempo += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	pontWRITE = fopen("Jogadores.txt", "a");
	fprintf(pontWRITE, "%s\t%d \r\n\r", nomeJog, tempo);
	fclose(pontWRITE);
}
