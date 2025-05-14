#include <iostream>
#include <vector>

#include "ros_tensorrt_bridge/utils.hpp"
#include <opencv2/opencv.hpp>

#include "ros_tensorrt_bridge/scratch/model_builder.hpp"

class TensorRTBridge
{
public:
    TensorRTBridge(TensorRTBridgeOptions options);
    ~TensorRTBridge();
    
    void infer(std::vector<cv::Mat> &images);
    void infer(std::vector<cv::Mat> &images, std::vector<std::vector<Detection>> &res_batch);
    void infer(cv::Mat &image);
    void infer(cv::Mat &image, std::vector<Detection> &res);


private:
    TensorRTBridgeOptions options_;
    ModelBuilder *model_builder = nullptr;
};