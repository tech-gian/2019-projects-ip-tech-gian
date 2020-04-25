#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header_color.h"

// Συνάρτηση για εύρεση θέσης χώρας στον πίνακα maxb
int j_in_maxb(int *maxb, int j, int k) {
    for (int i=0 ; i<k ; i++) {
        if (maxb[i]==j) return 0;
    }
    return 1;
}

// Χρωματισμός χάρτη
void color(Listptr *ptr, int n) {
    int i, k=0, j, max, maxj, *maxb, **col, m;
    Listptr *temp, *temp1, *ptr2, *temp2;
    char *colors[10]={"red", "green", "blue", "yellow", "orange", "violet", "cyan", "pink", "brown", "grey"};

    ptr2 = ptr;
    temp1 = ptr;
    temp2 = ptr;

    while (*ptr!=NULL) {
        // Αριθμός κόμβων στην λίστα για τις χώρες
        k++;
        ptr = &((*ptr)->next);
    }

    // Ο πίνακας maxb έχει ταξινομημένες τις θέσεις των χωρών στην λίστα
    maxb = malloc(k*sizeof(int));
    if (maxb==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }
    // Αρχικοποίηση του
    for (i=0 ; i<k ; i++) {
        maxb[i] = -1;
    }

    for (i=0 ; i<k ; i++) {
        temp = temp1;
        max = -1;
        maxj = 0;
        // Loop για το γέμισμα του maxb εφόσον έχει μεγαλύτερο πλήθος συνόρων και δεν υπάρχει ήδη
        for (j=0 ; j<k ; j++) {
            if ((*temp)->n_border>=max) {
                if (j_in_maxb(maxb, j, k)==1 && strcmp((*temp)->color, "nocolor")==0) {
                    max = (*temp)->n_border;
                    maxj = j;
                }
            }
            temp = &(*temp)->next;
        }
        if (max!=-1) {
            maxb[i] = maxj;
        }
    }

    // Δυναμική δέσμευση μνήμης για πίνακα που με 1 και 0 αντιστοιχεί μια σειρά χρωμάτων αν είναι διαθέσιμα ή οχι για κάθε χώρα
    col = malloc(k*sizeof(int *));
    if (col==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }
    for (i=0 ; i<k ; i++) {
        col[i] = malloc(n*sizeof(int));
        if (col[i]==NULL) {
            fprintf(stderr, "Sorry, cannot allocate memory\n");
            exit(-1);
        }
    }

    // Αρχικοποίηση του
    for (i=0 ; i<k ; i++) {
        for (j=0 ; j<n ; j++) {
            col[i][j] = 0;
        }
    }

    i = 0;
    while (i<k && i>-1) {
        if (maxb[i]==-1) {
            break;
        }
        temp2 = ptr2;
        // Εύρεση του κόμβου που δείχνει το maxb[i]
        for (j=0 ; j<maxb[i] ; j++) {
            temp2 = &((*temp2)->next);
        }

        change_color(&((*temp2)->borders), ptr2, colors, col, i, n);

        // Βάζω το πρώτο ελεύθερο χρώμα στη χώρα που βρίσκομαι
        for (m=0 ; m<n ; m++) {
            if (col[i][m]==0) {
                (*temp2)->color = colors[m];
                break;
            }
        }

        // Αν δεν υπήρχε ελεύθερο χρώμα
        if (strcmp((*temp2)->color, "nocolor")==0) {
            // Μηδενίζω τον col
            for (m=0 ; m<n ; m++) {
                col[i][m] = 0;
            }
            // Πάω μία θέση πίσω
            i--;
            // Αν δεν μπορώ άλλη θέση τότε δεν μπορώ να χρωματίσω με n χρώματα τον χάρτη
            if (i==-1) printf("Sorry, cannot color the given map\n");
            else {
                temp2 = ptr2;
                // Βρίσκω τον προηγούμενο κόμβο
                for (j=0 ; j<maxb[i] ; j++) {
                    temp2 = &((*temp2)->next);
                }
                // Του αφαιρώ το χρώμα
                (*temp2)->color = "nocolor";
                for (m=0 ; m<n ; m++) {
                    if (col[i][m]==0) {
                        col[i][m] = 1;
                        break;
                    }
                }
            }
        }
        // Αλλιώς πάω στον επόμενο κόμβο
        else {
            i++;
        }

    }

    // Ελευθέρωση μνήμης
    free(maxb);
    for (i=0 ; i<k ; i++) {
	    free(col[i]);
    }
    free(col);
}


// "Καίω" τα χρώματα με τα οποία έχουν ήδη χρωματιστεί τα σύνορα
void change_color(Borderptr *ptr, Listptr *lptr, char *colors[10], int **col, int i, int n) {
    char *color_country;
    int j;

    while (*ptr!=NULL) {
	color_country = cc(lptr, (*ptr)->border);

	for (j=0; j<n ; j++) {
	    if (strcmp(color_country, colors[j])==0) {
            col[i][j] = 1;
            break;
	    }
	}
	ptr = &((*ptr)->next);
    }
}

// Επιστροφή του χρώματα που είναι το σύνορο bor
char *cc(Listptr *ptr, char *bor) {
    while (strcmp((*ptr)->name, bor)!=0) {
	    ptr = &((*ptr)->next);
    }
    return (*ptr)->color;
}
