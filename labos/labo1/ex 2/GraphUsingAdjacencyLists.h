/*
 * File:   Graph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 29. août 2014, 15:14
 */

#ifndef GRAPH_H
#define	GRAPH_H

#include <iostream>
#include <list>
#include <vector>


class GraphUsingAdjacencyLists {
public:
    typedef const std::list<int> & Iterable;
    
    GraphUsingAdjacencyLists(std::istream& stream);
    GraphUsingAdjacencyLists(int V);
    
    void addEdge(int v, int w);              // ajoute une arête
    Iterable adjacent(int v) const;          // voisins du sommet v
    int V() const;                           // ordre du graphe
    
private:
    GraphUsingAdjacencyLists(const GraphUsingAdjacencyLists& G) {}; // constructeurs non autorises
    GraphUsingAdjacencyLists();
    
    std::vector<std::list<int>> adjacencyLists;
};

#endif	/* GRAPH_H */

