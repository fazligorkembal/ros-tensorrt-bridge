#include <iostream>
#include "ros_tensorrt_bridge/utils.hpp"

class TensorRTBridge
{
public:
    TensorRTBridge(TensorRTBridgeOptions options);
    ~TensorRTBridge();

private:
    TensorRTBridgeOptions options_;
};