message("---------------------------------------------")
message("Copying assets '${CMAKE_SOURCE_DIR}/assets' into '${CMAKE_RUNTIME_OUTPUT_DIRECTORY}'")
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("---------------------------------------------")



