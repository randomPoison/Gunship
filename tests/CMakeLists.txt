file(GLOB TEST_SOURCES
     *.cpp)

set(TEST_INCLUDE_DIRS
    Catch)

add_executable(GunshipTests ${TEST_SOURCES})
target_link_libraries(GunshipTests LibGunship)
