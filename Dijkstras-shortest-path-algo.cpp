#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/// One of the constraint of Dijkstra's algorithm is that the graph must only
/// contain non-negative edge weights. This constraint is imposed to ensure that
/// once the node has been visited its optimal distance cannot be improved.

/// This property enables Dijkstra's algorithm to act in a greedy manner by
/// always selecting the next most promising node.

namespace dijkstra
{
    struct node
    {
        node(int dst, int weight);
        int dst;
        int weight;
    };

    struct recursive_tag{};
    struct non_recursive_tag{};

    node::node(int dst, int weight) : dst(dst), weight(weight){}

    //template <typename RandomIt>
//    void make_heap( RandomIt first, RandomIt last )
//    {
//        const std::iterator_traits<RandomIt>::difference_type  len = last - first;
//        std::iterator_traits<RandomIt>::difference_type parent =
//        std::for_each( first, last, [&] ( std::iterator_traits<RandomIt>::value_type v ) {
//           insert(v);
//        });
//    }

    template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class priority_queue
    {
    public:
        priority_queue();
        priority_queue(Compare & c);
        ~priority_queue();

        typename Container::const_reference top();
        bool empty() const;
        size_t size() const;
        void push(const typename Container::value_type & value);
        void pop();

    protected:
        Container c;
        Compare   comp;
    };

    template<typename T, typename Container, typename Compare>
    priority_queue<T, Container, Compare>::priority_queue() {
    }

    template<typename T, typename Container, typename Compare>
    priority_queue<T, Container, Compare>::priority_queue(Compare & c) : c(c) {
    }

    template <typename T, typename Container, typename Compare>
    typename Container::const_reference priority_queue<T,Container,Compare>::top() {
        return c.front();
    }

    template <typename T, typename Container, typename Compare>
    bool priority_queue<T,Container,Compare>::empty() const {
        return c.empty();
    }

    template <typename T, typename Container, typename Compare>
    void priority_queue<T,Container,Compare>::push(const typename Container::value_type &value) {
        c.push_back(value);
        std::push_heap(c.begin(),c.end(), comp);
    }

    template <typename T, typename Container, typename Compare>
    void priority_queue<T,Container,Compare>::pop()
    {
        std::pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    template<typename T, typename Container, typename Compare>
    priority_queue<T, Container, Compare>::~priority_queue() {

    }

    template <class T>
    class graph
    {
    public:
        graph(size_t);
        void add_edge(const int src, const int dst, const int weight );
        std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<T>>>> adj;
    };

    template<class  T>
    graph<T>::graph( size_t size)
    {
        adj.resize( size );
        std::for_each(adj.begin(), adj.end(), [] (boost::shared_ptr<std::vector<boost::shared_ptr<T>>> & v ) {
            v = boost::make_shared<std::vector<boost::shared_ptr<T>>>();
        });
    }

    template <class T>
    void graph<T>::add_edge(const int src, const int dst, const int weight) {
        adj[src]->push_back(boost::make_shared<T>(dst, weight));
    }

    class comp {
    public:
            bool operator() ( const std::pair<int,int> & l, const std::pair<int,int> & r) const { return l.second > r.second; };
    };


    class dijkstra
    {
    public:
        dijkstra(size_t size);

        template <typename T>
        void run( graph<node> & g, int start, typename std::enable_if<std::is_same<T,recursive_tag>::value, void>::type * p = 0 );

        template <typename T>
        void run( graph<node> & g, int start, typename std::enable_if<std::is_same<T,non_recursive_tag>::value, void>::type * p = 0 );
        void shortest_distance( graph<node> & g, int parent );

        priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, comp> pq;
        std::vector<int>  dist;
        std::vector<bool>  visited;
        std::vector<int> prev;
    };

    dijkstra::dijkstra( size_t  size )
    {
        dist.resize(size, std::numeric_limits<int>::max());
        visited.resize(size, false);
        prev.resize(size, std::numeric_limits<int>::max());
    }

    void dijkstra::shortest_distance( graph<node> & g, int parent )
    {
        std::for_each( g.adj[parent]->begin(), g.adj[parent]->end(), [&] (boost::shared_ptr<node> n) {
            if ( n->weight + dist[parent] < dist[n->dst] ) dist[n->dst] = n->weight + dist[parent];
            pq.push(std::make_pair(n->dst, dist[n->dst]));
        } );
        pq.pop();
        if ( !pq.empty() )
        {
            if (pq.top().second < dist[pq.top().first]) dist[pq.top().first] = pq.top().second;
            shortest_distance(g, pq.top().first);
        }
        return;
    }

    template <class T>
    void dijkstra::run( graph<node> & g, int start, typename std::enable_if<std::is_same<T,recursive_tag>::value, void>::type * p)
    {
        dist[start] = 0;
        /// Push nodes into the priority queue
        pq.push(std::make_pair(start, 0));
        shortest_distance(g, start );

        std::for_each(dist.begin(), dist.end(), [](const int distance )
        {
            std::cout <<  distance << " ";
        });
        std::cout << std::endl;
    }

    template <class T>
    void dijkstra::run( graph<node> & g, int start, typename std::enable_if<std::is_same<T,non_recursive_tag>::value, void>::type * p)
    {
        dist[start] = 0;
        pq.push(std::make_pair( start, 0));
        int new_dist = 0;
        while ( !pq.empty() )
        {
            std::pair<int, int>  p = pq.top();
            pq.pop();
            if (dist[p.first] < p.second) continue;
            visited[p.first] = true;
            std::for_each(g.adj[p.first]->begin(), g.adj[p.first]->end(), [&] (boost::shared_ptr<node> n) {
                if ( visited[n->dst] == true ) return;
                new_dist = dist[p.first] + n->weight;
                if (new_dist < dist[n->dst]) {
                    prev[n->dst] = p.first;
                    dist[n->dst] = new_dist;
                    pq.push(std::make_pair(n->dst, new_dist));
                }
            } );
        }
        std::for_each(dist.begin(), dist.end(), [](const int distance )
        {
            std::cout <<  distance << " ";
        });
        std::cout << std::endl;

        std::for_each(prev.begin(), prev.end(), [](const int parent )
        {
            std::cout <<  parent << " ";
        });
        std::cout << std::endl;
    }

//    int main( int argc, char * argv[])
//    {
//        dijkstra::graph<dijkstra::node> g(5);
//        dijkstra::dijkstra dj(5);
//        g.add_edge(0, 1, 4);
//        g.add_edge(0, 2, 1);
//        g.add_edge(2, 1, 2);
//        g.add_edge(1, 3, 1);
//        g.add_edge(2, 3, 5);
//        g.add_edge(3, 4, 3);
//
//        dj.run<dijkstra::non_recursive_tag>(g, 0);
//    }
}


