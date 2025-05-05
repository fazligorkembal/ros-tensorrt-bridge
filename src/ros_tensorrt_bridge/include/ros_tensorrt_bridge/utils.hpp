#pragma once
enum class ConvertType {
    Scratch,
    Automatic
};

enum class OptimizationType {
    FP16,
    INT8,
    FP32
};

enum class TaskType {
    Classification,
    Detection,
    Segmentation, 
    Pose_estimation,
    Obb
};

enum class InputType {
    Image,
    ImageFolder,
    Video,
    VideoStream
};

// todo: Add output type enum