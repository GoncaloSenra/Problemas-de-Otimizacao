#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class node {
    public:
    int dim;
    vector<vector<int>> qr;

    node * right;
    node * left;

    node(int dim) : dim(dim), qr(dim, vector<int>(dim)) {}

};

void fill_line(node * root, vector<int> vec, int n, int blacks, int i, int line);


void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    cout << "teste" << endl;
    

    
    
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