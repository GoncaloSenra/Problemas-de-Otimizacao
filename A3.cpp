
/*
    Gonçalo Senra   nº 2020213750
    Henrique Costa  nº 2020214120
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<int>> saved;

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


bool isValid(vector<vector<int>> qr, int dim, int line, int col, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {

    //NOTE: COL TRANSITIONS
    if (line == dim - 1 && col > 0) {
        int transitions = 0;
        for (int i = 0; i < dim - 1; i++) {
            int j = i + 1;
            if (qr[i][col - 1] != qr[j][col - 1]) {
                transitions++;
            }
        }
        if (transitions != ct[col - 1]){
            return false;
        }
        
    } else if (line > 1) {
        int transitions = 0;
        for (int i = 0; i < line-1; i++) {
            int j = i + 1;
            if (qr[i][col] != qr[j][col]) {
                transitions++;
            }
            if (transitions > ct[col]) {
                return false;
            }
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
        int whites = dim;
        for (int i = 0; i < line; i++) {
            if (qr[i][col - 1] == 1) {
                blacks++;
            } else {
                whites--;
            }
            if (blacks > cb[col - 1]) {
                return false;
            }
            if (whites < cb[col - 1]) {
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
    } else if (col > 1) {
        int transitions = 0;
        for (int i = 0; i < col-1; i++) {
            int j = i + 1;
            if (qr[line][i] != qr[line][j]) {
                transitions++;
            }
            if (transitions > lt[line]) {
                return false;
            }
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
        int whites = dim;
        int blacks = 0;
        for (int i = 0; i < col; i++) {
            if (qr[line][i] == 1) {
                blacks++;
            } else {
                whites--;
            }
            if (blacks > lb[line]) {
                return false;
            }
            if (whites < lb[line]) {
                return false;
            }
        }
    }

    //NOTE: DIAGONAL LEFT - RIGHT
    if (line == col - 1) {
        int blacks = 0;
        int whites = dim;
        for (int i = 0; i < line + 1; i++) {
            if (qr[i][i] == 1) {
                blacks++;
            }else{
                whites--;
            }
            if(blacks > db[0]){
                return false;
            }
            if(whites < db[0]){
                return false;
            }
        }
        if(blacks != db[0] && line == dim){
            return false;
        }
    } 
    
    //NOTE: DIAGONAL RIGHT - LEFT
    if (line + col == dim) {
        int blacks = 0;
        int whites = dim;
        for (int i = 0; i < line + 1; i++) {
            int indice = dim-i-1;
            if(col <= indice){
                if (qr[i][indice] == 1) {
                    blacks++;
                }else{
                    whites--;
                }
            }
            if(whites < db[1]){
                return false;
            }
            if(blacks > db[1]){
                return false;
            }
        }
        if(blacks != db[1] && line == dim){
            return false;
        }
    }  
    
    //NOTE: QUADRANTS BLACKS
    if (col > 0) {
        int tam, tam2;
        int count_1 = 0, count_2 = 0, count_3 = 0, count_4 = 0;
        if (dim % 2 == 0) 
            tam = (dim / 2); tam2 = (dim / 2);
        if (dim % 2 != 0) 
            tam = (dim / 2); tam2 = (dim / 2) + 1;
        int aux1 = tam * tam2 , aux2 = tam * tam, aux3 = tam * tam2, aux4 = tam2 * tam2;
        for (int i = 0; i < line; i++) {
            for (int j = 0; j < col; j++) {
                if (i <= (dim / 2) - 1 && j <= (dim / 2) - 1 && qr[i][j] == 1) {
                    count_2++;
                } else if (i <= (dim / 2) - 1 && j <= (dim / 2) - 1 && qr[i][j] == 0) {
                    aux2--;
                } else if (i <= (dim / 2) - 1 && j > (dim / 2) - 1 && qr[i][j] == 1) {
                    count_1++;
                } else if (i <= (dim / 2) - 1 && j > (dim / 2) - 1 && qr[i][j] == 0) {
                    aux1--;
                } else if (i > (dim / 2) - 1 && j <= (dim / 2) - 1 && qr[i][j] == 1) {
                    count_3++;
                } else if (i > (dim / 2) - 1 && j <= (dim / 2) - 1 && qr[i][j] == 0) {
                    aux3--;
                } else if (i > (dim / 2) - 1 && j > (dim / 2) - 1 && qr[i][j] == 1) {
                    count_4++;
                } else if (i > (dim / 2) - 1 && j > (dim / 2) - 1 && qr[i][j] == 0) {
                    aux4--;
                }
            }
        }
        if (aux1 < qb[0] || aux2 < qb[1] || aux3 < qb[2] || aux4 < qb[3]) {
            return false;
        }

        if (count_1 > qb[0] || count_2 > qb[1] || count_3 > qb[2] || count_4 > qb[3]) {
            return false;
        }

    }

    return true;
}


bool rec(vector<vector<int>> qr, vector<vector<int>> visited, int dim, int i, int j, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    
    //if (qr[0][0] == 1 && qr[0][1] == 0 && qr[0][2] == 0 && qr[1][0] == 0 && qr[1][1] == 0 && qr[1][2] == 0 && qr[2][0] == 0 && qr[2][1] == 0 && qr[2][2] == 1)
        //cout << "debug";
    
    if (i == dim) {
        i = 0;
        j++;
    }
    
    if (!isValid(qr, dim, j, i, lb, cb, lt, ct, qb, db)){
        return false;
    }

    if (j == dim) {
        saved = qr;
        countqrs++;
        return true;
    }

    if (visited[j][i] == 0) {
        qr[j][i] = 1;
        visited[j][i] = 1;
        rec(qr, visited, dim, i + 1, j, lb, cb, lt, ct, qb, db);
        qr[j][i] = 0;
        visited[j][i] = 0;
        if (!isValid(qr, dim, j, i, lb, cb, lt, ct, qb, db)){
            return false;
        } else {
            rec(qr, visited, dim, i + 1, j, lb, cb, lt, ct, qb, db);
        }
    } else {
        rec(qr, visited, dim, i + 1, j, lb, cb, lt, ct, qb, db);
    }
    
    return true;
}

void pre_proc(vector<vector<int>> *qr, vector<vector<int>> *visited, int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    
    int countLines1 = 0; 
    int countCols1 = 0; 
    int countLines0 = 0; 
    int countCols0 = 0; 

    vector<int> idxLines(n);
    vector<int> idxCols(n);

    //NOTE: FILL LINES AND COLS
    for (int i = 0; i < n; i++) {
        if (lb[i] == 0) {
            idxLines[i] = 1;
            countLines0++;
            for (int j = 0; j < n; j++) {
                (*visited)[i][j] = 1;
            }
        }
        if (cb[i] == 0) {
            idxCols[i] = 1;
            countCols0++;
            for (int j = 0; j < n; j++) {
                (*visited)[j][i] = 1;
            }
        }
        if (lb[i] == n) {
            idxLines[i] = 2;
            countLines1++;
            for (int j = 0; j < n; j++) {
                (*qr)[i][j] = 1;
                (*visited)[i][j] = 1;
            }
        }
        if (cb[i] == n) {
            idxCols[i] = 2;
            countCols1++;
            for (int j = 0; j < n; j++) {
                (*qr)[j][i] = 1;
                (*visited)[j][i] = 1;
            }
        }
    }
    
    //NOTE:
    for (int i = 0; i < n; i++) {
        if (n - countLines0 == cb[i]) {
            for (int j = 0; j < n; j++) {
                if ((*visited)[j][i] == 0) {
                    (*visited)[j][i] = 1;
                    (*qr)[j][i] = 1;
                }
            }
        }
        if (n - countLines1 == cb[i]) {
            for (int j = 0; j < n; j++) {
                if ((*visited)[j][i] == 0) {
                    (*visited)[j][i] = 1;
                    (*qr)[j][i] = 0;
                }
            }
        }
        if (n - countCols1 == lb[i]) {
            for (int j = 0; j < n; j++) {
                if ((*visited)[i][j] == 0) {
                    (*visited)[i][j] = 1;
                    (*qr)[i][j] = 0;
                }
            }
        }
        if (n - countCols0 == lb[i]) {
            for (int j = 0; j < n; j++) {
                if ((*visited)[i][j] == 0) {
                    (*visited)[i][j] = 1;
                    (*qr)[i][j] = 1;
                }
            }
        }

    }

    idxLines.clear();
    idxCols.clear();
}

void func(int n, vector<int> lb, vector<int> cb, vector<int> lt, vector<int> ct, vector<int> qb, vector<int> db) {
    countqrs = 0;
    vector<vector<int>> qr(n, vector<int>(n));
    vector<vector<int>> visited(n, vector<int>(n));

    pre_proc(&qr, &visited, n, lb, cb, lt, ct, qb, db);
   
    rec(qr, visited, n, 0, 0, lb, cb, lt, ct, qb, db);
    
    if (countqrs == 0) {
        cout << "DEFECT: No QR Code generated!" << endl;
    } else if (countqrs == 1) {
        cout << "VALID: 1 QR Code generated!" << endl;
        printQrCode(saved, n);
    } else if (countqrs > 1) {
        cout << "INVALID: " << countqrs << " QR Codes generated!" << endl;
    }

}



int main() {

    //clock_t tStart = clock();

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

    //printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}