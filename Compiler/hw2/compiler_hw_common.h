#ifndef COMPILER_HW_COMMON_H
#define COMPILER_HW_COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Add what you need */

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_QUO,
    OP_REM,
    OP_EQL,
    OP_NEQ,
    OP_LSS,
    OP_LEQ,
    OP_GTR,
    OP_GEQ,
    OP_POS,
    OP_NEG,
    OP_NOT,
    OP_LOR,
    OP_LAND,
    OP_ASSIGN,
    OP_ADD_ASSIGN,
    OP_SUB_ASSIGN,
    OP_MUL_ASSIGN,
    OP_QUO_ASSIGN,
    OP_REM_ASSIGN,
} op_t;

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_FUNC,
} type_t;

#endif /* COMPILER_HW_COMMON_H */