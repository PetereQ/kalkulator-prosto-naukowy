#ifndef EVALUATE_RESULT_H
#define EVALUATE_RESULT_H
typedef enum {
    ERR_NONE,
    ERR_SYNTAX,
    ERR_DIV_ZERO,
    ERR_NEG_ROOT,
    ERR_PAREN,
    ERR_RANGE,
    ERR_OVERFLOW,
    ERR_TOO_LONG
} ErrorCode;
ErrorCode validate_and_eval(const char* expr,double* result);

#endif // EVALUATE_RESULT_H
