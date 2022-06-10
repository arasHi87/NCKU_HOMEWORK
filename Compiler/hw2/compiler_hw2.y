/* Please feel free to modify any content */

/* Definition section */
%{
    #include "compiler_hw_common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Custom variables to matian symbol table */
    typedef struct node {
        int idx;
        int addr;
        int lineno;
        char name[32]; 
        char func[32];
        type_t type;

        struct node *next;
    } Node;

    typedef struct table {
        Node* head;
        Node* tail;
        int cnt;    // count address
    } Table;

    int scope;            // symbol table index
    Table* s_table[1024]; // symbol table

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol();
    static Node* lookup_symbol();
    static void dump_symbol();
    static void insert_node();
    static Node* init_node();
    static char get_type();

    /* Global variables */
    int scope = 0;
    int addr = 0;
    bool HAS_ERROR = false;

    int op_idx;
    op_t ops[1024];

    /* Function */
    const char* get_op_name(op_t op) {
        switch (op) {
            case OP_ADD:
                return "ADD";
            case OP_SUB:
                return "SUB";
            case OP_MUL:
                return "MUL";
            case OP_QUO:
                return "QUO";
            case OP_REM:
                return "REM";
            case OP_EQL:
                return "EQL";
            case OP_NEQ:
                return "NEQ";
            case OP_LSS:
                return "LSS";
            case OP_LEQ:
                return "LEQ";
            case OP_GTR:
                return "GTR";
            case OP_GEQ:
                return "GEQ";
            case OP_POS:
                return "POS";
            case OP_NEG:
                return "NEG";
            case OP_NOT:
                return "NOT";
            case OP_LOR:
                return "LOR";
            case OP_LAND:
                return "LAND";
            case OP_ASSIGN:
                return "ASSIGN";
            case OP_ADD_ASSIGN:
                return "ADD";
            case OP_SUB_ASSIGN:
                return "SUB";
            case OP_MUL_ASSIGN:
                return "MUL";
            case OP_QUO_ASSIGN:
                return "QUO";
            case OP_REM_ASSIGN:
                return "REM";
            default:
                return "unknown";
        }
    }

    const char* get_type_name(type_t type) {
        switch (type) {
            case TYPE_INT:
                return "int32";
            case TYPE_FLOAT:
                return "float32";
            case TYPE_BOOL:
                return "bool";
            case TYPE_STRING:
                return "string";
            case TYPE_FUNC:
                return "func";
            default:
                return "ERROR";
        }
    } 
%}

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 *  - you can add new fields if needed.
 */
%union {
    struct {
        union {
            int i_val;
            float f_val;
            bool b_val;
            char* s_val;
        };
        type_t type;
    } val;
    char *s_val;
    op_t op;
    type_t type;
}

/* Token without return */
%token VAR PACKAGE NEWLINE IDENT RETURN FUNC
%token SEMICOLON COLON COMMA
%token INT FLOAT BOOL STRING
%token INC DEC GEQ LOR LAND EQL NEQ LSS LEQ GTR
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token IF ELSE FOR SWITCH CASE DEFAULT
%token LBRACE RBRACE
%token PRINT PRINTLN
%token ADD SUB MUL QUO REM NOT LPAREN RPAREN

/* Token with return, which need to sepcify type */
%token <val> INT_LIT
%token <val> FLOAT_LIT
%token <val> BOOL_LIT
%token <s_val> STRING_LIT

/* Nonterminal with return, which need to sepcify type */
%type <type> Type
%type <val> Operand
%type <val> Literal
%type <val> UnaryExpr
%type <val> Expression
%type <s_val> FuncOpen
%type <val> PrimaryExpr
%type <val> ConversionExpr
%type <s_val> ParameterList
%type <op> add_op mul_op unary_op assign_op

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : GlobalStatementList
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;

GlobalStatement
    : PackageStmt NEWLINE
    | FunctionDeclStmt
    | NEWLINE
;

PackageStmt
    : PACKAGE IDENT {
        create_symbol(scope++);
        printf("package: %s\n", $<s_val>2);
    }
;

FunctionDeclStmt
    : FuncOpen LPAREN ParameterList RPAREN Type {
        char tmp[4];
        tmp[0] = ')', tmp[1] = get_type($5), tmp[2] = '\0';
        strcat($3, tmp);
        scope--;
        insert_symbol($1, TYPE_FUNC, $3, yylineno + 1);
        scope++;
    } FuncBlock
    | FuncOpen LPAREN RPAREN {
        insert_symbol($1, TYPE_FUNC, "()V", yylineno + 1);
        scope++;
    } FuncBlock
;

FuncOpen
    : FUNC IDENT {
        $$ = $<s_val>2;
        printf("func: %s\n", $$);
        create_symbol(scope);
    }
;

FuncCallStmt
    : IDENT LPAREN RPAREN { 
        Node* tmp = lookup_symbol($<s_val>1);
        printf("call: %s%s\n", tmp->name, tmp->func);
    }
    | IDENT LPAREN  ArgumentList RPAREN {
        Node* tmp = lookup_symbol($<s_val>1);
        printf("call: %s%s\n", tmp->name, tmp->func);
    }
;

ArgumentList
    : Expression
    | ArgumentList COMMA Expression
;

ParameterList
    : IDENT Type {
        scope++;
        // malloc space to store parameter string
        $$ = (char*)malloc(sizeof(char) * 1024);
        $$[0] = '(';
        $$[1] = get_type($2);
        $$[2] = '\0';

        // insert parameter
        printf("param %s, type: %c\n", $<s_val>1, get_type($2));
        insert_symbol($<s_val>1, $2, "", yylineno + 1);
    }
    | ParameterList COMMA IDENT Type { 
        char tmp[2];
        tmp[0] = get_type($4), tmp[1] = '\0';
        strcat($$, tmp);

        // insert parameter
        printf("param %s, type: %c\n", $<s_val>3, get_type($4));
        insert_symbol($<s_val>3, $4, "", yylineno + 1);
    }
;

FuncBlock
    : LBRACE StatementList RBRACE
;

ReturnStmt
    : RETURN            { puts("return"); dump_symbol(); }
    | RETURN Expression { puts("ireturn"); dump_symbol(); }
;

/* ---------- Types ---------- */

Type
    : INT    { $<type>$ = TYPE_INT; }
    | FLOAT  { $<type>$ = TYPE_FLOAT; }
    | STRING { $<type>$ = TYPE_STRING; }
    | BOOL   { $<type>$ = TYPE_BOOL; }
;

/* ---------- Expressions ---------- */

Expression
    : UnaryExpr 
    | Expression binary_op { 
        ops[++op_idx] = $<op>2;
    } Expression {
        while (op_idx) {
            if (ops[op_idx] == OP_REM && ($1.type == TYPE_FLOAT || $4.type == TYPE_FLOAT))
                printf("error:%d: invalid operation: (operator REM not defined on float32)\n", yylineno);
            else if (($1.type == TYPE_INT || $1.type == TYPE_FLOAT) && ($4.type == TYPE_INT || $4.type == TYPE_FLOAT) && $1.type != $4.type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name($1.type),
                    get_type_name($4.type));
            else if ((ops[op_idx] == OP_LAND || ops[op_idx] == OP_LOR) && ($1.type != TYPE_BOOL || $4.type != TYPE_BOOL))
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", 
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name(($1.type == TYPE_BOOL ? $4.type : $1.type)));
            if (HAS_ERROR)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name($1.type),
                    get_type_name($4.type));
            printf("%s\n", get_op_name(ops[op_idx--]));
        }

        HAS_ERROR = false;

        if ($<op>2 == OP_EQL || $<op>2 == OP_NEQ || $<op>2 == OP_LSS|| $<op>2 == OP_LEQ || $<op>2 == OP_GTR || $<op>2 == OP_GEQ)
            $1.type = $4.type = TYPE_BOOL;

        if (($1.type == TYPE_BOOL) || ($4.type == TYPE_BOOL))        $$.type = TYPE_BOOL;
        else if (($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) $$.type = TYPE_FLOAT;
        else                                                         $$.type = TYPE_INT;
    }
;

UnaryExpr
    : PrimaryExpr { $$.type = $1.type; }
    | unary_op UnaryExpr {
        $$.type = $2.type;
        if ($$.type == TYPE_INT)        $$.i_val = ($<op>1 == OP_POS ? $<val>2.i_val : -$<val>2.i_val);
        else if ($$.type == TYPE_FLOAT) $$.f_val = ($<op>1 == OP_POS ? $<val>2.f_val : -$<val>2.f_val);
        printf("%s\n", get_op_name($<op>1));
    }
;

binary_op
    : LOR { 
        while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) printf("%s\n", get_op_name(ops[op_idx--]));
        $<op>$ = OP_LOR;
    }
    | LAND { 
        while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) printf("%s\n", get_op_name(ops[op_idx--]));
        $<op>$ = OP_LAND;
    }
    | cmp_op { while (op_idx) printf("%s\n", get_op_name(ops[op_idx--])); }
    | add_op
    | mul_op
;

cmp_op
    : EQL { $<op>$ = OP_EQL; }
    | NEQ { $<op>$ = OP_NEQ; }
    | LSS { $<op>$ = OP_LSS; }
    | LEQ { $<op>$ = OP_LEQ; }
    | GTR { $<op>$ = OP_GTR; }
    | GEQ { $<op>$ = OP_GEQ; }
;

add_op
    : ADD { $<op>$ = OP_ADD; }
    | SUB { $<op>$ = OP_SUB; }
;

mul_op
    : MUL { $<op>$ = OP_MUL; }
    | QUO { $<op>$ = OP_QUO; }
    | REM { $<op>$ = OP_REM; }
;

unary_op
    : ADD { $<op>$ = OP_POS; }
    | SUB { $<op>$ = OP_NEG; }
    | NOT { $<op>$ = OP_NOT; }
;

/* ---------- Primary expressions ---------- */

PrimaryExpr
    : Operand
    | FuncCallStmt
    | ConversionExpr { $$.type = $1.type; }
;

Operand
    : Literal
    | IDENT   { 
        Node* tmp = lookup_symbol($<s_val>1);
        if (tmp) {
            $$.type = tmp->type;
            printf("IDENT (name=%s, address=%d)\n", tmp->name, tmp->addr);
        } else {
            printf("error:%d: undefined: %s\n", yylineno + 1, $<s_val>1);
            HAS_ERROR = true;
            $$.type = 0x3f3f3f3f;
        }
    }
    | LPAREN Expression RPAREN { $$.type = $2.type; } 
;

Literal
    : INT_LIT    {
        $$.type = TYPE_INT;
        $$.i_val = atoi($<s_val>1);
        printf("INT_LIT %d\n", $$.i_val);
    }
    | FLOAT_LIT  {
        $$.type = TYPE_FLOAT;
        $$.f_val = atof($<s_val>1);
        printf("FLOAT_LIT %f\n", $$.f_val);
    }
    | BOOL_LIT   { 
        $$.type = TYPE_BOOL;
        $$.b_val = !strcmp($<s_val>1, "true") ? true : false;
        printf("%s %d\n", $$.b_val ? "TRUE" : "FALSE", $$.b_val);
    }
    | STRING_LIT {
        $$.type = TYPE_STRING;
        $$.s_val = $<s_val>1;
        printf("STRING_LIT %s\n", $<s_val>1); }
;

/* ---------- Conversion ---------- */

ConversionExpr
    : Type LPAREN Expression RPAREN { 
        $<s_val>$ = $<s_val>1;
        if ($1 == TYPE_INT) puts("f2i"), $$.type = TYPE_INT;
        else                puts("i2f"), $$.type = TYPE_FLOAT;
    }
;

/* ---------- Statements ---------- */

Statement
    : DeclarationStmt NEWLINE
    | SimpleStmt NEWLINE
    | Block
    | IfStmt
    | ForStmt
    | SwitchStmt
    | CaseStmt
    | PrintStmt NEWLINE
    | ReturnStmt NEWLINE
    | NEWLINE
;

SimpleStmt
    : AssignmentStmt | ExpressionStmt | IncDecStmt
;

DeclarationStmt
    : VAR IDENT Type {
        Node* tmp = lookup_symbol($<s_val>2);
        if (tmp) printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, $<s_val>2, tmp->lineno);
        insert_symbol($<s_val>2, $3, "", yylineno);
    }
    | VAR IDENT Type ASSIGN Expression { insert_symbol($<s_val>2, $3, "", yylineno); }
;

AssignmentStmt
    : Expression assign_op {
        ops[++op_idx] = $<op>2;
    } Expression {
        while (op_idx) {
            if (($1.type == TYPE_INT || $1.type == TYPE_FLOAT) && ($4.type == TYPE_INT || $4.type == TYPE_FLOAT) && $1.type != $4.type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name($1.type),
                    get_type_name($4.type));
            if (HAS_ERROR)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                        yylineno,
                        get_op_name(ops[op_idx]),
                        get_type_name($1.type),
                        get_type_name($4.type));
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        HAS_ERROR = false;
    }
;

assign_op
    : ASSIGN     { $<op>$ = OP_ASSIGN;}
    | ADD_ASSIGN { $<op>$ = OP_ADD_ASSIGN; }
    | SUB_ASSIGN { $<op>$ = OP_SUB_ASSIGN; }
    | MUL_ASSIGN { $<op>$ = OP_MUL_ASSIGN; }
    | QUO_ASSIGN { $<op>$ = OP_QUO_ASSIGN; }
    | REM_ASSIGN { $<op>$ = OP_REM_ASSIGN; }
;

ExpressionStmt
    : Expression
;

IncDecStmt
    : Expression INC { puts("INC"); }
    | Expression DEC { puts("DEC"); }
;

Block
    : LBRACE               { create_symbol(scope++); 
    } StatementList RBRACE { dump_symbol(); }
;

StatementList
    : Statement
    | Statement StatementList
;

IfStmt
    : IF Condition Block
    | IF Condition Block ELSE Block
    | IF Condition Block ELSE IfStmt
;

Condition
    : Expression {
        if ($1.type != TYPE_BOOL)
            printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 1, get_type_name($1.type));
    }
;

ForStmt
    : FOR Condition Block
    | FOR ForClause Block
;

ForClause
    : InitStmt SEMICOLON Condition SEMICOLON PostStmt
;

InitStmt
    : SimpleStmt
;

PostStmt
    : SimpleStmt
;

SwitchStmt
    : SWITCH Expression Block
;

CaseStmt
    : CASE INT_LIT {
        printf("case %s\n", $<s_val>2);
    }  COLON Block
    | DEFAULT COLON Block
;

PrintStmt
    : PRINT LPAREN Expression RPAREN   { printf("PRINT %s\n", get_type_name($3.type)); }
    | PRINTLN LPAREN Expression RPAREN { printf("PRINTLN %s\n", get_type_name($3.type)); }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

    while (scope) dump_symbol();

	printf("Total lines: %d\n", yylineno + 1);
    fclose(yyin);
    return 0;
}

static void create_symbol(int scope) {
    printf("> Create symbol table (scope level %d)\n", scope);
    s_table[scope] = (Table*)malloc(sizeof(Table));
    s_table[scope]->head = NULL;
    s_table[scope]->tail = NULL;
    s_table[scope]->cnt = 0; 
}

static void insert_symbol(char* name, type_t type, char* func, int lineno) {
    Node* tmp = init_node(name, type, func, lineno);
    insert_node(tmp);

    printf("> Insert `%s` (addr: %d) to scope level %d\n", tmp->name, tmp->addr, scope - 1);
}

static Node* lookup_symbol(char* name) {
    int idx = scope - 1;
    while (idx >= 0) {
        Node* tmp = s_table[idx]->head;
        while (tmp) {
            if (!strcmp(tmp->name, name))
                return tmp;
            tmp = tmp->next;
        }
        idx--;
    }
    return NULL;
}

static void dump_symbol() {
    int idx = scope - 1;
    Node* tmp = s_table[idx]->head;
    printf("\n> Dump symbol table (scope level: %d)\n", idx);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s\n",
            "Index", "Name", "Type", "Addr", "Lineno", "Func_sig");

    while (tmp) {
        printf("%-10d%-10s%-10s%-10d%-10d%-10s\n",
                tmp->idx, tmp->name, get_type_name(tmp->type), tmp->addr, tmp->lineno, tmp->func);
        tmp = tmp->next;
    }

    puts(""), scope--;
}

static Node* init_node(char* name, type_t type, char* func, int lineno) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    int idx = scope - 1;
    
    // calculate address and index
    tmp->idx = (s_table[idx]->tail == NULL ? 0 : s_table[idx]->tail->idx + 1);
    
    tmp->type = type;
    strcpy(tmp->name, name);
    strcpy(tmp->func, func);

    if (strlen(func) != 0) {
        tmp->addr = -1;
        printf("func_signature: %s\n", func);
    } else {
        tmp->addr = addr++;
        strcpy(tmp->func, "-\0");
    }

    tmp->lineno = lineno;
    return tmp;
}

static void insert_node(Node* node) {
    int idx = scope - 1;
    if (!s_table[idx]->head) s_table[idx]->head = s_table[idx]->tail = node;
    else {
        s_table[idx]->tail->next = node;
        s_table[idx]->tail = node;
    }
}

static char get_type(type_t type) {
    return (char)(get_type_name(type)[0] - 'a' + 'A');
}