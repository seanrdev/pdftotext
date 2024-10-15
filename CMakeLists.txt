cmake_minimum_required(VERSION 3.25.1)
project(pdfconvert C)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Find the required packages using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler-glib)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Add include directories
include_directories(${POPPLER_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})

# Link the necessary libraries
link_directories(${POPPLER_LIBRARY_DIRS} ${GLIB_LIBRARY_DIRS})

# Define the executable
add_executable(pdfconvert main.c)

# Link libraries to the executable
target_link_libraries(pdfconvert ${POPPLER_LIBRARIES} ${GLIB_LIBRARIES})

# Add any required compile options
target_compile_options(pdfconvert PRIVATE ${POPPLER_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER})
