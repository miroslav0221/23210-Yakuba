#include <iostream>
#include <gtest/gtest.h>
#include "CircularBuffer.h"

// TEST(Test_front, Test_front_throw) {
//     CircularBuffer cb;
//     EXPECT_THROW(cb.front(), std::logic_error);
// }

TEST(Test_constructor_copy, Test_copy) {
    CircularBuffer cb(10, 'a');
    CircularBuffer cb_new(cb);
    EXPECT_EQ(cb == cb_new, true);
}
TEST(Test_constructor_cap, Test) {
    CircularBuffer cb(10);
    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_EQ(cb.size(), 0);
}

TEST(Test_operator_brackets_const, Test_op) {
    const CircularBuffer cb(10, 'a');
    EXPECT_EQ(cb[0], 'a');
}
TEST(Test_at, Test_const) {
    const CircularBuffer cb(10, 'a');
    EXPECT_THROW(cb.at(100), std::out_of_range);
}

TEST(Test_at, Test_not_const) {
    CircularBuffer cb(10, 'a');
    EXPECT_THROW(cb.at(100), std::out_of_range);
    EXPECT_EQ(cb.at(0), 'a');
}


TEST(Test_front, Test_front) {
    CircularBuffer cb;
    CircularBuffer cb_new(10);
    CircularBuffer cb_new_r(10, 'a');
    EXPECT_EQ(cb_new_r.front(), 'a');
}
TEST(Test_back, Test_back) {
    CircularBuffer cb;
    CircularBuffer cb_new(10);
    CircularBuffer cb_new_r(10, 'a');
    EXPECT_EQ(cb_new_r.back(), 'a');

}

TEST(Test_front_const, Test_front_throw_const) {
    const CircularBuffer cb;
    const CircularBuffer cb_new(10);
    const CircularBuffer cb_new_r(10, 'a');
    EXPECT_EQ(cb_new_r.front(), 'a');
}

TEST(Test_back_const, Test_back_throw_const) {
    const CircularBuffer cb;
    const CircularBuffer cb_new(10);
    const CircularBuffer cb_new_r(10, 'a');
    EXPECT_EQ(cb_new_r.back(), 'a');

}


TEST(Test_linerize, Test_is_linearized) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.is_linearized(), true);
}

TEST(Test_linerize, Test_not_linearized) {
    CircularBuffer cb(5, 'a');
    cb.push_back('k');
    EXPECT_EQ((*cb.linearize()), cb[0]);
}

TEST(Test_linerized, Test_linearized) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(*(cb.linearize()), cb[0]);
}

TEST(Test_rotate, Test_rotate_throw) {
    CircularBuffer cb(10, 'b');
    EXPECT_THROW(cb.rotate(11), std::invalid_argument);
}

TEST(Test_rotate, Test_rotate) {
    CircularBuffer cb(10, 'b');
    cb.rotate(3);
}

TEST(Test_size, Test_size) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.capacity(), 5);
}

TEST(Test_empty, Test_empty) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.empty(), false);
    cb.clear();
    EXPECT_EQ(cb.empty(), true);
}

TEST(Test_full, Test_full) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.full(), true);
    cb.pop_back();
    EXPECT_EQ(cb.full(), false);
}

TEST(Test_reserve, Test_reserve) {
    CircularBuffer cb(5, 'a');
    EXPECT_EQ(cb.reserve(), 0);
    cb.pop_back();
    EXPECT_EQ(cb.reserve(), 1);

}

TEST(Test_set_capacity, Test_argument) {
    CircularBuffer cb(10, 'a');
    EXPECT_THROW(cb.set_capacity(-1), std::logic_error);
}

TEST(Test_set_capacity, Test_work) {
    CircularBuffer cb(10, 'a');
    cb.set_capacity(11);
    EXPECT_EQ(cb.capacity(), 11);
}

TEST(Test_resize, Test_argument) {
    CircularBuffer cb;
    EXPECT_THROW(cb.resize(-1), std::logic_error);
}

TEST(Test_resize, Test_new_size_more) {
    CircularBuffer cb(10, 'a');
    cb.resize(12, 'b');
    EXPECT_EQ(cb.size(), 12);
    cb.resize(8, 'b');
    EXPECT_EQ(cb.size(), 8);
}

TEST(Test_swap, Test_swap) {
    CircularBuffer cb;
    CircularBuffer buf(10, 'a');
    CircularBuffer cb_save;
    CircularBuffer buf_save;
    cb_save = cb;
    buf_save = buf;
    cb.swap(buf);
    EXPECT_EQ(cb == buf_save, true);
    EXPECT_EQ(buf == cb_save, true);
}

TEST(Test_operator_equality, Test_op_1) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(10, 'a');
    EXPECT_EQ(cb1==cb2, true);
}

TEST(Test_operator_equality, Test_op_2) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(10, 'b');
    EXPECT_EQ(cb1==cb2, false);
}

TEST(Test_operator_equality, Test_op_3) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(9, 'a');
    EXPECT_EQ(cb1==cb2, false);
}

TEST(Test_operator_not_equality, Test_op_1) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(10, 'a');
    EXPECT_EQ(cb1!=cb2, false);
}

TEST(Test_operator_not_equality, Test_op_2) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(10, 'b');
    EXPECT_EQ(cb1!=cb2, true);
}

TEST(Test_operator_not_equality, Test_op_3) {
    const CircularBuffer cb1(10, 'a');
    const CircularBuffer cb2(9, 'a');
    EXPECT_EQ(cb1!=cb2, true);
}

TEST(Test_push_back, Test) {
    CircularBuffer cb(10);
    cb.push_back('a');
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb.size(), 1);
}

TEST(Test_push_front, Test_start0) {
    CircularBuffer cb(10, 'a');
    cb.push_front('b');
    EXPECT_EQ(cb[0], 'b');
}

TEST(Test_push_front, Test) {
    CircularBuffer cb(10);
    cb.push_front('b');
    cb.push_front('b');
    EXPECT_EQ(cb[1], 'b');
}
//
// TEST(Test_pop_front, Test_size) {
//     CircularBuffer cb(10);
//     EXPECT_THROW(cb.pop_front(), std::out_of_range);
// }
//
// TEST(Test_pop_back, Test_size) {
//     CircularBuffer cb(10);
//     EXPECT_THROW(cb.pop_back(), std::out_of_range);
// }

TEST(Test_pop_back, Test_end) {
    CircularBuffer cb(10);
    cb.push_back('k');
    cb.push_back('k');
    cb.pop_back();
    EXPECT_EQ(cb[9], static_cast<value_type>(0));
}

TEST(Test_insert, Test_insert) {
    CircularBuffer cb(10, 'a');
    EXPECT_THROW(cb.insert(-1,'b'), std::out_of_range);
    cb.insert(0, 'b');
    EXPECT_EQ(cb[0], 'b');
}

TEST(Test_erase, Test_throw) {
    CircularBuffer cb(10, 'a');
    EXPECT_THROW(cb.erase(-15, 3), std::out_of_range);
    EXPECT_THROW(cb.erase(3, 0), std::invalid_argument);
}

TEST(Test_erase, Test_neg) {
    CircularBuffer cb(10, 'a');
    cb.insert(9, 'q');
    cb.erase(3, -2);
    EXPECT_EQ(cb[4], 'q');
}
TEST(Test_erase, Test) {
    CircularBuffer cb(10, 'a');
    cb.erase(4,7);
    EXPECT_EQ(cb[9], static_cast<value_type>(0));
}

TEST(Test_operator, Test_negative_num) {
    CircularBuffer cb(10, 'a');
    cb.insert(0, 'b');
    cb.insert(1, 'c');
    EXPECT_EQ(cb[-10], 'b');
    EXPECT_EQ(cb[-9], 'c');
    EXPECT_EQ(cb[-8], 'a');
}

TEST(Test_push_front, Test_end0) {
    CircularBuffer cb(3, 'a');
    cb.push_front('b');
    cb.push_front('c');
    cb.push_front('d');
    cb.push_front('e');
    cb.push_front('k');
    EXPECT_EQ(cb[2], 'd');
}

TEST(Test_rotate, Test_new_begin_neg) {
    CircularBuffer cb(10, 'a');
    cb.insert(9, 'q');
    cb.rotate(-1);
    EXPECT_EQ(cb[0], 'q');
}

TEST(Test_const_op, Test_neg) {
    const CircularBuffer cb(10, 'a');
    EXPECT_EQ(cb[-1], 'a');
}