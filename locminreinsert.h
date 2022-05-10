#include <iostream>
#include <vector>
using namespace std;

pair<int,int> getroute(vector<vector<int>> &routes, int a);
bool insertpath (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int i, int j);
double m_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int m);
double full_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity);
