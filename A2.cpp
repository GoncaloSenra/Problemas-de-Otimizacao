
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
2
0 1
0 1  
0 1 
0 1 
0 1 0 1 
2 0
2
2 2
2 2  
0 0 
0 0 
0 1 0 1 
2 0
2
2 0
1 1  
0 0 
1 1 
0 1 0 1 
2 0
*/

vector<vector<int>> test;

int countqrs = 0;

void printQrCode(vector<vector<int>> qr, int dim) {

    for (int i = 0; i < dim + 2; i++) {
        for (int j = 0; j < dim + 2; j++) {
            if (i == 0 || i == dim +1){
                if (j == 0) {
                    cout << "+";
                } else if (j == dim + 1) {
                    cout << "+\n";
                } else {
                    cout << "-";
                }
            } else {
                if (j == 0) {
                    cout << "|";
                } else if (j == dim +1) {
                    cout << "|\n";
                } else {
                    if (qr[i-1][j-1] == 0) {
                        cout << " ";
                    } else if (qr[i-1][j-1] == 1) {
                        cout << "#";
                    }
                }
            }
        }
    }

}

//TODO: Acabar as restrições
bool isValid(int aux, vector<vector<int>> qr, int dim, int line, int col, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    //NOTE: COLUMN TRANSITIONS
    /*
    if (line == dim-1) {
        int transitions_c = 0;
        for (int i = 0; i < dim - 1; i++) {
            int j = i + 1;
            if (qr[line][i] != qr[line][j]) {
                transitions_c++;
            }
        }
        if (transitions_c != lt[line]){
            return false;
        }
    }
    */
    //if (qr[0][0] == 0 && qr[0][1] == 0 && qr[1][0] == 0 && qr[1][1] == 1)
        //cout << "debug";
    
    if (aux == 1) {
        int lblacks = 0;
        int cblacks = 0;
        int ltrans = 0;
        int ctrans = 0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                int k = j + 1;
                int l = j + 1;
                if (qr[i][j] == 1) {
                    lblacks++;
                }
                if (qr[j][i] == 1) {
                    cblacks++;
                }
                if (j != dim - 1 && qr[i][j] != qr[i][k]) {
                    ltrans++;
                }
                if (j != dim - 1 && qr[j][i] != qr[l][i]) {
                    ctrans++;
                }
            }
            if (lblacks != lb[i]) {
                return false;
            }
            if (cblacks != cb[i]) {
                return false;
            }
            if (ltrans != lt[i]) {
                return false;
            }
            if (ctrans != ct[i]) {
                return false;
            }
            lblacks = 0;
            cblacks = 0;
            ltrans = 0;
            ctrans = 0;
            
        }
    }
    
    //NOTE: COLUMN BLACKS
    if (line == dim - 1 && col > 0) {
        int blacks = 0;
        for (int i = 0; i < dim; i++) {
            if (qr[i][col - 1] == 1) {
                blacks++;
            }
        }
        if (blacks != cb[col - 1]) {
            return false;
        }
    } else if (col > 0) {
        int blacks = 0;
        for (int i = 0; i < dim; i++) {
            if (qr[i][col] == 1) {
                blacks++;
            }
            if (blacks > cb[col]) {
                return false;
            }
        }
    }

    //NOTE: LINE TRANSITIONS
    if (col == 0 && line > 0) {
        int transitions = 0;
        for (int i = 0; i < dim - 1; i++) {
            int j = i + 1;
            if (qr[line-1][i] != qr[line-1][j]) {
                transitions++;
            }
        }
        if (transitions != lt[line - 1]){
            return false;
        }
    }

    //NOTE: LINE BLACKS
    if (col == 0 && line > 0) {
        int blacks = 0;
        for (int i = 0; i < dim; i++) {
            if (qr[line - 1][i] == 1) {
                blacks++;
            }
        }
        if (blacks != lb[line - 1]) {
            return false;
        }
    } else if (col > 0) {
        int blacks = 0;
        for (int i = 0; i < dim; i++) {
            if (qr[line][i] == 1) {
                blacks++;
            }
            if (blacks > lb[line]) {
                return false;
            }
        }
    }

    

    return true;
}

bool rec(vector<vector<int>> qr, vector<vector<int>> visited, int dim, int i, int j, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    //if (qr[0][0] == 0 && qr[0][1] == 0 && qr[1][0] == 0 && qr[1][1] == 0)
        //cout << "debug";

    if (i == dim) {
        i = 0;
        j++;
    }

    if (!isValid(0, qr, dim, j, i, lb, cb, lt, ct, qb, db)){
        return false;
    }

    if (j == dim) {
        test = qr;
        countqrs++;
        printQrCode(test, dim);
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
        if (k == dim - 1 && j < dim - 1 && isValid(0, qr, dim, j, k + 1, lb, cb, lt, ct, qb, db)) {
            i = 0;
            j++;
            rec(qr, visited, dim, i, j, lb, cb, lt, ct, qb, db);
        }else if (k == dim - 1 && j == dim - 1 && isValid(1, qr, dim, j, k + 1, lb, cb, lt, ct, qb, db)) {
            test = qr;
            countqrs++;
            printQrCode(test, dim);
            return false;
        }
        
    }

    return false;
}

void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    
    countqrs = 0;
    vector<vector<int>> qr(n, vector<int>(n));
    vector<vector<int>> visited(n, vector<int>(n));

    rec(qr, visited, n, 0, 0, lb, cb, lt, ct, qb, db);
    
    if (countqrs == 0) {
        cout << "DEFECT: No QR Code generated!" << endl;
    } else if (countqrs == 1) {
        cout << "VALID: 1 QR Code generated!" << endl;
        printQrCode(test, n);
    } else if (countqrs > 1) {
        cout << "INVALID: " << countqrs << " QR Codes generated!" << endl;
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