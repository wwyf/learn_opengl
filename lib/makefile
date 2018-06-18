# the ROOT dictionary
ROOT = ..
CXX_FLAGS = -std=c++11 -g -Wall  
CXX_INCLUDES =-I$(ROOT)/include

libGLAD.a:glad.o
	ar -r libGLAD.a glad.o
	-del glad.o

glad.o:glad.c
	g++ -c glad.c -o glad.o $(CXX_INCLUDES) $(CXX_FLAGS) 