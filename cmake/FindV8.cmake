find_path (V8_ROOT_DIR
  INCLUDE_DIR include/v8.h
  HINTS $ENV{V8_HOME} )

set(V8_INCLUDE_DIR ${V8_ROOT_DIR}/include)

if (NOT V8_ARCH)
  message("V8_ARCH not set, defaulting to native")
  set(V8_ARCH native
      CACHE STRING "The architecture selected when building v8 from source.")
endif()

set(V8_LINK_DIR_GYP ${V8_ROOT_DIR}/out/${V8_ARCH}/obj.target/tools/gyp)
set(V8_LINK_DIR_ICU ${V8_ROOT_DIR}/out/${V8_ARCH}/obj.target/third_party/icu)

file(GLOB V8_LINK_LIBRARIES
    ${V8_LINK_DIR_GYP}/libv8_base.a
    ${V8_LINK_DIR_GYP}/libv8_libbase.a
    ${V8_LINK_DIR_GYP}/libv8_snapshot.a
    ${V8_LINK_DIR_ICU}/libicuuc.a
    ${V8_LINK_DIR_ICU}/libicui18n.a
    ${V8_LINK_DIR_ICU}/libicudata.a)