
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

struct Detection {
    float* conf;      // Güven skorları dizisi
    float* class_id;  // Sınıf ID'leri dizisi
    size_t size;      // Dizi boyutu (eklemek zorundayız)
};




PYBIND11_MODULE(pybind_detections, m) {
    m.doc() = "pybind11 example plugin"; // Optional module docstring

    py::class_<Detection>(m, "Detection")
        .def(py::init<>())
        .def_readonly("size", &Detection::size)
        .def_property_readonly("conf_array", [](const Detection &d) {
            return py::array_t<float>(
                {d.size},                          // Şekil
                {sizeof(float)},                   // Adım (stride)
                d.conf,                           // Veri pointer'ı
                py::cast(d)                        // Bellek sahibi
            );
        })
        .def_property_readonly("class_id_array", [](const Detection &d) {
            return py::array_t<float>(
                {d.size},
                {sizeof(float)},
                d.class_id,
                py::cast(d)
            );
        });
    
}