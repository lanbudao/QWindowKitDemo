cmake_minimum_required(VERSION 3.19)

project(QWindowKitDemo
        VERSION 1.0.0.0
        LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/stdware/qwindowkit"
        DESCRIPTION "Cross-platform window customization framework"
)

# ----------------------------------
# Find basic dependencies
# ----------------------------------
find_package(qmsetup QUIET)

if(NOT TARGET qmsetup::library)
    # Modify this variable according to your project structure
    set(_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/qmsetup)

    # Import install function
    include("${_source_dir}/cmake/modules/private/InstallPackage.cmake")

    # Install package in place
    set(_package_path)
    qm_install_package(qmsetup
        SOURCE_DIR ${_source_dir}
        BUILD_TYPE Release
        RESULT_PATH _package_path
    )

    # Find package again
    find_package(qmsetup REQUIRED PATHS ${_package_path})

    # Update import path
    set(qmsetup_DIR ${_package_path} CACHE PATH "" FORCE)
endif()

qm_import(Filesystem)
qm_init_directories()

add_subdirectory(frameless)
add_subdirectory(examples)
