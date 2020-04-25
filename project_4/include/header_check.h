////////////////////////
// 
// Header file for check
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

// Έλεγχος για ήδη χρωματισμένο χάρτη

void check_map(Listptr *ptr, int n);

// Συνάρτηση για εύρεση θέσης χώρας στον πίνακα maxb 

int j_in_max(int *maxb, int j, int k);

// Ελέγχει τα χρώματα σε κάθε χώρα

int check_color(char *color, char **col, int n);

// Επιστροφή του χρώματα που είναι το σύνορο bor

char *cc(Listptr *ptr, char *bor);
