#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    s21_decl_to_null(result);
    if ((value_1.state == S21_PLUS_INF && value_2.state == S21_MINUS_INF) ||
        (value_1.state == S21_MINUS_INF && value_2.state == S21_PLUS_INF)) {
        flag = 3;
        result->state = S21_NAN;
    } else if (value_1.state == S21_PLUS_INF || value_2.state == S21_PLUS_INF) {
        flag = 1;
        result->state = S21_PLUS_INF;
    } else if (value_1.state == S21_MINUS_INF || value_2.state == S21_MINUS_INF) {
        flag = 2;
        result->state = S21_MINUS_INF;
    } else if (value_1.state == S21_NAN || value_2.state == S21_NAN) {
        flag = 3;
        result->state = S21_NAN;
    } else if (value_1.state == S21_NULL) {
        s21_copy(result, value_2);
        s21_set_sign(result, 1);
    } else if (value_2.state == S21_NULL) {
        s21_copy(result, value_1);
    } else if (value_1.state == S21_NORMAL && value_2.state == S21_NORMAL) {
        if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
            int sign_1 = s21_get_sign(value_1);
            int sign_2 = s21_get_sign(value_2);
            s21_set_sign(&value_1, 0);
            s21_set_sign(&value_2, 0);

            if (s21_is_greater(value_1, value_2)) {
                flag = s21_simple_sub(value_1, value_2, result);
                s21_set_sign(result, sign_1);
            } else {
                flag = s21_simple_sub(value_2, value_1, result);

                s21_set_sign(result, !sign_2);
            }
        } else {
            s21_set_sign(&value_2, !s21_get_sign(value_2));
            flag = s21_add(value_1, value_2, result);
        }
        if (!flag) {
            result->state = S21_NORMAL;
        }
    }
    return flag;
}
