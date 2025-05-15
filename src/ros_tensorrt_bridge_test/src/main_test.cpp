#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"
#include "ros_tensorrt_bridge/tracker/trackerlib.hpp"

int main(int argc, char **argv)
{
    Tracker tracker;

    TensorRTBridgeOptions options(
        "/home/user/Documents/ros_tensorrt_bridge/build/yolo11n-pose.wts",
        ModelType::Yolo11n,
        ConversionType::Scratch,
        TaskType::Pose,
        OptimizationType::FP16,
        InputType::Image);

    TensorRTBridge tensorrt_bridge(options);

    cv::Mat image = cv::imread("/home/user/Documents/ros_tensorrt_bridge/src/ros_tensorrt_bridge/yolo-tensorrt10/input_samples/test_input.jpg");
    if (image.empty())
    {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<cv::Mat> images;
    std::vector<std::vector<Detection>> res_batch;
    images.push_back(image);
    for (int i = 0; i < 15000; ++i)
    {
        tensorrt_bridge.infer(images, res_batch);
        tracker.track_from_scratch(images[0], res_batch);
    }

    std::cout << "Time taken for 15000 iterations: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::high_resolution_clock::now() - start_time)
                     .count()
              << " ms" << std::endl;
    std::cout << "FPS: " << 15000.0 / (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1000.0)
              << std::endl;

            

    /*
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }
    cv::Mat frame;
    // std::vector<std::vector<Detection>> res;
    std::vector<cv::Mat> images;
    std::vector<std::vector<Detection>> res;

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
            // res[0].clear();
        }
        else
        {
            images.push_back(frame);
        }

        tensorrt_bridge.infer(images, res);
        tracker.track_from_scratch(images[0], res);

        //cv::imshow("Camera", images[0]);
        //if (cv::waitKey(1) == 27) // Press 'Esc' to exit
        //    break;
    }
    */

    return 0;
}