all:
	gcc ./src/main.c ./src/camera.c ./src/draw.c ./src/model.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o beadando.exe

linux:
	gcc ./src/main.c ./src/camera.c ./src/draw.c -lglut -lGL -lSOIL -lGLU -o beadando
