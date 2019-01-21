# CMake generated Testfile for 
# Source directory: C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm/test/bug
# Build directory: C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm-build/test/bug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test-bug_ms_vec_static "C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm-build/test/bug/Debug/test-bug_ms_vec_static.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test-bug_ms_vec_static "C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm-build/test/bug/Release/test-bug_ms_vec_static.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test-bug_ms_vec_static "C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm-build/test/bug/MinSizeRel/test-bug_ms_vec_static.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test-bug_ms_vec_static "C:/Users/User/source/repos/Vulkan01/Vulkan01/Libraries/glm-build/test/bug/RelWithDebInfo/test-bug_ms_vec_static.exe")
else()
  add_test(test-bug_ms_vec_static NOT_AVAILABLE)
endif()
