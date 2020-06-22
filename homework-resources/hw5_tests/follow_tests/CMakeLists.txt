AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME follow
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE follow_tests.cpp
)
