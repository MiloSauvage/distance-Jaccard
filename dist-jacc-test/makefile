str_dir = ../str/
scale_dist = ../scale/
bst_dist = ../bst/
stream_dist = ../stream/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O0 -g \
  -I$(str_dir) -I$(scale_dist) -I$(bst_dist) -I$(stream_dist)
vpath %.c $(str_dir) $(scale_dist) $(bst_dist) $(stream_dist)
vpath %.h $(str_dir) $(scale_dist) $(bst_dist) $(stream_dist)

objects = main.o str.o bst.o scale.o stream.o
executable = jaccard_dist
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

main.o: main.c str.h bst.h scale.h
str.o: str.c str.h str_ip.h
bst.o: bst.c bst.h bst_ip.h
scale.o: scale.c scale.h scale_ip.h
stream.o : stream.c stream.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)


