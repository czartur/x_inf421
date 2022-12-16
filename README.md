# INF421
You are given a connected and undirected graph G = (V,E) representing the map of the city.
For every edge e in E, there is a non-negative integer value ce indicating the noise level at the
edge e.
For a pair (u, v) of vertices from V , a most pleasant itinerary between u and v is a u-to-v path
in the graph G such that the maximum noise level c_e of all edges e along this path is minimized.1
You are given a set of queries, each containing a pair of vertices (u, v) from V . For each query,
you need to compute the maximum noise level on a most pleasant itinerary between u and v.
