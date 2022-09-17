qt_add_executable(qdecimal_test
  QDecNumberTests.cc Main.cc
)

target_include_directories(qdecimal_test PUBLIC . ../decnumber ../src)
target_link_libraries(qdecimal_test 
 PRIVATE 
  qdecimal
  decnumber  
  Qt6::Core 
  Qt6::Core5Compat
  Qt6::Test
)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_test(
  NAME qdecimal_test 
  COMMAND $<TARGET_FILE:qdecimal_test>
)

add_test(
  NAME qdecimal_test_subset
  COMMAND $<TARGET_FILE:qdecimal_test> --testdir=${CMAKE_SOURCE_DIR}/test/tc_subset
)

add_test(
  NAME qdecimal_test_full
  COMMAND $<TARGET_FILE:qdecimal_test> --testdir=${CMAKE_SOURCE_DIR}/test/tc_full
)