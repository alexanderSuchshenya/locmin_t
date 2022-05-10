#include "locminreinsert.h"
#include <math.h>
using namespace std;

int main()
{
	vector<int> d;
	vector<double> x;
	vector<double> y;
	int N, V, c;

	cout << "number of verticies: ";
	cin >> N;
	cout << "number of routes: ";
	cin >> V;
	cout << "route capasity: ";
	cin >> c;
	for (int i = 0; i < N; i++)
	{
		int din;
	        double xin, yin;
		cin >> din >> xin >> yin;
		d.push_back(din);
		x.push_back(xin);
		y.push_back(yin);
	}
	cout << "verticies initialized" << endl;

	vector<vector<double>> dist(N, vector<double>(N, 0));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
	cout << "distances initialized" << endl;

	vector<vector<int>> routes(V, vector<int>(1,0));
	for (int i = 1; i < N; i++)
	{
		int count = 0;
		bool assigned = false;
		while (count < V && !assigned)
		{
			int weight = 0;
			for (int j = 0; j < routes[count].size(); j++)
				weight = weight + d[routes[count][j]];
			if (weight + d[i] < c)
			{
				routes[count].push_back(i);
				assigned = true;
			}
			count = count + 1;
		}
	}
	for (int i = 0; i < V; i++)
		routes[i].push_back(0);
	cout << "initial routes initialized:" << endl;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < routes[i].size(); j++)
			cout << routes[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	cout << m_pathfind(routes, dist, d, c, 10) << endl;
	return 0;
}
