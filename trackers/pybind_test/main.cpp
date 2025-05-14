#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <array>

#include <pybind11/embed.h> // Python yorumlayıcısını gömmek için
#include <pybind11/numpy.h>



namespace py = pybind11;


struct Detection {
    float* conf;      // Güven skorları dizisi
    float* class_id;  // Sınıf ID'leri dizisi
    size_t size;      // Dizi boyutu (eklemek zorundayız)
};





int main()
{
    py::scoped_interpreter guard{};
    
    cv::Mat image = cv::imread("/home/user/Documents/ros_tensorrt_bridge/src/ros_tensorrt_bridge/yolo-tensorrt10/input_samples/test_input.jpg");
    cv::imshow("Image CPP", image);
    cv::waitKey(0);

    py::array_t<uint8_t> img_array(
        {image.rows, image.cols, image.channels()},
        {static_cast<size_t>(image.step[0]), static_cast<size_t>(image.step[1]), static_cast<size_t>(image.elemSize1())},
        image.data);    
    
    
    
    std::filesystem::path parent_path = std::filesystem::current_path().parent_path();
    
    py::module_ sys_module = py::module_::import("sys");
    sys_module.attr("path").attr("append")(parent_path.string());
    py::module_ convert_module = py::module_::import("convert_module");
    py::object convert_grey = convert_module.attr("convert_grey");
    

    Detection detection_obj;
    detection_obj.size = 400;
    detection_obj.conf = new float[detection_obj.size];
    detection_obj.class_id = new float[detection_obj.size];
    for (size_t i = 0; i < detection_obj.size; ++i) {
        detection_obj.conf[i] = static_cast<float>(i);
        detection_obj.class_id[i] = static_cast<float>(i);
    }

    convert_grey(img_array, detection_obj);
    



    return 0;
}