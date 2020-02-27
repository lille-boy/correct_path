/**************************************************************************************************
 *
 * Tests:
 * r?d?drdd         -> rrdrdrdd
 * ???rrurdr?       -> dddrrurdrd
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
    int size = strlen(input);
    char *output = (char *)malloc(size);

    correct_path(input, output);
    executed++;

    for (int i = 0; i < size; i++) {
        if (output[i] != expected[i]) {
            match = false;
            fail++;
            if (DEBUG >= 1) {
                printf("output: %s - expected: %s\n", output, expected);
            }
            goto exit;
        }
    }

    if (match) {
        pass++;
    }

    exit: free(output);
}

static void test_1(void)
{
    test_path("r?d?drdd", "rrdrdrdd");
}

static void test_2(void)
{
    test_path("???rrurdr?", "dddrrurdrd");
}

static void test_3(void)
{
    test_path("drdr??rrddd?", "drdruurrdddd");
}

static void test_4(void)
{
    test_path("rd?u??dld?ddrr", "rdrurrdldlddrr");
}

static void test_5(void)
{
    test_path("dddd?uuuurrr????", "ddddruuuurrrdddd");
}

static void test_6(void)
{
    test_path("ddr?rdrrd?dr", "ddrurdrrdldr");
}

static void test_7(void)
{
    test_path("rdrdr??rddd?dr", "rdrdruurdddldr");
}

static void test_8(void)
{
    test_path("d?rrurrdldr?", "ddrrurrdldrd");
}

static void test_9(void)
{
    test_path("rrrrddlll?ddrrr?", "rrrrddllllddrrrr");
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
    test_8();
    test_9();

    printf("Tests Passed:   %d\n", pass);
	printf("Tests Failed:   %d\n", fail);
	printf("Tests Executed: %d\n", executed);
}
