#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"
#include <cassert>

TensorRTBridge::TensorRTBridge(TensorRTBridgOptions options)
{

    // todo: add gpu_id, max_workspace, batchsize, if used add to camera_id etc..
    // todo: get subpackage path to auto localization

    ASSERT(isFileExist(options.model_path),
           "Model file does not exist: " + options.model_path);

    // todo: add upcoming models here
    ASSERT(options.model_type != ModelType::None,
           "Model type is not set, available types: Yolo11n, Yolo11s, Yolo11m, Yolo11l, Yolo11x");

    ASSERT(options.conversion_type != ConversionType::None,
           "Conversion type is not set, available types: Scratch, Automatic");

    ASSERT(options.input_type != InputType::None,
           "Input type is not set, available types: Image, ImageFolder, Video, VideoStream");

    ASSERT(options.optimization_type != OptimizationType::None,
           "Optimization type is not set, available types: FP16, INT8, FP32");

    // Device info
    deviceInfo();


    if(options.conversion_type == ConversionType::Automatic)
    {
        ASSERT(false, "Automatic conversion is not supported yet");
    }
    else if(options.conversion_type == ConversionType::Scratch)
    {
        std::cout << "This is a Scratch model" << std::endl;

    }

    /*
        ASSERT(options.model_path.ends_with(".wts") || options.model_path.ends_with(".engine"),
               "Model file must be .wts or .engine for Yolo11n_Pose_Scratch, but got: " + options.model_path);

        // todo: add other optimization types
        ASSERT(options.optimization_type == OptimizationType::FP16,
               "Only FP16 optimization is supported for Yolo11n_Pose_Scratch currently, but got: " + std::to_string(static_cast<int>(options.optimization_type)));
    */
    
}

TensorRTBridge::~TensorRTBridge()
{
    std::cout << "TensorRTBridge destructor called" << std::endl;
}