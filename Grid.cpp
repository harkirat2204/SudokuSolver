 Student Name: Harkirat Singh

 #include <iostream>
 #include <fstream>  // for file input and output
 #include <iomanip>  // std::setw
 #include <cmath>
 //#include "Grid.h"

 // width of a number
 const int Grid::OUT_WIDTH = 2;
 // output that the position is empty
 const char Grid::OUT_BLANK = ' ';
 // should be as long as WIDTH + 1
 const std::string Grid::OUT_ROOF = "---";
 // output a wall around the number
 const char Grid::OUT_WALL = '|';
 // corner of a number
 const char Grid::OUT_CORNER = '+';

 // at first, the dimensions are 0
 Grid::Grid(){
    grid = new int *[0];
    boolGrid = new bool * [0];
    n = 0;
    assignments = 0;
    solutions = 0;
 }// returns false wherever it finds any other value than 0 else returns true
 bool Grid::isEmpty() const{
    for(int i = 0; i < n;i++){
         for(int j = 0; j< n; j++){
             if(grid[i][j]!=0)
                 return false;
         }
     }
     return true;
 }
 int Grid::numberOfSolutions() const {
    return solutions;
 }

 long Grid::workAssigns() const {
    return assignments;
 }

 int Grid::dimension() const {
    return n;
 }

 // if there was an allocated array already, deallocate it
 std::istream& operator >> (std::istream& in, Grid& G) {
   
    for(int i = 0; i < G.n; i++){
       delete [] G.grid[i];
       delete [] G.boolGrid[i]; // deallocating previous allocated array
    }
    delete [] G.grid;
    delete [] G.boolGrid;
    
    int r;
    int c;
    in >> r;
    in >> c;
     if (r!=c){ // if not square exit
         exit(0);
     }
          else{
       G.n = c;
       G.grid = new int * [G.n]; // vreating n x n grid and bool grid
       G.boolGrid = new bool *[G.n];
       for(int i = 0; i < G.n;i++){
          G.grid[i]= new int[G.n];
          G.boolGrid[i] = new bool[G.n];
       }
       for(int i = 0; i < G.n; i++){
          for(int j = 0; j<G.n;j++){ // putting 0 for all values grid and true for all boolGrid value
             G.grid[i][j] = 0;
             G.boolGrid[i][j]=true;
          }
       }
       while(in >> r){
         in >> c;
         in >> G.grid[r-1][c-1] ;
         if(G.grid[r-1][c-1]!=0)
           G.boolGrid[r-1][c-1]=false;
       }
    }
    return in;
 }

 // pretty printing
 void Grid::printHorizontalLine(int n, std::ostream& out) {
    out << OUT_CORNER;
    for (int i = 0; i < n; i++)  {
       out << OUT_ROOF << OUT_CORNER;
    }
    out << std::endl;
 }

 // pretty printing
 void Grid::printGrid(std::ostream& out) const {
    // print a top line
    printHorizontalLine(n, out);
    for (int i = 0; i < n; i++) {
       out << OUT_WALL;
       for (int j = 0; j < n; j++) {
          if ( grid[i][j]==0 ) { // grid[i][j]==0 then print blank else print the no
             out << std::setw(Grid::OUT_WIDTH) << Grid::OUT_BLANK;
          }
          else {
             out << std::setw(Grid::OUT_WIDTH) << grid[i][j];
          }
          out << OUT_BLANK << OUT_WALL;
       } // for j
       out << std::endl;
       printHorizontalLine(n, out);
    } // for i
    out << std::endl;
 }
 // overloads << so as to print the current square
 std::ostream& operator << (std::ostream& out, const Grid& g) {
    g.printGrid(out);
    return out;
 }
 // checks if the value we want at rowxcolumn is valid there or not
 bool Grid::isValid(int row, int column, int value){
    for(int i = 0; i < n ; i++){
 //         std::cout<<"ISVALID UPPER LOOP  "<< a[i][column]<< std::endl;
         if(grid[i][column]==value) // chechks the entire column for a dublicate value
             return false;
     }
    
     for(int i = 0; i < n ; i++){ // checks teh entire row for a dublicate value
 //          std::cout<<"ISVALID Lower LOOP  "<< a[row][i]<< std::endl;
         if(grid[row][i]==value)
             return false;
     }
     int sqrtN = sqrt(n); // square root of n
     int rowSubSq = (row/sqrtN)*sqrtN; // so as to find the top left small sq for the current small sq
     int colSubSq = (column/sqrtN)*sqrtN;
    
 //    std::cout << row <<" row " << column << " column " << rowSubSq << " rowSubSq "<< colSubSq<<" colSubSq"<<std::endl;
     for(int i = rowSubSq; i < rowSubSq + sqrtN;i++){
         for (int j = colSubSq; j < colSubSq +sqrtN; j++){ // checks the entire small sq for a dublicate entry
             if(grid[i][j]==value)
                return false;
         }
     }
     return true;
 }
 // calls recursive solve with row and column
 void Grid::solve(std::ostream& out) {
    solve(out,0,0);
 }
 // recursively solves the sudoko problem
 void Grid::solve(std::ostream& out,int row, int column) {
    if(row==n && column == n-1){ // solved for all the rows and columns (base case)
         out << *this;
         solutions++;
     }
    
     else if(row==n){ // if no of rows becomes n that is 1 more than what we have than start from 0 row again and add 1 to the column
          solve(out,0,column+1);
     }
     else if(!boolGrid[row][column]){ // if the cuurent idex we are at is fixed then move to the next row
        solve(out,row+1,column);
     }
     else{
         for(int i = 1; i <=n;i++){
             if(isValid(row,column,i)){ // if i is a valid placement place it and solve for next row and the same column
                 grid[row][column]=i;
                 assignments++;
 //                 printGrid(std::cout,a);
                 solve(out,row+1,column);
                 grid[row][column]=0; // undo what i that we  have placed so as to see more solutions or if this placement fails
             }
         }
     }
 }
 // copy constructor
 Grid::Grid(const Grid& other) {

     n = other.n;
     assignments = other.assignments;
     solutions = other.solutions;

     grid = new int *[n];
     boolGrid = new bool * [n];


     for(int i = 0; i < n ; i++){
         for (int j =0; j < n; j++){
             grid[i][j]=other.grid[i][j];
               boolGrid[i][j]=other.boolGrid[i][j];
         }
     }
 }
 // assignmnet operator
 Grid& Grid::operator = (const Grid& other) {
     if(this == &other)
         return *this;

     for(int i = 0; i < n; i++){
          delete [] grid[i];
          delete [] boolGrid[i];
       }
       delete [] grid;
       delete [] boolGrid;

     n = other.n;
        assignments = other.assignments;
        solutions = other.solutions;

        grid = new int *[n];
        boolGrid = new bool * [n];


        for(int i = 0; i < n ; i++){
            for (int j =0; j < n; j++){
                grid[i][j]=other.grid[i][j];
                  boolGrid[i][j]=other.boolGrid[i][j];
            }
        }

    return *this;
 }
 //destructor
 Grid::~Grid() {
  for(int i = 0; i < n; i++){
       delete [] grid[i];
       delete [] boolGrid[i];
    }
    delete [] grid;
    delete [] boolGrid;
 }
