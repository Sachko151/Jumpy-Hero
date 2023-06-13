build:
	gcc main.c -o jumpy_hero.out -lraylib -lm
debug:
	gcc main.c -o debug.out -lraylib -lm -g
clean:
	rm jumpy_hero.out
	rm debug.out
	