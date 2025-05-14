#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"

int main(int argc, char **argv)
{
    TensorRTBridgeOptions options(
        "/home/user/Documents/ros_tensorrt_bridge/build/yolo11n-pose.wts",
        ModelType::Yolo11n,
        ConversionType::Scratch,
        TaskType::Pose,
        OptimizationType::FP16,
        InputType::Image);
        
    TensorRTBridge tensorrt_bridge(options);
    
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }
    cv::Mat frame;
    //std::vector<std::vector<Detection>> res;
    std::vector<cv::Mat> images;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            std::cerr << "Failed to capture frame" << std::endl;
            break;
        }
        cv::resize(frame, frame, cv::Size(640, 640));
        if (images.size() > 0)
        {
            images[0] = frame;
            //res[0].clear();
        }else{
            images.push_back(frame);
        }


        tensorrt_bridge.infer(images);
        //std::cout << "Res size: " << res[0].size() << std::endl;

        
        cv::imshow("Camera", frame);
        if (cv::waitKey(1) == 27) // Press 'Esc' to exit
            break;
        
    }



    return 0;
}