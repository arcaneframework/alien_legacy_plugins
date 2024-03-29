enable_language(Fortran)

createLibrary(alien_interface_c
  EXPORT alien/AlienInterfaceCExport.h
  )


addSources(alien_interface_c
           alien/c/alienc.cc
           alien/fortran/alienf.c
           alien/fortran/M_AlienModule.f90
           )

linkLibraries(alien_interface_c Alien::alien_core alien_external_packages)

if (TARGET intel)
    linkLibraries(gtest.refmvhandlers intel)
endif ()

if (TARGET alien_external_packages)
    linkLibraries(alien_interface_c
            alien_external_packages
            )
endif ()

if (TARGET alien_ifpen_solvers)
    linkLibraries(alien_interface_c
            alien_ifpen_solvers
            )
endif ()

linkLibraries(alien_interface_c
        Boost::program_options
        Alien::alien_core
        Alien::alien_semantic_ref
        )

commit(alien_interface_c)

target_include_directories(alien_interface_c PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>)

install(DIRECTORY alien 
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
  )
