#pragma once
#include "logging.h"
#include "cuda_utils.h"
#include "model.h"
#include "postprocess.h"
#include "preprocess.h"
#include "utils.h"

#include "ros_tensorrt_bridge/model_builder.hpp"

using namespace nvinfer1;

class ModelBuilderScratch : public ModelBuilder
{
public:
    explicit ModelBuilderScratch(const TensorRTBridgeOptions options) : ModelBuilder(options)
    {
        ASSERT(options_.model_path.ends_with(".wts") || options_.model_path.ends_with(".engine") ||
                   options_.model_path.ends_with(".plan"),
               "Model path must be a .wts, .engine or .plan file for scratch conversion");
        // todo: Add other task types
        ASSERT(options_.task_type == TaskType::Pose || options_.task_type == TaskType::Segmentation, "Task is not supported for scratch conversion yet, only pose or segmentation are supported currently");
        // todo: Add other optimization types
        ASSERT(options_.optimization_type == OptimizationType::FP16, "Optimization is not supported for scratch conversion yet, only FP16 is supported currently");
        // todo: Add other input types
        ASSERT(options_.input_type == InputType::Image, "Input type is not supported for scratch conversion yet, only image is supported currently");

        std::string wts_path = options_.model_path;
        std::string engine_path = wts_path.substr(0, wts_path.find_last_of('.')) + ".engine";

        if (options_.model_path.ends_with(".wts"))
        {
            if (std::filesystem::exists(engine_path))
            {
                std::cout << "Engine file already exists, skipping conversion" << std::endl;
            }
            else
            {
                std::string type;
                float gd = 0.0f;
                float gw = 0.0f;
                int max_channels = 0;

                parse_options(type, gd, gw, max_channels);

                serialize_engine(wts_path, engine_path, type, gd, gw, max_channels);
            }
        }
        else if (options_.model_path.ends_with(".engine") || options_.model_path.ends_with(".plan"))
        {
            engine_path = options_.model_path;
        }
        else
        {
            ASSERT(false, "Model path must be a .wts, .engine or .plan file for scratch conversion");
        }

        deserialize_engine(engine_path);
        prepare_buffer(options_.task_type);
    }

    ~ModelBuilderScratch() override;

    void infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch) override;
    void infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch, std::vector<cv::Mat> &masks) override;
    void convert() override;
    void build() override;

private:
    void serialize_engine(std::string &wts_name, std::string &engine_path, std::string &type, float &gd, float &gw, int &max_channels);
    void deserialize_engine(std::string &engine_path);
    void parse_options(std::string &type, float &gd, float &gw, int &max_channels);
    void prepare_buffer(TaskType task_type);
    std::vector<cv::Mat> process_mask(const float *proto, int proto_size, std::vector<Detection> &dets);

    Logger gLogger;
    const int kOutputSize = kMaxNumOutputBbox * sizeof(Detection) / sizeof(float) + 1;
    const int kOutputSegSize = 32 * (kInputH / 4) * (kInputW / 4);

    IRuntime *runtime = nullptr;
    ICudaEngine *engine = nullptr;
    IExecutionContext *context = nullptr;
    cudaStream_t stream;

    int batch_size = 0;
    float *device_buffers[3];
    float *output_buffer_host = nullptr;
    float *output_seg_buffer_host = nullptr;
    float *decode_ptr_host = nullptr;
    float *decode_ptr_device = nullptr;
    std::unordered_map<int, std::string> labels_map;
};