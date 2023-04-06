/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> shares_vec;


int max_profit(vector<int>& company, int D, int K, int R) {
    vector<int> profits;
    for (int i = 0; i < D; i++) {
        for (int j = i+1; j < D; j++) {
            // Calculate the profit if we buy on day i and sell on day j
            int profit = ((company[j] - company[i]) * K) - (K * R);
            if (profit > 0) {
                profits.push_back(profit);
            }
        }
    }
    // Return the maximum profit, or 0 if there are no profitable trades
    return *max_element(profits.begin(), profits.end());
}



int main(){
    int task;

    int n, d, k, r;

    cin >> task;
    cin >> n >> d >> k >> r;
    
    shares_vec = vector<vector<int>>(n, vector<int>(d , 0));

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < d ; j++){
            cin >> shares_vec[i][j];       
        }
    }
    

    if (task == 1) {
        for (int i = 0; i < n; i++) {
            cout << max_profit(shares_vec[i], d, k, r) << endl;
        }
    } else if (task == 2) {
        cout << "2" << endl;
    } else if (task == 3) {
        cout << "3" << endl;
    }
    
    return 0;
}