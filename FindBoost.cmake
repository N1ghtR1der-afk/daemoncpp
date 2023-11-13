find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )
add_executable( run main.cpp ) # Example application based on main.cpp

# Alternatively you could use ${Boost_LIBRARIES} here.
target_link_libraries( run ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY}