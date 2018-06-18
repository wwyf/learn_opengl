# 配置OpenGL的笔记

## linux

好不容易在ubuntu下配置好OpenGL，在博客上记录一下。


```sh
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install freeglut3-dev
sudo apt-get install build-essential gdb subversion
sudo apt-get install automake autoconf libtool
sudo apt-get install libgtk2.0-dev libxmu-dev libxxf86vm-dev
```

在安装了参考资料里面的包之后，还另外安装了glfw,为了能够运行教程中的用到glfw代码的示例。

```sh
sudo apt install libglfw3 libglfw3-dev
sudo apt install libassimp-dev
```

## 小结

这是在wsl上配置的，为了能够让wsl里面的程序在window运行图形界面，还另外装了VcXsrv作为Xwindow server。然后在启动VcXsrv时还修改了一些配置才能运行起来。



## 参考资料

https://stackoverflow.com/questions/22008845/glfw-mingw-link-error
https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/
https://blog.csdn.net/evenness/article/details/9150351