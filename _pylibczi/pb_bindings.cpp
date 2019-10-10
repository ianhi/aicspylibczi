//
// Created by Jamie Sherman on 2019-08-20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "inc_libCZI.h"
#include "Reader.h"
#include "IndexMap.h"
#include "exceptions.h"
// the below headers are crucial otherwise the custom casts aren't recognized
#include "pb_caster_BytesIO.h"
#include "pb_caster_ImageVector.h"
#include "pb_caster_libCZI_DimensionIndex.h"

PYBIND11_MODULE(_pylibczi, m)
{

    namespace py = pybind11;

    m.doc() = "pylibczi C++ extension for reading ZISRAW/CZI files"; // optional module docstring


    py::register_exception<pylibczi::FilePtrException>(m, "PylibCZI_BytesIO2FilePtrException");
    py::register_exception<pylibczi::PixelTypeException>(m, "PylibCZI_PixelTypeException");
    py::register_exception<pylibczi::RegionSelectionException>(m, "PylibCZI_RegionSelectionException");
    py::register_exception<pylibczi::ImageAccessUnderspecifiedException>(m, "PylibCZI_ImageAccessUnderspecifiedException");
    py::register_exception<pylibczi::ImageIteratorException>(m, "PylibCZI_ImageIteratorException");
    py::register_exception<pylibczi::ImageSplitChannelException>(m, "PylibCZI_ImageSplitChannelException");
    py::register_exception<pylibczi::ImageCopyAllocFailed>(m, "PylibCZI_ImageCopyAllocFailed");
    py::register_exception<pylibczi::CdimSelectionZeroImagesException>(m, "PylibCZI_CDimSpecSelectedNoImagesException");

    py::class_<pylibczi::Reader>(m, "Reader")
            .def(py::init<pylibczi::FileHolder>())
            .def("is_mosaic", &pylibczi::Reader::isMosaic)
            .def("read_dims", &pylibczi::Reader::read_dims)
            .def("read_meta", &pylibczi::Reader::read_meta)
            .def("read_selected", &pylibczi::Reader::read_selected)
            .def("mosaic_shape", &pylibczi::Reader::mosaic_shape)
            .def("read_mosaic", &pylibczi::Reader::read_mosaic);

    py::class_<pylibczi::IndexMap>(m, "IndexMap")
            .def(py::init<>())
            .def("is_m_index_valid", &pylibczi::IndexMap::IsMIndexValid)
            .def("dim_index", &pylibczi::IndexMap::dimIndex)
            .def("m_index", &pylibczi::IndexMap::mIndex);

    py::class_<libCZI::CDimCoordinate>(m, "DimCoord")
            .def(py::init<>())
            .def("SetDim", &libCZI::CDimCoordinate::Set);

    py::class_<libCZI::IntRect>(m, "IntRect")
            .def(py::init<>())
            .def_readwrite("x", &libCZI::IntRect::x)
            .def_readwrite("y", &libCZI::IntRect::y)
            .def_readwrite("w", &libCZI::IntRect::w)
            .def_readwrite("h", &libCZI::IntRect::h);

}
