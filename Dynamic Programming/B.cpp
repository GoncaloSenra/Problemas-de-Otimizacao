/*
    Gonçalo Senra   2020213750
    Henrique Costa  2020214120
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> shares;


int task1(int k, int d) {

    

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
        cout << "1" << endl;
    } else if (task == 2) {
        cout << "2" << endl;
    } else if (task == 3) {
        cout << "3" << endl;
    }
    
    return 0;
}