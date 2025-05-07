#include "ros_tensorrt_bridge/yolo_scratch/model_generator.hpp"

Logger gLogger;
using namespace nvinfer1;

namespace yolo_scratch
{
    BuildModel::BuildModel(const TensorRTBridgeOptions &options) : mOptions(options)
    {

        if (mOptions.model_path.ends_with(".wts"))
        {
            std::string engine_path = mOptions.model_path;
            engine_path.replace(engine_path.end() - 4, engine_path.end(), ".engine");
            serialize_engine(engine_path);
        }
        else if (mOptions.model_path.ends_with(".engine") || mOptions.model_path.ends_with(".plan"))
        {
            ASSERT(false, "Engine file is not supported yet");
        }
    }

    void BuildModel::serialize_engine(std::string &engine_path)
    {
        std::string type;
        float gd = 0.0f;
        float gw = 0.0f;
        int max_channels = 0;

        parse_parameters(type, gd, gw, max_channels);
        ASSERT(!type.empty() && gd > 0.0f && gw > 0.0f && max_channels > 0, "Invalid parameters for model generation");

        IBuilder *builder = createInferBuilder(gLogger);
        IBuilderConfig *config = builder->createBuilderConfig();
        IHostMemory *serialized_engine = nullptr;

        switch (mOptions.task_type)
        {
        case TaskType::Pose:
            if (mOptions.model_type == ModelType::Yolo11n)
            {
                serialized_engine = buildEngineYolo11Pose(builder, config, DataType::kFLOAT, mOptions.model_path, gd, gw, max_channels, type);
                ASSERT(serialized_engine != nullptr, "Failed to build engine");
                std::ofstream p(engine_path, std::ios::binary);
                if (!p)
                {
                    ASSERT(false, "Failed to open plan output file");
                }
                p.write(reinterpret_cast<const char *>(serialized_engine->data()), serialized_engine->size());

                delete serialized_engine;
                delete config;
                delete builder;
            }
            else
            {
                ASSERT(false, "This model type is not supported yet, please check the model types for supported models");
            }

            break;

        case TaskType::Detection:
            ASSERT(false, "Detection task is not supported yet");
            break;
        case TaskType::Segmentation:
            ASSERT(false, "Segmentation task is not supported yet");
            break;
        case TaskType::Classification:
            ASSERT(false, "Classification task is not supported yet");
            break;
        case TaskType::Obb:
            ASSERT(false, "Obb task is not supported yet");
            break;

        default:
            break;
        }
    }

    void BuildModel::parse_parameters(std::string &type, float &gd, float &gw, int &max_channels)
    {
        if (mOptions.model_type == ModelType::Yolo11n)
        {
            gd = 0.50;
            gw = 0.25;
            max_channels = 1024;
            type = "n";
        }
        else if (mOptions.model_type == ModelType::Yolo11s)
        {
            gd = 0.50;
            gw = 0.50;
            max_channels = 1024;
            type = "s";
        }
        else if (mOptions.model_type == ModelType::Yolo11m)
        {
            gd = 0.50;
            gw = 1.00;
            max_channels = 512;
            type = "m";
        }
        else if (mOptions.model_type == ModelType::Yolo11l)
        {
            gd = 1.0;
            gw = 1.0;
            max_channels = 512;
            type = "l";
        }
        else if (mOptions.model_type == ModelType::Yolo11x)
        {
            gd = 1.0;
            gw = 1.50;
            max_channels = 512;
            type = "x";
        }
        else
        {
            ASSERT(false, "Invalid model type");
        }
    }

    void BuildModel::deserialize_engine()
    {
        std::cout << "deserialize_engine called" << std::endl;
    }
}