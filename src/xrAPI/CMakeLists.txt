add_library(xrAPI)

target_sources(xrAPI PRIVATE
    EngineGlobalEnvironment.cpp
)

target_include_directories(xrAPI
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(xrAPI PROPERTIES
    PREFIX ""
)

if (BUILD_SHARED_LIBS)
    install(TARGETS xrAPI LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
endif()
