## 整体设计

![](integrate_archetecture.png)



## 模块说明

#### 小车底盘
<img src="modules/car.jpg" style="zoom:70%;" />

外购小车底盘带直流电机。


#### 控制模块
<img src="modules/stc89c52rc.jpg" style="zoom: 67%;" />

使用51单片机（STC89C52RC）作为控制中心，其中P0口控制LED灯，与自带LED灯反向； P2.0-P2.5 为电机控制口，P2.6-P2.7 控制音乐开关和更换。P1.4-P1.7为PS2通信口。
晶振频率：11.0592

| GPIO | 连接口            | 初始值  | 说明     |
| ---- | ----------------- | ------- | -------- |
| P0_0 | LED1              | 1       |          |
| P0_1 | LED2              | 1       |          |
| P0_2 | LED3              | 1       |          |
| P0_3 | LED4              | 1       |          |
| P0_4 | LED5              | 1       |          |
| P0_5 | LED6              | 1       |          |
| P0_6 | LED7              | 1       |          |
| P0_7 | LED8              | 1       |          |
| P2_0 | L298N_EnB         | 0       |          |
| P2_1 | L298N_IN4         | 0       |          |
| P2_2 | L298N_IN3         | 0       |          |
| P2_3 | L298N_EnA         | 0       |          |
| P2_4 | L298N_IN2         | 0       |          |
| P2_5 | L298N_IN1         | 0       |          |
| P2_6 | FLM038A-SOP8_PLAY | 0       | 音乐开关 |
| P2_7 | FLM038A-SOP8_NEXT | 0       | 音乐更换 |
| P1_4 | PS2_D1/DATA       | default |          |
| P1_5 | PS2_D0/CMD        | default |          |
| P1_6 | PS2_CS            | default |          |
| P1_7 | PS2_CLK           | default |          |



#### 电机驱动模块
<img src="modules/L298N.png" style="zoom:60%;" />

使用L98N电机驱动，左右轮分两组控制。分两组控制电机，左、右轮各用一组控制。

12V输入电压，5V输出电压为控制单板、音乐板、LED灯、PS2通信模块供电。



#### 遥控通信模块

<img src="modules/ps2.jpg" style="zoom:50%;" />

使用PS2通信模块进行遥控。控制键说明：

| 按键        | 功能            | 控制端口     |
| ----------- | --------------- | ------------ |
| 左侧上键    | 小车前进        | 电机驱动端口 |
| 左侧下键    | 小车后退        | 电机驱动端口 |
| 左侧左键    | 左转            | 电机驱动端口 |
| 左侧右键    | 右转            | 电机驱动端口 |
| 右侧上健    | 音乐开关        | P2_6         |
| 右侧右键    | 音乐更换        | P2_7         |
| 右侧左/下键 | LED闪烁效果更换 | P0           |



#### 音乐模块

<img src="modules/flm038-sop8-body.jpg" style="zoom:70%;" />

<img src="modules/flm038-sop8-board.jpg" style="zoom:70%;" />

使用FLM038A-SOP8音乐芯片，通过P2_6, P2_7控制音乐开关和更换。 其中开关和更换使用两个PWM控制模块，如下图。都是高电平时开关打开。



#### PWM控制模块

配合音乐模块使用，实现音乐开关和切换。（开关和切换分别使用一个独立模块）

<img src="modules/pwm_mos.jpg" style="zoom:60%;" />

#### LED灯组模块

 两组灯，一组是车顶LED灯（8个），用P0控制。 一组是车头灯（前后左右共4个），常亮。车顶LED灯与单板自带LED灯反向。