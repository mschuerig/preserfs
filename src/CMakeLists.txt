
find_package( Boost 1.46 COMPONENTS system filesystem serialization )
find_package( openssl )

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
    MD5Shortener.cpp
)
target_link_libraries (
    dirmeta
    ${Boost_LIBRARIES}
    crypto
)

add_executable(
    transpath
    transpath.cpp
    DirectoryMetadata.cpp
    Etc.cpp
    MD5Shortener.cpp
)
target_link_libraries (
    transpath
    ${Boost_LIBRARIES}
    crypto
)

