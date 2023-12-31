#include<fstream>
#include<iomanip>
using namespace std;

int n, ret;
int r[16], m[21];
bool opt[16];
double cost[16], cmax = 2000000;

int main()
{
	ifstream fin("reteta.in");
	ofstream fout("reteta.out");
	fin >> n >> ret;
	
	int type, nr;
	for (int i = 0; i < ret; ++i)
	{
		fin >> type;
		opt[i] = (type == 2);
		
		fin >> nr;
		for (int j = 0, med; j < nr; ++j)
		{
			fin >> med;
			--med;
			r[i] |= (1 << med);   // r[i] = medicamentele din reteta i
		}
	}
	for (int i = 0; i < n; ++i)
		fin >> m[i];             // preturile
		
	for (int i = 0; i < ret; ++i)
	{
		for (int j = 0; j < n; ++j)
			if (r[i] & (1 << j))
			{
				cost[i] += m[j];
			}
		if (opt[i])
			cost[i] /= 2;
	}
	
	for (int i = 0; i < (1 << ret); ++i) // pt fiecare submultime de retete i
	{
		bool ok = true;
		int mask = 0;       // aici adun medicamentele
		double cst = 0;
		
		// daca exista suprapuneri de medic in submultimea i, se renunta la submultimea i
		for (int j = 0; j < ret; ++j)   // pt fiecare reteta j
			if (i & (1 << j))           // daca reteta j este printre retetele din i
			{
				if ((r[j] & mask) != 0) // si unele din medicamentele din reteta j sunt deja in mask
				{
					ok = false;
					break;
				}
				else
				{
					cst += cost[j];
					mask |= r[j];
				}
			}
			
		if (ok && (mask ^ ((1 << n) - 1)) == 0)  // daca sunt toate medicamentele in mask
			if (cst < cmax)
				cmax = cst;
	}
	
	fout << fixed << setprecision(1) << cmax;
}
