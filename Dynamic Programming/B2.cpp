/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> shares;

void task12(int n, int d, int r, int k, bool task2)
{

    for (int i = 0; i < n; i++)
    {
        int toSell = -shares[i][0] * k;
        int bought = 0;
        vector<int> tradingScheme;

        int j = 1;
        while (j < d)
        {
            bool entrou = false;

            int auxToSell = bought - (shares[i][j] * k);
            if (auxToSell > toSell)
            {
                toSell = auxToSell;
                if (task2)
                {
                    entrou = true;
                    tradingScheme.push_back(-k);
                }
                cout << "S ";
            } else {

                cout << "NS ";
            }

            int auxToBuy = toSell + (shares[i][j] * k) - (r * k);
            if (auxToBuy > bought)
            {
                bought = auxToBuy;
                if (task2)
                {
                    entrou = true;
                    tradingScheme.push_back(k);
                }
                cout << "B\n";
            } else {
                cout << "NB\n";
            }

            if (task2 && !entrou)
            {
                tradingScheme.push_back(0);
            }

            cout << "BOUGHT: " << bought << "\tTOSELL: " << toSell << endl;
            //cout << "J: " << j << endl;
            j++;
        }
        cout << bought << endl;
        if (task2)
        {
            for (int l = 0; l < d; l++)
            {
                cout << tradingScheme[l] << " ";
            }
            cout << endl;
        }
    }
}

void task22(int n, int d, int r, int k)
{
    for (int j = 0; j < n; j++)
    {
        int aheadNotBuy, aheadBuy, curBuy, curNotBuy;
        aheadBuy = aheadNotBuy = 0;

        vector<int> dp = vector<int>(d, 0);

        for (int i = d - 1; i >= 0; i--)
        {
            cout << i << ":\n";
            curNotBuy = max(shares[j][i] * k + aheadBuy, aheadNotBuy);
            if (shares[j][i] * k + aheadBuy > aheadNotBuy) {
                cout<<"Sold |";
                if(i == d - 1){
                    dp[i] = -k;
                } else if (i == 0) {
                    dp[i] == 0; 
                } else {
                    if (dp[i+1] == -k) {
                        dp[i+1] = 0;
                        dp[i] = -k;
                    } else {
                        dp[i] = -k;
                    }
                }
            }else {
                cout<<"Not Sold |";

            }
            //cout << "1> " << shares[j][i] * k + aheadBuy << "\t: " << aheadNotBuy << endl;

            curBuy = max(-(shares[j][i] * k) - (r * k) + aheadNotBuy, aheadBuy);
            if (-(shares[j][i] * k) - (r * k) + aheadNotBuy > aheadBuy) {
                cout<<" Bought\n";
                if(i == d - 1){
                    dp[i] = k;
                } else {
                    if (dp[i+1] == k) {
                        dp[i+1] = 0;
                        dp[i] = k;
                    } else {
                        dp[i] = k;
                    }
                }
            } else {
                cout<<" Not Bought\n";

            }
            //cout << "2> " << -(shares[j][i] * k) - (r * k) + aheadNotBuy << "\t: " << aheadBuy << endl;

            aheadBuy = curBuy;
            aheadNotBuy = curNotBuy;

        }

        cout << aheadBuy << endl;
        for (int l = 0; l < d; l++)
        {
            cout << dp[l] << " ";
        }
        cout << endl;
        cout << "------------------" << endl;
    }
}


    


int main()
{
    int task;

    int n, d, k, r;

    cin >> task;
    cin >> n >> d >> k >> r;

    shares = vector<vector<int>>(n, vector<int>(d, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            cin >> shares[i][j];
        }
    }

    if (task == 1)
    {
        task12(n, d, r, k, false);
        cout << "-----------------------------\n";
        task22(n, d, r, k);
    }
    else if (task == 2)
    {
        task12(n, d, r, k, true);
    }
    else if (task == 3)
    {
        cout << "3" << endl;
    }

    return 0;
}