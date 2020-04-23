#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPUTATIONS 10000000


int main() {
	int i, div, power, pd, large, small, temp, rem, sum, curtime, num, x, y, z;
	sum = 0;
	curtime = time(NULL);
	srand((unsigned int) curtime);
	printf("Current time is %d\n", curtime);
	
	// Επανάληψη για το πλήθος των τυχαίων που θα εξετάσω
	for (i = 1; i <= COMPUTATIONS; i++) {
		
		// Ορισμός των τυχαίων y, z και x βάση του τύπου
		y = rand();
		z = rand();
		x = ((y%32768)+1) * ((z%32768)+1) + 1;
		
		num = x;
		div = 2;
		power = 0;
		pd = 1;
		large = 0;
		
		// Παραγοντοποίηση του αριθμού
		while (num!=1) {
			if (num%div==0) {
				power += 1;
				num = num/div;
			}
			else {
				// Έλεγχος αν κάποιος παράγοντας του γινομένου έχει εκθέτη 1
				if (power == 1) {
					num = 1;
					pd = 0;
				}
				else {
					// Για το πρώτο ζευγάρι
					if (large == 0) {
						large = power;
					}
					// Εύρεση ΜΚΔ για κάθε ζευγάρι εκθετών και τελικά όλων
					small = power;
					if (large < small) {
						temp = large;
						large = small;
						small = temp;
					}
					while (small) {
						rem = large%small;
						large = small;
						small = rem;
					}
	
					power = 0;
					if (div == 2) {
						div = 3;
					}
					else {
						// Εύρεση του επόμενου πρώτου παράγοντα του αριθμού
						while (num%div!=0 && div*div<=num) {
							div += 2;
						}
						// Η περίπτωση που ο τελευταίος αριθμός είναι ο διαιρετέος που έχει απομείνει
						if (num%div!=0) {
							div = num;
						}
					}
				}
			}
		}
		// Το τελευταίο ζευγάρι ΜΚΔ
		small = power;
		if (large < small) {
			temp = large;
			large = small;
			small = temp;
		}
		while (small) {
			rem = large%small;
			large = small;
			small = rem;
		}
		// Αν ο τελευταίος εκθέτης είναι 1
		if (power == 1) {
			pd = 0;
		}
		// Εμφάνιση αχίλλειου και υπολογισμός αθροίσματος
		if (large == 1 && pd == 1) {
			printf("%10d is Achilles number\n", x);
			sum += 1;
		}
	}
	// Εμφάνιση αθροίσματος αχίλλειων
	printf("Found %d Achilles out of %d tested numbers\n", sum, COMPUTATIONS);
	return 0;
}
