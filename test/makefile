# the ROOT dictionary
ROOT = ..
# Target File
TARGET_FILE = $(ROOT)/test/ibl_irradiance_conversion.cpp
# compile option
CXX_FLAGS = -std=c++11 -g -Wall  
CXX_DEFINES = 
CXX_INCLUDES =-I$(ROOT)/includes -I$(ROOT)/configuration
# 增加静态链接库的寻找目录
CXX_LIB = $(ROOT)/lib
# 静态链接库的名称
STATIC_LIB_PATH = $(ROOT)/lib
libSTB_IMAGE_PATH=$(STATIC_LIB_PATH)/libSTB_IMAGE.a
libGLAD_PATH=$(STATIC_LIB_PATH)/libGLAD.a
STATIC_LINK_LIB = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -ldl -lpthread -lassimp $(libSTB_IMAGE_PATH) $(libGLAD_PATH)  -ldl

all:t.out t.o
	./t.out
	make clean

t.out:t.o
	g++ $(CXX_FLAGS) t.o -o t.out  -L$(CXX_LIB) $(STATIC_LINK_LIB) -rdynamic
t.o:
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o t.o -c $(TARGET_FILE)
# rpath 链接时使用的动态库
# 现代连接器在处理动态库时将链接时路径（Link-time path）和运行时路径（Run-time path）分开,用户可以通过-L指定连接时库的路径，通过-R（或-rpath）指定程序运行时库的路径，大大提高了库应用的灵活性
# -rpath: “运行”的时候，去找的目录。运行的时候，要找 .so 文件，会从这个选项里指定的地方去找。对于交叉编译，交叉编译链接器需已经配置 --with-sysroot 选项才能起作用。也就是说，-rpath指定的路径会被记录在生成的可执行程序中，用于运行时查找需要加载的动态库。-rpath-link 则只用于链接时查找。
# 在gcc中使用ld链接选项时，需要在选项前面加上前缀-Wl(是字母l，不是1，我曾多次弄错），以区别不是编译器的选项。
# https://my.oschina.net/shelllife/blog/115958

clean:
	# -rm t.out
	-rm t.o

# the function of -ldl: It tells the linker to link the dl library, which is located at /usr/lib/libdl.so. -l is the switch to add a library, dl is the name of it (without the lib prefix or .so extension).This library includes functions for dynamically loading shared libraries.
# -rdynamic:却是一个连接选项，它将指示连接器把所有符号（而不仅仅只是程序已使用到的外部符号，但不包括静态符号，比如被static修饰的函数）都添加到动态符号表（即.dynsym表）里，以便那些通过dlopen()或backtrace()（这一系列函数使用.dynsym表内符号）这样的函数使用。