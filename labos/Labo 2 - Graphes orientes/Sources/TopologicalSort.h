/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"

template < typename GraphType >
class TopologicalSort {
private:
    bool isDAG;
    std::vector<int> topo_order;
	/* A DEFINIR */

public:
	//constructeur
	TopologicalSort(const GraphType& g){
        DirectedCycle<GraphType> dcGraph = DirectedCycle<GraphType>(g);
		// Si on a un cylce, on ne peut pas trier topologiquement !
        if(!dcGraph.HasCycle())
        {
            isDAG = true;
        }
        if(isDAG)
        {
            topo_order.resize(g.V());
            int indexOrder = g.V() - 1;
            GraphType graphInverted = g.reverse();
            DFS<GraphType> dfs(graphInverted);
            dfs.visitGraph(
                    [](int){},
                    [&](int i){topo_order.at(indexOrder--) = i;}
                    );
        }

}
	
	//indique si le graphe est DAG (Directed Acyclic Graph))
	bool IsDAG() {
		/* A IMPLEMENTER */
        return isDAG;
	}
	
	//tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
	const std::vector<int>& Order() {
		/* A IMPLEMENTER */
        return topo_order;
	}
};

#endif
