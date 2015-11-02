/*
 * File:   ShortestPath.h
 * Author: Fabien Dutoit
 *
 * Created on 21. octobre 2015, 15:50
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "EdgeWeightedGraph.cpp"
#include "MinimumSpanningTree.cpp"

using namespace std;

// compare les algorithmes de Boruvska et Prim pour calculer le MST
// les vecteurs de Edges resultants sont compares

void testShortestPath(string filename, int start = 0) {
    cout << "Testing " << filename << endl;

    typedef EdgeWeightedGraph<double> Graph;
    Graph ewd(filename);
    
    //on execute les 2 algorithmes MST
    MinimumSpanningTree<Graph>::EdgeList toTest    = MinimumSpanningTree<Graph>::BoruvkaUnionFind(ewd);
    MinimumSpanningTree<Graph>::EdgeList reference = MinimumSpanningTree<Graph>::EagerPrim(ewd);

    // la solution d'un algorithme MST n'est pas forcement unique
    // on va verifier que:
    // 1. la somme des poids des edges formant le MST est identique
    // 2. qu'il y a exactement g.V() -1 edges
    // 3. que tous les sommets sont presents dans les edges
    
    //1. la somme doit etre identique, on admet toutefois une petite difference (arrondis)
    double sumReference = 0.0, sumToTest = 0.0;
    for(auto e : reference)
        sumReference += e.Weight();
    for(auto e : toTest)
        sumToTest += e.Weight();
    cout << "Poids total Boruvka:   " << sumReference << endl;
    bool ok1 = std::abs(sumReference - sumToTest) < 0.000000001;

    //2.
    bool ok2 = toTest.size() == ewd.V()-1;
    cout << "Nbr. edges Boruvka:   " << toTest.size() << endl;
    
    //3.
    vector<bool> accessibleVertex(ewd.V(), false);
    for(auto e : toTest) {
        int v = e.Either(), w = e.Other(v);
        accessibleVertex[v] = true;
        accessibleVertex[w] = true;
    }
    
    bool ok3 = true;
    for(auto a : accessibleVertex)
        ok3 &= a;
    
    if(ok1 && ok2 && ok3)   cout << " ... test succeeded " << endl << endl;
    else                    cout << " Tested algorithm produces a different result !" << endl << endl;
}

int main(int argc, const char * argv[]) {
    
    //config output for codecheck
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(4);
    
    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");

    return EXIT_SUCCESS;
    
}
