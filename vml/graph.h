#ifndef vml_graph_hpp
#define vml_graph_hpp

#include "basics.h"

#include <vector>
#include <functional>


namespace vml {

/**
 * @class Graph
 * @brief Graphen Template.
 *
 * Die Templateklasse implementiert eine einfache Graphenfuktionalität.
 * Dabei ist `N` die Knotenclasse und `E` ein Datentyp, der an einer Kante gespeichert wird.
 * Die Knoten werden in einem `std::vector` namens `nodes` gespeichert.
 * Um neue Knoten zuspeichern oder die vorhandenen Knoten zu manipulieren, kann ganz normal die API von [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) verwendet werden.
 * Die Indezes (`Key`) zwei verbundener Knoten werden in einer Kantenstruktur namens `Edge` gespeichert.
 * Dabei können optional mit `E` Daten wie eine Gewichtung an die Kante angehängt werden.
 * Diese Kanten werden in einer privaten Adjazenzliste `adjacencies` gespeichert.
 * `adjacencies` genauso viele Einträge wie `nodes`.
 * Jeder Knoten findet an seinem Index in `adjacencies` alle seine auswärtsdeutenden Kanten wieder, gespeichert als ein verpointerter `std::vector<Edge>`.
 * Die Kanten sind hier immer gerichtet. Um ungerichtete Kanten umzusetzt, können einfach zwei gerichtete Kanten erzeugt werden, die die zwei Knoten in beide Richtungen verbinden.
 * @tparam N Knotenklasse
 * @tparam E Kantendatenklasse
 */
template<class N, class E = char>
class Graph
{
public:

    /**
     * @brief Indextyp "Schlüssel"
     *
     * Den Index eines Knotens verwendets die `Graph`-Klasse, um die Referenzen zwischen Kanten und Knoten zu organisieren.
     * Sie entspricht dem [`std::size_t`-Typen](https://en.cppreference.com/w/cpp/types/size_t), welcher einem Integraltypen ohne Vorzeichen entspricht.
     */
    typedef std::size_t Key;
    
    /**
     * @brief Nonode (Kein Knoten).
     *
     * Der maximalste Index wird verwendet um keinen Knoten auszudrücken. Immer wenn ein Index zu einem nicht vorhandenen Element abgefragt wird, wird er nonode index zurückgeben, um so Fehler meldungen zu umgehen.
     * durch den static_cast von -1 auf den Key typen, welcher intern ein unsigned long ist wird automatisch die höchstmögliche Zahl genommen.
     */
    static constexpr Key nonode{ static_cast<Key>(-1) };
    
    
    /**
     * @brief Kantentyp.
     *
     * `Edge` repräsentiert eine Kante zwischen zwei Knoten. Die Knoten werden mit ihrem Index `Key` referrenziert.
     * Optional kann eine zusätzliche Information wie eine Gewichtung der Kante angehängt werden.
     * Diese wird dann durch `E` repräsentiert.
     */
    struct Edge
    {
        /**
         * @brief Elternknoten bzw. Ausgangsknoten.
         *
         * Index des Ausgangsknotens einer gerichtetenen Kante. Zur Veranschaulichung wird die Stammbaumanalogie angewendet, wodurch dieser Knoten als "Elter" bezeichnet wird.
         */
        Key parent;

        /**
         * @brief Kindknoten bzw. Zielknoten.
         *
         * Index des Zielknotens einer gerichtetenen Kante. Zur Veranschaulichung wird die Stammbaumanalogie angewendet, wodurch dieser Knoten als "Kind" bezeichnet wird.
         */
        Key child;

        /**
         * @brief Optionale Kanteninformation
         *
         * Pro Kante kann eine zusätzliche, optionale Information angegeben werden, wie eine Gewichtung. Diese wird durch `E` repräsentiert.
         */
        E data;

        /**
         * @brief Kanten Konstruktor.
         *
         * Der einzige Konstruktor, den die Kantenstruktur besitzt ist dieser. Er initialisiert alle Attribute explizit.
         * Er wird meisten nur von der Graphenklasse aufgerufen (siehe [link](@name Graph.link)) und muss nicht von außerhalb bedient werden.
         * @param _parent Index des Elternknotens
         * @param _child Index des Kindknotens
         * @param _data Optionale Kanteninfo
         */
        Edge(int _parent, int _child, const E& _data) :
        parent(_parent), child(_child), data(_data)
		{}

    };

    /**
     * @brief Knotenliste.
     *
     * Ein `std::vector`-Kontainer für Knotentypen `N`. Als öffentliches Objekt kann die Knotenliste zum einfügen neuer Knoten oder zum entfernen alter Knoten verwendet werden.
     * Achtung: Da die Kanten Indizes, verwendet um auf ihre Knoten zu verweisen, sollte die Reihenfolge der Knoten nicht verändert werden.
     */
    std::vector<N> nodes;


    /**
     * @brief Destruktor.
     *
     * Der Destruktor kümmert sich darum, dass alle verpointerten Kantenlisten in `adjacencies` gelöscht werden, um Datenlecks zu verhindern.
     */
    ~Graph()
    {
        for (std::vector<Edge>* e: adjacencies) delete e;
    }


    /**
     * @brief Verknüpft zwei Knoten mit einer Kante.
     *
     * Fügt eine Kante zu der Knotenliste hinzu, die am Index von `parent` in `adjacencies` gespeichert ist.
     *
     * @param parent Index des Elternknotens
     * @param child Index des Kindknotens
     * @param data Optionale Referenz zu einer Kanteninformation, bei keiner Angaben wir der default Konstruktor aufgerufen.
     */
    void link(Key parent, Key child, const E& data = E())
    {
        edges(parent).emplace_back(parent, child, data);
    }

    /**
     * @brief Bidirektionale Verknüpfung.
     *
     * Ruft link sowohl für die Richtung `parent->child` als auch für die Richtung `child->parent` auf.
     * Die Bezeichnung als "Eltern" oder "Kind" verliert dabei ihre Bedeutung.
     *
     * @param parent Index des Elternknotens
     * @param child Index des Kindknotens
     * @param data Optionale Referenz zu einer Kanteninformation, bei keiner Angaben wir der default Konstruktor aufgerufen.
     */
    void bilink(Key parent, Key child, const E& data = E())
    {
        link(parent, child, data);
        link(child, parent, data);
    }


    /**
     * @name edges
     * @brief Auswärtigen Kanten eines Knotens.
     *
     * Gibt einen Referenz zu den auswärtigen Kanten eines Knoten.
     * Der Pointer der entsprechenden Kantenliste wird abgefragt und als Refernz zurückgegeben.
     * Handelt es sich um einen nullptr, wir eine leere Liste als Referenz zurückgegeben.
     * @param node Index des Knotens
     */
    ///@{
    /**
     * Nicht-konstant:
     * die Adjazenzliste und Knotenlisten können syncronisiert werden.
     * Befindet sich an der gesuchten Stelle ein `nullptr` wird ein Pointer zu einer neuen Kantenliste dort gespeichert und die Refernz dazu zurückgegeben.
     */
    std::vector<Edge>& edges(Key node)
    {
        // syncronisiere die Anzahl der Einträge von adjacencies und nodes
        sync();
        // prüfe ob der Knoten noch keine auswärtigen Kanten hat
        if (!adjacencies[node])
            // erstelle eine neue leere Liste, deren Pointer in adjacencies gespeichert werden kann
            adjacencies[node] = new std::vector<Edge>();
        // now a refernce can be returned
        return *adjacencies[node];
    }
    /**
     * Konstant:
     * die Adjazenzliste und Knotenlisten können nicht syncronisiert werden, da die Klasse konstant ist.
     * Dadurch kann es sein, dass die Adjazenzliste weniger Einträge als Knotenliste hat.
     * Alle Knoten neuen Knoten werden, wie nullptr-Einträge behandelt, und es wird eine leere Liste zurück gegeben.
     * Da die leere Liste nicht in `adjacencies` gespeichert werden kann, wird eine statische Instanz einer leeren liste `empty` erstellt, welche als Refernze zurückgegeben werden kann.
     */
    const std::vector<Edge>& edges(Key node) const
    {
        // kreiere eine statische Instanz einer leeren Kantenliste
        static const std::vector<Edge> empty{};

        // prüfe ob der Key zu groß für adjacencies ist, trifft auch für nonode zu
        if (node >= adjacencies.size()) return empty;
        // prüfe ob der Knoten noch keine auswärtigen Kanten besitzt
        if (!adjacencies[node]) return empty;

        // andern falls gebe die richtige Kantenliste als konstante Referenz zurück
        return *adjacencies[node];
    }
    ///@}
    
    bool is_edge(Key parent, Key child) const
    {
        // get reference to adjacencies of parent
        const std::vector<Edge>& elist{ edges(parent) };
        // create a lambda to find child
        auto is_child
        {
            [child] (const Edge& e) { return child == e.child; }
        };
        auto found{ std::find_if(elist.begin(), elist.end(), is_child) };
        // return true if found
        return found != elist.end();
    }
    
    /**
     * @brief Kanten löschen.
     *
     * Löschen die Pointer zu den Kanten listen die in der privaten Adjazenz liste gespeichert sind
     */
    void delet_all_edges()
    {
        // delete all Edge vector in adjacency list
        for(auto evec : adjacencies) delete evec;
        adjacencies.clear();
    }


    /// children
    /// returns a vector of indices pointing towards the child nodes of given parent node
    /// @param parent idex of parent node
    /**
     * @brief Unmittelbaren Nachbarknoten (Kinder).
     *
     * Erstellt einen `std::vector` aus den Indizes der Kinderknoten von `parent`.
     *
     * @param parent Index des Elternknotens
     */
    std::vector<Key> children(Key parent) const
    {
        std::vector<Key> keys{};
        for(const Edge& e : edges(parent))
            keys.push_back(e.child);
        return keys;
    }

    // ----------------------------------------------
    // Iterieren

    /**
     * @brief Iteriere durch alle Kanten.
     *
     * Es durch die Implementierung durch eine private Adjazenzliste umständlich ist über alle Kanen zu iterieren.
     * Stattdessen kann dieser Funktion eine Lambda-Funktion übergeben werden, die für jede Kante ausgeführt werden soll.
     *
     * @param predicate Eine Lambda-Funktion, die eine Kanten Referenz als Eingang nimmt.
     */
    ///@{
    void for_edges(const std::function<void(Edge&)>& predicate)
    {
        for (std::vector<Edge>* evec : adjacencies)
            if (evec)
                for (Edge& e : *evec)
                    predicate( e );
    }
    void for_edges(const std::function<void(const Edge&)>& predicate) const
    {
        for (std::vector<Edge>* evec : adjacencies)
            if (evec)
                for (Edge& e : *evec)
                    predicate( e );
    }
    ///@}

    /**
     * @brief Iteriere durch alle Knoten.
     *
     * Die Funktion ruft die Lambda-Funktion für alle Knoten auf.
     *
     * @param predicate Eine Lambda-Funktion, die eine Kanten Referenz als Eingang nimmt.
     */
    ///@{
    void for_nodes(const std::function<void(N&)>& predicate)
    {
        for (N& nref : nodes) predicate( nref );
    }
    void for_nodes(const std::function<void(const N&)>& predicate) const
    {
        for (const N& nref : nodes) predicate( nref );
    }
    ///@}

private:
    /**
     * @brief Adjazenzliste.
     *
     * Die Kanten Beziehungen werden mit einem std::vector von verpointerten Kantenlisten repräsentiert.
     * Jeder Knoten erhält eine Kantenliste, die seine auswärtigen Kanten enthält.
     * Durch die Pointer, wird müssen bei einem Resize kaum Daten herum geschoben werden.
     * Diese Datenstruktur dient nur der Graph internen Implementierung un muss von außerhalb nicht aufgerufen werden.
     */
    std::vector< std::vector<Edge>* > adjacencies;

    /**
     * @brief Knoten und Adjazenzen syncronisieren.
     *
     * Die Funktion sorgt dafür das `adjacencies` genau so viele Einträge, wie `nodes` besitzt.
     * Dadurch hat jedes Knoten eine dazugehörige Kantenliste.
     * Die Einträge von neuen Knoten werden vorerst mit `nullptr` aufgefüllt.
     * Wird durch  die Funktion [edges](@name edges) aufgerufen.
     */
    void sync()
    {
        adjacencies.resize(nodes.size(), nullptr);
    }
};

} /* vml */

#endif /* vml_graph_hpp */
