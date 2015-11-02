/* 
 * File:   EdgeWeightedGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 27. octobre 2014, 16:24
 */

#ifndef __ASD2__EdgeWeightedGraph__
#define __ASD2__EdgeWeightedGraph__


#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <limits>
#include <fstream>

//  Classe regroupant toutes les parties communes de
//  Edge et Directed Edge.

template< typename T> // Type du poids, par exemple int ou double
// T doit etre comparable, et être un parametre
// valide pour std::numeric_limits
struct EdgeCommon {
public:
    // Type de donnée pour les poids.
    typedef T WeightType;
    
protected:
    // v1 et v2 sont les deux sommets de l'arc/arête
    int v1,v2;
    
    // weight en est le poids
    WeightType weight;
    
public:
    // Constructeur par défaut. Le poids est infini
    EdgeCommon() : v1(-1), v2(-1), weight(std::numeric_limits<T>::max()) { }
    
    // Constructeur spécifiant les deux sommets et le poids
    EdgeCommon(int v, int w, WeightType _weight) : v1(v), v2(w), weight(_weight) { }
    
    // renvoie la valeur du poids
    WeightType Weight() const { return weight; }
    
    // opérations de comparaison entre edges en fonction de leur poids.
    inline bool operator< (const EdgeCommon<T>& rhs) const { return weight < rhs.Weight(); }
    inline bool operator> (const EdgeCommon<T>& rhs) const {return rhs < *this;}
    inline bool operator<=(const EdgeCommon<T>& rhs) const {return !(*this > rhs);}
    inline bool operator>=(const EdgeCommon<T>& rhs) const {return !(*this < rhs);}
};


//  Classe regroupant toutes les parties communes de
//  EdgeWeightedGraph et EdgeWeightedDiGraph

template< typename T>  // type des edges, par exemple DirectedEdge<double> ou Edge<int> ou ...
// T doit définir le type T::WeightType
class EdgeWeightedGraphCommon {
public:
    // Type des arcs/arêtes.
    typedef T Edge;
    
    // Type de donnée pour les poids
    typedef typename Edge::WeightType WeightType;
    
protected:
    // Type pour une liste d'arcs/arêtes
    typedef std::list<Edge> EdgeList;
    
    // Structure de donnée pour les listes d'adjacences. Une EdgeList par sommet.
    std::vector<EdgeList> edgeAdjacencyLists;
    
public:
    
    // Constructeur par defaut.
    EdgeWeightedGraphCommon() { }
    
    // Constructeur specifiant le nombre de sommets V
    EdgeWeightedGraphCommon(int N) {
        edgeAdjacencyLists.resize(N);
    }
    
    // Renvoie le nombre de sommets V
    int V() const {
        return int(edgeAdjacencyLists.size());
    }
    
    // fonction a definir par les classes filles. Rend cette class abstraite
    virtual void addEdge(int v, int w, WeightType weight) = 0;
    
    // Parcours des arcs/arêtes adjacentes au sommet v.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraphCommon::Edge
    template<typename Func>
    void forEachAdjacentEdge(int v, Func f) const  {
        for(const Edge& e : adjacentEdges(v))
            f(e);
    }
    
    // Parcours de tous les sommets du graphe.
    // la fonction f doit prendre un seul argument de type int
    template<typename Func>
    void forEachVertex(Func f) const  {
        for(int v=0;v<V();++v)
            f(v);
    }
    
protected:
    // Renvoie une const reference a la list d'arcs/aretes
    // adjacent-es au sommet v
    const EdgeList& adjacentEdges(int v) const {
        return edgeAdjacencyLists.at(v);
    }
    
    // lecture depuis un fichier.
    void ReadFromFile(const std::string& filename) {
        std::ifstream s(filename);
        this->ReadFromStream(s);
        s.close();
    }
    
    // lecture depuis un stream. Utilise addEdge(...)
    // a definir par les classe fille
    void ReadFromStream(std::istream& s) {
        int V,E;
        
        s >> V >> E;
        
        edgeAdjacencyLists.resize(V);
        
        for (int i = 0; i < E; i++) {
            int v,w;
            WeightType weight;
            
            s >> v >> w >> weight;
            addEdge(v, w, weight);
        }
    }
};

// Classe definissant les aretes ponderes (non orientees)
// derive de la class EdgeCommon

template< typename T> // Type du poids, par exemple int ou double
// T doit etre comparable, et être un parametre
// valide pour std::numeric_limits
struct WeightedEdge : public EdgeCommon<T> {
    // defini la class mere comme BASE.
    typedef EdgeCommon<T> BASE;
    
public:
    // Constructeur par defaut. Appelle BASE() par defaut
    WeightedEdge() { }
    
    // Constructeur spécifiant les deux sommets et le poids
    WeightedEdge(int v, int w, T _weight) : BASE(v,w,_weight) { }
    
    // Renvoie un des deux sommets
    int Either() const { return this->v1; }
    
    // Renvoie l'autre sommet
    int Other(int v) const { return (v==this->v1) ? this->v2 : this->v1; }
    
    // Affiche "v1-v2 (weight)"
    friend std::ostream& operator << (std::ostream& s, const WeightedEdge<T>& e) {
        return s << e.Either() << "-" << e.Other(e.Either()) << " (" << e.Weight() << ")";
    }
};

// Classe definissant un graphe pondere non oriente.
// Elle herite de EdgeWeightedGraphCommon en
// specifiant des aretes de type Edge<T>

template< typename T> // Type du poids, par exemple int ou double
// T doit etre comparable, et être un parametre
// valide pour std::numeric_limits
class EdgeWeightedGraph : public EdgeWeightedGraphCommon<WeightedEdge<T> > {
    // defini la class mere comme BASE.
    typedef EdgeWeightedGraphCommon< WeightedEdge<T> > BASE;
    
public:
    // Type des arêtes.
    typedef typename BASE::Edge Edge;
    
    // Type de donnée pour les poids
    typedef typename BASE::WeightType WeightType;
    
    // Constructeur a partir d'un nom de fichier
    EdgeWeightedGraph(const std::string& filename) {
        this->ReadFromFile(filename);
    }
    
    // Constructeur a partie d'un stream
    EdgeWeightedGraph(std::istream& s) {
        this->ReadFromStream(s);
    }
    
    // Constructeur specifiant le nombre de sommet
    // Il faudra appeler addEdge pour ajouter les
    // aretes
    EdgeWeightedGraph(int N) : BASE(N) {
    }
    
    // Ajoute une arete de poids weight entre v et w
    // On ajoute cette arete aux listes d'adjacence des
    // deux sommets
    virtual void addEdge(int v, int w, WeightType weight) {
        this->edgeAdjacencyLists.at(v).push_back(Edge(v,w,weight));
        if(v != w) this->edgeAdjacencyLists.at(w).push_back(Edge(v,w,weight));
    }
    
    // Parcours de tous les sommets adjacents au sommet v
    // la fonction f doit prendre un seul argument de type int
    template<typename Func>
    void forEachAdjacentVertex(int v, Func f) const  {
        for(const Edge& e : this->adjacentEdges(v))
            f(e.Other(v));
    }
    
    // Parcours de toutes les arêtes du graphe.
    // la fonction f doit prendre un seul argument de type
    // EdgeWeightedGraph::Edge
    template<typename Func>
    void forEachEdge(Func f) const  {
        for(int v=0;v<this->V();++v)
            for(const Edge& e : this->adjacentEdges(v))
                if(e.Other(v) >= v)
                    f(e);
    }
    
};

#endif /* defined(__ASD2__EdgeWeightedGraph__) */
