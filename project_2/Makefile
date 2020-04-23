# Samples_Input
INPUT = Samples_Input/

# compiler
CC = gcc

# Αρχεία .o
OBJS = utf8validate.o

# Εκτελέσιμα αρχεία
EXEC = utf8validate

# Παράμετροι για δοκιμαστική εκτέλεση
# Πρέπει να δοθεί ως όρισμα ένα από τα αρχεία που υπάρχουν στο Samples_Input
ARGS = < $(INPUT)/elytis_mon.txt

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)