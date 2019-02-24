# Copyright (C) by Vesa Karvonen

add_conventional_library(rdcss)
target_link_libraries(rdcss PUBLIC dumpster_v1 polyfill_v1 PRIVATE intrinsics_v1)

add_conventional_executable_test(rdcss_test)
target_link_libraries(rdcss_test PRIVATE rdcss testing_v1)
