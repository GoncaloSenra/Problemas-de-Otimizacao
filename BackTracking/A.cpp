/*
    Gonçalo Senra   nº 2020213750
    Henrique Costa  nº 2020214120
*/

#include <iostream>
#include <vector>
#include <cstring>


using namespace std;


int saved[30][30];
int qr[30][30];
int visited[30][30];

vector<int> lb, cb, lt, ct, qb, db;

int tam, tam2;
int aux1, aux2, aux3, aux4;

int countqrs = 0;

void printQrCode(int dim) {

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
                    if (saved[i-1][j-1] == 0) {
                        cout << " ";
                    } else if (saved[i-1][j-1] == 1) {
                        cout << "#";
                    }
                }
            }
        }
    }

}

bool isValid(int dim, int line, int col) {

    if (line == 0 && col == 0)
        return true;

    if (col == 0) {

        //NOTE: FINAL DE LINHA
        if (lb[line - 1] != 0 || lt[line - 1] != 0) {
            return false;
        }
    }

    //NOTE: LIVE COUNTING
    if (line != dim && col > 0) {

        if (lb[line] == 0 && lt[line] != 0){
            return false;
        }

        if (cb[col - 1] == 0 && ct[col - 1] != 0){
            return false;
        }

        if (lb[line] < 0 || /*lt[line] < -1 ||*/ cb[col - 1] < 0 || /*ct[col - 1] < -1 ||*/ db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
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
        // 
        
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

void setBlack(int dim, int line, int col) {
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

    if (col > 0 && col <= dim -2) {
        if(qr[line][col -1] == 1 && qr[line][col +1] == 1){
            lt[line] += 2;
            
        }else if(1 != qr[line][col-1] && 1 != qr[line][col+1]){
            lt[line] -= 2;
        }
    }else if(col == dim - 1){
        if(0 != qr[line][col-1]){
            lt[line]++;
        }else{
            lt[line]--;
        }
    }else if (col == 0){
        if (0 != qr[line][col +1]){
            lt[line]++;
        }else{
            lt[line]--;
        }
    }

    if (line > 0 && line <= dim -2) {
        if(qr[line - 1][col] == 1 && qr[line + 1][col] == 1){
            ct[col] += 2;
            
        }else if(1 != qr[line - 1][col] && 1 != qr[line + 1][col]){
            ct[col] -= 2;
        }
    }else if(line == dim - 1){
        if(0 != qr[line - 1][col]){
            ct[col]++;
        }else{
            ct[col]--;
        }
    }else if (line == 0){
        if (0 != qr[line + 1][col]){
            ct[col]++;
        }else{
            ct[col]--;
        }
    }
}

void setWhite(int dim, int line, int col) {
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

    if (col > 0 && col <= dim -2) {
        if(qr[line][col -1] == 1 && qr[line][col +1] == 1){
            lt[line] -= 2;
            
        }else if(1 != qr[line][col-1] && 1 != qr[line][col+1]){
            lt[line] += 2;
        }
    }else if(col == dim - 1){
        if(0 != qr[line][col-1]){
            lt[line]--;
        }else{
            lt[line]++;
        }
    }else if (col == 0){
        if (0 != qr[line][col +1]){
            lt[line]--;
        }else{
            lt[line]++;
        }
    }

    if (line > 0 && line <= dim -2) {
        if(qr[line - 1][col] == 1 && qr[line + 1][col] == 1){
            ct[col] -= 2;
            
        }else if(1 != qr[line - 1][col] && 1 != qr[line + 1][col]){
            ct[col] += 2;
        }
    }else if(line == dim - 1){
        if(0 != qr[line - 1][col]){
            ct[col]--;
        }else{
            ct[col]++;
        }
    }else if (line == 0){
        if (0 != qr[line + 1][col]){
            ct[col]--;
        }else{
            ct[col]++;
        }
    }

    // if(col > 0){
    //     if (qr[line][col - 1] == 0 && qr[line][col] == 1 || qr[line][col - 1] == 1 && qr[line][col] == 0)
    //     {
    //         lt[line]++;
    //     }
    // }
}

bool rec(int dim, int i, int j) {
    
    if (i == dim) {
        i = 0;
        j++;
    }
    
    if (!isValid(dim, j, i)){
        return false;
    }

    if (j == dim) {
        memcpy(saved, qr, 30 * 30 * sizeof(int));
        //printQrCode(dim);
        countqrs++;
        return true;
    } 
    
    if (visited[j][i] == 0) {
        qr[j][i] = 1;
        visited[j][i] = 1;
        setBlack(dim, j, i);
        rec(dim, i + 1, j);
        qr[j][i] = 0;
        visited[j][i] = 0;
        setWhite(dim , j, i);
        rec(dim, i + 1, j);
    } else {
        //TODO: if lb == 0 passar a linha
        rec(dim, i + 1, j);
    }
    
    return true;
}

bool pre_proc(int n) {
    
    int countLines1 = 0; 
    int countCols1 = 0; 
    int countLines0 = 0; 
    int countCols0 = 0;

    int countDiagonal1 = 0; 
    int countDiagonal0 = 0;
    int countDiagonalInv1 = 0; 
    int countDiagonalInv0 = 0;

    int countcols[30];
    int countlines[30];
    memset(countcols, 0, sizeof(countcols));
    memset(countlines, 0, sizeof(countlines));

    //NOTE: FILL QUANDRANTS
    if (qb[0] == aux1) {
        for (int i = 0; i < tam; i++) {
            for (int j = tam ; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                    setBlack(n, i, j);
                    countcols[j]++;
                    countlines[i]++;
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
                    setBlack(n, i, j);
                    countcols[j]++;
                    countlines[i]++;
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
                    setBlack(n, i, j);
                    countcols[j]++;
                    countlines[i]++;
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
                    setBlack(n, i, j);
                    countcols[j]++;
                    countlines[i]++;
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
    
    if (db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
        return false;
    }


    if (db[0] == n) {
        countDiagonal1 = 1;
        for (int i = 0; i < n; i++) {
            if (visited[i][i] == 0) {
                qr[i][i] = 1;
                setBlack(n, i, i);
                visited[i][i] = 1;
                countlines[i]++;
                countcols[i]++;
            }
        }
    } else if (db[0] == 0) {
        countDiagonal1 = 1;
        for (int i = 0; i < n; i++) {
            if (visited[i][i] == 0) {
                visited[i][i] = -1;
            }
        }
    }

    if (db[1] == n - countDiagonal1) {
        countDiagonalInv1 = 1;
        for (int i = 0; i < n; i++) {
            if (visited[i][n - 1 - i] == 0) {
                qr[i][n - 1 - i] = 1;
                setBlack(n, i, n - 1 - i);
                visited[i][n - 1 - i] = 1;
                countlines[i]++;
                countcols[n - 1 - i]++;
            }
        }
    } else if (db[1] == 0) {
        countDiagonalInv1 = 1;
        for (int i = 0; i < n; i++) {
            if (visited[i][n - 1 - i] == 0) {
                visited[i][n - 1 - i] = -1;
            }
        }
    }

    if (db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
        return false;
    }

    //NOTE: FILL LINES AND COLS
    
    for (int i = 0; i < n; i++) {
        if (lb[i] == 0) {
            countLines0++;
            for (int j = 0; j < n; j++) {
                visited[i][j] = -1;
            }
        }
        if (cb[i] == 0) {
            countCols0++;
            for (int j = 0; j < n; j++) {
                visited[j][i] = -1;
            }
        }
        if (lb[i] == n - countlines[i]) {
            countLines1++;
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    qr[i][j] = 1;
                    setBlack(n, i, j);
                    visited[i][j] = 1;
                    countcols[j]++;
                }
            }
        }
        if (cb[i] == n - countcols[i]) {
            countCols1++;
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    qr[j][i] = 1;
                    setBlack(n, j, i);
                    visited[j][i] = 1;
                    countlines[j]++;
                }
            }
        }
    }

    if (db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
        return false;
    }
    
    //NOTE:
    for (int i = 0; i < n; i++) {
        if (n - countLines0 == cb[i]) {
            countCols1++;
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    visited[j][i] = 1;
                    qr[j][i] = 1;
                    setBlack(n, j, i);
                }
            }
        }
        if (n - countLines1 == cb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    visited[j][i] = -1;
                    
                }
            }
        }
        if (n - countCols1 == lb[i]) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = -1;
            
                }
            }
        }
        if (n - countCols0 == lb[i]) {
            countLines1++;
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    visited[i][j] = 1;
                    qr[i][j] = 1;
                    setBlack(n, i, j);
                }
            }
        }

    }

    if (db[0] < 0 || db[1] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
        return false;
    }

    // for (int i = 0; i < n; i++) {
    //     if ((n - countCols1) / 2 == lb[i] && lt[i] == (n - countCols1) - 1) {
    //         int temp = -1;
    //         for (int j = 0; j < n; j++) {
    //             if (qr[i][j] == 1) {
    //                 temp = j;
    //                 break;
    //             }
    //         }
    //         if (temp == -1)
    //             break;
    //         if (temp % 2 == 0) {
    //             for (int k = 0; k < n; k++) {
    //                 if (k % 2 == 0) {
    //                     if (visited[i][k] == 0) {
    //                         qr[i][k] = 1;
    //                         visited[i][k] = 1;
    //                         setBlack(n, i, k);
    //                     }
    //                 } else {
    //                     visited[i][k] = -1;
    //                 }
    //             }
    //         }
    //         if (temp % 2 != 0) {
    //             for (int k = 0; k < n; k++) {
    //                 if (k % 2 != 0) {
    //                     qr[i][k] = 1;
    //                     visited[i][k] = 1;
    //                     setBlack(n, i, k);
    //                 }
    //             }
    //         }
    //     }

    // }


    // for (int i = 0; i < n; i++) {
    //     int count = 0;
    //     for (int j = 0; j < n; j++) {
    //         if (visited[i][j] == 0) {
    //             count++;
    //         }
    //     }
    //     if (lt[i] == count / 2) {
    //         int aux = 0;
    //         for (int k = 0; k < n; k++) {
    //             if (aux == 0 && visited[i][k] != 0){
    //                 if (qr[i][k] == 0) {
    //                     aux = -1;
    //                 } else {
    //                     aux = 1;
    //                 }
    //             }
    //             if (aux == 1) {
    //                 aux = -1;
    //                 if (visited[i][k] == 0) {
    //                     qr[i][k] = 1;
    //                     visited[i][k] = 1;
    //                 }
    //             } else if (aux = -1) {
    //                 aux = 1;
    //                 if (visited[i][k] == 0) {
    //                     visited[i][k] = -1;
    //                 }

    //             }
    //         }

    //         if (lt[i] != 0) {
    //             int x;
    //         }
    //     }
    // }

    return true;
}

bool defect (int dim) {

    if (db[0] > dim || db[1] > dim || qb[0] > aux1 || qb[1] > aux2 || qb[2] > aux3 || qb[3] > aux4){
        return true;
    }

    for (int i = 0; i < dim; i++) {
        if (lb[i] > dim || cb[i] > dim || lt[i] > dim - 1 || ct[i] > dim - 1) {
            return true;
        }
    }

    int total1 = 0;
    int total2 = 0;
    int total3 = 0;
    int total4 = 0;
    
    for (int i = 0; i < dim; i++){
        if(i < tam){
            total1 += lb[i];
            total3 += cb[i];
        }else{
            total2 += lb[i];
            total4 += cb[i];
        }   
    }
    if (qb[0] + qb[1] != total1 || qb[2] + qb[3] != total2 || qb[1] + qb[2] != total3 || qb[0] + qb[3] != total4){
        return true;
    }
    

    // if (db[0] == dim || db[1] == dim) {
    //     for (int i = 0; i < dim; i++) {
    //         if (lb[i] == 0 || cb[i] == 0) {
    //             return false;
    //         }
    //     }
    // }


    return false;

}

void func(int n) {
    countqrs = 0;
    int aux = 0;
    memset(qr, 0, sizeof(qr));
    memset(visited, 0, sizeof(visited));
    memset(saved, 0, sizeof(saved));

    if (n % 2 == 0) {
        tam = (n / 2); tam2 = (n / 2);
    } else {
        tam = (n / 2); tam2 = (n / 2) + 1;
    }

    aux1 = tam * tam2;
    aux2 = tam * tam; 
    aux3 = tam * tam2; 
    aux4 = tam2 * tam2;

    // clock_t tStart = clock();
    if (defect(n) || !pre_proc(n)) {
        cout << "DEFECT: No QR Code generated!" << endl;
        return;
    }

    int aux2 = 0, aux3 = 0;

    for (int i = 0; i < n; i++) {
        if (lb[i] != 0 || cb[i] != 0 || db[0] != 0 || db[1] != 0 || qb[0] != 0 || qb[1] != 0 || qb[2] != 0 || qb[3] != 0) {
            aux = 1;
        }
        if (lb[i] < 0 || cb[i] < 0 || db[0] < 0 || db[1] < 0 ||  qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
            cout << "DEFECT: No QR Code generated!" << endl;
            return;
        }
        if (aux == 1)
            break;
    }

    // printf("Time PRE_PROC: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    // clock_t tStart2 = clock();

    if (aux == 1)
        rec(n, 0, 0);
    else {
        memcpy(saved, qr, 30 * 30 * sizeof(int));
        countqrs++;
    }
    
    if (countqrs == 1 || aux == 0) {
        cout << "VALID: 1 QR Code generated!" << endl;
        printQrCode(n);
    } else if (countqrs == 0 ) {
        cout << "DEFECT: No QR Code generated!" << endl;
    } else if (countqrs > 1) {
        cout << "INVALID: " << countqrs << " QR Codes generated!" << endl;
    }

    // printf("Time taken: %.10fs\n", (double)(clock() - tStart2)/CLOCKS_PER_SEC);

}



int main() {
    
    //clock_t tStart = clock();

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