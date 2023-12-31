//trece 6 teste din 10 ( ca timp de executie)
// testele 7 si 8 intre intre 1 si 2 secunde
// testul 9 ->  3 virgula 3 secunde

#include <fstream.h>
#include <iomanip.h>

#define FIN "urgenta.in"
#define FOUT "urgenta.out"


#define MUCHII 32390
#define NODURI 259

struct muchie {
	int a; // primul varf
	int b; // al doilea
	int cost;
	int ord; // nr ordine al muchiei
} *u, *graph;



int  p[NODURI], rang[NODURI];
int* luata;
int nr, j, i, n;
long int cost_min, cost_total, grav_max;
long int m; // nr muchii
int K; // nr de grupuri final
int nr_grupuri;

void Citeste();
void Afiseaza();
int Find(int x);
void Union(int x, int y);
void ConstrHeap();
void CombHeap(int i, int m);
//void SortMuchii(int, int);
void Kruskal();

void Union(int,int);
int Find(int);


int main()
{
	Citeste();
	Kruskal();
	Afiseaza();
	return 0;
}

void Citeste(void)
{
	ifstream fin(FIN);
	fin >> n >> m >> K;  // nr varfuri si nr muchii
	u     = new muchie [m + 1];
	graph = new muchie [m + 1];

	luata = new int [m + 1];

	for ( i = 1; i <= m; i++  )
	{

		fin >> u[i].a >> u[i].b >> u[i].cost;
		graph[i].a = u[i].a;
		graph[i].b = u[i].b;
		cost_total += (long)u[i].cost;
		u[i].ord = i;
		luata[i] = 0;
	}

	fin.close();
}

void Afiseaza()
{
	ofstream fout(FOUT);

	grav_max = cost_total - cost_min;
	fout << grav_max << endl
		 << m - nr << endl; //<<  m - nr << endl; // muchiile care nu fac parte din comp conexe

	for ( i = 1; i <= m; i++ )
		if ( !luata[i] ) fout << graph[i].a << " " << graph[i].b << endl;


	delete [] u;
	delete [] graph;

	delete [] luata;

	fout.close();
}


void Union(int x, int y)
{
	if (rang[x] > rang[y]) p[y] = x;
		else
		{
			p[x] = y;
			if (rang[x] == rang[y]) ++rang[y];
		}
}

int Find(int x)      // cautare cu compresie
{
	if ( x != p[x] ) p[x] = Find(p[x]);
	return p[x];
}

void Kruskal(void)
{
	// Formeaza multimile
	for (i = 1; i <= n; i++)
	{
		p[i] = i;     // n arbori cu 1 varf
		rang[i] = 0;  // adincime 0 in arbore
	}
	// Formeaza HEAP ul cu muchii
	ConstrHeap();
	//SortMuchii(1, m);
	cost_min = 0;
	nr = 0;  // nr de muchii alese
	int nr_grupuri = n;
	muchie min;
	for ( int i = m; i >= 1; )
	{
		if ( nr_grupuri == K ) goto end;
		int x, y;
		min = u[1];
		u[1] = u[i];
        i--;
        CombHeap(1, i);
		x = Find(min.a);
		y = Find(min.b);
		Union( x, y );

		if ( x != y )
		{
			luata[min.ord] = 1;
			cost_min += (unsigned long )min.cost;
			nr++;          // am luat
			nr_grupuri--;  // au ramas
		}

	}
	end:
	return;
}



void ConstrHeap()
{
	int i;
	for ( i = m / 2; i >= 1; i-- ) CombHeap(i, m);
}


void CombHeap(int i, int m)
{
	int parinte, fiu;
	muchie v;
	v = u[i];
	parinte = i;
	fiu = 2 * i;

	while ( fiu <= m )
	{
   		if ( fiu < m )
      		if ( u[fiu].cost > u[fiu+1].cost ) fiu = fiu + 1;

   		if ( v.cost > u[fiu].cost )
      	{
        	u[parinte] = u[fiu];
        	parinte = fiu;
        	fiu = fiu * 2;
		}
      	else fiu = m + 1;
	}
	u[parinte] = v;
}
