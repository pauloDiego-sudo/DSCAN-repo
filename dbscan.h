#ifndef DBSCAN_H
#define DBSCAN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "df_points_array.h"  // Include the points array header

// Function declarations
int* dbscan_fit(int minPoints, double eps, int* clusters, bool* visited);

#endif // DBSCAN_H