#include <vector>
#include <iostream>
#include <climits>

#define MAX_INT (2 << 30);

using namespace std;

struct Edge {
    int w;
    int o;
};

struct Node {
  int bestitems;
  int bestdist;
  int edgeLen;
  int items;
  vector<Edge> edges;
  bool visited;
  Node() {
    visited = false;
  }
};

Node nodes[100];
int nodeLen = 0;

vector<int> Q;

int f() {
  int best = 0;
  int bd = nodes[Q[best]].bestdist;

  for(int i = 0; i < Q.size(); ++i) {
    if(nodes[Q[i]].bestdist < bd) {
      bd = nodes[Q[i]].bestdist;
      best = i;
    }
  }
  return best;
}

void dd() {
  Q.push_back(0);
  
  while(Q.size() != 0) {
    int i = 0;//f();
    int uu = Q[i];
    Node& u = nodes[uu];
    Q.erase(begin(Q) + i);

    u.visited = true;

	for(int e = 0; e < u.edges.size(); e++) {
      int o = u.edges[e].o;
      Node& v = nodes[o];
			if(v.visited)
				continue;

			int newdist = u.edges[e].w + u.bestdist;
			int newitems = u.bestitems + v.items;

			if(newdist < v.bestdist || (newdist == v.bestdist && newitems > v.bestitems)) {
				v.bestdist = newdist;
				v.bestitems = newitems;
			}
			Q.push_back(o);
		}
  }
}

int main() {
  cin >> nodeLen;
  for(int i = 0; i < nodeLen; ++i) {
    cin >> nodes[i].items;
	nodes[i].bestitems = nodes[i].items;
    nodes[i].bestdist = INT_MAX;
  }
  nodes[0].bestdist = 0;

  int edges;
  cin >> edges;
  for(int i = 0; i < edges; ++i) {
    int n1, n2, w;
    cin >> n1 >> n2 >> w;

    n1 -= 1;
    n2 -= 1;

    Edge e;
    e.w = w;

    e.o = n2;
    nodes[n1].edges.push_back(e);

    e.o = n1;
    nodes[n2].edges.push_back(e);
  }

  dd();

  if(nodes[nodeLen - 1].bestdist == INT_MAX) {
			cout << "impossible" << endl;
	}
	else
    cout << nodes[nodeLen - 1].bestdist << " " << nodes[nodeLen - 1].bestitems << endl;
}
