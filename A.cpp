#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class node {
    public:
    int dim;
    vector<vector<int>> qr;

    vector<node*> children;

    node(int dim) : dim(dim), qr(dim, vector<int>(dim)) {}

    void newChild(node * child) {
        children.push_back(child);
    }

};

void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    cout << "teste" << endl;
    
    node * root = new node(n);
    node * child1 = new node(n);

    root->newChild(child1);

    child1->qr[0][0] = 1;

    
    
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