/* IN210 : tests unitaires */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "ratp.h"

/* Testing nothing (will always be true/passed) */
static void null_test_success(void **state){
    (void) state;
}

/* Testing equality on two floats (1) */
static void inf12_notourist(void **state){
    (void) state;
    assert_float_equal(0.6, computePrice(11,0), 0.001);
}
static void inf12_tourist(void **state){
    (void) state;
    assert_float_equal(1.2, computePrice(11,1), 0.001);
}
static void sup12_notourist(void **state){
    (void) state;
    assert_float_equal(1.2, computePrice(23,0), 0.001);
}
static void sup12_tourist(void **state){
    (void) state;
    assert_float_equal(2.4, computePrice(23,1), 0.001);
}

/* Testing equality on two floats (2) */
static void assertTrue(void **state){
    (void) state;
    assert_true(computePrice(11,0)==0.6f); // 0.6 is seen as a float
}

/* Creating set up and tear down */
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

/* Mocking the age limit */
void recupAge(int* ageLimit){
    function_called();
    *ageLimit = (int)mock();
}
static void inflim_tourist(void **state){
    (void) state;
    expect_function_calls(recupAge, 1);
    will_return(recupAge, 14);
    assert_float_equal(0.6, computePriceLim(10,0), 0.001);
}




/* Main function to list our tests */
int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(inf12_notourist),
        cmocka_unit_test(inf12_tourist),
        cmocka_unit_test(sup12_notourist),
        cmocka_unit_test(sup12_tourist),
        cmocka_unit_test(assertTrue),
        cmocka_unit_test(inflim_tourist),
    };
 //   cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests_name("TEST", tests, setup, teardown);
}
