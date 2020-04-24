#include <stdio.h>

#include "functions.h"

void solve(int n, int m, int **board) {
    int i=n-1, j, ms, temp_sum;

    printf("Running maxsumrec\n");

    // Προσπέλαση της τελευταίας γραμμής
    for (j=0 ; j<m ; j++) {
        temp_sum = sum(i, j, board, m);

	if (j==0) {
	    ms = temp_sum;
	}
    // Εύρεση μεγίστου αθροίσματος
	else if (temp_sum>ms) {
            ms = temp_sum;
        }
    }

    printf("Max sum is %d\n", ms);
}
