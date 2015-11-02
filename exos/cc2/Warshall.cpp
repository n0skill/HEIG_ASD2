/*
 * File:   Warshall.cpp
 * Author: Fabien Dutoit
 * Modified by: Marc Savioz, on oct 30 2015
 * Reference: https://fr.wikipedia.org/wiki/Algorithme_de_Warshall
 * Created on 11. septembre 2015, 14:34
 */

#ifndef WARSHALL_CPP
#define WARSHALL_CPP

#include <iostream>
#include <vector>

template<typename GraphType>
class Warshall {
public:
    
    Warshall(const GraphType& G) : g(G) {
        this->warshall();
    }
    
    bool isStronglyConnected() {
        return this->stronglyConnected;
    }
    
    void display() {
        int n = g.V();
        if(n > 20) {
            std::cout << "Too big matrix, no display" << std::endl;
        } else {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    std::cout << (a[i][j] ? 1 : 0);
                }
                std::cout << std::endl;
            }
        }
    }
    
    
private:
    const GraphType& g;
    std::vector<std::vector<bool> > a = g.getAdjMatrix(); //matrice booleene d'adjacence du graphe G*
    bool stronglyConnected = true;

           void warshall() {
            std::vector<std::vector<std::vector<bool> > > m; //Liste des matrices d'adjacence
            int s = g.V();

            m.resize(s); 
            // Calcule la transitive closure avec l'algorithme de warshall
            m.at(0) = g.getAdjMatrix();

           // Calcule les matrices d'adjacence
           for(int k=0; k<s-1; ++k)
           {
               // Resize la prochaine matrice d'adjacence 
               m.at(k+1).resize(s);
               for(int i=0; i<s; ++i)
               {
                   m.at(k+1).at(i).resize(s);
                   for(int j=0; j<s; ++j)
                   {
                       // Source: http://cs.winona.edu/lin/cs440/ch08-2.pdf
                       m.at(k+1).at(i).at(j) = m.at(k).at(i).at(j) || (m.at(k).at(i).at(k) && m.at(k).at(k).at(j));
                   }
               }
           }
           a = m.at(s-1);

           // Compare la matrice d'adjacence de degré n. Si == matrice d'origine -> fortment connecté
           for(int i = 0; i < s; ++i)
           {
               for(int j=0; j < s; ++j){
                   if(stronglyConnected)
                   {
                       stronglyConnected = (m.at(s-1).at(i).at(j) == a.at(i).at(j) ? true : false);
                   }
               }
           }
        }

    
};

#endif	/* WARSHALL_CPP */

