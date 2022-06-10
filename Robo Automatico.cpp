#include <stdio.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "TADPILHA.h"

#define TFL 200
#define TFC 200

struct TPosicao
{
	char Tipo;
	bool Visitado;
};
int RetornaTotalPosicoes(TPosicao Mapa[TFL][TFC], int L, int C) //Retorna o Total de Posicoes Possiveis
{
    int i, j, cont=0;
    for (i=0; i<L; i++)
        for (j=0; j<C; j++)
            if (Mapa[i][j].Tipo==' ' || Mapa[i][j].Tipo=='p')
                cont++;
                
    return cont;
}
int RetornaTotalPremios(TPosicao Mapa[TFL][TFC], int L, int C) //Retorna o Total de Premios
{
    int i, j, cont=0;
    for (i=0; i<L; i++)
        for (j=0; j<C; j++)
            if (Mapa[i][j].Tipo=='p')
                cont++;
    return cont;
}
void PosicaoInicial(TPosicao Mapa[TFL][TFC], int L, int C,int pos_inicial[2]) //Posicao Inicial
{
    int i, j;
	for(i=0;i<L;i++)
		for(j=0;j<C;j++)
			if(Mapa[i][j].Tipo=='o')
			{
				pos_inicial[0]=i;
				pos_inicial[1]=j;
			}		 
}
void PreencheMapa(FILE *PtrMapa,TPosicao Mapa[TFL][TFC], int &L, int &C, char NomeMapa[30]) //Preenche Mapa[][]
{
    char caracter;
	int i, j;
	fgets(NomeMapa,30,PtrMapa);
    fscanf(PtrMapa,"%d %d\n",&L,&C);
    for (i=0; i<L; i++)
    {
        for (j=0; j<C; j++)
        {
            caracter = fgetc(PtrMapa);
            if (caracter!='\n')
            {
                Mapa[i][j].Tipo = caracter;
                Mapa[i][j].Visitado = false;
            }
        }
        fgetc(PtrMapa);
    }
}

bool VerificaConsistencia(TPosicao Mapa[TFL][TFC], int L, int C) /*  ..::Verifica Consistencia do Mapa::..  */
{
    bool verifica_cons=true;
    int i, j;
    //Verifica Paredes Externas
    for (i=0, j=0; j<C && verifica_cons!=false; j++) //Parede Cima
        if (Mapa[i][j].Tipo!='x')
            verifica_cons = false;

    for (i=0, j=C-1; i<L && verifica_cons!=false; i++) //Parede Direita
        if (Mapa[i][j].Tipo!='x')
            verifica_cons = false;

    for (i=L-1, j=C-1; j>=0 && verifica_cons!=false; j--) //Parede Baixo
        if (Mapa[i][j].Tipo!='x')
            verifica_cons = false;

    for (i=L-1, j=0; i>=0 && verifica_cons!=false; i--) //Parede Esquerda
        if (Mapa[i][j].Tipo!='x')
            verifica_cons = false;
    return verifica_cons;
}

void MostrarMapa(TPosicao Mapa[TFL][TFC], int L, int C) //Mostra Mapa
{
    int i, j;
    system("cls");
    for (i=0; i<L; i++)
    {
        printf("\n");
        for (j=0; j<C; j++)
        {
        	if(Mapa[i][j].Tipo=='x')
				textcolor(7);
			else
			if(Mapa[i][j].Tipo=='p')
				textcolor(14);
			else
			if(Mapa[i][j].Tipo=='b')	
            	textcolor(8);
            else
            if(Mapa[i][j].Tipo=='o')
				textcolor(4);
			else
			if(Mapa[i][j].Tipo=='r')
				textcolor(1);
			printf("%c", Mapa[i][j].Tipo);
        }
    }
}
void Automatico(TPosicao Mapa[TFL][TFC], int L, int C, TpPilha &P, int pos_inicial[2],char NomeMapa[30])
{
    int i, j, cont_posicoes=0,cont_premios=0, total_posicoes,total_premios,checar;
    total_posicoes = RetornaTotalPosicoes(Mapa, L, C);
    total_premios = RetornaTotalPremios(Mapa, L, C);
    i = pos_inicial[0];
    j = pos_inicial[1];
    Mapa[i][j].Visitado = true;
    inicializar(P);
    system("cls");
    MostrarMapa(Mapa, L, C);
    do
    {
    	checar=0;
    	if(Mapa[i][j+1].Tipo!='x' && Mapa[i][j+1].Tipo!='b' && Mapa[i][j+1].Visitado==false)
    	{
    			if(Mapa[i][j+1].Tipo=='p')
    			{
    				cont_premios++;	
    			}
    			inserir(P,'D');
    			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
    			{
    				Mapa[i][j].Tipo = ' ';
	                Mapa[i][j+1].Tipo = 'r';
    			}
    			else
    			{
					Mapa[i][j].Tipo = 'o';
					Mapa[i][j+1].Tipo = 'r';
	            }
                Mapa[i][j+1].Visitado = true;
                j++;
                cont_posicoes++;
                MostrarMapa(Mapa,L,C);
                Sleep(500);
    	}
    	else
    	if(Mapa[i][j-1].Tipo!='x' && Mapa[i][j-1].Tipo!='b' && Mapa[i][j-1].Visitado==false)
    	{
			if(Mapa[i][j-1].Tipo=='p')
			{
				cont_premios++;	
			}
			inserir(P,'A');
			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
			{
				Mapa[i][j].Tipo = ' ';
                Mapa[i][j-1].Tipo = 'r';
			}
			else
			{
				Mapa[i][j].Tipo = 'o';
				Mapa[i][j-1].Tipo = 'r';
            }
            Mapa[i][j-1].Visitado = true;
            j--;
            cont_posicoes++;
            MostrarMapa(Mapa,L,C);
            Sleep(500);
    	}
    	else
    	if(Mapa[i+1][j].Tipo!='x' && Mapa[i+1][j].Tipo!='b' && Mapa[i+1][j].Visitado==false)
    	{
			if(Mapa[i+1][j].Tipo=='p')
			{
				cont_premios++;	
			}
			inserir(P,'S');
			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
			{
				Mapa[i][j].Tipo = ' ';
                Mapa[i+1][j].Tipo = 'r';
			}
			else
			{
				Mapa[i][j].Tipo = 'o';
				Mapa[i+1][j].Tipo = 'r';
            }
            Mapa[i+1][j].Visitado = true;
            i++;
            cont_posicoes++;
            MostrarMapa(Mapa,L,C);
            Sleep(500);
    	}
		else
    	if(Mapa[i-1][j].Tipo!='x' && Mapa[i-1][j].Tipo!='b' && Mapa[i-1][j].Visitado==false)
    	{
			if(Mapa[i-1][j].Tipo=='p')
			{
				cont_premios++;	
			}
			inserir(P,'W');
			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
			{
				Mapa[i][j].Tipo = ' ';
                Mapa[i-1][j].Tipo = 'r';
			}
			else
			{
				Mapa[i][j].Tipo = 'o';
				Mapa[i-1][j].Tipo = 'r';
            }
            Mapa[i-1][j].Visitado = true;
            i--;
            cont_posicoes++;
            MostrarMapa(Mapa,L,C);
            Sleep(500);
    	}
    	else
    	if(Mapa[i][j+1].Tipo!='x' && Mapa[i][j+1].Tipo!='b' && elementoTopo(P) == 'A')
    	{
    		if(Mapa[i][j+1].Visitado==true)
    		{
    			retirar(P);
    			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
				{
					Mapa[i][j].Tipo = ' ';
	                Mapa[i][j+1].Tipo = 'r';
				}
				else
				{
					Mapa[i][j].Tipo = 'o';
					Mapa[i][j+1].Tipo = 'r';
	            }
    			j++;
    			MostrarMapa(Mapa,L,C);
    			if(vazia(P.topo))
    			{
    				checar=1;
    			}
    			Sleep(500);
    		}
    	}
    	else
    	if(Mapa[i][j-1].Tipo!='x' && Mapa[i][j-1].Tipo!='b'&& elementoTopo(P) == 'D')
    	{
    		if(Mapa[i][j-1].Visitado==true)
    		{
    			retirar(P);
    			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
				{
					Mapa[i][j].Tipo = ' ';
	                Mapa[i][j-1].Tipo = 'r';
				}
				else
				{
					Mapa[i][j].Tipo = 'o';
					Mapa[i][j-1].Tipo = 'r';
	            }
    			j--;
    			MostrarMapa(Mapa,L,C);
    			if(vazia(P.topo))
    			{
    				checar=1;
    			}
    			Sleep(500);
    		}
    	}
    	else
    	if(Mapa[i+1][j].Tipo!='x' && Mapa[i+1][j].Tipo!='b' && elementoTopo(P)=='W')
    	{
    		if(Mapa[i+1][j].Visitado==true)
    		{
    			retirar(P);
    			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
				{
					Mapa[i][j].Tipo = ' ';
	                Mapa[i+1][j].Tipo = 'r';
				}
				else
				{
					Mapa[i][j].Tipo = 'o';
					Mapa[i+1][j].Tipo = 'r';
	            }
    			i++;
    			MostrarMapa(Mapa,L,C);
    			if(vazia(P.topo))
    			{
    				checar=1;
    			}
    			Sleep(500);
    		}
    	}
    	else
    	if(Mapa[i-1][j].Tipo!='x' && Mapa[i-1][j].Tipo!='b' && elementoTopo(P)=='S')
    	{
    		if(Mapa[i-1][j].Visitado==true)
    		{
    			retirar(P);
    			if(!(i == pos_inicial[0] && j == pos_inicial[1]))
				{
					Mapa[i][j].Tipo = ' ';
	                Mapa[i-1][j].Tipo = 'r';
				}
				else
				{
					Mapa[i][j].Tipo = 'o';
					Mapa[i-1][j].Tipo = 'r';
	            }
    			i--;
    			MostrarMapa(Mapa,L,C);
    			if(vazia(P.topo))
    			{
    				checar=1;
    			}
    			Sleep(500);
    		}
    	}
    	else;
    }
    while(!vazia(P.topo) || checar!=0);
    
    printf("\nNome: %s\n",NomeMapa);
    printf("Quantidade de Premios Total: %d\n",total_premios);
    printf("Quantidade de Premios Adquiridos: %d\n",cont_premios);
    printf("Quantidade de Posicoes do Mapa: %d\n",total_posicoes);
    printf("Quantidade de Posicoes que o Robo passou: %d\n",cont_posicoes);
    getch();
}
char Menu(void)
{
    system("cls");
	printf("\n----- LABIRINTO ROBO -----\n");
    printf("\n[A] Labirinto 1");
	printf("\n[B] Labirinto 2");
    printf("\n[C] Labirinto 3");
    printf("\n[D] Labirinto 4");
    printf("\n[E] Labirinto Inconsistente");
    printf("\n[ESC] Sair do Programa\n");
	printf("\nPressione a opcao desejada: ");
	return toupper(getche());
}

int main(void)
{
    FILE *PtrMapa;
    TPosicao Mapa[TFL][TFC];
    TpPilha P;
    bool verifica_cons;
    char NomeMapa[30],op;
    int L, C, pos_inicial[2];
    do
    {
    	op = Menu();
    	switch(op)
    	{
    		case 'A':
    			PtrMapa = fopen("Labirinto1.lab", "r");
    			PreencheMapa(PtrMapa, Mapa, L, C, NomeMapa);
    			verifica_cons = VerificaConsistencia(Mapa, L, C);
				PosicaoInicial(Mapa,L,C,pos_inicial);
				if(verifica_cons==true)
				{
				    system("cls");
				    Automatico(Mapa,L,C,P,pos_inicial,NomeMapa);
				}
				else
					printf("Mapa Inconsistente!");
				getch();
    			break;
    		case 'B':
    			PtrMapa = fopen("Labirinto2.lab","r");
    			PreencheMapa(PtrMapa, Mapa, L, C, NomeMapa);
    			verifica_cons = VerificaConsistencia(Mapa, L, C);
				PosicaoInicial(Mapa,L,C,pos_inicial);
				if(verifica_cons==true)
				{
				    system("cls");
				    Automatico(Mapa,L,C,P,pos_inicial,NomeMapa);
				}
				else
					printf("Mapa Inconsistente!");
				getch();
    			break;
    		case 'C':
    			PtrMapa = fopen("Labirinto3.lab","r");
    			PreencheMapa(PtrMapa, Mapa, L, C, NomeMapa);
    			verifica_cons = VerificaConsistencia(Mapa, L, C);
				PosicaoInicial(Mapa,L,C,pos_inicial);
				if(verifica_cons==true)
				{
				    system("cls");
				    Automatico(Mapa,L,C,P,pos_inicial,NomeMapa);
				}
				else
					printf("Mapa Inconsistente!");
				getch();
    			break;
    		case 'D':
    			PtrMapa = fopen("Labirinto4.lab","r");
    			PreencheMapa(PtrMapa, Mapa, L, C, NomeMapa);
    			verifica_cons = VerificaConsistencia(Mapa, L, C);
				PosicaoInicial(Mapa,L,C,pos_inicial);
				if(verifica_cons==true)
				{
				    system("cls");
				    Automatico(Mapa,L,C,P,pos_inicial,NomeMapa);
				}
				else
					printf("Mapa Inconsistente!");
				getch();
    			break;
    		case 'E':
    			PtrMapa = fopen("LabirintoInc.lab","r");
    			PreencheMapa(PtrMapa, Mapa, L, C, NomeMapa);
    			verifica_cons = VerificaConsistencia(Mapa, L, C);
				PosicaoInicial(Mapa,L,C,pos_inicial);
				if(verifica_cons==true)
				{
				    system("cls");
				    Automatico(Mapa,L,C,P,pos_inicial,NomeMapa);
				}
				else
					printf("Mapa Inconsistente!");
				getch();
    			break;
    	}
    	if(PtrMapa!=NULL)
    		fclose(PtrMapa);
    }
    while(op!=27);
}
