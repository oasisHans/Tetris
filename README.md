# Tetris (OOP Version)

这是一个基于 C++ 面向对象思想开发的俄罗斯游戏。

## 功能特点

- 完整的面向对象架构 (Manager-Block-Map-Render-Input)
- 状态机驱动 (支持 Start、Playing、GameOver 状态切换)
- 现代极简风格 (白色背景、无网格线设计、全英文 UI 界面)
- 极致操控体验 (支持平滑移动、加速下落及空格瞬间坠底)
- 专业随机系统 (基于 std::mt19937 梅森旋转算法生成方块)

## 环境依赖

- 编译器：MinGW (支持 C++11)
- 图形库：EasyX for MinGW
- 构建工具：CMake

## 如何编译

1. 确保安装了 EasyX 并在 CMakeLists.txt 中配置好路径。
2. 创建 build 目录：`mkdir build && cd build`
3. 执行 CMake：`cmake ..`
4. 编译：`mingw32-make`

developer : oasisHans
