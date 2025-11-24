// include/HexapodTypes.h
#ifndef HEXAPOD_TYPES_H
#define HEXAPOD_TYPES_H

#include <Arduino.h>

// 定义一个通用的 3D 坐标结构体
struct Point3D {
    float x;
    float y;
    float z;
};

// 定义机器人的六条腿的索引
enum LegIndex {
    RIGHT_FRONT = 0,
    RIGHT_MIDDLE = 1,
    RIGHT_BACK = 2,
    LEFT_FRONT = 3,
    LEFT_MIDDLE = 4,
    LEFT_BACK = 5
};

// 定义步态指令结构体 (从遥控器发来的指令)
struct GaitCommand {
    float velocity_x;     // 前后速度 (mm/s)
    float velocity_y;     // 左右平移速度 (mm/s)
    float angular_z;      // 自转速度 (rad/s)
    float body_height;    // 机身高度 (mm)
};

#endif