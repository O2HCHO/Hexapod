#include <Arduino.h>
#include "HexapodTypes.h"
#include "TripodGait.h" // 引用具体的步态库

// 1. 实例化步态对象
// 使用基类指针指向子类对象，这是多态的精髓
GaitPlanner* gait = new TripodGait();

// 2. 定义存储计算结果的数组
Point3D current_leg_targets[6];

// 3. 模拟一个指令
GaitCommand current_cmd = {0, 0, 0, 100.0}; // 原地不动，身高100mm

void setup() {
    Serial.begin(115200);

    // 初始化步态：抬腿高度 30mm，周期 1000ms (1秒一步)
    gait->init(30.0, 1000);

    Serial.println("Hexapod Gait System Initialized.");
}

void loop() {
    unsigned long now = millis();

    // 更新步态计算
    gait->update(now, current_cmd, current_leg_targets);

    // 打印调试信息 (观察第一条腿的 Z 轴变化)
    // 可以在 VSCode 的串口绘图器 (Serial Plotter) 中看到波形
    Serial.print("Time:");
    Serial.print(now);
    Serial.print(" Leg0_Z:");
    Serial.println(current_leg_targets[0].z);

    delay(10); // 模拟 100Hz 的控制频率
}