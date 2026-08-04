C_COMPILER=gcc
OUT_PUT_FILE=build/key
LIB=-lncurses
INCLUDE=-Iinclude
OTHER_FILES= src/utils.c src/linked_list.c src/interface.c

OUT_PUT_LINUX=/usr/local/bin/key

key: src/key.c
	@$(C_COMPILER) src/key.c $(INCLUDE) $(OTHER_FILES) $(LIB) -o $(OUT_PUT_FILE) && echo "build successful!"

global: src/key.c
	@$(C_COMPILER) src/key.c $(INCLUDE) $(OTHER_FILES) $(LIB) -o $(OUT_PUT_LINUX) && echo "build successful, the key is in /usr/local/bin/"

run:
	./$(OUT_PUT_FILE) ./test_file
