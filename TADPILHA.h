#define MAXPILHA 1000

struct TpPilha
{
    int topo;
    char pilha[MAXPILHA];
};

void inicializar(TpPilha &p)
{
    p.topo = -1;
}

void inserir(TpPilha &p, char Elemento)
{
    p.pilha[++p.topo] = Elemento;
}

char retirar(TpPilha &p)
{
    return p.pilha[p.topo--];
}

char elementoTopo(TpPilha p)
{
    return p.pilha[p.topo];
}

int cheia(int topo)
{
    return topo == MAXPILHA-1;
}

int vazia(int topo)
{
    return topo == -1;
}

int exib(TpPilha p)
{
   while( !vazia(p.topo) )
        printf("\n%c",retirar(p));
}



