C_COMPILER=gcc
OUT_PUT_FILE=build/key
LIB=-lncurses
OTHER_FILES=include/interface/interface.c include/interface/interface.h \
			include/utils/utils.c include/utils/utils.h

key: src/key.c
	@$(C_COMPILER) src/key.c $(OTHER_FILES) $(LIB) -o $(OUT_PUT_FILE) && echo "build successful!"

run:
	./$(OUT_PUT_FILE) ../test_file
