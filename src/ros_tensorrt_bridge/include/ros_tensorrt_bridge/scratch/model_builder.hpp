#pragma once
#include "logging.h"
#include "cuda_utils.h"
#include "model.h"
#include "postprocess.h"
#include "preprocess.h"
#include "utils.h"

#include "ros_tensorrt_bridge/model_builder.hpp"

class ModelBuilderScratch : public ModelBuilder
{
public:
    explicit ModelBuilderScratch(const TensorRTBridgeOptions options) : ModelBuilder(options)
    {
        ASSERT(options_.model_path.ends_with(".wts") || options_.model_path.ends_with(".engine") ||
                options_.model_path.ends_with(".plan"),
                "Model path must be a .wts, .engine or .plan file for scratch conversion");
        //todo: Add other task types
        ASSERT(options_.task_type == TaskType::Pose, "Task is not supported for scratch conversion yet, only pose is supported currently");
        //todo: Add other optimization types
        ASSERT(options_.optimization_type == OptimizationType::FP16, "Optimization is not supported for scratch conversion yet, only FP16 is supported currently");
        //todo: Add other input types
        ASSERT(options_.input_type == InputType::Image, "Input type is not supported for scratch conversion yet, only image is supported currently");

        serialize_model();

    }

    ~ModelBuilderScratch() override;

    void infer() override;
    void convert() override;
    void build() override;

    


private:
    void serialize_model();
    Logger gLogger;
    const int kOutputSize = kMaxNumOutputBbox * sizeof(Detection) / sizeof(float) + 1;
};