AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME mentions
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE mentions_tests.cpp
)
