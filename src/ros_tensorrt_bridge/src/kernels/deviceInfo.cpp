#include "ros_tensorrt_bridge/kernels/deviceInfo.hpp"

void deviceInfoo()
{
    int dev, driverVersion = 0, runtimeVersion = 0, deviceCount = 0;
    cudaGetDeviceCount(&deviceCount);
    cudaDriverGetVersion(&driverVersion);
    cudaRuntimeGetVersion(&runtimeVersion);
    
    for (dev = 0; dev < deviceCount; ++dev) {
        cudaSetDevice(dev);
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, dev);

        printf("\nDevice %d: \"%s\"\n", dev, deviceProp.name);
    }

    printf("CUDA Driver Version / Runtime Version");
}