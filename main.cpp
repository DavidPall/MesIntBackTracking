//
//  main.cpp
//  MesInt Backtracking
//
//  Created by David Pall on 25/02/2020.
//  Copyright © 2020 David Pall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <list>
#include <cstdlib>


using namespace std;

typedef struct{
    int value;
    int possibilities = 4;
    int direction[4] = {1,1,1,1};
    int order[4] = {0,1,2,3};
    }DOT;

typedef struct{
    DOT* dot;
    int direction;
}SORTABLE_DOT;

void first(DOT**,int,int,int);
void second(DOT**,int,int,int);
void third(DOT**,int,int,int);

bool simpleBacktrack(DOT**,int,int,int);
bool frwdBacktrack(DOT**,int,int,int);
bool ac3Backtrack(DOT**,int,int,int);

void myMVR(DOT**,int,int,int);

void frwdchecking(DOT**,int,int,int);

void AC3(DOT**,int);

void printMtx(DOT**,int, int, int);

bool isSide(int,int,int);

int mycmp(const void*, const void*);

int main(int argc, const char * argv[]) {
    
    int n,x,y;
    
    ifstream input;
    input.open("input.txt");
    
    input >> n;

    DOT** matrix = new DOT*[n];
    
    for(int i = 0; i < n; ++i){
        matrix[i] = new DOT[n];
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            input >> matrix[i][j].value;
        }
    }
    
    /// Starting point
    input >> x;
    input >> y;
    
    first(matrix,n,x,y);
    second(matrix,n,x,y);
    third(matrix, n, x, y);
    
    /// Clearing memory
    for(int i = 0; i < n; ++i){
        delete [] matrix[i];
    }
    
    delete [] matrix;
    
    
    return 0;
}

/// printMtx(matix,matrix size,current position)
void printMtx(DOT** matrix,int n, int x, int y){
    cout << "\n--------------------------\n";
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == x && j == y){
                cout << "|" << matrix[i][j].value << "|\t";
            } else {
                cout << matrix[i][j].value << "\t\t";
            }
        }
        cout << endl;
    }
}

void first(DOT** matrix,int n, int x, int y){
    
    auto start1 = chrono::high_resolution_clock::now();
    
    simpleBacktrack(matrix, n, x, y);
    
    auto stop1 = chrono::high_resolution_clock::now();
    chrono::duration<double> myTime1 = stop1 - start1;
    
    cout << "Simple Backtrack: " << myTime1.count() << endl;
    
}


void second(DOT** matrix,int n,int x,int y){
    
    auto start1 = chrono::high_resolution_clock::now();
    
    frwdchecking(matrix,n,x, y);
    myMVR(matrix, n, x, y);
    frwdBacktrack(matrix, n, x, y);
    
    auto stop1 = chrono::high_resolution_clock::now();
    chrono::duration<double> myTime1 = stop1 - start1;
    
    cout << "Backtrack + MVR + Forward Checking: " << myTime1.count() << endl;
}

void third(DOT** matrix,int n,int x,int y){
    
    auto start1 = chrono::high_resolution_clock::now();
    
    AC3(matrix, n);
    myMVR(matrix, n, x, y);
    ac3Backtrack(matrix, n, x, y);
    
    auto stop1 = chrono::high_resolution_clock::now();
    chrono::duration<double> myTime1 = stop1 - start1;
    
    cout << "Backtrack + MVR + AC-3: " << myTime1.count() << endl;
}

bool isSide(int n, int x, int y){
    
    if(x == 0){
        return true;
    }
    if(x == n-1){
        return true;
    }
    if(y == 0){
        return true;
    }
    if(y == n-1){
        return true;
    }
    
    return false;
}


bool simpleBacktrack(DOT** matrix,int n,int x, int y){
    
    if(isSide(n,x,y)){
        printMtx(matrix, n, x, y);
        return true;
    }
    
    for(int i = 0; i < 4; ++i){
        bool result = false;
        if(matrix[x][y].direction[matrix[x][y].order[i]]==1){
            switch(matrix[x][y].order[i]){
                case 0:
                    if(matrix[x][y].value > matrix[x-1][y].value){
                        result = simpleBacktrack(matrix,n, x-1, y);
                    }
                    break;
                case 1:
                    if(matrix[x][y].value > matrix[x][y + 1].value){
                        result = simpleBacktrack(matrix,n, x, y+1);
                    }
                    break;
                case 2:
                    if(matrix[x][y].value > matrix[x + 1][y].value){
                        result = simpleBacktrack(matrix,n,x + 1, y);
                    }
                    break;
                case 3:
                    if(matrix[x][y].value > matrix[x][y - 1].value){
                        result = simpleBacktrack(matrix,n, x, y - 1);
                    }
                    break;
            }
        }
        if(result){
            printMtx(matrix, n, x, y);
            return true;
        }
        
    }
    
    return false;
}

bool frwdBacktrack(DOT** matrix,int n,int x, int y){
    
    if(isSide(n,x,y)){
        printMtx(matrix, n, x, y);
        return true;
    }
    
    if(matrix[x][y].direction[0] == 1){
        frwdchecking(matrix,n,x - 1,y);
    }
    if(matrix[x][y].direction[1] == 1){
        frwdchecking(matrix,n,x,y + 1);
    }
    if(matrix[x][y].direction[2] == 1){
        frwdchecking(matrix,n,x + 1,y);
    }
    if(matrix[x][y].direction[3] == 1){
        frwdchecking(matrix,n,x,y - 1);
    }
    
    myMVR(matrix, n, x, y);
    
    for(int i = 0; i < 4; ++i){
        bool result = false;
        if(matrix[x][y].direction[matrix[x][y].order[i]]==1){
            switch(matrix[x][y].order[i]){
                case 0:
                    result = frwdBacktrack(matrix,n, x-1, y);
                    break;
                case 1:
                    result = frwdBacktrack(matrix,n, x, y+1);
                    break;
                case 2:
                    result = frwdBacktrack(matrix,n,x + 1, y);
                    break;
                case 3:
                    result = frwdBacktrack(matrix,n, x, y - 1);
                    break;
            }
        }
        
        if(result){
            printMtx(matrix, n, x, y);
            return true;
        }
        
    }
    
    return false;
}

bool ac3Backtrack(DOT** matrix,int n,int x, int y){
    
    if(isSide(n,x,y)){
        printMtx(matrix, n, x, y);
        return true;
    }

    myMVR(matrix, n, x, y);
    
    
    for(int i = 0; i < 4; ++i){
        bool result = false;
        if(matrix[x][y].direction[matrix[x][y].order[i]]==1){
            switch(matrix[x][y].order[i]){
                case 0:
                    result = ac3Backtrack(matrix,n, x-1, y);
                    break;
                case 1:
                    result = ac3Backtrack(matrix,n, x, y+1);
                    break;
                case 2:
                    result = ac3Backtrack(matrix,n,x + 1, y);
                    break;
                case 3:
                    result = ac3Backtrack(matrix,n, x, y - 1);
                    break;
            }
        }
        
        if(result){
            printMtx(matrix, n, x, y);
            return true;
        }
        
    }
    
    return false;
}


void myMVR(DOT** matrix,int n,int x,int y){
    
    SORTABLE_DOT neighbours[4];
    
    /// UP RIGHT DOWN LEFT
    neighbours[0].dot = &matrix[x - 1][y];
    neighbours[1].dot = &matrix[x][y + 1];
    neighbours[2].dot = &matrix[x + 1][y];
    neighbours[3].dot = &matrix[x][y - 1];
    
    
    neighbours[0].direction = 0;
    neighbours[1].direction = 1;
    neighbours[2].direction = 2;
    neighbours[3].direction = 3;
    
    qsort(neighbours,4,sizeof(SORTABLE_DOT),mycmp);
    
    for(int i = 0; i < 4; ++i){
        matrix[x][y].order[i] = neighbours[i].direction;
    }

}


int mycmp(const void* a, const void* b){
    const SORTABLE_DOT* x = (SORTABLE_DOT*)a;
    const SORTABLE_DOT* y = (SORTABLE_DOT*)b;

    if(x->dot -> possibilities > y->dot -> possibilities){
        return 1;
    }else if(x->dot -> possibilities > y->dot -> possibilities){
        return -1;
    }

     return 0;
}


void frwdchecking(DOT** matrix,int n,int x,int y){
    
    if(!isSide(n, x, y)){
        DOT* neighbours[4];
           
       neighbours[0] = &matrix[x - 1][y];
       neighbours[1] = &matrix[x][y + 1];
       neighbours[2] = &matrix[x + 1][y];
       neighbours[3] = &matrix[x][y - 1];
       
       for(int i = 0; i < 4; i++){
           if(neighbours[i]->value >= matrix[x][y].value){
               matrix[x][y].possibilities--;
               matrix[x][y].direction[i]=0;
           }
           else {
               matrix[x][y].direction[i] = 1;
           }
       }
    } else {
        matrix[x][y].possibilities = 0;
    }

}

void AC3(DOT** matrix,int n){
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            
            if(isSide(n,i,j)){
                matrix[i][j].possibilities = 0;
            } else {
                DOT* neighbours[4];
                    
                neighbours[0] = &matrix[i - 1][j];
                neighbours[1] = &matrix[i][j + 1];
                neighbours[2] = &matrix[i + 1][j];
                neighbours[3] = &matrix[i][j - 1];
                
                for(int k = 0; k < 4; k++){
                    if(neighbours[k]->value >= matrix[i][j].value){
                        matrix[i][j].possibilities--;
                        matrix[i][j].direction[k]=0;
                    }
                    else {
                        matrix[i][j].direction[k] = 1;
                    }
                }
            }
        }
    }
}
