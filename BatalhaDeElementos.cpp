#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct CARTA {
    int elemento; //fogo = 0, agua = 1, planta = 2
    int numero;
    int jogada;//boleana
};

struct JOGADOR
{
	CARTA cartas[9];
	int cartasJogadas[9];
	int contagemPontos;
};
void esperar_ok()
{
    system("cls");
    printf("Digite OK para continuar: ");
    fflush(stdin);

    char input[3]; // Aumentamos o tamanho do buffer de entrada para 3 caracteres para acomodar o '\n'
    fgets(input, sizeof(input), stdin); // Usamos fgets() para ler uma linha inteira, incluindo o '\n'

    // Removemos o caractere '\n' do final da string
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "OK") != 0) // Usamos strcmp() para comparar strings de forma maiúscula e minúscula
    {
        esperar_ok(); // Chamamos a função novamente para dar outra chance ao usuário
    }
}


void introducao() {
  printf("BBBBBB 	DDDDDD 	  EEEEEE\n");
  printf("B     B	D     D	  E\n");
  printf("BBBBBB	D     D	  EEEEEE\n");
  printf("B     B	D     D	  E\n");
  printf("BBBBBB 	DDDDDD 	  EEEEEE\n");
  printf("\nPressione Enter para jogar...\n");
  getchar();
}

const char *IndexElemento(int indice)
{
	if(indice==0)
		return "FOGO";
	if(indice==1)
		return "AGUA";
	if(indice==2)
		return "PLANTA";
}

int comparacaoElementos(struct JOGADOR* jogador1, struct JOGADOR* jogador2, int indice1, int indice2)
{	
	int resultados[3][3] = {
	{0,1,2},
	{2,0,1},
	{1,2,0}
	};//tabela de resultados, retorna quem ganhou
	
	return resultados[jogador2->cartas[indice2].elemento][jogador1->cartas[indice1].elemento];
}

int AnaliseJogadas(struct JOGADOR* jogador1, struct JOGADOR* jogador2, int quantRodadas)
{
	for(int i = 0; i < quantRodadas; i++)
	{
		if(jogador1->cartas[jogador1->cartasJogadas[i]].elemento == jogador2->cartas[jogador2->cartasJogadas[i]].elemento)
		{
			if(jogador1->cartas[jogador1->cartasJogadas[i]].numero > jogador2->cartas[jogador2->cartasJogadas[i]].numero)
			{
				jogador1->contagemPontos++;
			}
			else if(jogador1->cartas[jogador1->cartasJogadas[i]].numero < jogador2->cartas[jogador2->cartasJogadas[i]].numero)
			{
				jogador2->contagemPontos++;
			}
		}
		else
		{
			switch(comparacaoElementos(jogador1, jogador2, jogador1->cartasJogadas[i], jogador2->cartasJogadas[i]))
			{
				case 1:
					jogador1->contagemPontos++;
					break;
				case 2:
					jogador2->contagemPontos++;
					break;
			}
			
		}
	}
}

int PedirEVerificarJogada(struct JOGADOR* jogador1, struct JOGADOR* jogador2, int i, int quantRodadas, int index)
{
	
	int jogada;
	if(i % 2 == 0)
		{
			
			system("cls");
			printf("Vez do JOGADOR 1\n");
			for(int j = 0; j < quantRodadas; j++)
			{
				printf("Carta %d: Elemento %s e numero %d\n", j + 1, IndexElemento(jogador1->cartas[j].elemento), jogador1->cartas[j].numero);
			}
			printf("Escolha qual carta quer jogar: ");
			scanf("%d", &jogada);
			
			while(jogador1->cartas[jogada - 1].jogada == 1)
			{
				printf("Essa carta ja foi jogada, tente novamente \n");
				scanf("%d", &jogada);
			}
			jogador1->cartasJogadas[index] = jogada - 1;
			jogador1->cartas[jogada - 1].jogada = 1;
		}
	else
	{
		{
			system("cls");
			printf("Vez do JOGADOR 2\n");
			for(int j = 0; j < quantRodadas; j++)
			{
				printf("Carta %d: Elemento %s e numero %d\n", j + 1, IndexElemento(jogador2->cartas[j].elemento), jogador2->cartas[j].numero);
			}
			printf("Escolha qual carta quer jogar: ");
			scanf("%d", &jogada);
			
			while(jogador2->cartas[jogada - 1].jogada == 1)
			{
				printf("Essa carta j? foi jogada, tente novamente\n");
				scanf("%d", &jogada);
			}
			
			jogador2->cartasJogadas[index] = jogada - 1;
			jogador2->cartas[jogada - 1].jogada = 1;
			//printf("\n%s %d\n", jogador2->cartas[jogador2->cartasJogadas[index]].elemento, jogador2->cartas[jogador2->cartasJogadas[index]].numero);
			//getch();
		}
	}
}

int Rodada(struct JOGADOR* jogador1, struct JOGADOR* jogador2, int quantRodadas)
{
	
	int index = 0;
	for (int i = 0; i < (quantRodadas * 2); i++)
	{
		PedirEVerificarJogada(jogador1, jogador2, i, quantRodadas, index);
		if(i % 2 != 0)
		{
			index++;
		}
	}
	system("cls");
	
}

int main(void)
{
	introducao();
	system("cls");
	srand(time(NULL));//faz com que o sorteio de cartas seja diferente sempre que executar o c?digo
	
	struct JOGADOR* jogador1 = (struct JOGADOR*)malloc(sizeof(struct JOGADOR));
    struct JOGADOR* jogador2 = (struct JOGADOR*)malloc(sizeof(struct JOGADOR));
    
    jogador1->contagemPontos = 0;
    jogador2->contagemPontos = 0;

    int escolha, quantRodadas;    

    while (escolha < 1 || escolha > 3) {
        printf("Escolha o numero de cartas para cada jogador: \n");
        printf("1- Tres Cartas \n");
        printf("2- Cinco Cartas \n");
        printf("3- Nove Cartas\n");
        scanf("%d", &escolha);
    }
    
    switch(escolha)
    {
    	case 1:
    		quantRodadas = 3;
    		break;
    	case 2:
    		quantRodadas = 5;
    		break;
    	case 3:
    		quantRodadas = 9;
    		break;
	}
	
	CARTA* cartas1= (struct CARTA*)malloc(quantRodadas * sizeof(struct CARTA));
	CARTA* cartas2= (struct CARTA*)malloc(quantRodadas * sizeof(struct CARTA));
	
	for(int i = 0; i < quantRodadas; i++)
	{
		cartas1[i].numero = rand() % 10;
		cartas1[i].elemento = rand() % 3;
		cartas1[i].jogada = 0;
		cartas2[i].numero = rand() % 10;
		cartas2[i].elemento = rand() % 3;
		cartas2[i].jogada = 0;
	}//gera as cartas aleatoriamente
	
	for(int i = 0; i < quantRodadas; i++)
	{
		jogador1->cartas[i] = cartas1[i];
		jogador2->cartas[i] = cartas2[i];
	}
	
	Rodada(jogador1, jogador2, quantRodadas);
	AnaliseJogadas(jogador1, jogador2, quantRodadas);
	
	if(jogador1->contagemPontos > jogador2->contagemPontos)
	{
		printf("o JOGADOR 1 venceu com %d pontos!", jogador1->contagemPontos);
	}
	else if(jogador2->contagemPontos > jogador1->contagemPontos)
	{
		printf("o JOGADOR 2 venceu com %d pontos!", jogador2->contagemPontos);
	}
	else
	{
		printf("O resultado foi empate!");
	}
}

