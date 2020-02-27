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


using namespace std;

typedef struct{
    int value;
    int direction[4] = {1,1,1,1};
    int order[4] = {0,1,2,3};
    }PONT;

bool simpleBacktrack(PONT**,int,int,int);


void printMtx(PONT**,int, int, int);

bool isSide(int,int,int);

int main(int argc, const char * argv[]) {
    
    int n,x,y;
    
    ifstream input;
    input.open("input.txt");
    
    input >> n;
    
    PONT** matrix = new PONT*[n];
    
    for(int i = 0; i < n; ++i){
        matrix[i] = new PONT[n];
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            input >> matrix[i][j].value;
        }
    }
    
    /// Starting point
    input >> x;
    input >> y;
    
    auto start1 = chrono::high_resolution_clock::now();
    simpleBacktrack(matrix, n, x, y);
    auto stop1 = chrono::high_resolution_clock::now();
    chrono::duration<double> myTime1 = stop1 - start1;
    cout << "Simple Backtrack: " << myTime1.count() << endl;
    
    /// Clearing memory
    for(int i = 0; i < n; ++i){
        delete [] matrix[i];
    }
    
    delete [] matrix;
    
    
    return 0;
}

/// printMtx(matix,matrix size,current position)
void printMtx(PONT** matrix,int n, int x, int y){
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


bool simpleBacktrack(PONT** matrix,int n,int x, int y){
    
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
