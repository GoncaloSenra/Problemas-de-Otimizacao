/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> shares;

void task1(int n, int d, int r, int k)
{
    for (int i = 0; i < n; i++)
    {
        long long int toSell = -shares[i][0] * k;
        long long int bought = 0;

        int j = 0;
        while (j < d)
        {
            //cout <<  j << ": " << endl;
            long long int auxToBuy = bought - (shares[i][j] * k);
            if (auxToBuy >= toSell)
            {
                toSell = auxToBuy;
                //cout << "Bought | ";
            } else {
                //cout << "Not Bought | ";
            }

            long long int auxToSell = toSell + (shares[i][j] * k) - (r * k);
            if (auxToSell >= bought)
            {
                bought = auxToSell;
                //cout << "Sold\n";
            } else {
                //cout << "Not Sold\n";
            }

            //cout << "BOUGHT: " << bought << "\tTOSELL: " << toSell << endl;
            j++;
        }
        cout << bought << endl;
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
        task1(n, d, r, k);
    }
    

    return 0;
}