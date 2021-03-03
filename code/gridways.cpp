#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

#define MAX 8192000
#define MIN -1638400000
#define MAX_ALLOC 81920
#define MIN_ALLOC 256

// Number of ways to travel along the grid line of a 2D uniform unit length grid (xy plane) from (s_x, s_y) to a point in the same plane (x_target, y_target)

typedef long long int LL;
typedef unsigned long long int ULL;

LL* *arr = NULL;
ULL *buffer = NULL;

LL paths_found (LL s_x, LL s_y, LL x_target, LL y_target)
{
	if (x_target < 0 || y_target < 0) return 0LL;
	
	if (s_x == x_target || s_y == y_target || (s_x == x_target && s_y == y_target)) return 1LL;
	
	if (arr[x_target][y_target] > 0) return arr[x_target][y_target];
	
	if (x_target > s_x || y_target > s_y) {
		arr[x_target][y_target] = (paths_found(s_x, s_y, x_target - 1, y_target) + paths_found(s_x, s_y, x_target, y_target - 1) + paths_found(s_x, s_y, x_target - 1, y_target - 1)) % (LONG_MAX - 1);
		return arr[x_target][y_target];
	}
}

int main(int argc, char* *argv, char* *envp) 
{
	LL T = 0, N = 0, item = 0, buff = 0;
	scanf("%lld", &T);
	
	while(T--) {
	
		LL x_target_new = 0, y_target_new = 0, s_x = 0, s_y = 0, x_target = 0, y_target = 0;
		
		scanf("%lld", &s_x);
		scanf("%lld", &s_y);
		scanf("%lld", &x_target_new);
		scanf("%lld", &y_target_new);
		
		printf("(4-way + Diagonal) Ways : (%lld,%lld) to (%lld,%lld) : ", s_x, s_y, x_target_new, y_target_new);
		
		if (s_x > 0) x_target = x_target_new - s_x;
		else x_target = x_target_new;
		
		if (s_y > 0) y_target = y_target_new - s_y;
		else y_target = y_target_new;
		
		arr = (LL **) calloc ((y_target + 1) * (x_target + 1), sizeof(LL));
		for(int i = 0; i < x_target + 1; i++) {
			arr[i] = (LL *) calloc ((y_target + 1), sizeof(LL));
		}
	
		for(int i = 0; i < (x_target + 1); ++i) arr[i][0] = 1;
		for(int i = 0; i < (y_target + 1); ++i) arr[0][i] = 1;
		
		LL num_ways = (paths_found(0LL, 0LL, x_target, y_target) % LONG_MAX);

		printf("%lld ways \n", (num_ways % LONG_MAX));
	}
	
	fprintf(stderr, "Log : Run Successfull \n");
	return 0;
}
