// find Vertex Cover of a given undirected graph
#include<iostream>
#include <vector>
using namespace std;
 
class Graph
{
    int V; 
    vector<int> *adj;
    public:
        Graph(int V)
        {
            this->V = V;
            adj = new vector<int>[V];
        }
        void addEdge(int v, int w)
        {
            adj[v].push_back(w); 
            adj[w].push_back(v);
        }
        void printVertexCover(); 
};

void Graph::printVertexCover()
{
    bool visited[V];
    for (int i=0; i<V; i++)
        visited[i] = false;
 
    vector<int>::iterator i;
    for (int u=0; u<V; u++)
    {
        if (visited[u] == false)
        {
            for (i= adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if (visited[v] == false)
                {
                     visited[v] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }
    for (int i=0; i<V; i++)
        if (visited[i])
          cout << i << " ";
}
 
int main()
{
    int v;
    cout<<"Enter the number of vertices : ";
    cin>>v;
    int e;
    cout<<"Enter the number of edges : ";
    cin>>e;

    Graph g(v);
    for(int i=1;i<=e;i++)
    {
        int x,y;
        cout<<"Enter edge "<<i<<" u and v : ";
        cin>>x>>y;
        g.addEdge(x,y);
    }
    //[(0,1),(0,2),(1,3),(3,4),(4,5),(5,6)]
 
    g.printVertexCover();
    cout<<endl;
 
    return 0;
}