///////////////////////
// 
// Header file for main
// 
///////////////////////
    

// typedef ώστε να γίνουν πιο απλά

typedef struct country *Listptr;
typedef struct Borders *Borderptr;

// struct για το κάθε σύνορο

struct Borders {
    char *border;
    Borderptr next;
};

// struct για την κάθε χώρα

struct country {
    char *color;
    char *name;
    int n_border;
    Borderptr borders;
    Listptr next;
};

// Συνάρτηση για εισαγωγή χωρών και χρωμάτων

void insert(Listptr *ptr, int *ch);

// Εισαγωγή συνόρων (λίστα μέσα σε λίστα) για κάθε χώρα

void ins_bor(Borderptr *ptr);

// Εκτύπωση της λίστας με τις χώρες και τα χρώματα


void print(Listptr *ptr);

// Εκτύπωση της λίστας με τα σύνορα

void print_border(Borderptr *ptr);

// Εισαγωγή χωρών και χρωμάτων από αρχείο

void insert_file(FILE *newfile, Listptr *ptr, int *ch);

// Εισαγωγή συνόρων από αρχείο

void ins_bor_file(Borderptr *ptr, FILE *newfile);

// Αποδέσμευση μνήμης

void free_list(Listptr *ptr);

// Χρωματισμός χάρτη

void color(Listptr *ptr, int n);

// Έλεγχος για ήδη χρωματισμένο χάρτη

void check_map(Listptr *ptr, int n);
