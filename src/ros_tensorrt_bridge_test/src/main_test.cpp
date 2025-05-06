#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"

int main(int argc, char **argv)
{
    // Create an instance of RosTensorRTBridge

    TensorRTBridgOptions options(
        "/home/user/Documents/ros_tensorrt_bridge/install/yolo11n-pose.wts",
        ModelType::Yolo11n,
        ConversionType::Scratch,
        TaskType::Pose,
        OptimizationType::FP32,
        InputType::Image);
    TensorRTBridge tensorrt_bridge(options);
    // Test the constructor and destructor
    // std::cout << "Testing RosTensorRTBridge..." << std::endl;

    return 0;
}