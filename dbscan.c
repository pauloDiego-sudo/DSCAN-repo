#include "dbscan.h"
#include <string.h>

// Helper function to calculate Euclidean distance
static double euclidean_distance(const float* p1, const float* p2) {
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
}

// Find neighbors within eps radius
static void region_query(int point_idx, double eps, 
                        int neighbors[], int* neighbor_count) {
    *neighbor_count = 0;
    
    for (int i = 0; i < NUM_POINTS; i++) {
        double dist = euclidean_distance(
            points[point_idx],
            points[i]
        );
        
        if (dist <= eps) {
            neighbors[(*neighbor_count)++] = i;
        }
    }
}

// Expand cluster from seed point - optimized version
static void expand_cluster(int point_idx, int* clusters,
                         bool* visited, double eps, 
                         int minPoints, int current_cluster) {
    // Create a queue for BFS
    int queue[NUM_POINTS];
    int queue_start = 0;
    int queue_end = 0;
    
    // Add initial point
    queue[queue_end++] = point_idx;
    clusters[point_idx] = current_cluster;
    
    // Process queue
    while (queue_start < queue_end) {
        int current_point = queue[queue_start++];
        
        // Find neighbors
        int neighbors[NUM_POINTS];
        int neighbor_count;
        region_query(current_point, eps, neighbors, &neighbor_count);
        
        // If this is a core point
        if (neighbor_count >= minPoints) {
            // Process each neighbor
            for (int i = 0; i < neighbor_count; i++) {
                int neighbor_point = neighbors[i];
                
                // If this point hasn't been assigned to a cluster
                if (clusters[neighbor_point] == -1) {
                    clusters[neighbor_point] = current_cluster;
                    
                    // If this point hasn't been visited, add it to the queue
                    if (!visited[neighbor_point]) {
                        visited[neighbor_point] = true;
                        queue[queue_end++] = neighbor_point;
                    }
                }
            }
        }
    }
}

int* dbscan_fit(int minPoints, double eps, int* clusters, bool* visited) {
    int current_cluster = 0;
    
    // Initialize arrays
    for (int i = 0; i < NUM_POINTS; i++) {
        clusters[i] = -1;
        visited[i] = false;
    }
    
    // Process each point
    for (int i = 0; i < NUM_POINTS; i++) {
        if (!visited[i]) {
            visited[i] = true;
            
            int neighbors[NUM_POINTS];
            int neighbor_count;
            region_query(i, eps, neighbors, &neighbor_count);
            
            if (neighbor_count < minPoints) {
                clusters[i] = 0;  // Mark as noise
            } else {
                current_cluster++;
                expand_cluster(i, clusters, visited, eps, 
                             minPoints, current_cluster);
            }
        }
    }
    
    return clusters;
}