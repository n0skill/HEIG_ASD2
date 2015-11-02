/*
 * File:   GraphUsingAdjacencyMatrix.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 19. septembre 2014, 04:51
 */

#ifndef GRAPHUSINGADJACENCYMATRIX_CPP
#define	GRAPHUSINGADJACENCYMATRIX_CPP

#include <iostream>
#include <list>
#include <vector>

class DIGraphUsingAdjacencyMatrix {
public:
    typedef std::list<int> Iterable;
    
    DIGraphUsingAdjacencyMatrix(std::istream& s) {
        int V, E, v, w;
        
        s >> V;
        s >> E;
        
        Init(V);
        
        for (int i = 0; i < E; ++i) {
            s >> v;
            s >> w;
            addEdge(v, w);
        }
    }
    
    DIGraphUsingAdjacencyMatrix(int V) {
        Init(V);
    }
    
    // ajoute une arête
    //throws std::out_of_range
    void addEdge(int v, int w) {
        adjMatrix.at(v).at(w) = true;
    }
    
    // voisins du sommet v
    //throws std::out_of_range
    Iterable adjacent(int v) const {
        std::list<int> adj;
        for (int w = 0; w < V(); w++)
            if (adjMatrix.at(v)[w]) adj.push_back(w);
        return adj;
    }
    
    // ordre du graphe
    int V() const {
        return (int) adjMatrix.size();
    }
    
    // recuperation de la matrice d'adjacence
    std::vector<std::vector<bool> > getAdjMatrix() const {
        return adjMatrix;
    }
    
private:
    DIGraphUsingAdjacencyMatrix(const DIGraphUsingAdjacencyMatrix& G) {}; // constructeurs non autorises
    DIGraphUsingAdjacencyMatrix();
    
    void Init(int V) {
        adjMatrix.resize(V);
        for (int v = 0; v < V; v++)
            adjMatrix[v].resize(V);
    }
    
    std::vector<std::vector<bool> > adjMatrix;
};

#endif	/* GRAPHUSINGADJACENCYMATRIX_CPP */






