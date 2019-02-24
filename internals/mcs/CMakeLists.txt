# Copyright (C) by Vesa Karvonen

add_conventional_library(mcs)
target_link_libraries(mcs PUBLIC mcs_v1 dumpster_v1 polyfill_v1)

add_conventional_executable_test(mcs_test)
target_link_libraries(mcs_test PRIVATE mcs testing_v1)
