#pragma once
#include <fstream>
#include <string>
#include <iostream>

#include "ros_tensorrt_bridge/yolo_scratch/cuda_utils.hpp"
#include "ros_tensorrt_bridge/yolo_scratch/logging.hpp"
#include "ros_tensorrt_bridge/utils.hpp"
#include "ros_tensorrt_bridge/yolo_scratch/model.hpp"

using namespace nvinfer1;

namespace yolo_scratch
{
    class BuildModel
    {
    public:
        BuildModel(const TensorRTBridgeOptions &options);
        ~BuildModel() {}

        void parse_parameters(std::string &type, float &gd, float &gw, int &max_channels);
        void serialize_engine(std::string &engine_path);
        void deserialize_engine(std::string &engine_path, IRuntime **runtime, ICudaEngine **engine);

    private:
        const TensorRTBridgeOptions &mOptions;
        IRuntime *runtime = nullptr;

        IExecutionContext *context = nullptr;
        cudaStream_t stream;
    };
}