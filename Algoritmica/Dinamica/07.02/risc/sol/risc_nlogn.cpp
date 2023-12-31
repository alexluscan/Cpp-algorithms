/*
    Constantin Galatan
    Complexitate: O(n*log n)
*/
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using VI = vector<int>;

VI a, b; // sirul inaltimilor, sirul sortat
int n, V;

int main()
{
    ifstream fin("risc.in");
    ofstream fout("risc.out");

	int hmax(0), pmax(-1);
	fin >> V >> n;
	a = VI(n);
	for (int i = 0; i < n; ++i)
	{
		fin >> a[i];
		if ( a[i] > hmax )
			hmax = a[i], pmax = i;
	}
	if ( V == 1 )
	{
		bool ok = true;
		for (int i = 0; i < n && ok; ++i)
		{
			if ( i && i <= pmax && a[i - 1] > a[i] )
				ok = false;

			if ( i > pmax && a[i - 1] < a[i] )
				ok = false;
		}

		if ( ok && pmax && a[pmax - 1] > a[n - 1])
			ok = false;
		if ( ok )
			fout << pmax + 1 << '\n';
		else
			fout << -1 << '\n';
	}
	else
	{
		b = a;
		sort(b.begin(), b.end());
		int cntAsc(0), cntDesc(0), k(0);
		for (int i(0), j(0); i < n; ++i)   // partea crescatoare
        {
			if (a[i] == b[j] )
				cntAsc++, j++;

			if ( i == pmax )
                k = cntAsc;
        }

		for (int i(pmax), j(n - 1); i < n; ++i) // partea descrescatoare
			if (a[i] == b[j] )
				cntDesc++, j--;

		fout << n - max(cntAsc, cntDesc + k) << '\n';
	}

	fin.close();
	fout.close();
	return 0;
}
