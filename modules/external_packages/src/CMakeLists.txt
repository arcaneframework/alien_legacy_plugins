if (NOT TARGET hypre AND NOT TARGET petsc AND NOT TARGET mtl)
    return()
endif ()

createLibrary(alien_external_packages
        EXPORT alien/AlienExternalPackagesExport.h
        )

set_target_properties(alien_external_packages
        PROPERTIES LINKER_LANGUAGE "CXX")

if (TARGET arcane_core)
    set(AXL_OPTION_GENERATION_TYPE "ALL")
    set(NAMESPACE_TYPE "Arcane")
    set(IS_WITH_ARCANE "")
    set(IS_WITH_MESH "NO_MESH")
else ()
    set(AXL_OPTION_GENERATION_TYPE "STRONG_OPTIONS_ONLY")
    set(NAMESPACE_TYPE "Arccore")
    set(IS_WITH_ARCANE "NO_ARCANE")
    set(IS_WITH_MESH "NO_MESH")
endif ()

if(USE_AXLSTAR)
include(${AXLSTAR_CMAKE_COMMANDS})
endif()

if(TARGET hypre)
    addDirectory(alien/kernels/hypre)
endif()

if(TARGET mtl4)
    addDirectory(alien/kernels/mtl)
endif()

if(TARGET arcconpkg_MTL4)
    addDirectory(alien/kernels/mtl)
endif()

if(TARGET petsc)
    addDirectory(alien/kernels/petsc)
    addSources(alien_external_packages
            alien/functional/Dump.cc
            )
endif()

if (TARGET arcane_core)
    linkLibraries(alien_external_packages arcane_core arcane_std)
else ()
    linkLibraries(alien_external_packages alien_strong_options)
endif()

if(TARGET umfpack)
    linkLibraries(alien_external_packages umfpack)
endif()

linkLibraries(alien_external_packages 
              Alien::alien_core 
              Boost::program_options)

target_include_directories(alien_external_packages PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>)

commit(alien_external_packages)

install(DIRECTORY alien
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        )
