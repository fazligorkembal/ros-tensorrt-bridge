#include "ros_tensorrt_bridge/ros_tensorrt_bridge.hpp"
#include <cassert>


RosTensorRTBridge::RosTensorRTBridge(std::string model_path, ConvertType convert_type, OptimizationType optimization_type, TaskType task_type, InputType input_type)
{

    // todo: add gpu_id, max_workspace, batchsize, if used add to camera_id etc..
    
    assert(convert_type == ConvertType::Automatic && "ConvertType must be automatic. Scratch is not supported yet.");
    assert(optimization_type == OptimizationType::FP16 && "OptimizationType must be FP16. INT8 and FP32 are not supported yet.");
    assert(task_type == TaskType::Detection && "TaskType must be Detection. Classification, Segmentation, Pose_estimation, and Obb are not supported yet.");
    assert(input_type == InputType::Image && "InputType must be Image. Video, Camera, and File are not supported yet.");   
    
    
}

RosTensorRTBridge::~RosTensorRTBridge()
{
    std::cout << "RosTensorRTBridge destructor called" << std::endl;
}