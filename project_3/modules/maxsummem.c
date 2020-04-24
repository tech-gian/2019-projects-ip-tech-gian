#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define PATH 1

void solve(int n, int m, int **board) {
    int i, j, ms, temp_sum, maxj=-1;
    int **sums;

    // Δέσμευση μνήμης για τον πίνακα των μερικών αθροισμάτων
    sums = malloc(n*sizeof(int *));
    if (sums==NULL) {
        printf("Sorry, cannot allocate memory\n");
        exit(-1);
    }

    for (i=0 ; i<n ; i++) {
        sums[i] = malloc(m*sizeof(int));
        if (sums[i]==NULL) {
            printf("Sorry, cannot allocate memory\n");
                exit(-1);
        }
    }

    printf("Running maxsummem\n");

    // Αρχικοποίηση αυτού του πίνακα
    for (i=0 ; i<n ; i++) {
        for (j=0 ; j<m ; j++) {
            sums[i][j] = -1;
        }
    }

    // Προσπέλαση της τελευταίας γραμμής του πίνακα
    i = n-1;
    for (j=0 ; j<m ; j++) {
        temp_sum = summem(i, j, board, sums, m);

        if (j==0) {
            ms = temp_sum;
            maxj = j;
        }
        // Εύρεση μεγίστου αθροίσματος
        else if (temp_sum>ms) {
            ms = temp_sum;
            maxj = j;
        }
    }


    printf("Max sum is %d\n", ms);

    // Εφόσον έχει γίνει define, το ορίζουμε εμείς με #define, εύρεση του μονοπατιού του μεγαλύτερου αθροίσματος
    #ifdef PATH
    
    void path(int i, int j, int **pb, int **sums, int n, int m) {
        
        // Χρήση της στοίβας για την εύρεση του μονοπατιού του μεγαλύτερου αθροίσματος, αναδρομικά
        if (i==0) {
            printf("%d", pb[i][j]);
        }
        else if (j==0) {
            switch (maxp(sums[i-1][m-1], sums[i-1][j], sums[i-1][j+1])) {
                case 1: path(i-1, m-1, pb, sums, n, m); break;
                case 2: path(i-1, j, pb, sums, n, m); break;
                case 3: path(i-1, j+1, pb, sums, n, m); break;
            }
            printf("%d", pb[i][j]);
        }
        else if (j<m-1) {
            switch (maxp(sums[i-1][j-1], sums[i-1][j], sums[i-1][j+1])) {
                case 1: path(i-1, j-1, pb, sums, n, m); break;
                case 2: path(i-1, j, pb, sums, n, m); break;
                case 3: path(i-1, j+1, pb, sums, n, m); break;
            }
            printf("%d", pb[i][j]);
        }
        else if (j==m-1) {
            switch (maxp(sums[i-1][j-1], sums[i-1][j], sums[i-1][0])) {
                case 1: path(i-1, j-1, pb, sums, n, m); break;
                case 2: path(i-1, j, pb, sums, n, m); break;
                case 3: path(i-1, 0, pb, sums, n, m); break;
            }
            printf("%d", pb[i][j]);
        }
        if (i==n-1) {
            printf("\n");
        }
        else {
            printf(" -> ");
        }
    }
    path(i, maxj, board, sums, n, m);
    #endif

    // Αποδέσμευση μνήμης του πίνακα μερικών αθροισμάτων
    for (i=0 ; i<n ; i++) {
	    free(*(sums+i));
    }
    free(sums);
}
