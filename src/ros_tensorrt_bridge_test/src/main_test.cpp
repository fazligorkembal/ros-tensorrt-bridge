#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"

int main(int argc, char **argv)
{
    TensorRTBridgeOptions options(
        "/home/user/Documents/ros_tensorrt_bridge/build/yolo11n-pose.wts",
        ModelType::Yolo11n,
        ConversionType::Scratch,
        TaskType::Pose,
        OptimizationType::FP16,
        InputType::Image);
        
    TensorRTBridge tensorrt_bridge(options);
    
    return 0;
}