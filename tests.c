/**************************************************************************************************
 *
 * Tests:
 * r?d?drdd         -> rrdrdrdd
 * ???rrurdr?       -> rlrrrurdrl
 * drdr??rrddd?     -> drdruurrdddd
 * rd?u??dld?ddrr   -> rdrurrdldlddrr
 * dddd?uuuurrr???? -> ddddruuuurrrdddd
 * ddr?rdrrd?dr     -> ddrurdrrdldr
 * rdrdr??rddd?dr   -> rdrdruurdddldr
 *
 *************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "correct_path.h"
#include "tests.h"

unsigned int pass = 0;
unsigned int fail = 0;
unsigned int executed = 0;

static void test_path(const char *input, const char *expected)
{
    bool match = true;
    char *output = malloc(strlen(input));

    output = correct_path(input);

    for (int i = 0; i < strlen(input); i++) {
        if (output[i] != expected[i]) {
            match = false;
        }
    }

    if (match) {
        pass++;
    }
    else {
        fail++;
        if (DEBUG >= 1) {
            printf("output: %s - expected: %s\n", output, expected);
        }
    }

    executed++;
}

static void test_1(void)
{
    const char test_input[] = "r?d?drdd";
    const char test_expected[] = "rrdrdrdd";

    test_path(test_input, test_expected);
}

static void test_2(void)
{
    const char test_input[] = "???rrurdr?";
    const char test_expected[] = "rlrrrurdrl";

    test_path(test_input, test_expected);
}

static void test_3(void)
{
    const char test_input[] = "drdr??rrddd?";
    const char test_expected[] = "drdruurrdddd";

    test_path(test_input, test_expected);
}

static void test_4(void)
{
    const char test_input[] = "rd?u??dld?ddrr";
    const char test_expected[] = "rdrurrdldlddrr";

    test_path(test_input, test_expected);
}

static void test_5(void)
{
    const char test_input[] = "dddd?uuuurrr????";
    const char test_expected[] = "ddddruuuurrrdddd";

    test_path(test_input, test_expected);
}

static void test_6(void)
{
    const char test_input[] = "ddr?rdrrd?dr";
    const char test_expected[] = "ddrurdrrdldr";

    test_path(test_input, test_expected);
}

static void test_7(void)
{
    const char test_input[] = "rdrdr??rddd?dr";
    const char test_expected[] = "rdrdruurdddldr";

    test_path(test_input, test_expected);
}

void tests_run_all(void)
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();

    printf("Tests Passed:   %d\n", pass);
	printf("Tests Failed:   %d\n", fail);
	printf("Tests Executed: %d\n", executed);
}
