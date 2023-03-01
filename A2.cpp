
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

vector<vector<vector<int>>> test;

bool isNotValid(vector<vector<int>> qr, int dim, int line, int col, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    if (col == dim - 1) {
        int transitions = 0;
        for (int i = 0; i < dim - 1; i++) {
            int j = i + 1;
            if (qr[line][i] != qr[line][j]) {
                transitions++;
            }
        }
        if (transitions != lt[line]){
            return true;
        }
    }

    return false;
}


bool rec(vector<vector<int>> qr, int dim, int i, int j, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    if (j == dim) {
        test.push_back(qr);
        return true;
    }

    
    //TODO: verificar se é possivel

    if (i < dim - 1) {
        qr[j][i] = 1;
        if (isNotValid(qr, dim, j, i, lb, cb, lt, ct, qb, db) && rec(qr, dim, i + 1, j, lb, cb, lt, ct, qb, db)) {
            return true;
        }
        qr[j][i] = 0;
        return rec(qr, dim, i + 1, j, lb, cb,  lt, ct, qb, db);

    } else if (i == dim - 1) {
        qr[j][i] = 1;
        if (qr[0][0] == 1 && qr[0][1] == 1 && qr[0][2] == 1 && qr[1][0] == 1 && qr[1][1] == 1 && qr[1][2] == 1 && qr[2][0] == 1 && qr[2][1] == 1 && qr[2][2] == 1) {
            int aux;
        }
        if (isNotValid(qr, dim, j, i, lb, cb, lt, ct, qb, db) && rec(qr, dim, 0, j + 1, lb, cb, lt, ct, qb, db)) {
            return false;
        }
        qr[j][i] = 0;
        if (isNotValid(qr, dim, j, i, lb, cb, lt, ct, qb, db) && rec(qr, dim, 0, j + 1, lb, cb, lt, ct, qb, db)) {
            return false;
        }

    }
    
    return true;
}

void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    cout << "teste" << endl;
    
    vector<vector<int>> qr(n, vector<int>(n));

    rec(qr, n, 0, 0, lb, cb, lt, ct, qb, db);
    
    
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