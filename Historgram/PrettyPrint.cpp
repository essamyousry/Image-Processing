#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char *argv[])
{
    int vars[4], row, col, min, max;
    int x[2];
    ifstream myfile;
    myfile.open(argv[1]);
    
    for(int i = 0; i < 4; i++)
        myfile >> vars[i];
    
    cout << endl;
    
    row = vars[0];
    col = vars[1];
    min = vars[2];
    max = vars[3];

    cout << row << endl;
    cout << col << endl;
    cout << min << endl;
    cout << max << endl;
    
    ofstream myfile2;
    myfile2.open(argv[2]);
    
    myfile2 << row;
    myfile2 << ' ';
    myfile2 << col;
    myfile2 << ' ';
    myfile2 << "0 1";
    myfile2 << endl;
    
    int **data = new int*[row];
    for (int i = 0; i < row; ++i)
        data[i] = new int [col];
    
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            myfile >> data[i][j];
            
            if (data[i][j] > 0){
                myfile2 << data[i][j];
                myfile2 << ' ';
            }
            else {
                myfile2 << ' ';
                myfile2 << ' ';
            }
        }
        myfile2 << endl;
    }
    
    for (int i = 0; i < row; i++){
        delete data[i];
    }
    delete[] data;
    
    myfile.close();
    myfile2.close();
    
    return 0;
}
