# Tuya_DesktopAssistant
基于涂鸦智能WIFI模块的桌面助手，MCU开发

## Readme
This project is developed using T uya SDK, which enables you t o quickly develop branded
apps connect ing and cont rolling smart scenarios of many devices.
For more inf ormat ion, please check T uya Developer Websit e.

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

屏幕采用迪文科技03W，采用DGUS开发，现已完成相关界面的部分开发。主界面如图，其他界面暂不放出。
![Image 3.png](//image.lceda.cn/pullimage/joxN5CBLxzKx6gykXDegQpIjnz82ehvaODJT7tdW.png)

## 手机端APP开发

待完善。。。。

## 相关渲染图

![TUYA.jpg](https://github.com/justp7/Tuya_DesktopAssistant/tree/main/Img/PCB.png)
![镜面.png](https://github.com/justp7/Tuya_DesktopAssistant/blob/main/Img/NewYear.png)
