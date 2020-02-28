/**************************************************************************************************
 *
 * Tests
 *
 * r?d?drdd         -> rrdrdrdd
 * ???rrurdr?       -> dddrrurdrd
 * drdr??rrddd?     -> drdruurrdddd
 * rd?u??dld?ddrr   -> rdrurrdldlddrr
 * dddd?uuuurrr???? -> ddddruuuurrrdddd
 * ddr?rdrrd?dr     -> ddrurdrrdldr
 * rdrdr??rddd?dr   -> rdrdruurdddldr
 * d?rrurrdldr?     -> ddrrurrdldrd
 * rrrrddlll?ddrrr? -> rrrrddllllddrrrr
 *
 *************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "correct_path.h"
#include "tests.h"

struct results {
    unsigned int pass;
    unsigned int fail;
    unsigned int executed;
};

static void test_path(const char *input, const char *expected, struct results *results)
{
    int size = strlen(input);
    char *output = (char *)malloc(size);

    if (output != NULL) {
        correct_path(input, output);
        results->executed++;

        if (strcmp(output, expected) == 0) {
            results->pass++;
        }
        else {
            results->fail++;
            printf("fail: %d\n", results->fail);
            if (DEBUG >= 1) {
                printf("%s -> %s [expected: %s]\n", input, output, expected);
            }
        }
        free(output);
    }
    else {
        printf("Memory allocation error\n");
    }
}

static void test_1(struct results *results)
{
    test_path("r?d?drdd", "rrdrdrdd", results);
}

static void test_2(struct results *results)
{
    test_path("???rrurdr?", "dddrrurdrd", results);
}

static void test_3(struct results *results)
{
    test_path("drdr??rrddd?", "drdruurrdddd", results);
}

static void test_4(struct results *results)
{
    test_path("rd?u??dld?ddrr", "rdrurrdldlddrr", results);
}

static void test_5(struct results *results)
{
    test_path("dddd?uuuurrr????", "ddddruuuurrrdddd", results);
}

static void test_6(struct results *results)
{
    test_path("ddr?rdrrd?dr", "ddrurdrrdldr", results);
}

static void test_7(struct results *results)
{
    test_path("rdrdr??rddd?dr", "rdrdruurdddldr", results);
}

static void test_8(struct results *results)
{
    test_path("d?rrurrdldr?", "ddrrurrdldrd", results);
}

static void test_9(struct results *results)
{
    test_path("rrrrddlll?ddrrr?", "rrrrddllllddrrrr", results);
}

/******************************************************************************
 * Main test function
 *****************************************************************************/
void tests_run_all(void)
{
    struct results results = {.pass = 0, .fail = 0, .executed = 0};

    test_1(&results);
    test_2(&results);
    test_3(&results);
    test_4(&results);
    test_5(&results);
    test_6(&results);
    test_7(&results);
    test_8(&results);
    test_9(&results);

    printf("Tests Passed:   %d\n", results.pass);
    printf("Tests Failed:   %d\n", results.fail);
    printf("Tests Executed: %d\n", results.executed);
}
