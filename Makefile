C_COMPILER=gcc
OUT_PUT_FILE=build/key
INCLUDE=-Iinclude
OTHER_FILES= src/linked_list.c

key: src/key.c
	@$(C_COMPILER) src/key.c $(INCLUDE) $(OTHER_FILES) -o $(OUT_PUT_FILE); echo "build successful!"

global: src/key.c
	@set -e; $(C_COMPILER) src/key.c $(INCLUDE) $(OTHER_FILES) -o $(OUT_PUT_FILE); cp $(OUT_PUT_FILE) /usr/local/bin/; echo "build successful, the key is in /usr/local/bin/"
