AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME save
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE save_tests.cpp
)
