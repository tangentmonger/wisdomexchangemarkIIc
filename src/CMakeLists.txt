# Find and load a package.
find_package(OpenCV 3.1 REQUIRED)

# Add a library to the project, using the specified source files
add_library(Wisdom Wisdom.cpp Wisdom.h)

# Specify libraries used when linking Wisdom.
target_link_libraries(Wisdom ${OpenCV_LIBS})

# Add executable target to the project. Build in current directory, by default
# Build from the source(s) specified.
add_executable(DisplayImage DisplayImage.cpp)

# Specify libraries used when linking DisplayImage.
target_link_libraries(DisplayImage Wisdom)
