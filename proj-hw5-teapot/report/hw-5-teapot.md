# 计算机图形学 HW5 报告

实现一个具有简单光照效果的Teapot模型。

[TOC]

## 1 开发环境

本作业的开发环境是MinGW，完成作业后使用vs 2017编译并提交release版。
基于GLFW第三方库进行窗口管理。

## 2 程序实现说明

### 2.1 概述

由于本程序在OPENGL核心模式下进行编程，因此实现的方法有一些复杂，下面解释一下程序的细节。

整个程序大致分为三部分说明。

1. obj模型文件的读取。
1. 光照模型的实现。
1. 用户操作的实现


### 2.2 obj模型文件的读取

TODO:主要说明assimp库的使用

### 2.3 光照模型的实现

TODO:主要说明着色器的实现

### 2.4 用户操作的实现

在该步骤中，复用了在HW4-2-meshlab中的代码，因此与作业HW4-2-meshlab的实现相同，不做重复讲解。

具体操作可见第三部分使用说明，也可见demo视频。


## 3 程序运行方法

### 3.1 编译方法

在代码目录中，可使用cmake工具进行编译。

依赖的第三方库有

|库名称| 库作用|
|-|-|
|assimp| 读取模型文件|

### 3.2 运行方法

重点：在命令行下调用该程序时，第一个参数是模型文件名称。若无名称则默认为"cow.obj"。
    
1. 通用按键
   1. 按下t键，可进行模式的切换，具体切换到的模式可以在控制台输出查看
      1. 没有处理按键抖动的情况，因此有时会出现切换不成功的情况
   2. 按下c键，可清空之前的所有操作，回到最初的状态
2. 操作模式（operating mode)
   1. 可以使用小键盘的方向键，对物体进行上下平移。
   2. 键盘的`j`，`k`键，可以让物体前后平移
   3. 可以使用鼠标拖动，实现物体的旋转
3. 探索模式（exploring mode)
   1. 鼠标移动直接带来视角的改变
   2. 键盘wasd四个键可以改变摄像机的水平位置。
   3. 键盘ui两键可以改变摄像机的高度。u键上升，i键下降。


## 4 程序运行截图

![](https://lh3.googleusercontent.com/-DOJJoTAZJbg/WxqZbK85EeI/AAAAAAAAIMU/61jwFznuLMgbXyQPXY_P9fknrd5eWmykQCHMYCw/s0/Snipaste_2018-06-08_22-57-50.png)

![](https://lh3.googleusercontent.com/-CCFj_RNzhvw/WxqZVWyyIRI/AAAAAAAAIMQ/UWaXkH7OESMu4n2Zr6kHJmMiUSzENi7NwCHMYCw/s0/Snipaste_2018-06-08_22-57-16.png)

## 5 程序运行录屏

录屏展示键盘鼠标操作对模型的影响，以及光源的影响。

可见作业目录下的`teapot.mp4`