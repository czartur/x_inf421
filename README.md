# INF421

Given a connected and undirected graph G = (V,E), define a most pleasant itinerary between u and v as a (u --> v) path
in the graph G such that the maximum edge along this path is minimized.

Context: Graph ~ map of a city // edges ~ streets // edge weight ~ noise level of the street

Problem:

* INPUT: Graph G and a set of queries : pairs (u,v)
* OUTPUT: For each query (u,v) compute max edge in a most pleasent itinerary between u and v
