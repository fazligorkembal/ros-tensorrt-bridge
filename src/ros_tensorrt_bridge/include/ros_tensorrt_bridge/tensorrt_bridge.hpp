#pragma once
#include <iostream>

#include "ros_tensorrt_bridge/utils.hpp"
#include "ros_tensorrt_bridge/kernels/deviceInfo.hpp"
#include "ros_tensorrt_bridge/yolo_scratch/model_generator.hpp"

class TensorRTBridge
{
public:
    TensorRTBridge(TensorRTBridgeOptions options);
    ~TensorRTBridge();
};
