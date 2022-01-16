#include <bits/stdc++.h>
#include "vector.h"
#include "mergesort.h"


class edge {
public:
	int u, v, d;  // d is the distance of vertex u and vertex v
	edge() : u(0), v(0), d(0) {};
	edge(int u, int v, int d) : u(u), v(v), d(d) {};
	inline bool operator<(const edge &rhs) { return this->d < rhs.d; }
};


int main() {
	int K, N, M;
	char buf[BUFSIZ];  // string buffer
	mystl::vector<int> obstacles(26);  // obstacles cost
	
	std::cout << "Please enter input file name: ";
	std::cin >> buf;
	std::ifstream ifs(buf, std::ios::in);  // create input file stream
	
	// enter obstacles cost
	ifs >> K;
	for(int i = 0; i < K; i++) {
		char c;
		int cost;
		ifs >> c >> cost;
		obstacles[c-'A'] = cost;
	}
	
	// build edge and adjacency list
	ifs >> N >> M;
	mystl::vector<edge> edges(M);
	mystl::vector<int> adj[N];
	for(int i = 0; i < M; i++) {
		char c;
		int u, v, x;
		ifs >> u >> v;
		u--, v--;
		edges[i].u = u;
		edges[i].v = v;
		ifs.getline(buf, BUFSIZ);
		std::stringstream ss(buf);
		while(ss >> c >> x) edges[i].d += obstacles[c-'A']*x;  // sum up obstacles cost
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	// sort edges by distance
	mystl::mergesort(edges.begin(), edges.end());
	
	// init disjoint set
	mystl::vector<int> p(N);
	for(int i = 0; i < N; i++) p[i] = i;
	
	// track parent util root on the disjoint set
	std::function<int(int)> find = [&p, &find](int x) {
		return p[x] = (p[x] == x ? x : find(p[x]));
	};
	
	// kruskal algorithm
	int cnt = 0, sum = 0;  // count and sum of the added edges
	for(auto &edge : edges) {
		auto &[u, v, d] = edge;
		if(find(u) == find(v)) continue;  // two vertex is in the same set, skip this edge
		p[find(u)] = find(v);  // union two set
		sum += d;
		if(++cnt == N-1) break;  // break if threre are already n-1 edges been added
	}
	std::cout << sum << std::endl;
	
	// // print adjacency list
	// for(int i = 0; i < N; i++) {
	// 	mystl::mergesort(adj[i].begin(), adj[i].end());
	// 	std::cout << i+1 << ": ";
	// 	for(auto j : adj[i]) std::cout << j+1 << " ";
	// 	std::cout << std::endl;
	// }
	
	
	return 0;
}