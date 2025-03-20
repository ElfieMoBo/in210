/* IN210 : tests unitaires */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "cmocka.h"
#include <string.h>
#include "compute.h"

static int setup(void **state){
    (void) state;
    printf("SetUp:\n");
    return 0;
}
static int teardown(void **state){
    (void) state;
    printf("TearDown:\n");
    return 0;
}

/* Creating mocks for age limits*/
void recupLimitAge1(int* ageLimit){
    function_called(); // To be sure the mock is only called once per test
    *ageLimit = (int)mock();
}
void recupLimitAge2(int* ageLimit){
    function_called(); // To be sure the mock is only called once per test
    *ageLimit = (int)mock();
}

/* Creating test relatively to our study */
static void negativeAge(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(-1, getReducedTicket(-2,0));
}
static void negativeBound(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    // assuming 0 is not "negative"
    assert_int_equal(1, getReducedTicket(0,0));
}
static void youngAge(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(1, getReducedTicket(5,0));
}
static void youngBound(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(1, getReducedTicket(12,0));
}
static void mediumAge(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(0, getReducedTicket(20,0));
}
static void oldBoundRetired(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(1, getReducedTicket(65,1));
}
static void oldBoundNotRetired(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(0, getReducedTicket(65,0));
}
static void oldAgeRetired(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(1, getReducedTicket(70,1));
}
static void oldAgeNotRetired(void **state){
    (void) state;
    expect_function_calls(recupLimitAge1, 1);
    expect_function_calls(recupLimitAge2, 1);
    will_return(recupLimitAge1, 12);
    will_return(recupLimitAge2, 65);
    assert_int_equal(0, getReducedTicket(70,0));
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(negativeAge),
        cmocka_unit_test(negativeBound),
        cmocka_unit_test(youngAge),
        cmocka_unit_test(youngBound),
        cmocka_unit_test(mediumAge),
        cmocka_unit_test(oldBoundNotRetired),
        cmocka_unit_test(oldBoundRetired),
        cmocka_unit_test(oldAgeNotRetired),
        cmocka_unit_test(oldAgeRetired),
    };
    return cmocka_run_group_tests_name("TESTS", tests, setup, teardown);
}