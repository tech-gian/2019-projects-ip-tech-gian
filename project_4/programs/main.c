#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header_main.h"


int main(int argc, char *argv[]) {
    Listptr map;
    int ch=0, n=4, flag_input=0;

    map = NULL;

    // Ανάλογα με τον αριθμό του argc και το ορίσματα που δίνονται, καλούνται οι αντίστοιχες συναρτήσεις
    if (argc==1) {
        flag_input = 1;
            // Εισαγωγή δεδομένων στην λίστα από stdin
            while (ch!=EOF) {
                insert(&map, &ch);
            }
        color(&map, n);
        print(&map);
    }
    else if (argc==2) {
        if (strcmp(argv[1], "-c")==0) {
            flag_input = 1;
            while (ch!=EOF) {
                insert(&map, &ch);
            }
            check_map(&map, n);
        }
    }
    else if (argc==3) {
        if (strcmp(argv[1], "-i")==0) {
            flag_input = 1;
            FILE *newfile;
            newfile = fopen(argv[2], "r");
            // Εισαγωγή δεδομέων στην λίστα από αρχείο
            while (ch!=EOF){
                insert_file(newfile, &map, &ch);
            }
            fclose(newfile);
            color(&map, n);
            print(&map);
        }
        else if (strcmp(argv[1], "-c")==0) {
            flag_input = 1;
            FILE *newfile;
            newfile = fopen(argv[2], "r");
            while (ch!=EOF){
                insert_file(newfile, &map, &ch);
            }
            fclose(newfile);
            check_map(&map, n);
        }
        else if (strcmp(argv[1], "-n")==0) {
            flag_input = 1;
            n = atoi(argv[2]);
            while (ch!=EOF) {
                insert(&map, &ch);
            }
            color(&map, n);
            print(&map);
        }
    }
    else if (argc==4) {
        if (strcmp(argv[1], "-i")==0 && strcmp(argv[3], "-c")==0) {
            flag_input = 1;
            FILE *newfile;
            newfile = fopen(argv[2], "r");
            while (ch!=EOF){
                insert_file(newfile, &map, &ch);
            }
            fclose(newfile);
            check_map(&map, n);
        }
        else if (strcmp(argv[1], "-c")==0 && strcmp(argv[2], "-n")==0) {
            flag_input = 1;
            n = atoi(argv[3]);
            while (ch!=EOF) {
                insert(&map, &ch);
            }
            check_map(&map, n);
        }
    }
    else if (argc==5) {
        if (strcmp(argv[1], "-i")==0 && strcmp(argv[3], "-n")==0) {
            flag_input = 1;
            FILE *newfile;
            newfile = fopen(argv[2], "r");
            while (ch!=EOF){
                insert_file(newfile, &map, &ch);
            }
            fclose(newfile);
            n = atoi(argv[4]);
            color(&map, n);
            print(&map);
        }
    }
    if (flag_input==0) {
        fprintf(stderr, "Error: Parametres werenot correct\n");
        return -1;
    }

    free_list(&map);
    return 0;
}

// Συνάρτηση για εισαγωγή χωρών και χρωμάτων
void insert(Listptr *ptr, int *ch) {
    int c, count=0;

    while (*ptr!=NULL) {
	    ptr = &((*ptr)->next);
    }

    *ptr = malloc(sizeof(struct country));
    if (*ptr==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }
    (*ptr)->color = malloc(32*sizeof(char));
    if ((*ptr)->color==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }
    (*ptr)->name = malloc(32*sizeof(char));
    if ((*ptr)->name==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }


    scanf("%s", (*ptr)->color);
    scanf("%s", (*ptr)->name);

    c = getchar();
    // Όταν βρεθεί ο τελευταίος χαρακτήρας \n, αλλάζει ο κόμβος
    while (c!='\n') {
        ungetc(c, stdin);

        ins_bor(&((*ptr)->borders));

        count++;
        c = getchar();
    }
    (*ptr)->n_border = count;
    (*ptr)->next = NULL;

    c = getchar();
    // Αν βρεθεί EOF, τον επιστρέφω και τελειώνει η εισαγωγή
    if (c==EOF) *ch = c;
    else {
        ungetc(c, stdin);
        *ch = c;
    }
}

// Εισαγωγή συνόρων (λίστα μέσα σε λίστα) για κάθε χώρα
void ins_bor(Borderptr *ptr) {
    while (*ptr!=NULL) {
	    ptr = &((*ptr)->next);
    }

    *ptr = malloc(sizeof(struct Borders));
    if (*ptr==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }
    (*ptr)->border = malloc(32*sizeof(char));
    if ((*ptr)->border==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }

    scanf("%s", (*ptr)->border);

    (*ptr)->next = NULL;
}


// Εκτύπωση της λίστας με τις χώρες και τα χρώματα
void print(Listptr *ptr) {
    while (*ptr!=NULL) {
        printf("%s %s", (*ptr)->color, (*ptr)->name);

        print_border(&((*ptr)->borders));
        ptr = &((*ptr)->next);
    }
}

// Εκτύπωση της λίστας με τα σύνορα
void print_border(Borderptr *ptr) {
	while (*ptr!=NULL) {
	    printf(" %s", (*ptr)->border);
	    ptr = &((*ptr)->next);
	}
	printf("\n");
}

// Εισαγωγή χωρών και χρωμάτων από αρχείο
void insert_file(FILE *newfile, Listptr *ptr, int *ch) {
    int c, count=0;

    while (*ptr!=NULL) {
        ptr = &((*ptr)->next);
    }

    *ptr = malloc(sizeof(struct country));
    if (*ptr==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }

    (*ptr)->color = malloc(32*sizeof(char));
    if ((*ptr)->color==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }

    (*ptr)->name = malloc(32*sizeof(char));
    if ((*ptr)->name==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }


    fscanf(newfile, "%s", (*ptr)->color);
    fscanf(newfile, "%s", (*ptr)->name);

    c = getc(newfile);
    while (c!='\n') {
        ungetc(c, newfile);

        ins_bor_file(&((*ptr)->borders), newfile);

        count++;
        c = getc(newfile);
    }
    (*ptr)->n_border = count;
    (*ptr)->next = NULL;

    c = getc(newfile);
    if (c==EOF){
        *ch = c;
    }
    else {
        ungetc(c, newfile);
        *ch = c;
    }
}

// Εισαγωγή συνόρων από αρχείο
void ins_bor_file(Borderptr *ptr, FILE *newfile) {

    while (*ptr!=NULL) {
        ptr = &((*ptr)->next);
    }

    *ptr = malloc(sizeof(struct Borders));
    if (*ptr==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }

    (*ptr)->border = malloc(32*sizeof(char));
    if ((*ptr)->border==NULL) {
        fprintf(stderr, "Sorry, cannot allocate memory\n");
        exit(-1);
    }

    fscanf(newfile, "%s", (*ptr)->border);

    (*ptr)->next = NULL;
}

// Αποδέσμευση μνήμης
void free_list(Listptr *ptr) {
    Listptr *temp;
    Borderptr *head, *temp1;

    while (*ptr!=NULL) {
        temp = ptr;
        head = &((*ptr)->borders);
        while (*head!=NULL) {
            temp1 = head;

            free((*head)->border);

            head = &((*head)->next);
            free(*temp1);
        }

        // Εδώ κανονικά θα μπορούσε να γίνει free
        // αλλά κάπου χρησιμοποιείται και δεν το
        // επιτρέπει
        // free((*ptr)->color);
        
        free((*ptr)->name);

        ptr = &((*ptr)->next);
        free(*temp);
    }
}
