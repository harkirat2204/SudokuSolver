//
//  main.cpp
//  sudoku
//
//  Created by Harkirat Singh on 3/3/21.
//  Copyright © 2021 Harkirat Singh. All rights reserved.
//

#include <iostream>
#include <iomanip>  // std::setw
const int OUT_WIDTH = 2;
   // output that the position is empty
   const char OUT_BLANK = ' ';
   // should be as long as WIDTH + 1
   const std::string OUT_ROOF = "---";
   // output a wall around the number
   const char OUT_WALL = '|';
   // corner of a number
   const char OUT_CORNER = '+';
void printHorizontalLine(int n, std::ostream& out) {
   out << OUT_CORNER;
   for (int i = 0; i < n; i++)  {
      out << OUT_ROOF << OUT_CORNER;
   }
   out << std::endl;
}

// pretty printing
void printGrid(std::ostream& out,int** a)  {
   // print a top line
   printHorizontalLine(4, out);
   for (int i = 0; i < 4; i++) {
      out << OUT_WALL;
      for (int j = 0; j < 4; j++) {
         if (a[i][j]==0 ) {
            out << std::setw(OUT_WIDTH) <<OUT_BLANK;
         }
         else {
             out << std::setw(OUT_WIDTH) << a[i][j];
         }
         out << OUT_BLANK << OUT_WALL;
      } // for j
      out << std::endl;
      printHorizontalLine(4, out);
   } // for i
   out << std::endl;
}
bool isValid(int**a,int row, int column,int value){
    for(int i = 0; i < 4 ; i++){
//         std::cout<<"ISVALID UPPER LOOP  "<< a[i][column]<< std::endl;
        if(a[i][column]==value)
            return false;
    }
    
    for(int i = 0; i < 4 ; i++){
//          std::cout<<"ISVALID Lower LOOP  "<< a[row][i]<< std::endl;
        if(a[row][i]==value)
            return false;
    }
    int rowSubSq = (row/2)*2;
    int colSubSq = (column/2)*2;
    
//    std::cout << row <<" row " << column << " column " << rowSubSq << " rowSubSq "<< colSubSq<<" colSubSq"<<std::endl;
    for(int i = rowSubSq; i < rowSubSq + 2;i++){
        for (int j = colSubSq; j < colSubSq + 2; j++){
            if(a[i][j]==value)
                return false;
        }
    }
    return true;
}
int solve(int ** a,bool** b,int row, int column,int cc){
    if(row==4 && column == 3){
        printGrid(std::cout,a);
            std::cout<< cc << std::endl;
        return cc;
    }
    
    else if(row==4){
         solve(a,b,0,++column,cc);
    }
    else if(!b[row][column]){
       solve(a,b,row+1,column,cc);
    }
    else{
        for(int i = 1; i <=4;i++){
            if(isValid(a,row,column,i)){//&&b[row][column]){
                a[row][column]=i;
//                 printGrid(std::cout,a);
                solve(a,b,row+1,column,++cc);
                a[row][column]=0;
            }
            
            
        }
    }
    return cc;
    
}
int main(int argc, const char * argv[]) {
    int**a = new int *[4];
    for (int i = 0; i < 4;i++){
        a[i] = new int[4];
    }
    
    for(int i = 0; i < 4 ; i++){
        for (int j = 0; j < 4; j++)
            a[i][j]=0;
    }
    
    bool**b = new bool *[4];
    for (int i = 0; i < 4;i++){
        b[i] = new bool[4];
    }
    
    
    for(int i = 0; i < 4 ; i++){
        for (int j = 0; j < 4; j++)
            b[i][j]=true;
    }
    
    
    a[0][1]=4;
     a[1][1]=1;
    a[2][2] = 2;
     a[3][2] = 1;
    
    b[0][1]=false;
     b[1][1]=false;
    b[2][2] = false;
     b[3][2] = false;
    printGrid(std::cout,a);
    int cc = solve(a,b,0,0,0);
   // cc = a
//
    std::cout<< cc << std::endl;
}

//00 01 02 03
//10 11 12 13
//20 21 22 23
//30 31 32 33
