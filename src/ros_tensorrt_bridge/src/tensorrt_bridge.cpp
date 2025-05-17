#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"
#include "ros_tensorrt_bridge/assert.hpp"

TensorRTBridge::TensorRTBridge(TensorRTBridgeOptions options) : options_(options)
{
    ASSERT(!options_.model_path.empty(), "Model path cannot be empty");
    ASSERT(options_.model_type != ModelType::None, "Model type cannot be None");

    model_builder = new ModelBuilderScratch(options_);
}

void TensorRTBridge::infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch)
{
    res_batch.clear();
    model_builder->infer(images, res_batch);
}

void TensorRTBridge::infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch, std::vector<cv::Mat> &masks)
{
    res_batch.clear();
    masks.clear();
    model_builder->infer(images, res_batch, masks);
}

TensorRTBridge::~TensorRTBridge()
{
    std::cout << "TensorRTBridge destructor called" << std::endl;
}