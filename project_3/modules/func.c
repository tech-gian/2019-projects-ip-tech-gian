#include <stdio.h>

#include "functions.h"

// Βοηθητική συνάρτηση

// Εύρεση μεγίστου και επιστροφή του ίδιου στοιχείου
static int max3(int a, int b, int c) {
    if (a>=b && a>=c) return a;
    else if (b>a && b>c) return b;
    else return c;
}

// Κύριες συναρτήσεις

// Εύρεση μεγίστου και επιστροφή μίας τιμής
int maxp(int a, int b, int c) {
    if (a>=b && a>=c) return 1;
    else if (b>a && b>c) return 2;
    else return 3;
}

// Υπολογισμός αθροίσματος αναδρομικά
int sum(int i, int j, int **pb, int m) {

    if (i==0) {
        return pb[i][j];
    }
    else if (j==0) {
        return pb[i][j] + max3(sum(i-1, m-1, pb, m), sum(i-1, j, pb, m), sum(i-1, j+1, pb, m));
    }
    else if (j<m-1) {
        return pb[i][j] + max3(sum(i-1, j-1, pb, m), sum(i-1, j, pb, m), sum(i-1, j+1, pb, m));
    }
    else {
        return pb[i][j] + max3(sum(i-1, j-1, pb, m), sum(i-1, j, pb, m), sum(i-1, 0, pb, m));
    }
}

// Υπολογισμός αθροισμάτων αναδρομικά με αποθήκευση
int summem(int i, int j, int **pb, int **sums, int m) {

    if (i==0) {
	    return pb[i][j];
    }
    else if (j==0) {
	    if (sums[i-1][m-1]==-1) sums[i-1][m-1] = summem(i-1, m-1, pb, sums, m);
        if (sums[i-1][j]==-1) sums[i-1][j] = summem(i-1, j, pb, sums, m);
        if (sums[i-1][j+1]==-1) sums[i-1][j+1] = summem(i-1, j+1, pb, sums, m);
	    
        return pb[i][j] + max3(sums[i-1][m-1], sums[i-1][j], sums[i-1][j+1]);
    }
    else if (j<m-1) {
	    if (sums[i-1][j-1]==-1) sums[i-1][j-1] = summem(i-1, j-1, pb, sums, m);
        if (sums[i-1][j]==-1) sums[i-1][j] = summem(i-1, j, pb, sums, m);
        if (sums[i-1][j+1]==-1) sums[i-1][j+1] = summem(i-1, j+1, pb, sums, m);
	    
        return pb[i][j] + max3(sums[i-1][j-1], sums[i-1][j], sums[i-1][j+1]);
    }
    else {
        if (sums[i-1][j-1]==-1) sums[i-1][j-1] = summem(i-1, j-1, pb, sums, m);
        if (sums[i-1][j]==-1) sums[i-1][j] = summem(i-1, j, pb, sums, m);
        if (sums[i-1][0]==-1) sums[i-1][0] = summem(i-1, 0, pb, sums, m);
        
        return pb[i][j] + max3(sums[i-1][j-1], sums[i-1][j], sums[i-1][0]);
    }
}

// Υπολογισμός αθροισμάτων επαναληπτικά
void sumdp(int i, int j, int **pb, int **sums, int m) {

    if (i==0) {
	    sums[i][j] = pb[i][j];
    }
    else if (j==0) {
	    sums[i][j] = pb[i][j] + max3(sums[i-1][m-1], sums[i-1][j], sums[i-1][j+1]);
    }
    else if (j<m-1) {
	    sums[i][j] = pb[i][j] + max3(sums[i-1][j-1], sums[i-1][j], sums[i-1][j+1]);
    }
    else {
	    sums[i][j] = pb[i][j] + max3(sums[i-1][j-1], sums[i-1][j], sums[i-1][0]);
    }
}
