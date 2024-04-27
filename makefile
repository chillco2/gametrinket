default:
	g++ -Wall -I include/ -I src/ -lglfw -lGL -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o out.a src/main.cpp src/glad.c
