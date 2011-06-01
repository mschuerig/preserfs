
find_package( Boost 1.46 COMPONENTS system filesystem serialization )

link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )

add_definitions(
    -DBOOST_FILESYSTEM_NO_DEPRECATED
    -Wall -Wextra -Wunused -Werror
)
# -Weffc++

add_executable(
    dirmeta
    dirmeta.cpp
    DirectoryMetadata.cpp
    Etc.cpp
)
target_link_libraries (
    dirmeta
    ${Boost_LIBRARIES}
)

add_executable(
    transpath
    transpath.cpp
    DirectoryMetadata.cpp
    Etc.cpp
)
target_link_libraries (
    transpath
    ${Boost_LIBRARIES}
)

