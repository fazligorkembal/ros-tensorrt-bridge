#pragma once
#include <filesystem>
#include <iostream>
#include <string>

#define ASSERT(condition, message)                                                       \
    do                                                                                   \
    {                                                                                    \
        if (!(condition))                                                                \
        {                                                                                \
            std::cerr << "\n\nAssertion failed: " << message << "\n\t\t  " << #condition \
                      << ", file " << __FILE__ << ", line " << __LINE__ << std::endl;    \
            std::exit(EXIT_FAILURE);                                                     \
        }                                                                                \
    } while (false)

enum class ModelType
{
    None,
    Yolo11n,
    Yolo11s,
    Yolo11m,
    Yolo11l,
    Yolo11x

};

enum class TaskType
{
    None,
    Detection,
    Segmentation,
    Classification,
    Pose,
    Obb
};

enum class ConversionType
{
    None,
    Scratch,
    Automatic
};

enum class OptimizationType
{
    None,
    FP16,
    INT8,
    FP32
};

enum class InputType
{
    None,
    Image,
    ImageFolder,
    Video,
    VideoStream
};

class TensorRTBridgOptions
{
public:
    std::string model_path = "";
    ModelType model_type = ModelType::None;
    ConversionType conversion_type = ConversionType::None;
    TaskType task_type = TaskType::None;
    OptimizationType optimization_type = OptimizationType::None;
    InputType input_type = InputType::None;

    TensorRTBridgOptions(std::string model_path,
                         ModelType model_type,
                         ConversionType conversion_type,
                         TaskType task_type,
                         OptimizationType optimization_type,
                         InputType input_type)
        : model_path(model_path),
          model_type(model_type),
          conversion_type(conversion_type),
          task_type(task_type),
          optimization_type(optimization_type),
          input_type(input_type)
    {
    }
};

bool isFileExist(const std::string &filePath)
{
    return std::filesystem::exists(filePath);
}

// todo: Add output type enum