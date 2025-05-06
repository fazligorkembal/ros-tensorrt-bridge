#pragma once
#include <iostream>

#include "ros_tensorrt_bridge/utils.hpp"
#include "ros_tensorrt_bridge/kernels/deviceInfo.hpp"
//#include "ros_tensorrt_bridge/model_generator_automatic.hpp"

class TensorRTBridge
{
public:
    TensorRTBridge(TensorRTBridgOptions options);
    ~TensorRTBridge();
};
