str_dir = ./str/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(str_dir)
vpath %.c $(str_dir)
vpath %.h $(str_dir)

# Ajout de bst.o et scale.o
objects = main.o str.o bst.o scale.o
executable = jaccard_dist
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

# Compilation de l'exécutable avec tous les fichiers objets
$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

# Ajout des dépendances
main.o: main.c str.h str_ip.h bst.h scale.h
str.o: str.c str.h str_ip.h
bst.o: bst.c bst.h
scale.o: scale.c scale.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
