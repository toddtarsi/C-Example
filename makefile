CC     = g++
CFLAGS = -g -std=c++11 -Wall
LFLAGS = -lglut -lGLU -lGL -lm
OBJS   = main.cpp

main : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main.out $(LFLAGS)
