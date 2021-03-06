/*
A C++ program for calculating shortest distance with allowed hops on 
different airports for a plane.
*/

#include<iostream>
#include<string> // for string class
#include <limits.h>
#include <sstream> // for extracting int from space delimited string
#include <cmath> // for trignometric functions

using namespace std;

#define NUM_OF_AIRPORTS 3 // Number of airports for the question
#define RADIUS_OF_EARTH 4000 // Approximate radius of our earth
#define RADIAN_FACTOR 0.0174533 // USED TO CONVERT DEGREE TO RADIAN

/*
A utility function to find the vertex with minimum distance value, from 
the set of vertices not yet included in shortest path tree
*/
int minDistance(double dist[], bool sptSet[]){ 
    // Initialize min value 
    int min = INT_MAX, min_index; 

    for (int v = 0; v < NUM_OF_AIRPORTS; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 

    return min_index; 
}

/*
Function that implements Dijkstra's single source shortest path algorithm 
for a graph represented using adjacency matrix representation
*/
string findShortestDistWithPath(double graph[NUM_OF_AIRPORTS][NUM_OF_AIRPORTS], int src, int dest){ 
	/* The output array. dist[i] will hold the shortest 
	distance from src to i */
    double dist[NUM_OF_AIRPORTS];

    /* array of path for shortest distance */
    string path[NUM_OF_AIRPORTS];

    /* sptSet[i] will true if vertex i is included in shortest 
	path tree or shortest distance from src to i is finalized */
	bool sptSet[NUM_OF_AIRPORTS]; 

	/* Initialize all distances as INFINITE and stpSet[] as false */
	for (int i = 0; i < NUM_OF_AIRPORTS; i++) 
		dist[i] = INT_MAX, sptSet[i] = false; 

	/* Distance of source vertex from itself is always 0 */
	dist[src] = 0; 

	/* Find shortest path for all vertices */
	for (int count = 0; count < NUM_OF_AIRPORTS-1; count++){ 
        /* Pick the minimum distance vertex from the set of vertices not 
        yet processed. u is always equal to src in the first iteration. */
        int u = minDistance(dist, sptSet); 

        /* Mark the picked vertex as processed */
        sptSet[u] = true; 

        /* Update dist value of the adjacent vertices of the picked vertex. */
        for (int v = 0; v < NUM_OF_AIRPORTS; v++){
            /* Update dist[v] only if is not in sptSet, there is an edge from 
            u to v, and total weight of path from src to v through u is 
            smaller than current value of dist[v] */
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                stringstream ssU;
                ssU << u;
                path[v] = path[v] + ssU.str() + " ";
            }
        }
	}

    for (int i = 0; i < NUM_OF_AIRPORTS; i++){
        stringstream ssDist;
        ssDist << dist[i];
        path[i] = ssDist.str() + " " + path[i];
    }

	if(dist[dest] == INT_MAX)
        return "-1";
    else
        return path[dest];
} 

double distanceBetweenTwoCoordinates(int lat1, int log1, int lat2, int log2){
    return RADIUS_OF_EARTH * acos(sin(lat1*RADIAN_FACTOR) * sin(lat2*RADIAN_FACTOR) + cos(lat1*RADIAN_FACTOR) * cos(lat2*RADIAN_FACTOR) * cos((log1*RADIAN_FACTOR) - (log2*RADIAN_FACTOR)));
}

// driver program to test above function 
int main(){
    
    // Latitude and Longitude coordinates of airports.
    int latitudes[NUM_OF_AIRPORTS] = {0, 0, 70};
    int longitudes[NUM_OF_AIRPORTS] = {90, 0, 45};

    // canTravel array gives the set of airports (space delimited) that airport 'i' allowed to fly to.
    string canTravel[NUM_OF_AIRPORTS] = {"2", "0 2", "0 1"};

    /* Let us create a directed weighted graph from details above */
    double airportsGraph[NUM_OF_AIRPORTS][NUM_OF_AIRPORTS];

    /* Initialize the graph with 0 (indicating no airports are linked yet) */
    for (int i = 0; i < NUM_OF_AIRPORTS; i++)
        for (int j = 0; j < NUM_OF_AIRPORTS; j++)
            airportsGraph[i][j] = 0;

    /* Fill graph with distance at the location defined by 'canTravel' */
    for(int i = 0; i < NUM_OF_AIRPORTS; i++){
        string s = canTravel[i];
        istringstream is( s );
        int n;
        while( is >> n ) {
            airportsGraph[i][n] = distanceBetweenTwoCoordinates(latitudes[i], longitudes[i], latitudes[n], longitudes[n]);
        }
    }

    for (int i = 0; i < NUM_OF_AIRPORTS; i++){
        for (int j = 0; j < NUM_OF_AIRPORTS; j++)
            cout << airportsGraph[i][j] << "  ";
        cout << endl;
    }
    cout << endl;

    string result = findShortestDistWithPath(airportsGraph, 0, 1);
    cout << "Minimum distance : " << result;

	return 0; 
} 
