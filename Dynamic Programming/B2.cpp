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
        long long int toSell = -shares[i][0] * k;
        long long int bought = 0;
        vector<int> tradingScheme = vector<int>(d, 0);

        int j = 0;
        while (j < d)
        {
            // cout <<  j << ": " << endl;
            long long int auxToBuy = bought - (shares[i][j] * k);
            if (auxToBuy >= toSell)
            {
                toSell = auxToBuy;
                if (task2)
                {
                    if (j != d - 1)
                    {
                        if (j > 0 && tradingScheme[j - 1] == k)
                        {
                            tradingScheme[j - 1] = 0;
                            tradingScheme[j] = k;
                        }
                        else
                        {
                            tradingScheme[j] = k;
                        }
                    }
                }
                // cout << "Bought | ";
            }
            else
            {
                // cout << "Not Bought | ";
            }

            long long int auxToSell = toSell + (shares[i][j] * k) - (r * k);
            if (auxToSell >= bought)
            {
                bought = auxToSell;
                if (task2)
                {

                    if (j > 0 && tradingScheme[j - 1] == -k)
                    {
                        tradingScheme[j - 1] = 0;
                        tradingScheme[j] = -k;
                    }
                    else
                    {
                        tradingScheme[j] = -k;
                    }
                }
                // cout << "Sold\n";
            }
            else
            {
                // cout << "Not Sold\n";
            }

            // cout << "BOUGHT: " << bought << "\tTOSELL: " << toSell << endl;
            j++;
        }
        cout << bought << endl;
        if (task2)
        {
            int idx = 0;
            int state = 0;
            for (int m = 0; m < d; m++) {
                if (tradingScheme[m] == -k) {
                    state = -k;
                    idx = m;
                } else if (tradingScheme[m] == k) {
                    state = k;
                    idx = m;
                }
            }
            if (state == k) {
                tradingScheme[idx] = 0;
            }

            if (bought == 0)
            {
                for (int l = 0; l < d; l++)
                {
                    cout << "0 ";
                }
            }
            else
            {
                for (int l = 0; l < d; l++)
                {
                    cout << tradingScheme[l] << " ";
                }
            }

            cout << endl;
        }
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