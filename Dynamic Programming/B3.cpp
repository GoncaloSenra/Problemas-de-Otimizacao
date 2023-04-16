/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> shares;
vector<vector<int>> scheme;
int k, r;

long getAns(int i , int ind, int buy, int n, vector<vector<long>> &dp)
{

    if (ind == n)
    {
        return 0;
    }

    if (dp[ind][buy] != -1)
        return dp[ind][buy];

    long profit;

    if (buy == 0)
    { // We can buy the stock
        long f = getAns(i, ind + 1, 0, n, dp);
        long w = (-shares[i][ind] * k) - (k * r) + getAns(i, ind + 1, 1, n, dp);

        profit = max(f, w);
        if (f < w)
        {
            //cout << "buy" << ind << " ";
            if(shares[i][ind] <= shares[i][ind-1]){
                scheme[i][ind] = k;
                scheme[i][ind-1] = 0;
            }
        }
    }

    if (buy == 1)
    { // We can sell the stock
        long f = getAns(i, ind + 1, 1, n, dp);
        long w = (shares[i][ind] * k) + getAns(i, ind + 1, 0, n, dp);
        profit = max(f, w);
        if (f < w)
        {
            //cout << "sell" << ind << " ";
            if(shares[i][ind] >= shares[i][ind-1]){
                scheme[i][ind] = -k;
                scheme[i][ind-1] = 0;
            }
        }
    }

    return dp[ind][buy] = profit;
}

long getMaximumProfit(int i, int n)
{
    vector<vector<long>> dp(n, vector<long>(2, -1));

    if (n == 0)
        return 0;
    long ans = getAns(i, 0, 0, n, dp);
    return ans;
}

int main()
{
    int task;

    int n, d;

    cin >> task;
    cin >> n >> d >> k >> r;

    shares = vector<vector<int>>(n, vector<int>(d, 0));
    scheme = vector<vector<int>>(n, vector<int>(d, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            cin >> shares[i][j];
        }
    }

    if (task == 1)
    {
        for (int i = 0; i < n; i++)
        {
            cout << getMaximumProfit(i, d) << endl;
            for (int j = 0; j < d; j++) {
                cout << scheme[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else if (task == 2)
    {
        for (int i = 0; i < n; i++)
        {
            cout << getMaximumProfit(i, d) << endl;
            for (int j = 0; j < d; j++) {
                cout << scheme[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else if (task == 3)
    {
        cout << "3" << endl;
    }

    return 0;
}