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

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

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
    static Node* insert_symbol();
    static Node* lookup_symbol();
    static void dump_symbol();
    static void insert_node();
    static Node* init_node();
    static char get_type();

    const char* get_op_name();
    const char* get_ls_name();
    const char* get_type_name();
    const char* get_print_type();

    void get_op_inst(); // operation instruct

    /* Global variables */
    bool g_has_error = false;
    FILE *fout = NULL;
    char buffer[128]; // use to store string function return value
    char assign[128]; // use to store which parameter should be assign
    int kase[128];    // use to store case expression
    int label[128];   // use to matain label
    int g_indent_cnt = 0;
    int scope = 0;
    int addr = 0;
    int c_exp;        // use to check if current expression is const expression
    int returned = 0; // if function already returned;
    int op_idx;       // operation stake index
    int lb_idx;       // label stake index
    int ks_idx;       // kase stake index
    int sw_cnt;       // switch statement count
    int fr_cnt;       // for statement count
    int ce_cnt;       // const expression count
    op_t ops[1024];
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
        char name[16];
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
%token IF FOR SWITCH CASE DEFAULT
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
        CODEGEN(".method public static %s%s\n", $1, $3);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
        scope++;
        returned = 0;
    } FuncBlock {
        if (!returned) {
            returned = 1;
            CODEGEN("\treturn\n");
            CODEGEN(".end method\n");
        }
    }
    | FuncOpen LPAREN RPAREN {
        insert_symbol($1, TYPE_FUNC, "()V", yylineno + 1);
        if (!strcmp($1, "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                     CODEGEN(".method public static %s()V\n", $1);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
        scope++;
        returned = 0;
    } FuncBlock {
        if (!returned) {
            returned = 1;
            CODEGEN("\treturn\n");
            CODEGEN(".end method\n");
        }
    }
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
        CODEGEN("\tinvokestatic Main/%s%s\n", tmp->name, tmp->func);
    }
    | IDENT LPAREN  ArgumentList RPAREN {
        Node* tmp = lookup_symbol($<s_val>1);
        printf("call: %s%s\n", tmp->name, tmp->func);
        CODEGEN("\tinvokestatic Main/%s%s\n", tmp->name, tmp->func);
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
    : RETURN {
        puts("return");
        dump_symbol();
        CODEGEN("\treturn\n");
        CODEGEN(".end method\n");
    }
    | RETURN Expression {
        puts("ireturn");
        dump_symbol(); 
        CODEGEN("\tireturn\n");
        CODEGEN(".end method\n");
    }
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
        // Lgogic operation
        if ($<op>2 == OP_LOR || $<op>2 == OP_LAND) {
            while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) {
                get_op_inst(buffer, $<val>1.type, ops[op_idx]);
                CODEGEN("\t%s", buffer);

                // deal compare op
                if ($<val>1.type == TYPE_FLOAT) CODEGEN("\n");
                else {
                    if (ops[op_idx] == EQL || ops[op_idx] == OP_NEQ || ops[op_idx] == OP_LSS
                    || ops[op_idx] == OP_LEQ || ops[op_idx] == OP_GTR || ops[op_idx] == OP_GEQ){
                        CODEGEN(" L_cmp_%d\n", ce_cnt++);
                        CODEGEN("\ticonst_1\n");
                        CODEGEN("\tgoto L_cmp_%d\n", ce_cnt++);
                        CODEGEN("L_cmp_%d:\n", ce_cnt - 2);
                        CODEGEN("\ticonst_0\n");
                        CODEGEN("L_cmp_%d:\n", ce_cnt - 1);
                    } else CODEGEN("\n");
                }
                printf("%s\n", get_op_name(ops[op_idx--]));
            }
        }

        // compare operation
        if ($<op>2 == EQL || $<op>2 == OP_NEQ || $<op>2 == OP_LSS || $<op>2 == OP_LEQ || $<op>2 == OP_GTR || $<op>2 == OP_GEQ ) {
            while (op_idx) { 
                get_op_inst(buffer, $<val>1.type, ops[op_idx]);
                printf("%s\n", get_op_name(ops[op_idx--]));
                CODEGEN("\t%s\n", buffer);
            }
        }
        ops[++op_idx] = $<op>2;
    } Expression {
        // check expression type
        if ($<op>2 == OP_EQL || $<op>2 == OP_NEQ || $<op>2 == OP_LSS|| $<op>2 == OP_LEQ || $<op>2 == OP_GTR || $<op>2 == OP_GEQ)
            $1.type = $4.type = TYPE_BOOL;
        if (($1.type == TYPE_BOOL) || ($4.type == TYPE_BOOL))        $$.type = TYPE_BOOL;
        else if (($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) $$.type = TYPE_FLOAT;
        else                                                         $$.type = TYPE_INT;

        // detect error and print operation stack
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
            if (g_has_error)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name($1.type),
                    get_type_name($4.type));
            if (ops[op_idx] != OP_ASSIGN) {
                get_op_inst(buffer, $$.type, ops[op_idx]);
                if (ops[op_idx] == OP_EQL || ops[op_idx] == OP_NEQ || ops[op_idx] == OP_LSS
                || ops[op_idx] == OP_LEQ || ops[op_idx] == OP_GTR || ops[op_idx] == OP_GEQ) {
                    if (!c_exp) CODEGEN("\t%s Label_%d\n", buffer, lb_idx);
                    else {
                        
                    }
                } else
                    CODEGEN("\t%s\n", buffer);
            } else {
                Node* tmp = lookup_symbol(assign);
                CODEGEN("\t%s %d\n", get_ls_name($1.type, 1), tmp->addr);
            }
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        g_has_error = false;
    }
;

UnaryExpr
    : PrimaryExpr { $$.type = $1.type; }
    | unary_op UnaryExpr {
        $$.type = $2.type;
        if ($$.type == TYPE_INT || $$.type == TYPE_BOOL) {
            if ($1 == OP_POS)      $$.i_val = $<val>2.i_val;
            else if ($1 == OP_NEG) $$.i_val = -$<val>2.i_val;
            else                   $$.i_val = ~$<val>2.i_val + 2;
            if ($1 == OP_NEG) CODEGEN("\tineg\n");
        }
        else if ($$.type == TYPE_FLOAT) {
            $$.f_val = ($<op>1 == OP_POS ? $<val>2.f_val : -$<val>2.f_val);
            if ($1 == OP_NEG) CODEGEN("\tfneg\n");
        }

        printf("%s\n", get_op_name($<op>1));
    }
;

binary_op
    : LOR  { $<op>$ = OP_LOR; }
    | LAND { $<op>$ = OP_LAND; }
    | cmp_op
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
            strcpy($$.name, tmp->name);
            CODEGEN("\t%s %d\n", get_ls_name($$.type, 0), tmp->addr);
            printf("IDENT (name=%s, address=%d)\n", tmp->name, tmp->addr);
        } else {
            printf("error:%d: undefined: %s\n", yylineno + 1, $<s_val>1);
            g_has_error = true;
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
        if ($$.i_val >= 0 && $$.i_val <= 5) CODEGEN("\ticonst_%d\n", $$.i_val);
        else                                CODEGEN("\tldc %d\n", $$.i_val);
    }
    | FLOAT_LIT  {
        $$.type = TYPE_FLOAT;
        $$.f_val = atof($<s_val>1);
        printf("FLOAT_LIT %f\n", $$.f_val);
        CODEGEN("\tldc %f\n", $$.f_val);
    }
    | BOOL_LIT   { 
        $$.type = TYPE_BOOL;
        $$.b_val = !strcmp($<s_val>1, "true") ? true : false;
        $$.i_val = $$.b_val;
        printf("%s %d\n", $$.b_val ? "TRUE" : "FALSE", $$.b_val);
        CODEGEN("\tldc %d\n", $$.b_val);
    }
    | STRING_LIT {
        $$.type = TYPE_STRING;
        $$.s_val = $<s_val>1;
        printf("STRING_LIT %s\n", $<s_val>1); 
        CODEGEN("\tldc \"%s\"\n", $$.s_val);
    }
;

/* ---------- Conversion ---------- */

ConversionExpr
    : Type LPAREN Expression RPAREN { 
        $<s_val>$ = $<s_val>1;
        if ($1 == TYPE_INT) {
            $$.type = TYPE_INT;
            puts("f2i");
            CODEGEN("\tf2i\n");
        } else { 
            $$.type = TYPE_FLOAT;
            puts("i2f");
            CODEGEN("\ti2f\n");
        }
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
    | ReturnStmt NEWLINE { returned = 1; }
    | NEWLINE
;

SimpleStmt
    : AssignmentStmt
    | ExpressionStmt
    | IncDecStmt
;

DeclarationStmt
    : VAR IDENT Type {
        Node* tmp = lookup_symbol($<s_val>2);

        // check re-declaration
        if (tmp) printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, $<s_val>2, tmp->lineno);
        
        // push default val to operation stack
        if ($3 == TYPE_INT)         CODEGEN("\tldc 0\n");
        else if ($3 == TYPE_FLOAT)  CODEGEN("\tldc 0.0\n");
        else if ($3 == TYPE_STRING) CODEGEN("\tldc \"\"\n");
        else                        CODEGEN("\terror\n");

        // get insert node and write buffer
        tmp = insert_symbol($<s_val>2, $3, "", yylineno);
        CODEGEN("\t%s %d\n",get_ls_name($3, 1), tmp->addr);
    }
    | VAR IDENT Type ASSIGN Expression { 
        Node* tmp = insert_symbol($<s_val>2, $3, "", yylineno);

        // store variable to local variable
        CODEGEN("\t%s %d\n", get_ls_name($3, 1), tmp->addr);
    }
;

AssignmentStmt
    : Expression assign_op {
        ops[++op_idx] = $<op>2;
        strcpy(assign, $1.name);
    } Expression {
        Node* tmp = lookup_symbol($1.name);
        while (op_idx) {
            // detect error
            if (($1.type == TYPE_INT || $1.type == TYPE_FLOAT) && ($4.type == TYPE_INT || $4.type == TYPE_FLOAT) && $1.type != $4.type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name($1.type),
                    get_type_name($4.type));
            if (g_has_error)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                        yylineno,
                        get_op_name(ops[op_idx]),
                        get_type_name($1.type),
                        get_type_name($4.type));
            
            // push instruct
            if ($2 != OP_ASSIGN) {
                get_op_inst(buffer, $1.type, ops[op_idx]);
                CODEGEN("\t%s\n", buffer);
            }
            CODEGEN("\t%s %d\n", get_ls_name($1.type, 1), tmp->addr);
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        g_has_error = false;
    }
;

assign_op
    : ASSIGN     { $<op>$ = OP_ASSIGN; }
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
    : Expression INC {
        Node* node = lookup_symbol($1.name);
        puts("INC");
        if ($1.type == TYPE_INT) {
            CODEGEN("\tldc 1\n");
            CODEGEN("\tiadd\n");
            CODEGEN("\tistore %d\n", node->addr);
        }
        else {
            CODEGEN("\tldc 1.0\n");
            CODEGEN("\tfadd\n");
            CODEGEN("\tfstore %d\n", node->addr);
        }
    }
    | Expression DEC {
        Node* node = lookup_symbol($1.name);
        puts("DEC");
        if ($1.type == TYPE_INT) {
            CODEGEN("\tldc -1\n");
            CODEGEN("\tiadd\n");
            CODEGEN("\tistore %d\n", node->addr);
        } else { 
            CODEGEN("\tldc -1.0\n");
            CODEGEN("\tfadd\n");
            CODEGEN("\tfstore %d\n", node->addr);
        }
    }
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
    : IF Condition {
        CODEGEN("Label_%d:\n", lb_idx++);
    } Block {
        CODEGEN("Exit_%d:\n", --lb_idx);
    }
;

Condition
    : Expression {
        if ($1.type != TYPE_BOOL)
            printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 1, get_type_name($1.type));
        else
            CODEGEN("\tgoto Exit_%d\n", lb_idx);
    }
;

ForStmt
    : FOR {
        CODEGEN("For_%d:\n", fr_cnt++);
    } Condition { 
        CODEGEN("Label_%d:\n", lb_idx++);
    } Block {
        CODEGEN("\tgoto For_%d\n", --fr_cnt);
        CODEGEN("Exit_%d:\n", --lb_idx);
    }
;

SwitchStmt
    : SWITCH Expression {
        CODEGEN("\tgoto Switch_%d\n", sw_cnt++);
    } Block {
        CODEGEN("Switch_%d:\n", sw_cnt - 1);
        CODEGEN("\tlookupswitch\n");
        for (int i = 0; i < ks_idx; i++)
            CODEGEN("\t\t%d: Case_%d\n", kase[i], kase[i]);
        CODEGEN("\t\tdefault: Default_%d\n", sw_cnt - 1);
        CODEGEN("End_%d:\n", sw_cnt - 1);
        ks_idx = 0;
    }
;

CaseStmt
    : CASE INT_LIT {
        printf("case %s\n", $<s_val>2);
        CODEGEN("Case_%s:\n", $<s_val>2);
        kase[ks_idx++] = atoi($<s_val>2);
    } COLON Block {
        CODEGEN("\tgoto End_%d\n", sw_cnt - 1);
    }
    | DEFAULT COLON {
        CODEGEN("Default_%d:\n", sw_cnt - 1);
    } Block {
        CODEGEN("\tgoto End_%d\n", sw_cnt - 1);
    }
;

PrintStmt
    : PRINT {
        c_exp = 1;
    } LPAREN Expression RPAREN   {
        c_exp = 0;
        printf("PRINT %s\n", get_type_name($4.type));
        CODEGEN("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("\tswap\n");
        CODEGEN("\tinvokevirtual java/io/PrintStream/print(%s)V\n", get_print_type($4.type));
    }
    | PRINTLN {
        c_exp = 1;
    } LPAREN Expression RPAREN {
        c_exp = 0;
        printf("PRINTLN %s\n", get_type_name($4.type));
        CODEGEN("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("\tswap\n");
        CODEGEN("\tinvokevirtual java/io/PrintStream/println(%s)V\n", get_print_type($4.type));
    }
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
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");

    /* Symbol table init */
    // Add your code

    yylineno = 0;
    yyparse();

    while (scope) dump_symbol();

    /* Symbol table dump */
    // Add your code

	printf("Total lines: %d\n", yylineno + 1);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
    return 0;
}


static void create_symbol(int scope) {
    printf("> Create symbol table (scope level %d)\n", scope);
    s_table[scope] = (Table*)malloc(sizeof(Table));
    s_table[scope]->head = NULL;
    s_table[scope]->tail = NULL;
    s_table[scope]->cnt = 0; 
}

static Node* insert_symbol(char* name, type_t type, char* func, int lineno) {
    Node* tmp = init_node(name, type, func, lineno);
    insert_node(tmp);

    printf("> Insert `%s` (addr: %d) to scope level %d\n", tmp->name, tmp->addr, scope - 1);
    return tmp;
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

const char* get_ls_name(type_t type, int inst) {
    // inst = 0 => load
    // inst = 1 => store
    switch (type) {
        case TYPE_INT:
            return (!inst ? "iload" : "istore");
        case TYPE_FLOAT:
            return (!inst ? "fload" : "fstore");
        case TYPE_BOOL:
            return (!inst ? "iload" : "istore");
        case TYPE_STRING:
            return (!inst ? "aload" : "astore");
        case TYPE_FUNC:
            return "func";
        default:
            return "ERROR";
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

const char* get_print_type(type_t type) {
    switch (type) {
        case TYPE_INT:
            return "I";
        case TYPE_FLOAT:
            return "F";
        case TYPE_BOOL:
            return "Z";
        case TYPE_STRING:
            return "Ljava/lang/String;";
        case TYPE_FUNC:
            return "func";
        default:
            return "ERROR";
    }
}

void get_op_inst(char* buf, type_t type, op_t op) {
    char tmp[16];
    int idx = 0;

    buf[0] = get_type_name(type)[0], idx = 1;
    if (type == -1 || op == OP_EQL || op == OP_NEQ || op == OP_LSS || op == OP_LEQ || op == OP_GTR || op == OP_GTR || op == OP_GEQ || op == OP_LOR || op == OP_LAND)
        idx = 0;

    switch (op) {
        case OP_QUO:
        case OP_QUO_ASSIGN:
            strcpy(tmp, "DIV");
            break;
        case OP_LOR:
            strcpy(tmp, "IOR");
            break;
        case OP_LAND:
            strcpy(tmp, "IAND");
            break;
        case OP_EQL:
            strcpy(tmp, "IF_ICMPEQ");
            break;
        case OP_NEQ:
            strcpy(tmp, "IF_ICMPNE");
            break;
        case OP_LSS:
            strcpy(tmp, "IF_ICMPLS");
            break;
        case OP_LEQ:
            strcpy(tmp, "IF_ICMPLE");
            break;
        case OP_GTR:
            if (type == TYPE_INT || type == TYPE_BOOL) c_exp ? strcpy(tmp, "IFGT") : strcpy(tmp, "IF_ICMPGT");
            else                                       strcpy(tmp, "fcmpg");
            break;
        case OP_GEQ:
            strcpy(tmp, "IF_ICMPGE");
            break;
        default:
            strcpy(tmp, get_op_name(op));
            break;
    }

    for (int i = 0; i < strlen(tmp); i++)
        buf[i + idx] = ((tmp[i] >= 'A' && tmp[i] <= 'Z') ? (char)(tmp[i] + 32) : tmp[i]);
    buf[strlen(tmp) + idx] = '\0';
}