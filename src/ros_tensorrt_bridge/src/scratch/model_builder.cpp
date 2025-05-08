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

void ModelBuilderScratch::serialize_model()
{
    std::cout << "ModelBuilderScratch serialize_model called" << std::endl;
    nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(gLogger);

    std::cout << "ModelBuilderScratch serialize_model done" << std::endl;
    
    
}

