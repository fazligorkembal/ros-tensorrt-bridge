#include "ros_tensorrt_bridge/tensorrt_bridge.hpp"
#include <cassert>

TensorRTBridge::TensorRTBridge(TensorRTBridgeOptions options)
{

       // todo: add gpu_id, max_workspace, batchsize, if used add to camera_id etc..
       // todo: get subpackage path to auto localization

       // Device info
       deviceInfo();

       if (options.conversion_type == ConversionType::Automatic)
       {
              ASSERT(false, "Automatic conversion is not supported yet");
       }
       else if (options.conversion_type == ConversionType::Scratch)
       {
              yolo_scratch::BuildModel build_model(options);
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