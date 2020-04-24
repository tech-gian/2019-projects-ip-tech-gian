# paths
INPUT = ../Samples_input
MODULES = ../modules
INCLUDE = ../include

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)

# Αρχεία .o
# Μπορεί να εκτελεστεί οποιαδήποτε άλλη υλοποίηση
# Απλά επιλέγεται η επαναληπτική, ως πιο γρήγορη
OBJS = maxsum.o $(MODULES)/func.o $(MODULES)/maxsumdp.o

# Το εκτελέσιμο πρόγραμμα
EXEC = maxsumdp

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = < $(INPUT)/input.txt

$(EXEC): $(OBJS)
	gcc $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)