
/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

int n;
int t;
vector<vector<int>> edges;
stack<int> pilha;
vector<int> low;
vector<int> dfs;
vector<int> in;
vector<vector<int>> scc;

void Tarzan(int v)
{
    low[v] = dfs[v] = t;
    t++;
    pilha.push(v);
    in[v] = 1;
    for (int w = 1; w <= n; w++)
    {
        if (edges[v][w] > 0)
        {
            if (dfs[w] == 0)
            {
                Tarzan(w);
                low[v] = min(low[v], low[w]);
            }
            else if (in[w] == 1)
            {
                low[v] = min(low[v], dfs[w]);
            }
        }
    }
    if (low[v] == dfs[v])
    {
        vector<int> c;
        int w;
        do
        {
            w = pilha.top();
            pilha.pop();
            in[w] = 0;
            c.push_back(w);
        } while (w != v);
        scc.push_back(c);
    }
}

int main()
{
    int id, m, b;
    t = 1;
    while (cin >> n)
    {
        edges = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        dfs = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        in = vector<int>(n + 1, 0);

        for (int i = 0; i < n; i++)
        {
            cin >> id;

            while (1)
            {
                cin >> m;
                if (m == 0)
                    break;

                cin >> b;

                edges[id][b] = m;
            }
        }

        /*for (int j = 1; j < n + 1; j++)
        {
            int l = 0;
            for (int k = 1; k < n + 1; k++)
            {
                if (edges[k][j] > 0)
                {
                    l = 1;
                }
            }
            if (l == 0)
            {
                Tarzan(j);
            }
        }*/

        for (int j = 1; j < n + 1; j++) {
            if (dfs[j] == 0) {
                Tarzan(j);
            }
        }

        if (scc.size() == n)
        {
            cout << "No cluster" << endl;
        }
        else
        {
            int total = 0;
            for (int z = 0; z < scc.size() ;z++) {
                if (scc[z].size() > 1) {
                    for (int l = 0; l < scc[z].size(); l++)
                    {
                        int debt = 0;
                        for (int x = 1; x < n+1; x++)
                        {
                            debt -= edges[scc[z][l]][x];
                            debt += edges[x][scc[z][l]];
                        }
                        total += debt;
                    }
                }
            }
            cout << total << endl;
        }

        pilha = stack<int>();
        scc = vector<vector<int>>();
    }

    return 0;
}