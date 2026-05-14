#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int go(int row, int col)
{
	return maze[row][col] == 0 ? 1 : -1;
}

int main(void)
{
	start(0, 0);

	return 0;
}