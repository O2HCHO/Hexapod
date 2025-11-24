#ifndef GAIT_PLANNER_H
#define GAIT_PLANNER_H

#include "HexapodTypes.h"

/**
 * @brief 步态规划器的抽象基类
 * 所有的具体步态（三角、波浪等）都必须继承这个类
 */
class GaitPlanner {
public:
    GaitPlanner() {}
    virtual ~GaitPlanner() {}

    /**
     * @brief 初始化步态参数
     * @param step_height 抬腿高度 (mm)
     * @param cycle_time 单个步态周期的时间 (ms)
     */
    virtual void init(float step_height, unsigned long cycle_time) {
        this->step_height_ = step_height;
        this->cycle_time_ = cycle_time;
    }

    /**
     * @brief 计算当前时刻所有足尖的目标坐标
     * * @param current_time 当前系统时间 (ms)
     * @param cmd 当前的运动指令
     * @param leg_targets 输出参数：数组，存储6个腿的目标坐标(相对于各腿零点)
     */
    virtual void update(unsigned long current_time, GaitCommand cmd, Point3D leg_targets[6]) = 0; // 纯虚函数

protected:
    float step_height_;
    unsigned long cycle_time_;
};

#endif