cmake_minimum_required(VERSION 3.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES runAllTests.cpp TestSettings.cpp TestMp3Player.cpp TestTrack.cpp TestPlayList.cpp TestAlbum.cpp)

add_executable(allMp3PlrTests ${SOURCE_FILES})

target_link_libraries(allMp3PlrTests ${GTEST_BOTH_LIBRARIES} core ${wxWidgets_LIBRARIES})
