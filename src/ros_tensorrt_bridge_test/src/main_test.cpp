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
        
    cv::Mat image = cv::imread("/home/user/Documents/ros_tensorrt_bridge/images/original.jpg");
    cv::resize(image, image, cv::Size(640, 640));


    if (image.empty())
    {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }
    /*
    auto start = std::chrono::system_clock::now();
    for(int i = 0; i < 15000; ++i)
    {
        tensorrt_bridge.infer(image);
    }
    auto end = std::chrono::system_clock::now();
    std::cout << "Time taken for 15000 inferences: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::cout << "FPS: " << 15000.0 / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 1000 << std::endl;
    std::cout << "Inference completed" << std::endl;

    cv::imshow("Image", image);
    cv::waitKey(0);
    */


    
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }
    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            std::cerr << "Failed to capture frame" << std::endl;
            break;
        }
        cv::resize(frame, frame, cv::Size(640, 640));
        tensorrt_bridge.infer(frame);
        cv::imshow("Camera", frame);
        if (cv::waitKey(1) == 27) // Press 'Esc' to exit
            break;
    }



    return 0;
}