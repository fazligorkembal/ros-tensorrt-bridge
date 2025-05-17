#pragma once

#include <fstream>
#include "ros_tensorrt_bridge/utils.hpp"
#include "ros_tensorrt_bridge/assert.hpp"

class ModelBuilder
{
public:
    // todo: Add here to output type
    explicit ModelBuilder(const TensorRTBridgeOptions options) : options_(options)
    {
        ASSERT(!options_.model_path.empty(), "Model path cannot be empty");
        ASSERT(std::filesystem::exists(options_.model_path) && std::filesystem::is_regular_file(options_.model_path), "Model path must be full-path and a valid file");
        ASSERT(options_.model_type != ModelType::None, "Model type cannot be None, please check available model types in include/utils.hpp");
        ASSERT(options_.conversion_type != ConversionType::None, "Conversion type cannot be None, please check available conversion types in include/utils.hpp");
        ASSERT(options_.task_type != TaskType::None, "Task type cannot be None, please check available task types in include/utils.hpp");
        ASSERT(options_.optimization_type != OptimizationType::None, "Optimization type cannot be None, please check available optimization types in include/utils.hpp");
        ASSERT(options_.input_type != InputType::None, "Input type cannot be None, please check available input types in include/utils.hpp");
    }

    virtual ~ModelBuilder() = default;

    virtual void build() = 0;
    virtual void infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch) = 0;
    virtual void infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch, std::vector<cv::Mat> &masks) = 0;
    virtual void convert() = 0;

protected:
    TensorRTBridgeOptions options_;
};