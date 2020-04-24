#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int n, m;

int main(int argc, char *argv[]) {
    int i, j, **pb;

    // Διαστάσεις του πίνακα
    scanf("%d", &n);
    scanf("%d", &m);

    // Δέσμευση μνήμης
    pb = malloc(n*sizeof(int *));
    if (pb == NULL) return -1;

    for (i=0 ; i<n ; i++) {
        pb[i] = malloc(m*sizeof(int));
        if (pb[i] == NULL) return -1;
    }

    // Πέρασμα τιμών στον πίνακα
    for (i=0 ; i<n ; i++) {
	    for(j=0 ; j<m ; j++) {
	    scanf("%d", &pb[i][j]);
	    }
    }

    // Κάλεσμα της solve
    solve(n, m, pb);

    // Αποδέσμευση μνήμης
    for (i=0 ; i<n ; i++) {
        free(*(pb+i));
    }
    free(pb);

    return 0;
}
