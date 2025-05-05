#pragma once
#include <iostream>
#include "ros_tensorrt_bridge/utils.hpp"

class RosTensorRTBridge
{
public:
    RosTensorRTBridge(std::string model_path, ConvertType convert_type, OptimizationType optimization_type, TaskType task_type, InputType input_type);
    ~RosTensorRTBridge();
};
