#ifndef TRIPOD_GAIT_H
#define TRIPOD_GAIT_H

#include "GaitPlanner.h"
#include <math.h>

class TripodGait : public GaitPlanner {
public:
    // 实现父类的 update 方法
    void update(unsigned long current_time, GaitCommand cmd, Point3D leg_targets[6]) override {
        
        // 1. 计算在步态周期中的进度 (0.0 ~ 1.0)
        float progress = (float)(current_time % cycle_time_) / cycle_time_;

        // 2. 三角步态逻辑：将腿分为 A 组 (0, 2, 4) 和 B 组 (1, 3, 5)
        // 这里仅做演示：让 A 组抬起，B 组放下，模拟简单的上下运动
        
        for (int i = 0; i < 6; i++) {
            bool is_group_A = (i == 0 || i == 2 || i == 4);
            
            // 初始化为默认位置
            leg_targets[i].x = 0; 
            leg_targets[i].y = 0; 
            leg_targets[i].z = -cmd.body_height; // 负数表示向下

            // 简单的测试逻辑：
            // 如果是 A 组，且进度在前半段，则抬高 z 轴
            if (is_group_A) {
                 if (progress < 0.5) {
                     // 使用正弦波模拟平滑抬腿
                     leg_targets[i].z += sin(progress * 2 * PI) * step_height_; 
                 }
            } else {
                // B 组在后半段抬腿
                if (progress >= 0.5) {
                     leg_targets[i].z += sin((progress - 0.5) * 2 * PI) * step_height_;
                }
            }
            
            // 注意：真正的步态还需要计算 x 和 y 的位移（这是最复杂的数学部分）
            // 我们将在下一阶段完善这里
        }
    }
};

#endif