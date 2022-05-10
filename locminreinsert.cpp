#include "locminreinsert.h"
using namespace std;

pair<int,int> getroute(vector<vector<int>> &routes, int a)
{
	for (int i = 0; i < routes.size(); i++)
	{
		for (int j = 0; j < routes[i].size(); j++)
		{
			if (routes[i][j] == a)
			{
				pair<int,int> ans;
				ans.first = i;
				ans.second = j;
				return ans;
			}
		}
	}
	pair<int,int> ans;
	ans.first = 0;
	ans.second = 0;
	return ans;
}

bool insertpath (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int i, int j)
{
	int routelimit = routes.size();
	for (int a = 0; a < routelimit; a++)
	{
		// looking at the same route
		if (a == i)
		{
			int routesize = routes[i].size();
			for (int b = 1; b < routesize - 1; b++)
			{
				if (b != j)
				{
					// checking if nodes swap will bring results
					if (b < j && dist[routes[a][j]][routes[a][j-1]] + dist[routes[a][j+1]][routes[a][j]]
						+ dist[routes[a][b]][routes[a][b-1]]
						> dist[routes[a][j]][routes[a][b]] + dist[routes[a][j]][routes[a][b-1]]
                                                + dist[routes[a][j-1]][routes[a][j+1]])
					{
						int tmp = routes[i][j];
						for (int c = j; c > b; c--)
							routes[a][c] = routes[a][c-1];
						routes[a][b] = tmp;
						return true;
					}
					else if (b > j && dist[routes[a][j]][routes[a][j-1]] + dist[routes[a][j+1]][routes[a][j]]
                                                + dist[routes[a][b]][routes[a][b+1]]
                                                > dist[routes[a][j]][routes[a][b]] + dist[routes[a][j]][routes[a][b+1]]
                                                + dist[routes[a][j-1]][routes[a][j+1]])
					{ 
						int tmp = routes[i][j];
						for (int c = j; c < b; c++)
							routes[a][c] = routes[a][c+1];
						routes[a][b] = tmp;
                                               	return true;
					}
				}
			}
		}
		else
		{
			int initialroute = routes[i].size();
			int routesize = routes[a].size();
			for (int b = 1; b < routesize - 1; b++)
			{
				// checking if nodes swap will bring results
				if (dist[routes[i][j]][routes[i][j-1]] + dist[routes[i][j+1]][routes[i][j]]
                                	+ dist[routes[a][b]][routes[a][b-1]]
                                	> dist[routes[i][j-1]][routes[i][j+1]] + dist[routes[a][b-1]][routes[i][j]]
                                	+ dist[routes[i][j]][routes[a][b]])
				{
					int routemass = 0;
					for (int c = 0; c < routesize; c++)
						routemass = routemass + request[routes[a][c]];
					
					// checking if acceptor route will overload
					if (routemass + request[routes[i][j]] < routecapasity)
					{	
				        	int tmp = routes[i][j];
						for (int c = j; c < initialroute-1; c++)
							routes[i][c] = routes[i][c+1];
						routes[i].pop_back();
						routes[a].push_back(0);
						for (int c = routesize; c > b; c--)
							routes[a][c] = routes[a][c-1];
						routes[a][b] = tmp;
						return true;
					}
				}
			}
		}
	}	
	return false;
}

double m_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int m)
{
	bool ongoing = true;
	int count = 0;
	while (ongoing && count < m)
	{
		ongoing = false;
		count = count + 1;
		for (int c = 1; c < request.size(); c++)
			{
				// trying to minimalize
				pair<int,int> node = getroute(routes, c);
				if(insertpath(routes, dist, request, routecapasity, node.first, node.second)) ongoing = true;
			}
	}

	cout << count << "//" << m << endl;
        for (int i = 0; i < routes.size(); i++)
        {
                for (int j = 0; j < routes[i].size(); j++)
                        cout << routes[i][j] << " ";
                cout << endl;
        }
        cout << endl;

	double sum = 0;
	for (int a = 0; a < routes.size(); a++)
	{
		// counting routes length
		int weight = 0;
		for (int b = 1; b < routes[a].size(); b++)
		{
			sum = sum + dist[routes[a][b-1]][routes[a][b]];
			weight = weight + request[routes[a][b]];
		}
		// checking for incorrect solutions
		if (weight > routecapasity)
			cout << "_error: route " << a << " overloaded" << endl;
	}
	return sum;
}

double full_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity)
{
	bool ongoing = true;
	int count = 0;
        while (ongoing)
        {
		ongoing = false;
		count = count + 1;
                for (int c = 1; c < request.size(); c++)
                        {
                                // trying to minimalize
                                pair<int,int> node = getroute(routes, c);
                                ongoing = ongoing || insertpath(routes, dist, request, routecapasity, node.first, node.second);
                        }
        }
	cout << "_reached local minimum on step " << count << endl;

	for (int i = 0; i < routes.size(); i++)
	{
		for (int j = 0; j < routes[i].size(); j++)
			cout << routes[i][j] << " ";
		cout << endl;
	}
	cout << endl;

        double sum = 0;
        for (int a = 0; a < routes.size(); a++)
        {
                // counting routes length
                int weight = 0;
                for (int b = 1; b < routes[a].size(); b++)
                {
                        sum = sum + dist[routes[a][b-1]][routes[a][b]];
			weight = weight + request[routes[a][b]];
                }
                // checking for incorrect solutions
                if (weight > routecapasity)
                        cout << "_error: route " << a << " overloaded" << endl;
        }
        return sum;
}
