
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
class node {
    public:
    int dim;
    vector<vector<int>> qr;

    node * right;
    node * left;

    node(int dim) : dim(dim), qr(dim, vector<int>(dim)) {}

};
*/

vector<vector<int>> test;

bool isValid(vector<vector<int>> qr, int dim, int line, int col, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    if (col == dim) {
        int transitions = 0;
        for (int i = 0; i < dim - 1; i++) {
            int j = i + 1;
            if (qr[line][i] != qr[line][j]) {
                transitions++;
            }
        }
        if (transitions != lt[line]){
            return false;
        }
    }

    return true;
}


bool rec(vector<vector<int>> qr, vector<vector<int>> visited, int dim, int i, int j, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    if (i == dim) {
        i = 0;
        j++;
    }

    if (!isValid(qr, dim, j, i, lb, cb, lt, ct, qb, db)){
        return false;
    }

    if (j == dim) {
        test = qr;
        return false;
    }

    for (int k = i; k < dim; k++) {
        if (visited[j][k] == 0) {
            visited[j][k] = 1;
            qr[j][k] = 1;
            rec(qr, visited, dim, i + 1, j, lb, cb, lt, ct, qb, db);
            qr[j][k] = 0;
            visited[j][k] = 0;   
        }
        if (k == dim - 1 && j < dim - 1 && isValid(qr, dim, j, i + 1, lb, cb, lt, ct, qb, db)) {
            i = 0;
            j++;
            rec(qr, visited, dim, i, j, lb, cb, lt, ct, qb, db);
        }else if (k == dim - 1 && j == dim - 1 && isValid(qr, dim, j, i + 1, lb, cb, lt, ct, qb, db)) {
            test = qr;
            return false;
        }
        
    }

    return false;
}

void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    cout << "teste" << endl;
    
    vector<vector<int>> qr(n, vector<int>(n));
    vector<vector<int>> visited(n, vector<int>(n));

    rec(qr, visited, n, 0, 0, lb, cb, lt, ct, qb, db);
    
    cout << "teste2" << endl;


}



int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int num, n, aux;
    vector<int> lb, cb, lt, ct, qb, db;

    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> aux;
            lb.push_back(aux);
        }
        for (int j = 0; j < n; j++){
            cin >> aux;
            cb.push_back(aux);
        }
        for (int j = 0; j < n; j++){
            cin >> aux;
            lt.push_back(aux);
        }
        for (int j = 0; j < n; j++){
            cin >> aux;
            ct.push_back(aux);
        }
        for (int j = 0; j < 4; j++){
            cin >> aux;
            qb.push_back(aux);
        }
        for (int j = 0; j < 2; j++){
            cin >> aux;
            db.push_back(aux);
        }

        func(n, lb, cb, lt, ct, qb, db);
        lb.clear();
        cb.clear();
        lt.clear();
        ct.clear();
        qb.clear();
        db.clear();
    }

    return 0;
}