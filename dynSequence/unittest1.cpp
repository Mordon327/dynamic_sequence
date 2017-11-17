#include<iostream>
#include "test.h"
#include "sequence2.h"



void test_empty()
{
	sequence testSeq;
	test_(0.0 == testSeq.current());
	test_(!testSeq.is_item());
	test_(0 == testSeq.size());
}

void test_attach_to_empty()
{
	sequence testSeq;
	testSeq.attach(10);
	test_(1 == testSeq.size());
}

void test_insert_to_empty()
{
	sequence testSeq;
	testSeq.insert(10);
	test_(1 == testSeq.size());
	test_(10.0 == testSeq.current());
}

void test_insert_in_front()
{
	sequence testSeq;
	int len = 4;
	double expected[] = { 5, 10, 20, 30 };
	for (int i = 1; i < len; i++) {
		testSeq.attach(expected[i]);
		test_(expected[i] == testSeq.current());
	}
	testSeq.start();
	testSeq.insert(expected[0]);
	testSeq.start();
	for (int i = 0; i < len; i++) {
		test_(expected[i] == testSeq.current());
		testSeq.advance();
	}
}

void test_insert_in_middle()
{
	sequence testSeq;
	testSeq.attach(10);
	testSeq.attach(20);
	testSeq.attach(30);
	testSeq.start();
	testSeq.advance();
	testSeq.insert(15);
	testSeq.start();
	int len = 4;
	double expected[] = { 10,15,20,30 };
	for (int i = 0; i < len; i++) {
		test_(expected[i] == testSeq.current());
		testSeq.advance();
	}
}

void test_attach_in_middle()
{
	sequence testSeq;
	testSeq.attach(10);
	testSeq.attach(20);
	testSeq.attach(30);
	testSeq.start();
	testSeq.advance();
	testSeq.attach(15);
	testSeq.start();
	int len = 4;
	double expected[] = { 10, 20,15, 30 };
	for (int i = 0; i < len; i++) {
		test_(expected[i] == testSeq.current());
		testSeq.advance();
	}
}

void test_attach_in_front()
{
	sequence testSeq;
	testSeq.attach(10);
	testSeq.attach(20);
	testSeq.attach(30);
	testSeq.start();
	testSeq.attach(15);
	testSeq.start();
	int len = 4;
	double expected[] = { 10, 15, 20, 30 };
	for (int i = 0; i < len; i++) {
		test_(expected[i] == testSeq.current());
		testSeq.advance();
	}
}

void test_advance_beyond_two()
{
	sequence testSeq;
	testSeq.attach(20);
	testSeq.attach(30);
	//test_(20.0, testSeq.current());
	testSeq.advance();
	test_(!testSeq.is_item());
}

void test_advance_beyond_three()
{
	sequence testSeq;
	testSeq.attach(20);
	testSeq.attach(30);
	testSeq.insert(10);
	testSeq.advance();
	testSeq.advance();
	testSeq.advance();
	test_(!testSeq.is_item());
}



void test_advance_beyond_full()
{
	sequence testSeq;
	for (int i = 1; i <= testSeq.DEFAULT_CAPACITY; i++) {
		testSeq.attach(10 * i);
	}
	testSeq.start();
	for (int i = 1; i <= testSeq.DEFAULT_CAPACITY; i++) {
		//Assert::IsTrue(testSeq.is_item());
		test_((double)10 * i == testSeq.current());
		testSeq.advance();
	}
	test_(!testSeq.is_item());
}

void test_remove_middle_first_last()
{
	sequence testSeq;
	double expected[] = { 10, 30 };
	for (int i = 10; i < 40; i += 10) {
		testSeq.attach(i);
	}
	testSeq.start();
	testSeq.advance();
	testSeq.remove_current();
	test_(2 == testSeq.size());
	testSeq.start();
	for (int i = 0; i < 2; i++, testSeq.advance())
	{
		test_(expected[i] == testSeq.current());
	}
	testSeq.start();
	testSeq.remove_current();
	test_(1 == testSeq.size());
	testSeq.start();
	test_(30.0 == testSeq.current());
	testSeq.remove_current();
	test_(0 == testSeq.size());
}

void test_romove_middle_last_first()
{
	sequence testSeq;
	double expected[] = { 10, 30 };
	for (int i = 10; i < 40; i += 10) {
		testSeq.attach(i);
	}
	testSeq.start();
	testSeq.advance();
	testSeq.remove_current();
	test_(2 == testSeq.size());
	testSeq.start();
	for (int i = 0; i < 2; i++, testSeq.advance())
	{
		test_(expected[i] == testSeq.current());
	}
	testSeq.start();
	testSeq.advance();
	testSeq.remove_current();
	test_(1 == testSeq.size());
	testSeq.start();
	test_(10.0 == testSeq.current());
	testSeq.remove_current();
	test_(0 == testSeq.size());
}

void test_fill_then_remove_all() {

	sequence testSeq;

	for (int i = 0; i < testSeq.DEFAULT_CAPACITY; i++, testSeq.advance())
	{
		testSeq.attach(65);
	}
	for (int i = 0; i < testSeq.DEFAULT_CAPACITY; i++, testSeq.advance())
	{
		testSeq.remove_current();
	}
	testSeq.remove_current();
}

void test_resize() {
	sequence testSeq;
	int new_capacity = 2 * testSeq.DEFAULT_CAPACITY;
	testSeq.resize(new_capacity);
	for (int i = 0; i < new_capacity; i++)
	{
		testSeq.attach(i);
	}
	testSeq.start();
	for (int i = 0; i < new_capacity; i++, testSeq.advance())
	{
		test_((double)i == testSeq.current());
	}
	test_(new_capacity == testSeq.size());
	//try an illegal resize--nothing should change
	testSeq.resize(1);
	test_(new_capacity == testSeq.size());
}

void test_copy_constructor() {
	sequence original;
	sequence copy1(original);
	original.attach(1);
	test_(original.size() != copy1.size());

}

void test_op_assignment() {
	sequence original;
	sequence copy1;
	copy1 = original;
	original.attach(1);
	(original.size() != copy1.size());

}

void test_op_assign_self() {
	sequence original;
	original.attach(1);
	original = original;
	test_(1 == original.size());
	original.start();
	test_(1.0 == original.current());
}

void unit_tests() {
	test_empty();
	test_attach_to_empty();
	test_insert_to_empty();
	test_insert_in_front();
	test_insert_in_middle();
	test_attach_in_middle();
	test_attach_in_front();
	test_advance_beyond_two();
	test_advance_beyond_three();
	test_advance_beyond_full();
	test_remove_middle_first_last();
	test_romove_middle_last_first();
	test_fill_then_remove_all();
	test_resize();
	test_copy_constructor();
	test_op_assignment();
	test_op_assign_self();

}

int main()
{
	unit_tests();
	report_();
	std::cin.ignore();
	return 0;

}
