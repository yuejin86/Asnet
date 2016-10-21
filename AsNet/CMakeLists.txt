# Asnet

# Ô´Âë
FILE(GLOB_RECURSE src_net *.cpp *.h)
SET(NET_SCRS ${src_net})

# ÒÀÀµ°üº¬
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/third_party/include)

LINK_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/third_party/lib/lib32-msvc-11.0
	${PROJECT_SOURCE_DIR}/third_party/lib/lib32-pb
	${PROJECT_SOURCE_DIR}/third_party/lib/lib32-rpb
	)

Set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Lib)
ADD_LIBRARY( Asnet STATIC ${NET_SCRS})

TARGET_LINK_LIBRARIES(Asnet libprotobuf)