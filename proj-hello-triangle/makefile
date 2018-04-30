# the ROOT dictionary
ROOT = ..
# Target File
TARGET_FILE = hello.cpp
# compile option
CXX_FLAGS = -std=c++11 -g -Wall  
CXX_INCLUDES =-I$(ROOT)/include
# 增加静态链接库的寻找目录
CXX_LIB = -L$(ROOT)/lib
STATIC_LINK_LIB = -lglfw3 -lopengl32 -lgdi32 -lGLAD

all:t.exe
	./t.exe
	make clean
t.exe:t.o glad.o
	g++ t.o glad.o -o t.exe $(CXX_FLAGS)  $(CXX_LIB)  $(STATIC_LINK_LIB)
t.o:$(TARGET_FILE)
	g++ -c $(TARGET_FILE) -o t.o $(CXX_INCLUDES) $(CXX_FLAGS)
glad.o:glad.c
	g++ -c glad.c -o glad.o $(CXX_INCLUDES) $(CXX_FLAGS) 
clean:
	-del *.o
	-del *.exe

