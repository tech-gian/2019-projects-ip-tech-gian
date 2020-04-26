# paths
INPUT = ../Samples_input
MODULES = ../modules
INCLUDE = ../include

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
OBJS = $(MODULES)/check.o $(MODULES)/color.o main.o

# Το εκτελέσιμο πρόγραμμα
EXEC = main

# Παράμετροι για δοκιμαστική εκτέλεση

# Μπορεί να χρησιμοποιηθεί οποιοδήποτε αρχείο από
# το folder Samples_input, με τα κατάλληλα ορίσματα
# ή η έξοδος του genmap.c όπως χρησιμοποιείται στην εκφώνηση
# (απλά πρέπει να γίνει κι αυτό compile)
# (βλέπε εκφώνηση)
ARGS = < $(INPUT)/Balkans.txt

$(EXEC): $(OBJS)
	gcc $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)
