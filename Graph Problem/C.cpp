
/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int n, m, o;
vector<vector<int>> edges;
vector<int> low;
vector<int> dfs;
vector<int> parent;
int t;
int points;

void AP(int v)
{

    low[v] = dfs[v] = t;
    t++;

    for (v = 1; v < n + 1; v++)
    {
        for (int w = 1; w < n + 1; w++)
        {
            if (edges[v][w] == 1)
            {
                if (dfs[w] == 0)
                {
                    parent[w] = v;
                    AP(w);
                    low[v] = min(low[v], low[w]);
                    if (dfs[v] == 1 && dfs[w] != 2)
                    {
                        points++;
                    }
                    if (dfs[v] != 1 && low[w] >= dfs[v])
                    {
                        points++;
                    }
                }
                else if (parent[v] != w)
                {
                    low[v] = min(low[v], dfs[w]);
                }
            }
        }
    }
}

int main()
{

    char c;
    string line;
    while (getline(cin, line))
    {
        t = 0;
        points = 0;
        istringstream iss(line);
        iss >> n;
        if (n == 0)
            continue;
        edges = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        dfs = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        parent = vector<int>(n + 1, 0);
        while (getline(cin, line))
        {
            istringstream iss2(line);
            iss2 >> m;
            if (m == 0)
                break;
            while (iss2 >> o)
            {
                edges[m][o] = 1;
                edges[o][m] = 1;
            }
        }
        cout << points << endl;
    }

    return 0;
}