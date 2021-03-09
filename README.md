# Tuya_DesktopAssistant

基于涂鸦智能WIFI模块的桌面助手，MCU开发

## Readme

This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

## 相关地址🔗

[硬件开源地址](https://oshwhub.com/LC717863696/wen-shi-du-zhuo-mian-zhu-shou) 

[功能演示地址](https://www.bilibili.com/video/BV1ky4y1a7U3)

## 功能介绍 💻

### 天气获取显示 🌻

通过涂鸦SDK天气接口，获取天气信息并解析。天气信息每半小时下发一次。

### 设备操控 💡

通过涂鸦设备联动功能，即可实现对涂鸦所有设备的操作功能。本项目测试使用的是涂鸦智能灯💡，可实现开关💡，模式设置等功能。

### 电脑状态显示 💻

通过python上位机获取电脑CPU、内存、网络运行情况，通过蓝牙串口发送到桌面端，进行解析显示。

### 温湿度获取 📈

温湿度通过SHT30进行测量，STM32定时检测，检测完成后将数据上报云平台。

### 备忘设置 📃

通过电脑pythn上位机可进行4条备忘设置，支持修改完成/未完成情况。

### 游戏界面 🎰

通过开源的Vousforte软件，通过蓝牙串口将数据发送到桌面端，桌面端获取数据后进行解析，解析后显示在屏幕上。

## 上位机功能

### python自开发

通过python开发电脑上位机，获取电脑内存、网速、CPU使用、备忘设置，主要适配办公场景，主要界面如下：
![Image.png](https://github.com/justp7/Tuya_DesktopAssistant/blob/main/Img/python.png)

### 开源软件Vousforte

电脑软件信息获取更加全面，增加了CPU和GPU温度等内容，无法进行备忘设置功能，将会适配游戏显示界面。主界面如下：
![Image 2.png](https://github.com/justp7/Tuya_DesktopAssistant/blob/main/Img/Vousforte.png)

## 板载功能

### 涂鸦WB3S模块

通过WB3S模块与涂鸦IOT平台进行通讯，获取天气、时间等信息；控制家庭设备；温湿度上报；OTA升级。

### JDY-31蓝牙模块

通过蓝牙模块与电脑建立蓝牙连接，通过蓝牙串口进行电脑数据的透传，在屏幕上进行显示。

### SHT30

获取环境温湿度并上报到云端，并在屏幕上进行显示。

### TEMP6000

获取环境亮度并进行屏幕的自动亮度调节。

### NT3H1101 NFC模块

通过IIC接口进行数据通讯，预计功能是实现上下班打卡。待完善。。

## 屏幕开发

屏幕采用迪文科技03W，采用DGUS开发，现已完成相关界面的部分开发。



## 相关渲染图

![TUYA.jpg](https://github.com/justp7/Tuya_DesktopAssistant/blob/main/Img/PCB.png)
![镜面.png](https://github.com/justp7/Tuya_DesktopAssistant/blob/main/Img/NewYear.png)
