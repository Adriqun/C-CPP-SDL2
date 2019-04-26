#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void calc_LIS(vector<int> &D) {
	// The longest increasing subsequence.
	vector<vector<int>> L(D.size());
	L[0].push_back(D[0]);

	for (int i = 1; i < D.size(); ++i) // N
	{
		for (int j = 0; j < i; ++j) // N
			if (D[j] < D[i] && L[i].size() < L[j].size())
				L[i] = L[j];
		L[i].push_back(D[i]);
	}

	std::sort(L.begin(), L.end(), [](const vector<int> &a, const vector<int> &b) { return a.size() > b.size(); });
	for (auto &jt : L[0])
		printf("%d ", jt);
	printf("\n");
}

int main()
{
	int a[] = { 0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15 };
	vector<int> arr(a, a + sizeof(a) / sizeof(a[0]));
	calc_LIS(arr);
	return 0;
}