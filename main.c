#include <time.h>
#include <sys/time.h>  // Add this for gettimeofday
#include "dbscan.h"
#include <stdlib.h>

#define MAX_CLUSTERS 100  // Define a reasonable maximum number of clusters

// Function to get current time in seconds with microsecond precision
double get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

int main() {
    // Initialize DBSCAN parameters
    double eps = 0.008;  // Example value
    int minPoints = 10;  // Example value
    
    // Allocate arrays for clusters and visited flags
    int clusters[NUM_POINTS];
    bool visited[NUM_POINTS];
    
    // Start timing
    double start_time = get_wall_time();
    
    // Run clustering
    dbscan_fit(minPoints, eps, clusters, visited);
    
    // End timing
    double end_time = get_wall_time();
    double elapsed_time = end_time - start_time;
    
    // Print formatted results
    printf("Points: %d, eps: %.3f, MinPoints: %d\n", 
           NUM_POINTS, eps, minPoints);
    
    // Count points in each cluster
    int max_cluster = -1;
    for (int i = 0; i < NUM_POINTS; i++) {
        if (clusters[i] > max_cluster) max_cluster = clusters[i];
    }
    
    int cluster_counts[MAX_CLUSTERS] = {0};  // Initialize all elements to 0
    
    // Ensure we don't exceed array bounds
    if (max_cluster >= MAX_CLUSTERS) {
        printf("Error: Too many clusters detected. Maximum is %d\n", MAX_CLUSTERS - 1);
        return 1;
    }
    
    for (int i = 0; i < NUM_POINTS; i++) {
        if (clusters[i] >= 0) {  // Only count valid clusters
            cluster_counts[clusters[i]]++;
        }
    }
    
    // Print cluster counts
    for (int i = 0; i <= max_cluster; i++) {
        printf("Group %d: %d  |  ", i, cluster_counts[i]);
    }
    printf("\n\n");

    // Print performance metrics
    printf("Performance Metrics:\n");
    printf("-------------------\n");
    printf("Wall clock time: %.6f seconds\n", elapsed_time);
    
    // Calculate and print memory usage
    size_t points_memory = NUM_POINTS * NUM_FEATURES * sizeof(float);
    size_t clusters_memory = NUM_POINTS * sizeof(int);
    size_t visited_memory = NUM_POINTS * sizeof(bool);
    size_t neighbors_memory = NUM_POINTS * sizeof(int);
    size_t total_memory = points_memory + clusters_memory + visited_memory + neighbors_memory;
    
    printf("\nMemory Usage:\n");
    printf("-------------\n");
    printf("Points array:    %zu bytes (%.2f KB)\n", points_memory, points_memory/1024.0);
    printf("Clusters array:  %zu bytes (%.2f KB)\n", clusters_memory, clusters_memory/1024.0);
    printf("Visited array:   %zu bytes (%.2f KB)\n", visited_memory, visited_memory/1024.0);
    printf("Neighbors array: %zu bytes (%.2f KB)\n", neighbors_memory, neighbors_memory/1024.0);
    printf("Total memory:    %zu bytes (%.2f KB)\n", total_memory, total_memory/1024.0);

    return 0;
}