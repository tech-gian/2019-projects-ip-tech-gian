#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header_check.h"

// Έλεγχος για ήδη χρωματισμένο χάρτη
void check_map(Listptr *ptr, int n) {
    Borderptr *head;
    Listptr *temp;
    temp = ptr;
    char *color, **col;

	// Δυναμική δέσμευση του col, πίνακας για μέτρηση χρωμάτων που έχουν χρησιμοποιηθεί
    col = malloc(n*sizeof(char *));
    if (col==NULL) {
		fprintf(stderr, "Sorry, cannot allocate memory\n");
		exit(-1);
    }
    for (int i=0 ; i<n ; i++) {
		col[i] = malloc(32*sizeof(char));
		if (col[i]==NULL) {
			fprintf(stderr, "Sorry, cannot allocate memory\n");
			exit(-1);
		}
		col[i][0] = '\0';
    }

    while (*ptr!=NULL) {
		// Αν είναι αχρωμάτιστος ο χάρτης τότε κλείνει
		if (strcmp((*ptr)->color, "nocolor")==0) {
			printf("Please, color the map first\n");
			exit(-1);
		}
		ptr = &((*ptr)->next);
    }

    ptr = temp;
    while (*ptr!=NULL) {
		// Ελέγχει αν έχουν χρησιμοποιηθεί παραπάνω από n χρώματα
		if (check_color((*ptr)->color, col, n)==0) {
			printf("More than %d colors used\n", n);
			exit(-1);
	}

	head = &((*ptr)->borders);
	while (*head!=NULL) {
	    color = cc(temp, (*head)->border);
		// Ελέγχει αν μία χώρα έχει το ίδιο χρώμα με ένα σύνορό της
	    if (strcmp(color, (*ptr)->color)==0) {
			printf("%s - %s: Should have different color\n", (*ptr)->name, (*head)->border);
	    }
	    head = &((*head)->next);
	}
	ptr = &((*ptr)->next);
    }
	
	// Ελεύθερωση μνήμης
    for (int i=0 ; i<n ; i++) {
		free(col[i]);
    }
    free(col);
}

// Ελέγχει τα χρώματα σε κάθε χώρα
int check_color(char *color, char **col, int n) {
    for (int i=0 ; i<n ; i++) {
		// Αποθηκεύει τα χρώματα την πρώτη φορά
    	if (col[i][0]=='\0') {
	    	strcpy(col[i], color);
	    	return 1;
  		}
		// Απλά ελέγχει αν είναι ίδιο με κάποιο προηγούμενο χρώμα
		else if (strcmp(col[i], color)==0) {
	    	return 1;
		}
    }
    return 0;
}
