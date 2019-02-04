PROJECT(simd_with_intrinsics)

# TODO: Adjust compiler flags/options by editing the OPTS variable
SET(OPTS -mavx2 -march=native -O3)

# TODO: New source files should be added to the HW1_CPP variable's list
SET(SIMD_EXAMPLE_CPP simd_example.cpp)

# DO NOT ADJUST ANYTHING BELOW THIS LINE
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

ADD_EXECUTABLE(${PROJECT_NAME}
  ${SIMD_EXAMPLE_CPP}
)

# TARGET_LINK_LIBRARIES(${PROJECT_NAME}
#   ${MKL_LINK_LINE}
#   CLI11
# )

TARGET_COMPILE_OPTIONS(${PROJECT_NAME}
  PRIVATE
  ${OPTS}
)

INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/
)
