#pragma once

#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <array>

#include <pybind11/embed.h> // Python yorumlayıcısını gömmek için
#include <pybind11/numpy.h>

#include "ros_tensorrt_bridge/tracker/tracker_util.hpp"
#include "types.h"

namespace py = pybind11;

class Tracker
{
public:
    Tracker();
    ~Tracker() = default;

    void track_from_scratch(cv::Mat &image, std::vector<std::vector<Detection>> &detections);

private:
    DetectionTrack detection_track_;
    py::scoped_interpreter guard{};
    py::module_ tracker_module;
    py::object deep_sort_compute;
    py::array_t<uint8_t> img_array;
};
