#include <iostream>
#include <vector>
using namespace std;

// this fucntion tells position of verticie a in routes list
// requires: routes list, verticie a id
// returns: pair [number of the route, position on the route]
pair<int,int> getroute(vector<vector<int>> &routes, int a);

// this function tries to move current verticie to another
// place in same or other route and compares whether it will
// decrese overall routes length
// requires: routes list, distances matrix, verticies request
// values, maximum capasity of a route, initial verticie position
// returns: wheter any changes would yield results
bool insertpath (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int i, int j);

// this function goes through all the verticies m times trying
// to decrese overall routes legth by moveng said verticie to
// any other position
// requires: routes list, distances matrix, verticies request
// values, maximum capasity of a route, maximum iterrations
double m_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity, int m);

// this function goes through all the verticies trying to
// decrese overall routes legth by moveng said verticie to
// any other position until no more changes can be made
// requires: routes list, distances matrix, verticies request
// values, maximum capasity of a route
double full_pathfind (vector<vector<int>> &routes, vector<vector<double>> &dist, vector<int> &request, int routecapasity);
