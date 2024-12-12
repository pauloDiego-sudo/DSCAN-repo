# DBSCAN Implementation in C

This is an optimized implementation of the DBSCAN (Density-Based Spatial Clustering of Applications with Noise) algorithm in C.

## Time Complexity Analysis

### Overall Complexity
- Best case: O(n²)
- Average case: O(n²)
- Worst case: O(n²)

where n is the number of points in the dataset (NUM_POINTS).

### Breakdown by Component

1. **Main Loop**: O(n)
   ```c
   for (int i = 0; i < NUM_POINTS; i++) {
       if (!visited[i]) {
           // ...
       }
   }
   ```

2. **Region Query**: O(n) per call
   - Calculates distance to every point in dataset
   ```c
   for (int i = 0; i < NUM_POINTS; i++) {
       double dist = euclidean_distance(...);
   }
   ```

3. **Expand Cluster**: O(n) per point
   - Uses BFS with a queue to process each point exactly once
   - Each point is visited at most once
   - Region query is performed once per point
   ```c
   while (queue_start < queue_end) {
       // Process each point once
       // Region query: O(n)
   }
   ```

### Complexity Explanation
O(n²) is achieved because:
1. Each point is processed exactly once due to the visited flag
2. For each point, we perform exactly one region query O(n)
3. The BFS queue ensures no redundant processing
4. No repeated neighbor list merging operations

### Memory Complexity
- Space complexity: O(n)
- Fixed arrays used:
  - Points array: n × 2 × sizeof(float)
  - Clusters array: n × sizeof(int)
  - Visited array: n × sizeof(bool)
  - Queue array: n × sizeof(int)
  - Temporary neighbors array: n × sizeof(int)

### Key Optimizations Made
1. Replaced recursive DFS with iterative BFS
2. Eliminated redundant neighbor searches
3. Removed neighbor list merging operations
4. Single visit per point guarantee through visited flags
5. Queue-based processing instead of recursive calls

### Implementation Benefits
1. More predictable performance
2. Better memory usage
3. No recursive call overhead
4. Maintains clustering quality while improving efficiency
5. More scalable for larger datasets

## Output Format

The program outputs:
1. Input parameters (points, eps, minPoints)
2. Cluster distribution
3. Performance metrics (wall clock time)
4. Memory usage statistics

Note: The implementation prioritizes efficiency while maintaining the core DBSCAN clustering properties.
