/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> shares;

void task12(int n, int d, int r, int k, bool task2) {
    
    for (int i = 0; i < n; i++) {
        int toSell = -shares[i][0] * k;
        int bought = 0;
        vector<int> tradingScheme;

        int j = 1;
        while (j < d) {
            bool entrou = false;

            int auxToSell = bought - (shares[i][j] * k);
            if (auxToSell > toSell) {
                toSell = auxToSell;
                if (task2) {
                    entrou = true;
                    tradingScheme.push_back(-k);
                }
            }

            int auxToBuy = toSell + (shares[i][j] * k) - (r * k);
            if (auxToBuy > bought) {
                bought = auxToBuy;
                if (task2) {
                    entrou = true;
                    tradingScheme.push_back(k);
                }
            }

            if (task2 && !entrou) {
                tradingScheme.push_back(0);
            }

            j++;
        }
        cout << bought << endl;
        if (task2) {
            for (int k = 0; k < d; k++) {
                cout << tradingScheme[k] << " "; 
            }
            cout << endl;
        }
        
    }
    
}


int main(){
    int task;

    int n, d, k, r;

    cin >> task;
    cin >> n >> d >> k >> r;
    
    shares = vector<vector<int>>(n, vector<int>(d , 0));

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < d ; j++){
            cin >> shares[i][j];       
        }
    }
    
    if (task == 1) {
        task12(n, d, r, k, false);
    } else if (task == 2) {
        task12(n, d, r, k, true);
    } else if (task == 3) {
        cout << "3" << endl;
    }
    
    return 0;
}