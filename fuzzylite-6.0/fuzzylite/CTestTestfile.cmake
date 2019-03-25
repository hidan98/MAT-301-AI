# CMake generated Testfile for 
# Source directory: C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite
# Build directory: C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(RunTests "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/bin/Debug/fuzzylite-tests-debug.exe")
  set_tests_properties(RunTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;218;add_test;C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(RunTests "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/bin/Release/fuzzylite-tests.exe")
  set_tests_properties(RunTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;218;add_test;C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(RunTests "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/bin/MinSizeRel/fuzzylite-tests.exe")
  set_tests_properties(RunTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;218;add_test;C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(RunTests "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/bin/RelWithDebInfo/fuzzylite-tests.exe")
  set_tests_properties(RunTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;218;add_test;C:/Users/danday/Documents/GitHub/MAT-301-AI/fuzzylite-6.0/fuzzylite/CMakeLists.txt;0;")
else()
  add_test(RunTests NOT_AVAILABLE)
endif()
