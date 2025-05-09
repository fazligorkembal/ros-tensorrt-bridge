#include <iostream>
#include <vector>

#include "ros_tensorrt_bridge/utils.hpp"
#include <opencv2/opencv.hpp>



class TensorRTBridge
{
public:
    TensorRTBridge(TensorRTBridgeOptions options);
    ~TensorRTBridge();
    void infer(std::vector<cv::Mat> images);
    void infer(cv::Mat image);


private:
    TensorRTBridgeOptions options_;
    
};