set(IMAGEFILTERING_SRCS image_io.cpp FilteredImage.cpp ThreadedFilteredImage.cpp)
add_library(imagefiltering ${IMAGEFILTERING_SRCS})