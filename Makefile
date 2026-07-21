C_COMPILER=gcc
OUT_PUT_FILE=build/key
LIB=-lncurses
INCLUDE=-Iinclude
OTHER_FILES= src/utils.c src/linked_list.c src/interface.c

key: src/key.c
	@$(C_COMPILER) -g -O0 src/key.c $(INCLUDE) $(OTHER_FILES) $(LIB) -o $(OUT_PUT_FILE) && echo "build successful!"

run:
	./$(OUT_PUT_FILE) ./test_file
