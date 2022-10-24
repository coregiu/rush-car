# RUCAR
    利用51单片机、L298N电机驱动、PS2手柄、音乐芯片、PWM控制模块、DIY灯组和小车底盘DIY实现的PS2摇控小车，并且可以用PS2控制的音乐播放和流水灯。

## 功能说明
#### 遥控小车行驶
可通过PS2控制小车前进、后退、左转、右转。

#### 遥控音乐播放及切换
可通过PS2控制轩载音乐播放，音乐更换。

#### 遥控LED灯光效果切换
可通过PS2控制小车顶LED灯光开关和切换。
灯光效果可以有常亮、间隔闪烁等效果。



## 设计说明

#### 硬件设计

![](hardware/integrate_archetecture.png)

详细参照：[硬件设计说明](hardware/README.md)



#### 软件设计

![](software/class_design.png)

详细参照：[软件设计说明和代码](software/README.md)



## 成品效果



敬请期待...



## 使用的相关工具软件：

#### OS： Ubuntu 20.04



#### 硬件设计工具KiCAD

安装：https://docs.kicad.org/5.1/zh/getting_started_in_kicad/getting_started_in_kicad.html



#### 软件设计开发工具:

- 软件设计工具： StarUML  https://staruml.io/download

- 开发IDE： VSCODE

- 编译软件： sdcc/packihx, cmake

ubuntu下安装： sudo apt-get install sdcc

- 烧录软件：stcflash

ubuntu下安装： 从社区下载到本地，社区地址：https://github.com/laborer/stcflash

将stcflash.py文件解压到/usr/local/bin。 并去掉后缀名。

- 依赖： python3, python-pip3, python serial

安装python serial: https://www.geeksforgeeks.org/how-to-install-python-serial-package-on-linux/

如果执行: stcflash报错： usr/bin/env: ‘python’: No such file or directory

执行以下命令解决： sudo ln -s /usr/bin/python3 /usr/bin/python

- 串口调试工具： comtool

安装： sudo pipe3 install comtool
