#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"
#include "ros_tensorrt_bridge/assert.hpp"




TensorRTBridge::TensorRTBridge(TensorRTBridgeOptions options) : options_(options)
{
    ASSERT(!options_.model_path.empty(), "Model path cannot be empty");
    ASSERT(options_.model_type != ModelType::None, "Model type cannot be None");

    ModelBuilder *model_builder = new ModelBuilderScratch(options_);

}

void TensorRTBridge::infer(std::vector<cv::Mat> images)
{
    
}

void TensorRTBridge::infer(cv::Mat image)
{
    std::vector<cv::Mat> images;
    images.push_back(image);
    infer(images);
}

TensorRTBridge::~TensorRTBridge()
{
    std::cout << "TensorRTBridge destructor called" << std::endl;
}