cmake_minimum_required(VERSION 3.31.6)
project(Tag_AI_Sandbox)

set(ACCOUNT "https://github.com/AndreM222")
set(AIENTITY "AI-Entities")
set(WORLDGENERATOR "Procedural-Generator")

set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/../Source/Tag_AI_Sandbox")

set(CLONED_DIR "${CMAKE_SOURCE_DIR}/../tmpRepos")

# Clean tmp file at startup if exist in case stopped midway and run again
if(EXISTS ${CLONED_DIR})
    message(STATUS "Cleaning old cloned repos")
    file(REMOVE_RECURSE ${CLONED_DIR})
endif()

file(MAKE_DIRECTORY ${CLONED_DIR})


# Clone repositories into temporary directory
macro(clone_repo project_name repo_name)
    set(REPO_PATH "${CLONED_DIR}/${project_name}")
    if(NOT EXISTS ${REPO_PATH})
        message(STATUS "Cloning ${ACCOUNT}/${repo_name} into ${REPO_PATH}")
        execute_process(COMMAND git clone "${ACCOUNT}/${repo_name}" ${REPO_PATH})
    else()
        message(STATUS "${project_name} already exists. Skipping clone.")
    endif()
endmacro()

clone_repo("AIEntity" ${AIENTITY})
clone_repo("WorldGenerator" ${WORLDGENERATOR})

# Copy source files excluding the build script into current project source directory
function(copy_source repo_name)
    set(SOURCE_DIR "${CLONED_DIR}/${repo_name}/Source/${repo_name}")
    if(EXISTS ${SOURCE_DIR})
        message(STATUS "Copying source from ${repo_name}")

        # If exist already, then delete to replace with new one
        if(EXISTS "${SOURCE_PATH}/${repo_name}")
            message(STATUS "Updating ${repo_name} setup.")
            file(REMOVE_RECURSE "${SOURCE_PATH}/${repo_name}")
        endif()

        file(COPY ${SOURCE_DIR}/ DESTINATION "${SOURCE_PATH}/${repo_name}" PATTERN "*.Build.cs" EXCLUDE)
    else()
        message(WARNING "No repository directory found in ${repo_name}")
    endif()
endfunction()

copy_source("AIEntity")
copy_source("WorldGenerator")

# Cleanup temporary directory
function(clean_dir)
    if(EXISTS ${CLONED_DIR})
        message(STATUS "Cleaning cloned repos")
        file(REMOVE_RECURSE ${CLONED_DIR})
    endif()

    if(NOT EXISTS ${CLONED_DIR})
        message(STATUS "Cleaned project")
    else()
        message(WARNING "Failed to clean project")
    endif()
endfunction()

clean_dir()

# Replace api from projects with current project api
function(api_replacement repo_name)
    string(TOUPPER "${repo_name}_API" repo_api)

    message("Replacing ${repo_api} with TAG_AI_SANDBOX_API in ${repo_name}")

    file(GLOB_RECURSE repo_files
     "${SOURCE_PATH}/${repo_name}/*.h"
     "${SOURCE_PATH}/${repo_name}/*.cpp"
    )

    foreach(path IN LISTS repo_files)
        file(READ "${path}" replaced_api)
        string(REPLACE "${repo_api}" "TAG_AI_SANDBOX_API" replaced_api "${replaced_api}")
        file(WRITE "${path}" "${replaced_api}")
    endforeach()
endfunction()

api_replacement("AIEntity")
api_replacement("WorldGenerator")

message(STATUS "Projects merge completed. Ready to start working.")
