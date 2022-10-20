# RUCAR
    利用51单片机、L298N驱动、PS2手柄和DIV小车实现的摇控音乐闪灯小车。

## 功能说明
#### 遥控小车行驶
可通过PS2控制小车前进、后退、左转、右转。

#### 遥控音乐播放及切换
可通过PS2控制轩载音乐播放，音乐更换。

#### 遥控LED灯光效果切换
可通过PS2控制小车顶LED灯光变换。
灯光效果有常亮、跑马灯、间隔闪烁、互切、关闭等效果。



## 设计说明

#### 硬件设计

![](hardware/integrate_archetecture.png)

详细参照：[硬件设计说明](hardware/design.md)



#### 软件设计

![](software/class_design.png)

详细参照：[软件设计说明和代码](software/design.md)



## 成品效果



敬请期待...



## 使用的相关软件：

#### 硬件设计工具KiCAD

安装：https://docs.kicad.org/5.1/zh/getting_started_in_kicad/getting_started_in_kicad.html

#### 软件设计工具StarUML:

https://staruml.io/download

#### 软件开发相关软件
OS： Ubuntu 20.04
开发IDE： VSCODE
编译软件： sdcc/packihx
ubuntu下安装： sudo apt-get install sdcc

烧录软件：stcflash
ubuntu下安装： 从社区下载到本地，社区地址：https://github.com/laborer/stcflash
将stcflash.py文件解压到/usr/local/bin。 并去掉后缀名。
依赖： python3, python-pip3, python serial

安装python serial: https://www.geeksforgeeks.org/how-to-install-python-serial-package-on-linux/

如果执行: stcflash报错： usr/bin/env: ‘python’: No such file or directory
执行以下命令解决： sudo ln -s /usr/bin/python3 /usr/bin/python

串口调试工具： comtool
安装： sudo pipe3 install comtool
运行： sudo comtool

#### 编译烧录：

第一步，编译：
$sudo sdcc led_basic.c -o led_basic.ihx

第二步，转换成可烧录的hex文件：
$packihx led_basic.ihx > led_basic.hex

第三步，烧录文件到MCU：
$sudo stcflash led_basic.hex 

此命令会自动寻找USB口发命令。如果有多个USB口，需要指定相应端口。
$sudo stcflash led_basic.hex --port /dev/ttyUSB0



#### PS2通讯说明：
购买PS2后老板都会发教程和代码的。