
/*
    Gonçalo Senra   nº 2020213750
    Henrique Costa  nº 2020214120
*/

#include <iostream>
#include <vector>


using namespace std;


vector<vector<int>> saved;

vector<int> lb, cb, lt, ct, qb, db;
vector<vector<int>> qr;
vector<vector<int>> visited;

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

bool isValid(int dim, int line, int col) {

    int tam, tam2;

    if (dim % 2 == 0) {
        tam = (dim / 2); tam2 = (dim / 2);
    } else {
        tam = (dim / 2); tam2 = (dim / 2) + 1;
    }

    int aux1 = tam * tam2 , aux2 = tam * tam, aux3 = tam * tam2, aux4 = tam2 * tam2;

    if (line == 0 && col == 0)
        return true;

    /*if (col > 0) {
        if (col > 1) {
            if (qr[line][col - 2] != qr[line][col - 1]) {
                lt[line]--;
            }
        }
        if (line > 0) {
            if (qr[line][col - 1] != qr[line - 1][col - 1]) {
                ct[col - 1]--;
            }
        }
    } */
    if (col == 0) {
        
        // if (qr[line - 1][dim - 2] != qr[line - 1][dim - 1]) {
        //     lt[line - 1]--;
        // }
        
        // if (line > 1) {
        //     if (qr[line - 1][dim - 1] != qr[line - 2][dim - 1]) {
        //         ct[dim - 1]--;
        //     }
        // }
        

        //NOTE: FINAL DE LINHA
        if (lb[line - 1] != 0 || lt[line - 1] != 0) {
            return false;
        }

    }
    

    //NOTE: LIVE COUNTING
    if (line != dim && col > 0) {
        if (lb[line] < 0 || lt[line] < 0 || cb[col - 1] < 0 || ct[col - 1] < 0 || db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
            return false;
        }
        //NOTE: COUNT WHITES
        if (col > 0 && dim - col < lb[line]){
            return false;
        }
        if (col > 0 && dim - line < cb[col - 1]) {
            return false;
        }

        //NOTE: QUADRANTS WHITES    
        int q1 = (tam * line) + (col - tam);    
        int q2 = (tam * line) + col;    
        int q3 = (tam * (line - tam)) + col;    
        int q4 = (tam * (line - tam)) + (col - tam);    
        if (col < tam - 1 && line < tam - 1) {    
            if ((aux2 - q2) < qb[1]) {    
                return false;    
            }    
        } else if (col > tam - 1 && line < tam - 1) {    
            if ((aux1 - q1) < qb[0]) {    
                return false;    
            }    
        } else if (col < tam - 1 && line > tam - 1) {    
            if ((aux3 - q3) < qb[2]) {    
                return false;    
            }    
        } else if (col > tam - 1 && line > tam - 1) {    
            if ((aux4 - q4) < qb[3]) {    
                return false;    
            }    
        }    
        //NOTE: WHITES DIAGONALS    
        if (line == col - 1) {    
            if (dim - (line + 1) < db[0]) {    
                return false;    
            }    
        }    
        if (line + col == dim) {    
            if (dim - (line + 1) < db[1]) {    
                return false;    
            }    
        }
    }
    
    //NOTE: FINAL DE COLUNA
    if (line == dim - 1 && col > 0 ) {
        if (cb[col - 1] != 0 || ct[col - 1] != 0) {
            return false;
        }
    }

    //NOTE: FINAL DE CONTRA-DIAGONAL
    if (line == dim - 1 && col == 1){
        if (db[1] != 0) {
            return false;
        }
    }

    //NOTE: FINAL DA MATRIZ
    if (line == dim) {
        if (cb[dim - 1] != 0 || db[0] != 0 || qb[0] != 0 || qb[1] != 0 || qb[2] != 0 || qb[3] != 0 || ct[dim - 1] != 0) {
            return false;
        }
    }

    return true;
}


void setBlack(int dim, int line, int col, int *x, int *y) {
    lb[line]--;
    cb[col]--;
    if (line == col) {
        db[0]--;
    }
    if (line + col == dim - 1) {
        db[1]--;
    }

    if (line <= (dim / 2) - 1 && col <= (dim / 2) - 1) {
        qb[1]--;
    } else if (line <= (dim / 2) - 1 && col > (dim / 2) - 1) {
        qb[0]--;
    } else if (line > (dim / 2) - 1 && col <= (dim / 2) - 1) {
        qb[2]--;
    } else if (line > (dim / 2) - 1 && col > (dim / 2) - 1) {
        qb[3]--;
    }

    if (col > 0) {
        if (qr[line][col - 1] != 1) {
            lt[line]--;
            (*x)--;
        }
    }
    if (line > 0) {
        if (qr[line - 1][col] != 1) {
            ct[col]--;
            (*y)--;
        }
    }
}

void setWhite(int dim, int line, int col, int *x, int *y) {
    lb[line]++;
    cb[col]++;
    if (line == col) {
        db[0]++;
    }
    if (line + col == dim - 1) {
        db[1]++;
    }

    if (line <= (dim / 2) - 1 && col <= (dim / 2) - 1) {
        qb[1]++;
    } else if (line <= (dim / 2) - 1 && col > (dim / 2) - 1) {
        qb[0]++;
    } else if (line > (dim / 2) - 1 && col <= (dim / 2) - 1) {
        qb[2]++;
    } else if (line > (dim / 2) - 1 && col > (dim / 2) - 1) {
        qb[3]++;
    }

    if (col > 0) {
        if (qr[line][col - 1] != 0) {
            lt[line]--;
            (*x)--;
        } else {
            lt[line]++;
            (*x)++;
        }
    }
    if (line > 0) {
        if (qr[line - 1][col] != 0) {
            ct[col]--;
            (*y)--;
        } else {
            ct[col]++;
            (*y)++;
        }
    }
}

bool rec(int dim, int i, int j, int x, int y) {

    if (qr[0][0] == 1 && qr[0][1] == 0 && qr[0][2] == 1 && qr[0][3] == 0){
        cout << "debug";
        if (qr[1][0] == 1 && qr[1][1] == 0 && qr[1][2] == 1 && qr[1][3] == 0){
            cout << "";
            if (qr[2][0] == 0 && qr[2][1] == 1 && qr[2][2] == 0 && qr[2][3] == 1){
                cout << "";
                if (qr[3][0] == 0 && qr[3][1] == 1 && qr[3][2] == 0 && qr[3][3] == 1){
                    cout << "";
                }
            }
        }
    }
    
    if (i == dim) {
        i = 0;
        lt[j] = x;
        j++;
        x = lt[j];
    }
    
    if (!isValid(dim, j, i)){
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
        setBlack(dim, j, i, &x, &y);
        rec(dim, i + 1, j, x, y);
        qr[j][i] = 0;
        visited[j][i] = 0;
        setWhite(dim , j, i, &x, &y);
        rec(dim, i + 1, j, x, y);
    } else {
        //TODO: if lb == 0 passar a linha
        rec(dim, i + 1, j, x, y);
    }
    
    lt[j] = x;
    return true;
}

void pre_proc(int n) {
    
    int countLines1 = 0; 
    int countCols1 = 0; 
    int countLines0 = 0; 
    int countCols0 = 0;

    int countDiagonal1 = 0; 
    int countDiagonal0 = 0;
    int countDiagonalInv1 = 0; 
    int countDiagonalInv0 = 0;


    vector<int> idxLines(n);
    vector<int> idxCols(n);

    //NOTE: FILL LINES AND COLS
    for (int i = 0; i < n; i++) {
        if (lb[i] == 0) {
            idxLines[i] = 1;
            countLines0++;
            for (int j = 0; j < n; j++) {
                visited[i][j] = -1;
            }
        }
        if (cb[i] == 0) {
            idxCols[i] = 1;
            countCols0++;
            for (int j = 0; j < n; j++) {
                visited[j][i] = -1;
            }
        }
        if (lb[i] == n) {
            idxLines[i] = 2;
            countLines1++;
            for (int j = 0; j < n; j++) {
                qr[i][j] = 1;
                visited[i][j] = 1;
            }
        }
        if (cb[i] == n) {
            idxCols[i] = 2;
            countCols1++;
            for (int j = 0; j < n; j++) {
                qr[j][i] = 1;
                visited[j][i] = 1;
            }
        }
    }

    int tam, tam2;

    if (n % 2 == 0) {
        tam = (n / 2); tam2 = (n / 2);
    } else {
        tam = (n / 2); tam2 = (n / 2) + 1;
    }

    int aux1 = tam * tam2 , aux2 = tam * tam, aux3 = tam * tam2, aux4 = tam2 * tam2;
    
    //NOTE: FILL QUANDRANTS
    if (qb[0] == aux1) {
        for (int i = 0; i < tam; i++) {
            for (int j = tam ; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                }
            }
        }
    } else if (qb[0] == 0) {
        for (int i = 0; i < tam; i++) {
            for (int j = tam ; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
                }
            }
        }
    }
    if (qb[1] == aux2) {
        for (int i = 0; i < tam; i++) {
            for (int j = 0 ; j < tam; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                }
            }
        }
    } else if (qb[1] == 0) {
        for (int i = 0; i < tam; i++) {
            for (int j = 0 ; j < tam; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
                }
            }
        }
    }
    if (qb[2] == aux3) {
        for (int i = tam; i < n; i++) {
            for (int j = 0 ; j < tam; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                }
            }
        }
    } else if (qb[2] == 0) {
        for (int i = tam; i < n; i++) {
            for (int j = 0 ; j < tam; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
                }
            }
        }
    }
    if (qb[3] == aux4) {
        for (int i = tam; i < n; i++) {
            for (int j = tam ; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                }
            }
        }
    } else if (qb[3] == 0) {
        for (int i = tam; i < n; i++) {
            for (int j = tam ; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
                }
            }
        }
    }
    
    //FIXME: DIAGONAIS OTIMIZADAS (1 FOR) 
    for (int i = 0; i < n; i++){
        if(db[0] == 0){
            visited[i][i] = -1;
            qr[i][i] = 0;
        }
        if(db[0] == n){
            visited[i][i] = 1;
            qr[i][i] = 1;
        }
        if(db[1] == 0){
            visited[i][n-i-1] = -1;
            qr[i][n-i-1] = 0;
        }
        if(db[1] == n){
            visited[i][n-i-1] = 1;
            qr[i][n-i-1] = 1;
        }

        if(visited[i][i] == 1){
            countDiagonal1++;
        }else if(visited[i][i] == -1){
            countDiagonal0++;
        }

        if(visited[i][n - i -1] == 1){
            countDiagonalInv1++;
        }else if(visited[i][n - i -1] == -1){
            countDiagonalInv0++;
        }

        if (n - countDiagonal0 == db[0]) {
            if (visited[i][i] == 0) {
                visited[i][i] = 1;
                qr[i][i] = 1;
            }
        }else if(countDiagonal1 == db[0]){
            if (visited[i][i] == 0) {
                visited[i][i] = -1;
                qr[i][i] = 0;
            }
        }

        if (n - countDiagonalInv0 == db[0]) {
            if (visited[i][n - i -1] == 0) {
                visited[i][n -i -1] = 1;
                qr[i][n-i-1] = 1;
            }
        }else if(countDiagonalInv1 == db[0]){
            if (visited[i][n - i - 1] == 0) {
                visited[i][n - i - 1] = -1;
                qr[i][n - i - 1] = 0;
            }
        }
    }
    


    //NOTE:
    for (int i = 0; i < n; i++) {
        if (n - countLines0 == cb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    visited[j][i] = 1;
                    qr[j][i] = 1;
                }
            }
        }
        if (n - countLines1 == cb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    visited[j][i] = -1;
                    qr[j][i] = 0;
                }
            }
        }
        if (n - countCols1 == lb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
                    qr[i][j] = 0;
                }
            }
        }
        if (n - countCols0 == lb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                }
            }
        }

    }

    idxLines.clear();
    idxCols.clear();
}

void func(int n) {
    countqrs = 0;
    int aux = 0;
    qr = vector<vector<int>>(n, vector<int>(n, 0));
    visited = vector<vector<int>>(n, vector<int>(n, 0));


    //pre_proc(n);

    //TODO: Se a matriz visited estiver totalmente preenchida a 1 na entrar no rec!

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 0) {
                aux = 1;
                break;
            }
        }
        if (aux == 1)
            break;
    }

    //TODO: Se o pre_proc retornar impossivel nao entrar no rec 
    

    if (aux == 1)
        rec(n, 0, 0, lt[0], ct[0]);
    else
        saved = qr;

    
    if (countqrs == 1 || aux == 0) {
        cout << "VALID: 1 QR Code generated!" << endl;
        printQrCode(saved, n);
    } else if (countqrs == 0 ) {
        cout << "DEFECT: No QR Code generated!" << endl;
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

        func(n);
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