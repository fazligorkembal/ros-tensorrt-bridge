#include "ros_tensorrt_bridge/scratch/model_builder.hpp"

using namespace nvinfer1;

ModelBuilderScratch::~ModelBuilderScratch()
{
    std::cout << "ModelBuilderScratch destructor called" << std::endl;
}
void ModelBuilderScratch::infer()
{
    std::cout << "ModelBuilderScratch infer called" << std::endl;
}
void ModelBuilderScratch::convert()
{
    std::cout << "ModelBuilderScratch convert called" << std::endl;
}

void ModelBuilderScratch::build()
{
    std::cout << "ModelBuilderScratch build called" << std::endl;
}

void ModelBuilderScratch::serialize_engine(std::string &wts_name, std::string &engine_path, std::string &type, float &gd, float &gw, int &max_channels)
{
    IBuilder *builder = createInferBuilder(gLogger);
    IBuilderConfig *config = builder->createBuilderConfig();
    IHostMemory *serialized_engine = nullptr;

    switch (options_.task_type)
    {
    case TaskType::Pose:
        if (options_.model_type == ModelType::Yolo11n)
        {
            serialized_engine = buildEngineYolo11Pose(builder, config, DataType::kFLOAT, options_.model_path, gd, gw, max_channels, type);
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

void ModelBuilderScratch::deserialize_engine(std::string &engine_path)
{
    ASSERT(std::filesystem::exists(engine_path) && std::filesystem::is_regular_file(engine_path), "Engine path must be full-path and a valid file");
    std::ifstream file(engine_path, std::ios::binary);

    if (!file.good())
    {
        ASSERT(false, "Failed to open engine file");
    }
    size_t size = 0;
    file.seekg(0, file.end);
    size = file.tellg();
    file.seekg(0, file.beg);
    char *serialized_engine = new char[size];
    assert(serialized_engine);
    file.read(serialized_engine, size);
    file.close();

    runtime = createInferRuntime(gLogger);
    ASSERT(runtime != nullptr, "Failed to create runtime");
    engine = runtime->deserializeCudaEngine(serialized_engine, size);
    ASSERT(engine != nullptr, "Failed to create engine");
    context = engine->createExecutionContext();
    ASSERT(context != nullptr, "Failed to create context");

    delete[] serialized_engine;

    std::cout << "Engine deserialized successfully, " << engine_path << std::endl;
}

void ModelBuilderScratch::parse_options(std::string &type, float &gd, float &gw, int &max_channels)
{
    if (options_.model_type == ModelType::Yolo11n)
    {
        gd = 0.50;
        gw = 0.25;
        max_channels = 1024;
        type = "n";
    }
    else if (options_.model_type == ModelType::Yolo11s)
    {
        gd = 0.50;
        gw = 0.50;
        max_channels = 1024;
        type = "s";
    }
    else if (options_.model_type == ModelType::Yolo11m)
    {
        gd = 0.50;
        gw = 1.00;
        max_channels = 512;
        type = "m";
    }
    else if (options_.model_type == ModelType::Yolo11l)
    {
        gd = 1.0;
        gw = 1.0;
        max_channels = 512;
        type = "l";
    }
    else if (options_.model_type == ModelType::Yolo11x)
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

    ASSERT(gd > 0 && gw > 0, "gd and gw must be greater than 0");
    ASSERT(max_channels > 0, "max_channels must be greater than 0");
    ASSERT(type == "n" || type == "s" || type == "m" || type == "l" || type == "x", "Invalid model type");
}