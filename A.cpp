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

void fill_line(node * root, vector<int> vec, int n, int blacks, int i, int line);


void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    cout << "teste" << endl;
    
    node * root = new node(n);
    //node * child1 = new node(n);

    //root->newChild(child1);

    //child1->qr[0][0] = 1;

    
    for (int i = 0; i < n; i++) {
        vector<int> line(n);

        fill_line(root, line, n, lb[i], 0, i);

    }
    cout << "teste2" << endl;

}

void rec(node * root){

    for (int i = 0; i < root->children.size(); i++) {
        vector<int> line(n);

        fill_line(root->children[i], line, n, lb[i], 0, i);

    }

}


void fill_line(node * root, vector<int> vec, int n, int blacks, int i, int line) {

    if (blacks == 0) {
        node * child = new node(n);
        child->qr = root->qr;
        child->qr[line] = vec;
        root->newChild(child);
        
        return;
    }

    for (int j = i; j < n; j++) {
        vec[j] = 1;
        fill_line(root, vec, n, blacks - 1, i + 1, line);
        vec[j] = 0;
    }
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