add_executable(workshop3.6 main.cpp blocks.cpp blocks.h random.cpp random.h)

target_include_directories(workshop3.6 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3.6 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.6 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.6 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})