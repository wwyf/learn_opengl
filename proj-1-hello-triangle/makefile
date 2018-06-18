# Target PROJECT and File
PROJECT = proj-1-hello-triangle
TARGET_FILE = hello.cpp

# the ROOT dictionary
ROOT = ..
# compile option
CXX_FLAGS = -std=c++11 -g -Wall  
CXX_INCLUDES =-I$(ROOT)/include
# 增加静态链接库的寻找目录
CXX_LIB = -L$(ROOT)/lib
STATIC_LINK_LIB = -lglfw3 -lopengl32 -lgdi32 -lGLAD

all:t.exe
	./t.exe
	make clean
t.exe:t.o
	g++ t.o -o t.exe $(CXX_FLAGS)  $(CXX_LIB)  $(STATIC_LINK_LIB)
t.o:$(TARGET_FILE)
	g++ -c $(TARGET_FILE) -o t.o $(CXX_INCLUDES) $(CXX_FLAGS)


.PHONY:glad clean
# 生成glad静态链接库
glad:
	cd ../lib && make
	cd ../$(PROJECT)
clean:
	-del *.o
	# -del *.exe

