/* 
 * File:   ShortestPath.h
 * Author: Olivier Cuisenaire
 *
 * Created on 5. novembre 2014, 10:16
 */

#ifndef ASD2_ShortestPath_h
#define ASD2_ShortestPath_h

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <functional>


// Classe parente de toutes les classes de plus court chemin.
// Defini les membres edgeTo et distanceTo commun à toutes ces
// classes, ainsi que les methodes DistanceTo, EdgeTo et PathTo
// qui permettent de les interroger.
//
// Le calcul des plus courts chemins est fait dans les constructeurs
// des classes derivees.

template<typename GraphType>   // Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// WeightEdgeedDiGraph et definir le
// type GraphType::Edge
class ShortestPath {
    public:
        // Type des arcs. Normalement ASD2::DirectedEdge<double>
        typedef typename GraphType::Edge Edge;

        // Type des poids. Normalement double ou int.
        typedef typename Edge::WeightType Weight;

        // Listes d'arcs et de poids
        typedef std::vector<Edge> Edges;
        typedef std::vector<Weight> Weights;

        // Renvoie la distance du chemin le plus court du sommet source a v
        Weight DistanceTo(int v) {
            return distanceTo.at(v);
        }

        // Renvoie le dernier arc u->v du chemin le plus court du sommet source a v
        Edge EdgeTo(int v) {
            return edgeTo.at(v);
        }

        // Renvoie la liste ordonnee des arcs constituant un chemin le plus court du
        // sommet source à v.
        Edges PathTo(int v) {
            shortestPath.


            // 
            /* A IMPLEMENTER */
        }

    protected:
        Edges edgeTo;
        Weights distanceTo;
        Edges shortestPath;
};

// Classe a mettre en oeuvre au labo 3. S'inspirer de BellmaFordSP pour l'API

template<typename GraphType>
class DijkstraSP : public ShortestPath<GraphType> {
    public:
        typedef ShortestPath<GraphType> BASE;
        typedef typename BASE::Edge Edge;
        typedef typename BASE::Weight Weight;



        // Faire un parcours selon l'algo de dijkstra
        // afin de représenter l'arbre des plus courts
        // chemins par deux tableaux (edgeTo[] & distanceTo[])
        DijkstraSP(const GraphType& g, int v)  {

            typedef std::pair<Weight, int> WeightEdge;
            std::set<WeightEdge> pq; // Queue de priorité des paires (en réalité c'est un set)
            std::vector<Edge>(g.V());
            
            // initialisation
            this->edgeTo.reserve(g.V());
            this->distanceTo.assign(g.V(),std::numeric_limits<Weight>::max());


            // Pour tout sommet dans g atteignable depuis v
            g.forEachVertex([&](int i){
                    if(i!=v)
                    {
                        this->distanceTo[i] = std::numeric_limits<Weight>::max();
                    }
                    pq.insert(std::make_pair(this->distanceTo[i], i));

            });
            this->distanceTo[v] = 0;

            // Pour tout sommet adjacent à e
            while(!pq.empty())
            {
                auto pairFromPQ = pq.begin();
                int i = pairFromPQ->second;
                pq.erase(pairFromPQ); 

                g.forEachEdge([&](const Edge& e){
                    int v = e.From(), w = e.To();
                    Weight distThruE = this->distanceTo[i] + e.Weight();

                    // Si on trouve un nouveau chemin plus court
                    if(distThruE < this->distanceTo[w])
                     {
                        pq.erase(std::make_pair(this->distanceTo[w], w));
                        this->distanceTo[w] = distThruE;
                        this->edgeTo[w] = e;
                        pq.insert(std::make_pair(this->distanceTo[w], w));
                     }
                });
            }
            /* A IMPLEMENTER */
        }
};

// Algorithme de BellmanFord.

template<typename GraphType> // Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// WeightEdgeedDiGraph et definir forEachEdge(Func),
// ainsi que le type GraphType::Edge. Ce dernier doit
// se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
// To() et Weight()

class BellmanFordSP : public ShortestPath<GraphType> {

    private:
        typedef ShortestPath<GraphType> BASE;
        typedef typename BASE::Edge Edge;
        typedef typename BASE::Weight Weight;

        // Relachement de l'arc e
        void relax(const Edge& e) {
            int v = e.From(), w = e.To();
            Weight distThruE = this->distanceTo[v]+e.Weight();

            if(this->distanceTo[w] > distThruE) {
                this->distanceTo[w] = distThruE;
                this->edgeTo[w] = e;
            }
        }

    public:

        // Constructeur a partir du graphe g et du sommet v a la source
        // des plus courts chemins
        BellmanFordSP(const GraphType& g, int v) {

            this->edgeTo.reserve(g.V());
            this->distanceTo.assign(g.V(),std::numeric_limits<Weight>::max());

            this->edgeTo[v] = Edge(v,v,0);
            this->distanceTo[v] = 0;

            for(int i=0;i<g.V();++i)
                g.forEachEdge([this](const Edge& e){
                        this->relax(e);
                        });
        }
};


/* Fera l'objet d'un exercice de programmation
// Algorithme de BellmanFord avec queue simple reprenant les sommets ayant
// ete modifies par la derniere iteration.
template<typename GraphType> // Type du graphe pondere oriente a traiter
    // GraphType doit se comporter comme un
    // WeightEdgeedDiGraph et definir forEachAdjacentEdge(int,Func),
    // ainsi que le type GraphType::Edge. Ce dernier doit
    // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
    // To() et Weight()

    class BellmanFordQueueSP : public ShortestPath<GraphType> {

    private:
    typedef ShortestPath<GraphType> BASE;
    typedef typename BASE::Edge Edge;
    typedef typename BASE::Weight Weight;

    public:
    BellmanFordQueueSP(const GraphType& g, int v) {

    }
    };
    */

#endif
