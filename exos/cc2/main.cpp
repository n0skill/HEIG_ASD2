/*
 * File:   main.cpp
 * Author: Fabien Dutoit
 *
 * Created on 11 sept. 2015, 14:11:23
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "DIGraphUsingAdjacencyMatrix.cpp"
#include "Warshall.cpp"


using namespace std;

void test(string filename) {
    ifstream file(filename);
    
    DIGraphUsingAdjacencyMatrix G(file);
    Warshall<DIGraphUsingAdjacencyMatrix> W(G);
    file.close();
    
    cout << filename << (W.isStronglyConnected() ? " est fortement connexe" : " n'est pas fortement connexe") << ":" << endl;
    W.display();
    cout << endl;
}

int main(int argc, char** argv) {
    
    
    string filenameTiny("tinyG.txt");
    test(filenameTiny);
    
    string filenameSmall("smallG.txt");
    test(filenameSmall);
    
    string filenameTiny2("tinyG2.txt");
    test(filenameTiny2);
    
    string filenameTiny3("tinyG3.txt");
    test(filenameTiny3);
    
    string filenameMedium("mediumG.txt");
    test(filenameMedium);
    
    return (EXIT_SUCCESS);
    
}