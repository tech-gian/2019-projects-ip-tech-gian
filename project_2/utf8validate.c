#include <stdio.h>

int main(void) {
	int ch;
	int sum1=0, sum=0, codepoint;
	
	ch = getchar();
	// Main Loop
	while (ch != EOF) {
		// 1 byte
		if ((ch>>7) == 0) {
			codepoint = ch;
			sum1 += 1;	// Άθροισμα χαρακτήρων και τελικό codepoint
		}
		// 2 bytes
		else if ((ch>>5) == 6) {
			codepoint = (ch&31)<<6;
			ch = getchar();
			// Έλεγχος για EOF
			if (ch==EOF) {
				printf("Unexpected EOF\n");
				break;
			}
			else if ((ch>>6) == 2) {
				codepoint = codepoint | (ch&63);
				sum += 1;	// Άθροισμα χαρακτήρων και τελικό codepoint
				// Έλεγχος για oversized
				if (codepoint<=0x7f) {
					printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
					break;
				}
			}
			// Έλεγχος για invalid-tail
			else {
				printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
				break;
			}
		}
		// 3 bytes
		else if ((ch>>4) == 14) {
			codepoint = (ch&15)<<12;
			ch = getchar();
			// Έλεγχος για EOF
			if (ch==EOF) {
				printf("Unexpected EOF\n");
				break;
			}
			else if ((ch>>6) == 2) {
				codepoint = codepoint | ((ch&63)<<6);
				ch = getchar();
				// Έλεγχος για EOF
				if (ch==EOF) {
					printf("Unexpected EOF\n");
					break;
				}
				else if ((ch>>6) == 2) {
					codepoint = codepoint | (ch&63);
					sum += 1;	// Άθροισμα χαρακτήρων και τελικό codepoint
					if (codepoint<=0x7ff) {
						printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
						break;
					}
				}
				// Έλεγχος για invalid-tail
				else {
					printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
					break;
				}
			}
			// Έλεγχος για invalid-tail
			else {
				printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
				break;
			}
		}
		// 4 bytes
		else if ((ch>>3) == 30) {
			codepoint = (ch&7)<<18;
			ch = getchar();
			// Έλεγχος για EOF
			if (ch==EOF) {
				printf("Unexpected EOF\n");
				break;
			}
			else if ((ch>>6) == 2) {
				codepoint = codepoint | ((ch&63)<<12);
				ch = getchar();
				// Έλεγχος για EOF
				if (ch==EOF) {
					printf("Unexpected EOF\n");
					break;
				}
				else if ((ch>>6) == 2) {
					codepoint = codepoint | ((ch&63)<<6);
					ch = getchar();
					// Έλεγχος για EOF
					if (ch==EOF) {
						printf("Unexpected EOF\n");
						break;
					}
					else if ((ch>>6) == 2) {
						codepoint = codepoint | (ch&63);
						sum += 1;	// Άθροισμα χαρακτήρων και τελικό codepoint
						// Έλεγχος για oversized
						if (codepoint<=0xffff) {
							printf("Oversized UTF-8 code point: U+%04X\n", codepoint);
							break;
						}
					}
					// Έλεγχος για invalid-tail
					else {
						printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
						break;
					}
				}
				// Έλεγχος για invalid-tail
				else {
					printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
					break;
				}
			}
			// Έλεγχος για invalid-tail
			else {
				printf("Invalid UTF-8 tail byte: 0x%02X\n", ch);
				break;
			}
		}
		// Έλεγχος για όλες τις περιπτώσεις header-byte να είναι invalid
		else {
			printf("Invalid UTF-8 header byte: 0x%02X\n", ch);
			break;
		}

		// Έλεγχος για invalid-codepoint
		if ((codepoint>=0xd800 && codepoint<=0xdfff) || codepoint>0x10ffff) {					
			printf("Invalid UTF-8 code point: U+%04X\n", codepoint);
			break;
		}
		else {
			ch = getchar();
		}
	}
	
	// Έμφανιση χαρακτήρων αν δεν έχει γίνει break
	if (ch==EOF) {
		printf("Found %d ASCII and %d multi-byte UTF-8 characters.\n", sum1, sum);
	}
	return 0;
}
