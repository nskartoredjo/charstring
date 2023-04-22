#!/usr/bin/env python3

import sys
import argparse
import re
from os import walk
import os
from pathlib import Path


def generate(test_functs, extern_functs, test_cases):
    return f"""
/* THIS FILE HAS BEEN AUTO GENERATED AND SHOULD NOT BE MODIFIED */

# define UNITY_USE_COMMAND_LINE_ARGS

# include <stdlib.h>
# include <stdbool.h>
# include <unity.h>

# define TOTAL_TEST_CASES {len(test_functs)}
# define RUN_TEST_CASE(ITERATOR)                                \\
    UnityDefaultTestRun(tests[ITERATOR].f, tests[ITERATOR].name, \\
                        tests[ITERATOR].line);
# define TEST_CASE_DEF(FUNCTION) \\
    {{ FUNCTION, #FUNCTION, __LINE__ }}

{extern_functs}

struct {{
    void (*f)(void);
    const char *name;
    unsigned line;
}} tests[] = {{
{test_cases}
}};

void setUp(void) {{}}
void tearDown(void) {{}}

int main(int argc, char *argv[]) {{
    UNITY_BEGIN();
    if (argc == 1) {{
        for (unsigned i = 0; i < TOTAL_TEST_CASES; i++) {{
            RUN_TEST_CASE(i);
        }}
        return (UNITY_END());
    }}

    unsigned i = atoi(argv[1]);
    if (i < TOTAL_TEST_CASES) {{
        RUN_TEST_CASE(i);
    }} else {{
        TEST_ASSERT_TRUE(false);
    }}

    return (UNITY_END());
}}"""


def main():
    extentions = ['c', 'cpp']
    prefix = ['test', 'spec']
    runner = 'runner.c'
    database = 'tests.csv'

    parser = argparse.ArgumentParser(
        description='List the content of a folder')

    parser.add_argument('path', metavar='path/to/source', type=str, default='.',
                        help='the path to the files')
    parser.add_argument('-o', '--output', metavar='path/to/output',
                        type=str, default='.', help='the output directory')
    parser.add_argument('-t', '--touch', action='store_true',
                        help='touch the required files')

    test_functs = []
    args = parser.parse_args()
    path = args.path
    output = args.output
    touch = args.touch

    if touch:
        Path(f'{output}/{runner}').touch()
        Path(f'{output}/{database}').touch()
        quit(0)

    print(f'Generating the test runner: {output}/{runner} ...')

    prefix_match = '|'.join([str(i) for i in prefix])
    funct_match = f'(?<!\/\/)\s+(?:void)\s+(({prefix_match})\w+)'

    ext_match = '|'.join(['\.' + s for s in extentions])
    file_match = f'(({prefix_match})\w+({ext_match}))'
    file_regex = re.compile(file_match)

    for (p, _, filenames) in walk(path):
        test_files = [n for n in filenames if file_regex.match(n)]
        file_string = ', '.join([f for f in test_files])
        print(f'Detected the following test files: {file_string} ...')

        for file in test_files:
            file = p + '/' + file
            with open(file, 'r') as f:
                f_data = f.read()
                f_matches = re.findall(funct_match, f_data)
                test_functs.extend([i[0] for i in f_matches])

    extern_functs = '\n'.join(
        [f'extern void {funct}(void);' for funct in test_functs])
    test_cases = '\n'.join(
        [f'    TEST_CASE_DEF({funct}),' for funct in test_functs])
    test_database = ';'.join([funct for funct in test_functs])

    print(f'{len(test_functs)} tests have been found ...')

    with open(f'{output}/{database}', 'w+') as file:
        file.write(test_database)

    with open(f'{output}/{runner}', 'w+') as file:
        file.writelines(generate(test_functs, extern_functs, test_cases))

    print('Generating the test runner completed!')


if __name__ == "__main__":
    main()
