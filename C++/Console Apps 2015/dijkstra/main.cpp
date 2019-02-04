#include <iostream>
#include <cstring>
#include <vector>
#include <queue>


using namespace std;


const int MAX = 1024;       // Max number of nodes in the graph, nodes are numered from 1 to n.
const int INF = 0x3f3f3f3f; // Maximum possible shortest path length - it's a 2 to the power 20.


typedef pair < int, int > pii;  // Pair object for graph is assumed to be < node, weight >.


vector < pii > graph[ MAX ];
int path[ MAX ];   // path[] array holds the shortest path from the source.


void dijkstra( int start )
{
    // We use the default comparator class greater<T> defined in queue.h
    priority_queue < pii, vector < pii >, greater < pii > > Queue;


    memset( path, 0x3f, sizeof( path ) );   // Reset the distance array and set INF as initial value.

    Queue.push( pii( 0, start ) );          // We push (0, start) in the priority queue

    path[ start ] = 0;                      // Start node has 0 weight


    // As long as queue is not empty, check each adjacent node of u
    int u, v, c, w;
    while( !Queue.empty() )
    {
        u = Queue.top().second; // node
        c = Queue.top().first;  // node cost so far
        Queue.pop();            // remove the top item.

        /*
        We have discarded the visit array as we do not need it.
        If d[u] has already a better value than the currently
        popped node from queue, discard the operation on this node.
        */

        if( path[ u ] < c ) continue;


        for( unsigned i = 0; i < graph[ u ].size(); i++ )
        {
            v = graph[ u ][ i ].first;  // node
            w = graph[ u ][ i ].second; // edge weight


            // Relax only if it improves the already computed shortest path weight.
            if( path[ v ] > path[ u ] + w)
            {
                path[ v ] = path[ u ] + w;
                Queue.push( pii( path[ v ], v ) );
            }
        }

    }
}

int main()
{
    int nodes, edges;
    cout << "Dijkstra's algorithm - algorithm for finding the shortest paths\n\n";
    cout << "Write how many nodes: "; cin >> nodes;
    cout << "Write how many edges: "; cin >> edges;


    // Reset the graph
    for( int i = 1; i <= nodes; i++ )
    {
        graph[ i ].clear();
    }


    cout << "\nWrite all the edges. From u to v with cost w\n";
    int u, v, w;
    for( int i = 0; i < edges; i++)
    {
        cin >> u >> v >> w;
        graph[ u ].push_back( pii( v, w ) );
        graph[ v ].push_back( pii( u, w ) ); // Only if bi-directional
    }


    int from, to;
    cout << "\nWrite destination\n";
    cout << "From  ";   cin >> from;
    cout << "To    ";   cin >> to;
    cout << endl;


    dijkstra( from );   // For a start node call dijkstra.


    cout << "Shortest path from node " << from << " to node " << to << " is ";
    if( path[ to ] >= INF )    cout << "unreachable";
    else if( from == to )   cout << '0';
    else                    cout << path[ to ];
    cout << endl;

    return 0;
}
