cmake_minimum_required(VERSION 3.0)
project(iir_biquad)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(FindPortaudio)

add_executable(iir_biquad src/IIRFilter.c src/main.c)
target_link_libraries(iir_biquad ${PORTAUDIO_LIBRARIES})
target_include_directories(iir_biquad PUBLIC ${PORTAUDIO_INCLUDE_DIRS})
