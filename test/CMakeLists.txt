# Add directories to those used by the compiler to search for include files
# "dpkg -L somepackage" to locate installed libraries and header files
include_directories(../src)
include_directories(/usr/include)
link_directories(/usr/lib)

# Add executable target to the project. Build in current directory, by default
# Build from the source(s) specified.
add_executable(WisdomTest  main.cpp )

# Specify libraries used when linking a given target.
target_link_libraries( WisdomTest Wisdom cpptest)
