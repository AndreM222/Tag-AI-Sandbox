cmake_minimum_required(VERSION 3.31.6)
project(Tag_AI_Sandbox)

set(ACCOUNT "https://github.com/AndreM222")
set(AIENTITY "AI-Entities")
set(WORLDGENERATOR "Procedural-Generator")

set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/../Source/Tag_AI_Sandbox")

set(CLONED_DIR "${CMAKE_SOURCE_DIR}/../tmpRepos")

file(MAKE_DIRECTORY ${CLONED_DIR})

macro(clone_repo repo_name repo_url)
    set(REPO_PATH "${CLONED_DIR}/${repo_name}")
    if(NOT EXISTS ${REPO_PATH})
        message(STATUS "Cloning ${ACCOUNT}/${repo_url} into ${REPO_PATH}")
        execute_process(COMMAND git clone "${ACCOUNT}/${repo_url}" ${REPO_PATH})
    else()
        message(STATUS "${repo_name} already exists. Skipping clone.")
    endif()
endmacro()

clone_repo("AIEntity" ${AIENTITY})
clone_repo("WorldGenerator" ${WORLDGENERATOR})

function(copy_source repo_name)
    set(SOURCE_DIR "${CLONED_DIR}/${repo_name}/Source/${repo_name}")
    if(EXISTS ${SOURCE_DIR})
        message(STATUS "Copying source from ${repo_name}")
        file(COPY ${SOURCE_DIR}/ DESTINATION "${SOURCE_PATH}/${repo_name}" PATTERN "*.Build.cs" EXCLUDE)
    else()
        message(WARNING "No repository directory found in ${repo_name}")
    endif()
endfunction()

copy_source("AIEntity")
copy_source("WorldGenerator")

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

message(STATUS "Projects merge completed. Ready to start working.")
