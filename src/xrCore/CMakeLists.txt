add_library(xrCore)

target_sources(
    xrCore
    PRIVATE
    cpu.cpp
    Math/compressed_normal.cpp
    Math/cylinder.cpp
    Math/math_funcs.cpp
    Math/matrix.cpp
    Math/quaternion.cpp
    Math/sphere.cpp
    Math/vector.cpp
    Math/vector3_ext.cpp
    Text/string_conversion.cpp
    Threading/Event.cpp
    Threading/Lock.cpp
    Threading/ScopeLock.cpp
    Threading/TaskManager.cpp
    Threading/ThreadUtil.cpp
    timestamp.cpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Animation"
    FILES
    Animation/Bone.cpp
    Animation/Bone.hpp
    Animation/BoneEditor.cpp
    Animation/Envelope.cpp
    Animation/Envelope.hpp
    Animation/interp.cpp
    Animation/Motion.cpp
    Animation/Motion.hpp
    Animation/SkeletonMotionDefs.hpp
    Animation/SkeletonMotions.cpp
    Animation/SkeletonMotions.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\lz"
    FILES
    LzHuf.cpp
    lzhuf.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\lzo"
    FILES
    Compression/lzo_compressor.cpp
    Compression/lzo_compressor.h
    Compression/rt_compressor9.cpp
    Compression/rt_compressor.cpp
    Compression/rt_compressor.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\ppmd"
    FILES
    Compression/ppmd_compressor.cpp
    Compression/ppmd_compressor.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\ppmd\\common"
    FILES
    Compression/PPMd.h
    Compression/PPMdType.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\ppmd\\core"
    FILES
    Compression/Coder.hpp
    Compression/Model.cpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\ppmd\\core\\allocator"
    FILES
    Compression/SubAlloc.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Compression\\ppmd\\stream"
    FILES
    Compression/compression_ppmd_stream.h
    Compression/compression_ppmd_stream_inline.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Containers"
    FILES
    Containers/AssociativeVectorComparer.hpp
    Containers/AssociativeVector.hpp
    Containers/FixedMap.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Crypto"
    FILES
    Crypto/trivial_encryptor.cpp
    Crypto/trivial_encryptor.h
    Crypto/xr_dsa.cpp
    Crypto/xr_dsa.h
    Crypto/xr_dsa_signer.cpp
    Crypto/xr_dsa_signer.h
    Crypto/xr_dsa_verifyer.cpp
    Crypto/xr_dsa_verifyer.h
    Crypto/xr_sha.cpp
    Crypto/xr_sha.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Debug core"
    FILES
    xrDebug.cpp
    xrDebug.h
    xrDebug_macros.h
)

#target_sources_grouped(
#    TARGET xrCore
#    NAME "Debug core\\DxErr"
#    FILES
#    Debug/dxerr.cpp
#    Debug/dxerr.h
#    Debug/DXGetErrorDescription.inl
#    Debug/DXGetErrorString.inl
#    Debug/DXTrace.inl
#)

target_sources_grouped(
    TARGET xrCore
    NAME "Debug core\\StackTrace"
    FILES
    Debug/StackTrace.cpp
    Debug/StackTrace.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Events"
    FILES
    Events/Notifier.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "FMesh"
    FILES
    FMesh.cpp
    FMesh.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "FS"
    FILES
    FileCRC32.cpp
    FileSystem.cpp
    FileSystem.h
    FileSystem_borland.cpp
    FS.cpp
    FS.h
    FS_impl.h
    FS_internal.h
    LocatorAPI.cpp
    LocatorAPI.h
    LocatorAPI_auth.cpp
    LocatorAPI_defs.cpp
    LocatorAPI_defs.h
    log.cpp
    log.h
    NET_utils.cpp
    net_utils.h
    xr_ini.cpp
    xr_ini.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "FS\\file_stream_reader"
    FILES
    file_stream_reader.cpp
    file_stream_reader.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "FS\\stream_reader"
    FILES
    stream_reader.cpp
    stream_reader.h
    stream_reader_inline.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "intrusive_ptr"
    FILES
    intrusive_ptr.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Kernel"
    FILES
    cdecl_cast.hpp
    FTimer.cpp
    FTimer.h
    ModuleLookup.cpp
    ModuleLookup.hpp
    resource.h
    xr_shortcut.h
    xrCore.cpp
    xrCore.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Math"
    FILES
    dump_string.cpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Math\\Extensions"
    FILES
    #ChooseTypes.H
    #client_id.h
    clsid.cpp
    fastdelegate.h
    xr_token.cpp
    xr_token.h
    xr_trims.cpp
    xr_trims.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Math\\Extensions\\buffer_vector"
    FILES
    buffer_vector.h
    buffer_vector_inline.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Math\\RNG"
    FILES
    Math/fast_lc16.cpp
    Math/fast_lc16.hpp
    Math/Random32.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Math\\STLext"
    FILES
    FixedVector.h
    xrPool.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "Media"
    FILES
    Media/Image.cpp
    Media/Image.hpp
    Media/ImageJPEG.cpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "Memory"
    FILES
    xrMemory.cpp
    xrMemory.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "OS"
    FILES
    os_clipboard.cpp
    os_clipboard.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "PostProcess"
    FILES
    PostProcess/PostProcess.cpp
    PostProcess/PostProcess.hpp
    PostProcess/PPInfo.cpp
    PostProcess/PPInfo.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "shared memory/string library"
    FILES
    crc32.cpp
    string_concatenations.cpp
    string_concatenations.h
    string_concatenations_inline.h
    xr_resource.h
    xr_shared.cpp
    xr_shared.h
    xrsharedmem.cpp
    xrsharedmem.h
    xrstring.cpp
    xrstring.h
)

target_sources_grouped(
    TARGET xrCore
    NAME "XML"
    FILES
    XML/XMLDocument.cpp
    XML/XMLDocument.hpp
)

target_sources_grouped(
    TARGET xrCore
    NAME "XML\\TinyXML"
    FILES
    XML/tinystr.cpp
    XML/tinystr.h
    XML/tinyxml.cpp
    XML/tinyxmlerror.cpp
    XML/tinyxml.h
    XML/tinyxmlparser.cpp
)

target_include_directories(xrCore
    PUBLIC
    "${CMAKE_SOURCE_DIR}/Externals/tracy/public"

    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/Externals"
)

target_link_libraries(xrCore
    PUBLIC
    pthread
    $<$<PLATFORM_ID:FreeBSD,OpenBSD,NetBSD,DragonFlyBSD>:execinfo>
    SDL2::SDL2

    PRIVATE
    $<$<BOOL:${JPEG_FOUND}>:JPEG::JPEG>
    LZO::LZO
)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "OpenBSD" AND NOT CMAKE_SYSTEM_NAME STREQUAL "NetBSD" AND NOT WIN32 AND NOT HAIKU)
    target_link_libraries(xrCore
        PRIVATE
        dl
    )
endif()

target_compile_definitions(xrCore
    PRIVATE
    XRCORE_EXPORTS
    CMAKE_INSTALL_FULL_LIBDIR=\"${CMAKE_INSTALL_FULL_LIBDIR}\"
    CMAKE_INSTALL_FULL_DATAROOTDIR=\"${CMAKE_INSTALL_FULL_DATAROOTDIR}\"
    CI=$ENV{CI}
    GITHUB_ACTIONS=$ENV{GITHUB_ACTIONS}
    GITHUB_RUN_ID=\"$ENV{GITHUB_RUN_ID}\"
    GITHUB_RUN_NUMBER=\"$ENV{GITHUB_RUN_NUMBER}\"
    GITHUB_REPOSITORY=\"$ENV{GITHUB_REPOSITORY}\"
    GIT_INFO_CURRENT_COMMIT=\"${XRAY_GIT_SHA}\"
    GIT_INFO_CURRENT_BRANCH=\"${XRAY_GIT_BRANCH}\"
    OPENSSL_NO_DEPRECATED
)

set_target_properties(xrCore PROPERTIES
    PREFIX ""
)

if (BUILD_SHARED_LIBS)
    install(TARGETS xrCore LIBRARY
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
endif()
