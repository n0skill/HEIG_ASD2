/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */
#include "ParcoursEnProfondeur.h"
#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

template<typename GraphType>
class DirectedCycle {
    private:
        const GraphType&  g;
        std::list<int>    cyclelist; // Liste des elements étant dans un cycle
        std::vector<bool> stack;
        std::vector<bool> visit;
        bool hasCycle =   false;

        // Function definitions
        void detectionCycle(const GraphType& g, int v)
        {
            stack.at(v) = true;
            visit.at(v) = true;

            for(int j : g.adjacent(v))
            {
                if(hasCycle == true)
                {
                    return;
                }
                else if(!visit.at(j))
                {
                    detectionCycle(g, j);
                }
                else if(stack.at(j))
                {
                    hasCycle = true;
                }
            }
            stack.at(v) = false;
        }
    public:
        //constructeur
        DirectedCycle(const GraphType& G) : g(G) {
            /* A IMPLEMENTER */
            stack.resize(g.V());
            visit.resize(g.V());
            for(int i = 0; i < g.V(); i++)
            {
                if(visit.at(i) && Cycle().empty())
                {
                    detectionCycle(g, i);
                }
            }
        }

        //indique la presence d'un cycle
        bool HasCycle() {
            return hasCycle;
        }

        //liste les indexes des sommets formant une boucle
        std::list<int> Cycle() {
            std::list<int> cyclelist;
            if(hasCycle)
            {
                for(int i = 0; i < visit.size(); i++)
                {
                    if(visit.at(i))
                    {
                        cyclelist.push_back(i);
                    }
                }
            }
            return cyclelist;
        }
};

#endif
