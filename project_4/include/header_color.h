////////////////////////
// 
// Header file for color
// 
////////////////////////


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

// Συνάρτηση για εύρεση θέσης χώρας στον πίνακα maxb 

int j_in_max(int *maxb, int j, int k);

// Χρωματισμός χάρτη

void color(Listptr *ptr, int n);


// "Καίω" τα χρώματα με τα οποία έχουν ήδη χρωματιστεί τα σύνορα

void change_color(Borderptr *ptr, Listptr *lptr, char *[4], int **col, int i, int n);

// Επιστροφή του χρώματα που είναι το σύνορο bor

char *cc(Listptr *ptr, char *bor);
