C_COMPILER=gcc
OUTPUT_FILE=key
LIB=-lncurses
OTHER_FILES=key_interface.c key_interface.h

key: key.c
	$(C_COMPILER) key.c $(OTHER_FILES) -o $(OUTPUT_FILE) $(LIB)
