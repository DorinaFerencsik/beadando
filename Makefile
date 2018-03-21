all:
	gcc main.c camera.c draw.c model.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o beadando.exe

linux:
	gcc main.c camera.c draw.c -lglut -lGL -lSOIL -lGLU -o beadando
