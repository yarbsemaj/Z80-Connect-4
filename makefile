setup:
	mkdir -p bin

build_z80: setup
	zcc +rc2014 -subtype=basic connect4.c -o bin/connect4_z80 -create-app

build_local: setup
	gcc connect4.c -o bin/connect4_local
