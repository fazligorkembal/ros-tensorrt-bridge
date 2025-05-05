#include "ros_tensorrt_bridge/ros_tensorrt_bridge.hpp"

int main(int argc, char **argv)
{
    // Create an instance of RosTensorRTBridge
    RosTensorRTBridge bridge("model_path", ConvertType::Automatic, OptimizationType::FP16, TaskType::Detection, InputType::Image);
    // Test the constructor and destructor
    std::cout << "Testing RosTensorRTBridge..." << std::endl;

    return 0;
}