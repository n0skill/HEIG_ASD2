/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 */


#include <stdlib.h>
#include <iostream>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 1, ex 2 (cf. donnee)
#include "Util.h"
#include "SymbolGraph.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // cours
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            } 
        }
    }
    s.close();
    
    return ok;
}

int main(int argc, const char * argv[]) {
    if(argc != 2)
    {
        cout << "Arguments invalides" << endl;
    }
    else
    {
        SymbolGraph<DiGraph> graph = SymbolGraph<DiGraph>(argv[1]);
        TopologicalSort<DiGraph> tps = TopologicalSort<DiGraph>(graph.G());
        DirectedCycle<DiGraph> directedCycle = DirectedCycle<DiGraph>(graph.G());
        // Si on a pas de cycle on peut trier !
        if(directedCycle.HasCycle() == false)
        {
            auto order = tps.Order();
            cout << "est un Directed Cycle " << endl;
            
            if(checkOrder(tps.Order(), graph, argv[1], ','))
            {
                for(auto index: order)
                {
                    cout << graph.name(index) << endl;
                }
                cout << "Verification reussie" << endl;
            }
            else
            {
                cout << argv[1] << "nest pas un DAG" << endl << endl;
                cout << "Cycle trouve:" << endl;
                for(auto index: directedCycle.Cycle())
                {
                    cout << graph.name(index);
                }
                cout << "Verification echouee" << endl;
            }
        }
    }
    /* A IMPLEMENTER */
    
    return EXIT_SUCCESS;
} 
