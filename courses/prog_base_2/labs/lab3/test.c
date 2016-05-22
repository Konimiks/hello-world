#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "test.h"
#include "queue.h"

static void new_NewQueue_SizeZeroAndEmpty(void ** state) {
	queue_t * queueSmp = queue_new();
	assert_int_equal(0, queue_getSize(queueSmp));
	assert_int_equal(OK, queue_isEmpty(queueSmp));
	queue_free(queueSmp);
}

static void enqueueRand_EnqueueOne_SizeOne(void ** state) {
	queue_t * queueSmp = queue_new();
	queue_enqueueRand(queueSmp);
	assert_int_equal(1, queue_getSize(queueSmp));
	queue_free(queueSmp);
}

static void enqueueRand_EnqueueTwo_SizeTwo(void ** state) {
	queue_t * queueSmp = queue_new();
	for (int i = 0; i < 2; i++) {
		queue_enqueueRand(queueSmp);
	}
	assert_int_equal(2, queue_getSize(queueSmp));
	queue_free(queueSmp);
}

static void getByInd_EnqueueTwoGetFirst_ReturnedFirst(void ** state) {
	queue_t * queueSmp = queue_new();
	float enqElem;
	for (int i = 0; i < 2; i++) {
		enqElem = queue_enqueueRand(queueSmp);
	}
	float getElem = queue_getByInd(queueSmp, 1);
	assert_true(enqElem == getElem);
	queue_free(queueSmp);
}

static void getByInd_EnqueueThreeGetFifth_ErrorCode(void ** state) {
	queue_t * queueSmp = queue_new();
	for (int i = 0; i < 3; i++) {
		queue_enqueueRand(queueSmp);
	}
	assert_true(EMPTY_ELEM == queue_getByInd(queueSmp, 5));
	queue_free(queueSmp);
}

static void getSize_EnqueueFourGetTwo_SizeFour(void ** state) {
	queue_t * queueSmp = queue_new();
	for (int i = 0; i < 4; i++) {
		queue_enqueueRand(queueSmp);
	}
	queue_getByInd(queueSmp, 1);
	queue_getByInd(queueSmp, 2);
	assert_int_equal(4, queue_getSize(queueSmp));
	queue_free(queueSmp);
}

static void getSize_EnqueueTen_SizeTenAndFull(void ** state) {
	queue_t * queueSmp = queue_new();
	for (int i = 0; i < 10; i++) {
		queue_enqueueRand(queueSmp);
	}
	assert_int_equal(10, queue_getSize(queueSmp));
	assert_int_equal(OK, queue_isFull(queueSmp));
	queue_free(queueSmp);
}

void cmockaTest(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(new_NewQueue_SizeZeroAndEmpty),
		cmocka_unit_test(enqueueRand_EnqueueOne_SizeOne),
		cmocka_unit_test(enqueueRand_EnqueueTwo_SizeTwo),
		cmocka_unit_test(getByInd_EnqueueTwoGetFirst_ReturnedFirst),
		cmocka_unit_test(getByInd_EnqueueThreeGetFifth_ErrorCode),
		cmocka_unit_test(getSize_EnqueueFourGetTwo_SizeFour),
		cmocka_unit_test(getSize_EnqueueTen_SizeTenAndFull)
	};
	cmocka_run_group_tests(tests, NULL, NULL);
}
