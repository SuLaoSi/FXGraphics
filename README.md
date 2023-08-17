# FXGraphics

### 简介

我的个人图形仓库，用于日常编码练习和OpenGL功能测试。基于glfw3与glad开发，为简单的OpenGL应用提供支持

### 要求

OpenGL 4.3+ 

（OpenGL 4.3发布于2012年，这之后发布的显卡应当都支持，你可以通过显卡驱动程序查看你的OpenGL版本）

### 构建项目

首先，你需要拉取代码到本地

如果你安装了Git或其他版本管理工具，可以通过克隆的方式获取代码，如

    git clone https://github.com/SuLaoSi/FXGraphics.git

否则，你需要通过下载压缩包等方式将代码下载到本地

之后，你需要构建项目

如果你安装了CMake (3.12+)与Git，可以双击运行FXGraphics/build.sh，或是在FXGraphics文件夹中执行指令：

    ./build.sh

会自动创建FXGraphics/build文件夹并使用CMake生成解决方案。

否则，请自行创建工作空间。仓库提供了较为完善的CMake文件，推荐使用CMake构建项目

### 运行

FXGraphics默认编译成dll库

为方便运行，我在仓库中添加了FXMain项目，它会被编译成为exe文件，并链接了其他仓库，你可以直接在FXMain中修改代码并运行

或者你可以将FXGraphics作为子文件夹加入到你的项目中，或是直接使用编译得到的dll库，如果是这样你可以删除FXMain

所有编译结果会输出到FXGraphics/bin文件夹中

### 注意事项

此项目的只是为了简化OpenGL的绘制流程，并不是完备的图形系统，要求使用者有一定的OpenGL基础（包括基本绘制流程、shader编写、矩阵运算等）

在release模式下我设置了隐藏控制台，可以在顶级的CMake文件中找到并修改

### 依赖

- [glfw3](https://www.glfw.org/)
- [glad](https://github.com/Dav1dde/glad)
- [freetype2](https://freetype.org/)
- [glm](https://github.com/g-truc/glm) 
