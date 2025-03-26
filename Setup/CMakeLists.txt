cmake_minimum_required(VERSION 3.31.6)
project(Tag_AI_Sandbox) # Unreal Engine project name
set(ACCOUNT "https://github.com/AndreM222") # Github account where to get repos

set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/../Source/${CMAKE_PROJECT_NAME}")
set(CLONED_DIR "${CMAKE_SOURCE_DIR}/../tmpRepos")

execute_process(
    COMMAND jq -c ".[]" ../repositories.json
    OUTPUT_VARIABLE repositories
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" ";" repositories "${repositories}")

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

foreach(repository IN LISTS repositories)
    string(JSON name GET "${repository}" name)
    string(JSON repo GET "${repository}" repo)

    clone_repo("${name}" "${repo}")
endforeach()

# Copy source files excluding the build script into current project source directory
function(copy_source repo_name filter)
    set(SOURCE_DIR "${CLONED_DIR}/${repo_name}/Source/${repo_name}")
    if(EXISTS ${SOURCE_DIR})
        message(STATUS "Copying source from ${repo_name}")

        # If exist already, then delete to replace with new one
        if(EXISTS "${SOURCE_PATH}/${repo_name}")
            message(STATUS "Updating ${repo_name} setup.")
            file(REMOVE_RECURSE "${SOURCE_PATH}/${repo_name}")
        endif()

        file(COPY ${SOURCE_DIR}/ DESTINATION "${SOURCE_PATH}/${repo_name}" PATTERN "*.Build.cs" EXCLUDE PATTERN "${repo_name}.*" EXCLUDE)

        # Find filter items path
        set(filter_path "")
        if (filter)
            string(JSON filter_length ERROR_VARIABLE length_error LENGTH "${repository}" filter)
            math(EXPR filter_length "${filter_length}-1")

            foreach(index RANGE 0 ${filter_length})
                string(JSON filter_item ERROR_VARIABLE item_error GET "${repository}" filter ${index})

                file(GLOB_RECURSE repo_files "${SOURCE_PATH}/${filter_item}")

                list(APPEND filter_path "${repo_files}")
            endforeach()
        endif()

        # Delete filtered content
        foreach(path IN LISTS filter_path)
            message(STATUS "Filtering out: ${path}")
            file(REMOVE ${path})
        endforeach()
    else()
        message(WARNING "No repository directory found in ${repo_name}")
    endif()
endfunction()

foreach(repository IN LISTS repositories)
    string(JSON name GET "${repository}" name)
    string(JSON filter ERROR_VARIABLE not_Found GET "${repository}" filter)

    copy_source("${name}" "${filter}")
endforeach()

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
    string(TOUPPER "${CMAKE_PROJECT_NAME}_API" project_api)

    message(STATUS "Replacing ${repo_api} with ${project_api} in ${repo_name}")

    file(GLOB_RECURSE repo_files
     "${SOURCE_PATH}/${repo_name}/*.h"
     "${SOURCE_PATH}/${repo_name}/*.cpp"
    )

    foreach(path IN LISTS repo_files)
        file(READ "${path}" replaced_api)
        string(REPLACE "${repo_api}" "${project_api}" replaced_api "${replaced_api}")
        file(WRITE "${path}" "${replaced_api}")
    endforeach()
endfunction()

foreach(repository IN LISTS repositories)
    string(JSON name GET "${repository}" name)
    api_replacement("${name}")
endforeach()

message(STATUS "Projects merge completed. Ready to start working.")
