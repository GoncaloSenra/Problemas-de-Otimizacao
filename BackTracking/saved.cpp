/*
    Gonçalo Senra   nº 2020213750
    Henrique Costa  nº 2020214120
*/

#include <iostream>
#include <vector>


using namespace std;

vector<int> lb, cb, lt, ct, qb, db;
vector<vector<int>> qr;
vector<vector<int>> visited;

int countqrs = 0;


void printQrCode(vector<vector<int>> saved, int dim) {
    //cout << "entrei" << endl;
    vector<vector<char>> qrCode(dim + 2, vector<char>(dim + 2, ' '));

    for (int i = 0; i < dim + 2; i++) {
        qrCode[i][0] = qrCode[i][dim + 1] = '|';
        qrCode[0][i] = qrCode[dim + 1][i] = '-';
    }
    qrCode[0][0] = qrCode[0][dim + 1] = qrCode[dim + 1][0] = qrCode[dim + 1][dim + 1] = '+';

    for (int i = 1; i <= dim; i++) {
        for (int j = 1; j <= dim; j++) {
            qrCode[i][j] = (saved[i-1][j-1] == 0) ? ' ' : '#';
        }
    }

    for (int k = 0; k < dim+2; k++) {
        for (int l = 0; l < dim+2; l++) {
            cout << qrCode[k][l];
        }
        cout << "\n";
    }
    //cout << "saiu" << endl;
}

// void printQrCode(vector<vector<int>> qr, int dim) {

//     for (int i = 0; i < dim + 2; i++) {
//         for (int j = 0; j < dim + 2; j++) {
//             if (i == 0 || i == dim +1){
//                 if (j == 0) {
//                     cout << "+";
//                 } else if (j == dim + 1) {
//                     cout << "+\n";
//                 } else {
//                     cout << "-";
//                 }
//             } else {
//                 if (j == 0) {
//                     cout << "|";
//                 } else if (j == dim +1) {
//                     cout << "|\n";
//                 } else {
//                     if (qr[i-1][j-1] == 0) {
//                         cout << " ";
//                     } else if (qr[i-1][j-1] == 1) {
//                         cout << "#";
//                     }
//                 }
//             }
//         }
//     }

// }

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
        // for (int i = 0; i < dim; i++) {
        //     if (lt[i] != 0 || ct[i] != 0) {
        //         return false;
        //     }
        // }
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


bool rec(vector<vector<int>> *saved, int dim, int i, int j) {
    
    if (i == dim) {
        i = 0;
        j++;
    }
    
    if (!isValid(dim, j, i)){
        return false;
    }


    if (j == dim) {
        *saved = qr;
        //printQrCode(saved, dim);
        countqrs++;
        return true;
    } 
    
    if (visited[j][i] == 0) {
        qr[j][i] = 1;
        visited[j][i] = 1;
        setBlack(dim, j, i);
        rec(saved, dim, i + 1, j);
        qr[j][i] = 0;
        visited[j][i] = 0;
        setWhite(dim , j, i);
        rec(saved, dim, i + 1, j);
    } else {
        //TODO: if lb == 0 passar a linha
        rec(saved, dim, i + 1, j);
    }
    
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
        if (lb[i] == n - countCols1) {
            idxLines[i] = 2;
            countLines1++;
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 0) {
                    qr[i][j] = 1;
                    setBlack(n, i, j);
                    visited[i][j] = 1;
                }
            }
        }
        if (cb[i] == n - countLines1) {
            idxCols[i] = 2;
            countCols1++;
            for (int j = 0; j < n; j++) {
                if (visited[j][i] == 0) {
                    qr[j][i] = 1;
                    setBlack(n, j, i);
                    visited[j][i] = 1;
                }
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
                    setBlack(n, i, j);
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
    // for (int i = 0; i < n; i++){
    //     if(db[0] == 0){
    //         visited[i][i] = -1;
    //         qr[i][i] = 0;
    //     }
    //     if(db[0] == n){
    //         visited[i][i] = 1;
    //         qr[i][i] = 1;
    //         setBlack(n, i, n-i-1);
    //     }
    //     if(db[1] == 0){
    //         visited[i][n-i-1] = -1;
    //         qr[i][n-i-1] = 0;
    //     }
    //     if(db[1] == n){
    //         visited[i][n-i-1] = 1;
    //         qr[i][n-i-1] = 1;
    //         setBlack(n, i, n-i-1);
    //     }

    //     if(visited[i][i] == 1){
    //         countDiagonal1++;
    //     }else if(visited[i][i] == -1){
    //         countDiagonal0++;
    //     }

    //     if(visited[i][n - i -1] == 1){
    //         countDiagonalInv1++;
    //     }else if(visited[i][n - i -1] == -1){
    //         countDiagonalInv0++;
    //     }

    //     if (n - countDiagonal0 == db[0]) {
    //         if (visited[i][i] == 0) {
    //             visited[i][i] = -1;
    //             qr[i][i] = 0;
                
    //         }
    //     }else if(countDiagonal1 == db[0]){
    //         if (visited[i][i] == 0) {
    //             visited[i][i] = 1;
    //             qr[i][i] = 1;
    //             setBlack(n, i, i);
    //         }
    //     }

    //     if (n - countDiagonalInv0 == db[0]) {
    //         if (visited[i][n - i -1] == 0) {
    //             visited[i][n -i -1] = 1;
    //             qr[i][n - i - 1] = 0;
    //         }
    //     }else if(countDiagonalInv1 == db[0]){
    //         if (visited[i][n - i - 1] == 0) {
    //             visited[i][n - i - 1] = -1;
    //             qr[i][n-i-1] = 1;
    //             setBlack(n, i, n-i-1);
    //         }
    //     }
    // }
    
    
    //NOTE:
    for (int i = 0; i < n; i++) {
        if (n - countLines0 == cb[i]) {
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
                    setBlack(n, i, j);
                }
            }
        }

    }
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


    idxLines.clear();
    idxCols.clear();
}

void func(int n) {
    countqrs = 0;
    int aux = 0;
    qr = vector<vector<int>>(n, vector<int>(n, 0));
    visited = vector<vector<int>>(n, vector<int>(n, 0));
    vector<vector<int>> saved = vector<vector<int>>(n, vector<int>(n, 0));

    pre_proc(n);

    //TODO: Se a matriz visited estiver totalmente preenchida a 1 na entrar no rec!
    int aux2 = 0, aux3 = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (visited[i][j] == 0) {
    //             aux = 1;
    //             break;
    //         }
    //     }
        
    //     if (aux == 1)
    //         break;
    // }

    for (int i = 0; i < n; i++) {
        if (lb[i] != 0 || cb[i] != 0 || db[0] != 0 || qb[0] != 0 || qb[1] != 0 || qb[2] != 0 || qb[3] != 0) {
            aux2 = 1;
        }
        if (aux2 == 1)
            break;
    }
    for (int i = 0; i < n; i++) {
        if (lb[i] != 0 || cb[i] != 0 || db[0] != 0 || qb[0] != 0 || qb[1] != 0 || qb[2] != 0 || qb[3] != 0) {
            aux2 = 1;
        }
        if (lb[i] < 0 || cb[i] < 0 || db[0] < 0 || qb[0] < 0 || qb[1] < 0 || qb[2] < 0 || qb[3] < 0) {
            aux3 = 1;
        }
        
    }

    //TODO: Se o pre_proc retornar impossivel nao entrar no rec     

    if (aux2 == 1)
        rec(&saved, n, 0, 0);
    else if (aux3 == 1)
        countqrs = 0;
    else if (aux2 == 0){
        saved = qr;
        countqrs++;
    }
    
    if (countqrs == 1) {
        cout << "VALID: 1 QR Code generated!" << endl;
        printQrCode(saved, n);
    } else if (countqrs == 0 ) {
        cout << "DEFECT: No QR Code generated!" << endl;
    } else if (countqrs > 1) {
        cout << "INVALID: " << countqrs << " QR Codes generated!" << endl;
    }

    saved.clear();
    qr.clear();
    visited.clear();


}

int main() {
    
    //clock_t tStart = clock();

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);

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