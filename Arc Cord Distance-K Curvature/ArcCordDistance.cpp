#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
using namespace std;

class point{
    
private:
    int row, col, maxVotes, corner, localMax;
    double maxDist;
    
public:
    point(int x = 0, int y = 0){
        row = x;
        col = y;
    }
    void setMaxVotes(int lmax){
        maxVotes = lmax;
    }
    void setMaxDist(double mDist){
        maxDist = mDist;
    }
    void setLocalMax(int lmax){
        localMax = lmax;
    }
    void setCorner(int corn){
        corner = corn;
    }
    
    int getCorner(){ return corner; }
    int getMaxVotes(){ return maxVotes; }
    int getLocalMax(){ return localMax; }
    double getMaxDist() { return maxDist; }
    int getRow(){ return row; }
    int getCol(){ return col; }
    
};

void storePt(int x, int y, int index, point *ptAry){
    point p = point(x, y);
    ptAry[index] = p;
}


void plotPt2Img(int **imgAry, point *ptAry, int numPts){
    int index = 0;
    while (index < numPts){
        imgAry[ptAry[index].getRow()][ptAry[index].getCol()] = ptAry[index].getCorner();
        index++;
    }
}

double computeDistance(int P1, int P2, int Pt, point *ptAry){
    
    double distance;
    
    int x = ptAry[Pt].getRow();
    int y = ptAry[Pt].getCol();
    
    int x1 = ptAry[P1].getRow();
    int y1 = ptAry[P1].getCol();
    
    int x2 = ptAry[P2].getRow();
    int y2 = ptAry[P2].getCol();
    
    int A = (y2 - y1);
    int B = (x1 - x2);
    int C = abs(x2 * y1) - abs(x1 * y2);
    int Denominator = sqrt((A * A) + (B * B));
    
    distance = abs((A * x) + (B * y) + C) / ((double)(Denominator));
    
    
    return abs(distance);
    
}

int findMaxDistance(double *chordAry, int chordLength){
    int max = 0;
    for (int i = 1; i < chordLength; i++){
        if (chordAry[i] > chordAry[max]) max = i;
    }
    return max;
}

bool computeLocalMaxima(point *ptAry, int i, int numPts){
    
    bool check = true;
    int votes = ptAry[i].getMaxVotes();
    for (int a = i - 2; a <= i + 2; a++){
        if (votes < ptAry[a % numPts].getMaxVotes()){
            check = false;
            break;
        }
    }
    if (check == true){
        ptAry[i].setLocalMax(1);
        return true;
    }
    else{
        ptAry[i].setLocalMax(0);
        return false;
    }
}

int SetCorner(point *ptAry, int i){
    
    bool check1 = false;
    if (ptAry[i].getLocalMax() == 1){
        check1 = true;
    }
    bool check2 = false;
    if ((ptAry[i + 2].getLocalMax() == 0) && (ptAry[i - 2].getLocalMax() == 0)){
        check2 = true;
    }
    
    if ((check1 == true) && (check2 == true)){
        ptAry[i].setCorner(9);
        return 9;
    }
    else {
        ptAry[i].setCorner(1);
        return 1;
    }
}

void prettyPrint(int **imgAry, int row, int col, ofstream& myfile){
    for(int x = 0; x < row; x++){
        for (int y = 0; y < col; y++){
            if (imgAry[x][y] > 0){
                myfile << (imgAry[x][y]);
                myfile << ' ';
            }
            
            else {
                myfile << ' ';
                myfile << ' ';
            }
            
        }
        myfile << endl;
    }
}

int main (int argc, char *argv[])
{
    int vars[5], row, col, min, max, label;
    int x, chordLength, P1, P2, maxIndex;
    int numPts = 0;
    
    ifstream myfile;
    myfile.open(argv[1]);
    
    for(int i = 0; i < 5; i++)
        myfile >> vars[i];
    
    cout << endl;
    
    row = vars[0];
    col = vars[1];
    min = vars[2];
    max = vars[3];
    label = vars[4];
    
    int count = 0;
    while (myfile >> x){
        ++count;
    }
    numPts = count / 2;
    myfile.close();
    
    myfile.open(argv[1]);
    
    ofstream myfile2;
    myfile2.open(argv[2]);
    ofstream myfile3;
    myfile3.open(argv[3]);
    ofstream myfile4;
    myfile4.open(argv[4]);
    
    int i = 0;
    while(i < 5){
        myfile >> x;
        i++;
    }
    point* ptAry = new point [numPts];
    
    int index = 0;
    int r;
    int c;
    while (index < numPts){
        myfile >> r;
        myfile >> c;
        storePt(r, c, index, ptAry);
        index++;
    }
    
    int K;
    cout << ("Please Enter a Value For K: ") << endl;
    cin >> K;
    
    chordLength = 2 * K;
    
    double *chordAry = new double [chordLength];
    
    P1 = 0;
    P2 = chordLength - 1;
    
    myfile4 << "P1";
    myfile4 << ' ';
    myfile4 << "x1";
    myfile4 << ' ';
    myfile4 << "y1";
    myfile4 << ' ';
    myfile4 << "P2";
    myfile4 << ' ';
    myfile4 << "x2";
    myfile4 << ' ';
    myfile4 << "y2";
    myfile4 << ' ';
    myfile4 << "CP";
    myfile4 << ' ';
    myfile4 << "x";
    myfile4 << ' ';
    myfile4 << "y";
    myfile4 << ' ';
    myfile4 << "dist";
    myfile4 << ' ';
    myfile4 << "ind";
    myfile4 << ' ';
    myfile4 << "chordAry[ind]";
    myfile4 << endl;
    myfile4 << endl;
    
    double dist;
    
    do {
        int ind = 0;
        int currPt = (P1) % numPts;
        do{
            dist = computeDistance(P1, P2, currPt, ptAry);
            chordAry[ind] = dist;
            
            int x = ptAry[currPt].getRow();
            int y = ptAry[currPt].getCol();
            
            int x1 = ptAry[P1].getRow();
            int y1 = ptAry[P1].getCol();
            
            int x2 = ptAry[P2].getRow();
            int y2 = ptAry[P2].getCol();
            
            myfile4 << P1;
            myfile4 << ' ';
            myfile4 << x1;
            myfile4 << ' ';
            myfile4 << y1;
            myfile4 << ' ';
            myfile4 << P2;
            myfile4 << ' ';
            myfile4 << x2;
            myfile4 << ' ';
            myfile4 << y2;
            myfile4 << ' ';
            myfile4 << currPt;
            myfile4 << ' ';
            myfile4 << x;
            myfile4 << ' ';
            myfile4 << y;
            myfile4 << ' ';
            myfile4 << dist;
            myfile4 << ' ';
            myfile4 << ind;
            myfile4 << ' ';
            myfile4 << chordAry[ind];
            myfile4 << endl;
            
            ind++;
            currPt = (currPt + 1) % numPts;
            
        } while (ind < chordLength);
        
        maxIndex = findMaxDistance(chordAry, chordLength);
        int whichIndex = (P1 + maxIndex) % numPts;
        ptAry[whichIndex].setMaxVotes(ptAry[whichIndex].getMaxVotes() + 1);
        if (ptAry[whichIndex].getMaxDist() < chordAry[maxIndex]){
            ptAry[whichIndex].setMaxDist(chordAry[maxIndex]);
        }
        
        P1++;
        
        if (P2 == numPts - 1){
            P2 = 0;
        }
        else P2++;
    }while (P2 != (chordLength) - 1);
    
    for (int i = 0; i < numPts; i++){
        computeLocalMaxima(ptAry, i, numPts);
    }
    
    for (int j = 0; j < numPts; j++){
        SetCorner(ptAry, j);
    }
    
    myfile4 << "-----------------------------------------";
    myfile4 << endl;
    myfile4 << "ptAry";
    myfile4 << endl;
    myfile4 << endl;
    for (int a = 0; a < numPts; a++){
        myfile4 << ptAry[a].getRow();
        myfile4 << ' ';
        myfile4 << ptAry[a].getCol();
        myfile4 << ' ';
        myfile4 << ptAry[a].getCorner();
        myfile4 << ' ';
        myfile4 << ptAry[a].getMaxDist();
        myfile4 << ' ';
        myfile4 << ptAry[a].getMaxVotes();
        myfile4 << endl;
    }
    
    myfile2 << row;
    myfile2 << ' ';
    myfile2 << col;
    myfile2 << ' ';
    myfile2 << min;
    myfile2 << ' ';
    myfile2 << max;
    myfile2 << endl;
    
    myfile2 << label;
    myfile2 << endl;
    myfile2 << numPts;
    myfile2 << endl;
    
    for (int k = 0; k < numPts; k++){
        myfile2 << ptAry[k].getRow();
        myfile2 << ' ';
        myfile2 << ptAry[k].getCol();
        myfile2 << ' ';
        myfile2 << ptAry[k].getCorner();
        myfile2 << endl;
    }
    
    int **imgAry = new int *[row];
    for (int i = 0; i < row; i++)
        imgAry[i] = new int [col];
    
    plotPt2Img(imgAry, ptAry, numPts);
    
    prettyPrint(imgAry, row, col, myfile3);
    
    for (int i = 0; i < row; i++){
        delete imgAry[i];
    }
    delete[] imgAry;
    
    delete[] ptAry;
    delete[] chordAry;
    
    myfile.close();
    myfile2.close();
    myfile3.close();
    myfile4.close();
    
    return 0;
}

