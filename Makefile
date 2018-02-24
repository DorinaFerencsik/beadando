all:
	gcc main.c brick.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o beadando.exe

linux:
	gcc main.c brick.c -lglut -lGL -lSOIL -lGLU -o beadando
