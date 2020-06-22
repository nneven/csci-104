#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_HSORT = os.path.join(source_dir, 'rubric', 'hsort.config')
RUBRIC_HEAP = os.path.join(source_dir, 'rubric', 'heap.config')
RUBRIC_SAVE = os.path.join(source_dir, 'rubric', 'save.config')
RUBRIC_FOLLOW = os.path.join(source_dir, 'rubric', 'follow.config')
RUBRIC_MENTIONS = os.path.join(source_dir, 'rubric', 'mentions.config')


GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    5,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

P3 = cs_grading.Problem(HOMEWORK, 5.3, 'mentions', 22)
P2_part1 = cs_grading.Problem(HOMEWORK, 5.21, 'save', 3)
P2_part2 = cs_grading.Problem(HOMEWORK, 5.22, 'follow', 5)
P6 = cs_grading.Problem(HOMEWORK, 5.6, 'hsort', 15)
P4 = cs_grading.Problem(HOMEWORK, 5.4, 'heap', 22)

for problem, rubric in [(P2_part1, RUBRIC_SAVE), 
                        (P2_part2, RUBRIC_FOLLOW), 
                        (P3, RUBRIC_MENTIONS), 
                        (P6, RUBRIC_HSORT), 
                        (P4, RUBRIC_HEAP)]:

    problem.generate_results(
        cmake_problem.cmake_problem,
        True,
        timeout=0,)
    if setting.GENERATE_GRADE_REPORT:
        problem.grade_problem(RUBRIC_GENERAL, rubric)
    if setting.OPEN_RESULT:
        problem.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)
