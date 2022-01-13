%error-verbose

%{
    #include <stdio.h>

    #include "tree_nodes.h"
    #include "tree_creators.h"
    #include "../flex/utilities/chararray_utilities.h"

    extern int yylex();
    void yyerror(const char* s) {
        fprintf(stderr, "%s\n", s);
    }

    struct program_strct* tree_root = NULL;
    unsigned int curr_node_index = 0;
%}

%union {
    /* Common */
    struct identifiers_comma_seq_strct* identifiers_comma_seq_field;

    /* Main */
    struct program_strct*           program_field;
    struct class_decl_seq_strct*    class_decl_seq_field;
    struct class_decl_strct*        class_decl_field;

    /* Class */
    // Inheritance block
    struct parent_seq_strct*    parent_seq_field;
    struct parent_strct*        parent_field;
    struct rename_seq_strct*    rename_seq_field;

    // Creators block
    struct creators_seq_strct*          creators_seq_field;

    // Features block
    struct features_seq_strct*          features_seq_field;
    struct feature_decl_seq_strct*      feature_decl_seq_field;
    struct feature_decl_strct*          feature_decl_field;

    struct ids_with_type_seq_strct*     ids_with_type_seq_field;
    struct type_strct*                  type_field;

    // ... Instruction
    struct instruction_seq_strct*   instruction_seq_field;
    struct instruction_strct*       instruction_field;

    struct argument_seq_strct*              argument_seq_field;
    struct expr_strct* expr_field;

    /* Constants */
    short       liter_boolean_field;
    long long   liter_integer_field;
    char        liter_char_field;
    CharArray*  liter_string_field;

    char*       id_field;
}

// ================== TOKENS =================
// -------------- BASIC TOKENS --------------
%start program

%token<id_field> ID
%token CLASS
%token END
%token IF
%token THEN
%token ELSE
%token FROM
%token UNTIL
%token LOOP
%token CONSOLEIO

// --------------- DATA TYPES ---------------
%token DATATYPE_BOOLEAN
%token DATATYPE_CHARACTER
%token DATATYPE_INTEGER
%token DATATYPE_NATURAL
%token DATATYPE_STRING
%token DATATYPE_ARRAY

// --------------- OPERATORS ----------------
%token ASSIGNMENT

%left OR XOR
%left AND
%left '<' '>' LESS_EQUAL GREAT_EQUAL '=' NOTEQUAL
%left '+' '-'
%left '*' INTEGER_DIVISION
%right UMINUS NOT
%left '@'
%left '.'
%nonassoc '('

// ---------------- LITERALS ----------------
%token<liter_boolean_field> LITER_BOOLEAN
%token<liter_integer_field> LITER_INTEGER
%token<liter_char_field>    LITER_CHAR
%token<liter_string_field>  LITER_STRING
%token                      LITER_VOID

// -------------- CLASS TOKENS --------------
// Inheritance block
%token INHERIT
%token RENAME
%token UNDEFINE
%token REDEFINE
%token SELECT
%token AS

// Creators block
%token CREATE

// Features block
%token FEATURE
%token LOCAL
%token DO
%token CURRENT
%token RESULT
%token PRECURSOR

// ================== TYPES ==================
// -------------- COMMON TYPES --------------
%type<identifiers_comma_seq_field> identifiers_comma_seq;

// --------------- MAIN TYPES ---------------
%type<program_field>                program;
%type<class_decl_seq_field>         class_decl_seq;
%type<class_decl_field>             class_decl;

// --------------- CLASS TYPES --------------
// Inheritance block
%type<parent_seq_field>     parent_seq;
%type<parent_field>         parent;
%type<rename_seq_field>     rename_seq;

// Creators block
%type<creators_seq_field>     creators_seq;

// Features block
%type<features_seq_field>        features_seq;
%type<feature_decl_seq_field>    feature_decl_seq;
%type<feature_decl_field>        feature_decl;

%type<ids_with_type_seq_field>   ids_with_type_seq;
%type<type_field>                type;

// ... Instruction
%type<instruction_seq_field>    instruction_seq;
%type<instruction_field>        instruction;

// ... Expression
%type<argument_seq_field>   argument_seq;
%type<expr_field>           expr;

%%

// COMMON RULES
identifiers_comma_seq: ID                               { $$ = create_identifiers_comma_seq(curr_node_index++, $1); }
                     | identifiers_comma_seq ',' ID     { $$ = append_identifiers_comma_seq(curr_node_index++, $1, $3); }
                     ;

opt_semicolon: /* EMPTY */
             | ';'
             ;

opt_semicolon_seq: /* EMPTY */
                  | nonempty_opt_semicolon_seq
                  ;

nonempty_opt_semicolon_seq: ';'
                           | nonempty_opt_semicolon_seq ';'
                           ;

// MAIN RULES
program: class_decl_seq { $$ = create_program(curr_node_index++, $1); tree_root = $$; }
       ;

class_decl_seq: class_decl                  { $$ = create_class_decl_seq(curr_node_index++, $1); }
              | class_decl_seq class_decl   { $$ = append_class_decl_seq(curr_node_index++, $1, $2); }
              ;

// CLASS DECLARATION ...
class_decl: CLASS ID INHERIT parent_seq creators_seq features_seq END   { $$ = create_class_decl(curr_node_index++, $2, $4, $5, $6); }
          | CLASS ID INHERIT parent_seq creators_seq END                { $$ = create_class_decl(curr_node_index++, $2, $4, $5, NULL); }
          | CLASS ID INHERIT parent_seq features_seq END                { $$ = create_class_decl(curr_node_index++, $2, $4, NULL, $5); }
          | CLASS ID INHERIT parent_seq END                             { $$ = create_class_decl(curr_node_index++, $2, $4, NULL, NULL); }

          | CLASS ID creators_seq features_seq END                      { $$ = create_class_decl(curr_node_index++, $2, NULL, $3, $4); }
          | CLASS ID creators_seq END                                   { $$ = create_class_decl(curr_node_index++, $2, NULL, $3, NULL); }
          | CLASS ID features_seq END                                   { $$ = create_class_decl(curr_node_index++, $2, NULL, NULL, $3); }
          | CLASS ID END                                                { $$ = create_class_decl(curr_node_index++, $2, NULL, NULL, NULL); }
          ;

// ... INHERITANCE BLOCK
parent_seq: parent opt_semicolon                { $$ = create_parent_seq(curr_node_index++, $1); }
          | parent_seq parent opt_semicolon     { $$ = append_parent_seq(curr_node_index++, $1, $2); }
          ;

parent: ID RENAME rename_seq REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq END   { $$ = create_parent(curr_node_index++, $1, $3, $5, $7); }
      | ID REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq END                     { $$ = create_parent(curr_node_index++, $1, NULL, $3, $5); }
      | ID RENAME rename_seq SELECT identifiers_comma_seq END                                  { $$ = create_parent(curr_node_index++, $1, $3, NULL, $5); }
      | ID SELECT identifiers_comma_seq END                                                    { $$ = create_parent(curr_node_index++, $1, NULL, NULL, $3); }

      | ID RENAME rename_seq REDEFINE identifiers_comma_seq END                                { $$ = create_parent(curr_node_index++, $1, $3, $5, NULL); }
      | ID REDEFINE identifiers_comma_seq END                                                  { $$ = create_parent(curr_node_index++, $1, NULL, $3, NULL); }
      | ID RENAME rename_seq END                                                               { $$ = create_parent(curr_node_index++, $1, $3, NULL, NULL); }
      | ID                                                                                     { $$ = create_parent(curr_node_index++, $1, NULL, NULL, NULL); }
      ;

rename_seq: ID AS ID                    { $$ = create_rename_seq(curr_node_index++, $1, $3); }
          | rename_seq ',' ID AS ID     { $$ = append_rename_seq(curr_node_index++, $1, $3, $5); }
          ;

// ... CREATORS BLOCK
creators_seq: CREATE identifiers_comma_seq                { $$ = create_creators_seq(curr_node_index++, $2); }
            | creators_seq CREATE identifiers_comma_seq   { $$ = append_creators_seq(curr_node_index++, $1, $3); }
            ;

// ... FEATURES BLOCK
features_seq: FEATURE feature_decl_seq                  { $$ = create_features_seq(curr_node_index++, $2); }
            | features_seq FEATURE feature_decl_seq     { $$ = append_features_seq(curr_node_index++, $1, $3); }
            ;

feature_decl_seq: feature_decl opt_semicolon_seq                      { $$ = create_feature_decl_seq(curr_node_index++, $1); }
                | feature_decl_seq feature_decl opt_semicolon_seq     { $$ = append_feature_decl_seq(curr_node_index++, $1, $2); }
                ;

feature_decl: identifiers_comma_seq ':' type                                                                            { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, NULL, NULL); }

            | identifiers_comma_seq DO instruction_seq END                                                              { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, NULL, $3); }
            | identifiers_comma_seq LOCAL DO instruction_seq END                                                        { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, NULL, $4); }
            | identifiers_comma_seq LOCAL ids_with_type_seq DO instruction_seq END                                      { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, $3, $5); }

            | identifiers_comma_seq '(' ')' DO instruction_seq END                                                      { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, NULL, $5); }
            | identifiers_comma_seq '(' ')' LOCAL DO instruction_seq END                                                { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, NULL, $6); }
            | identifiers_comma_seq '(' ')' LOCAL ids_with_type_seq DO instruction_seq END                              { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, $5, $7); }

            | identifiers_comma_seq ':' type DO instruction_seq END                                                     { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, NULL, $5); }
            | identifiers_comma_seq ':' type LOCAL DO instruction_seq END                                               { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, NULL, $6); }
            | identifiers_comma_seq ':' type LOCAL ids_with_type_seq DO instruction_seq END                             { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, $5, $7); }

            | identifiers_comma_seq '(' ')' ':' type DO instruction_seq END                                             { $$ = create_feature_decl(curr_node_index++, $1, $5, NULL, NULL, $7); }
            | identifiers_comma_seq '(' ')' ':' type LOCAL DO instruction_seq END                                       { $$ = create_feature_decl(curr_node_index++, $1, $5, NULL, NULL, $8); }
            | identifiers_comma_seq '(' ')' ':' type LOCAL ids_with_type_seq DO instruction_seq END                     { $$ = create_feature_decl(curr_node_index++, $1, $5, NULL, $7, $9); }

            | identifiers_comma_seq '(' ids_with_type_seq ')' DO instruction_seq END                                    { $$ = create_feature_decl(curr_node_index++, $1, NULL, $3, NULL, $6); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' LOCAL DO instruction_seq END                              { $$ = create_feature_decl(curr_node_index++, $1, NULL, $3, NULL, $7); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' LOCAL ids_with_type_seq DO instruction_seq END            { $$ = create_feature_decl(curr_node_index++, $1, NULL, $3, $6, $8); }

            | identifiers_comma_seq '(' ids_with_type_seq ')' ':' type DO instruction_seq END                           { $$ = create_feature_decl(curr_node_index++, $1, $6, $3, NULL, $8); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' ':' type LOCAL DO instruction_seq END                     { $$ = create_feature_decl(curr_node_index++, $1, $6, $3, NULL, $9); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' ':' type LOCAL ids_with_type_seq DO instruction_seq END   { $$ = create_feature_decl(curr_node_index++, $1, $6, $3, $8, $10); }
            ;

ids_with_type_seq: identifiers_comma_seq ':' type opt_semicolon                     { $$ = create_ids_with_type_seq(curr_node_index++, $1, $3); }
                 | ids_with_type_seq identifiers_comma_seq ':' type opt_semicolon   { $$ = append_ids_with_type_seq(curr_node_index++, $1, $2, $4); }
                 ;

type: ID                            { $$ = create_type(curr_node_index++, dtype_user_defined, $1, NULL); }
    | DATATYPE_BOOLEAN              { $$ = create_type(curr_node_index++, dtype_boolean, "BOOLEAN", NULL); }
    | DATATYPE_CHARACTER            { $$ = create_type(curr_node_index++, dtype_character, "CHARACTER", NULL); }
    | DATATYPE_INTEGER              { $$ = create_type(curr_node_index++, dtype_integer, "INTEGER", NULL); }
    | DATATYPE_NATURAL              { $$ = create_type(curr_node_index++, dtype_natural, "NATURAL", NULL); }
    | DATATYPE_STRING               { $$ = create_type(curr_node_index++, dtype_string, "STRING", NULL); }
    | DATATYPE_ARRAY '[' type ']'   { $$ = create_type(curr_node_index++, dtype_array, "ARRAY", $3); }
    ;

instruction_seq: opt_semicolon_seq                              { $$ = create_instruction_seq(curr_node_index++, NULL); }
               | instruction_seq instruction opt_semicolon_seq  { $$ = append_instruction_seq(curr_node_index++, $1, $2); }
               ;

instruction: CREATE ID                                                      { $$ = create_create_instruction(curr_node_index++, $2, NULL, NULL); }
           | CREATE ID '.' ID                                               { $$ = create_create_instruction(curr_node_index++, $2, $4, NULL); }
           | CREATE ID '.' ID '(' ')'                                       { $$ = create_create_instruction(curr_node_index++, $2, $4, NULL); }
           | CREATE ID '.' ID '(' argument_seq ')'                          { $$ = create_create_instruction(curr_node_index++, $2, $4, $6); }

           | ID ASSIGNMENT expr                                             { $$ = create_assign_instruction(curr_node_index++, $1, $3); }

           | IF '(' expr ')' THEN instruction_seq END                       { $$ = create_if_instruction(curr_node_index++, $3, $6, NULL); }
           | IF '(' expr ')' THEN instruction_seq ELSE instruction_seq END  { $$ = create_if_instruction(curr_node_index++, $3, $6, $8); }
           | FROM instruction_seq UNTIL expr LOOP instruction_seq END       { $$ = create_loop_instruction(curr_node_index++, $2, $4, $6); }

           | expr                                                           { $$ = create_instruction_as_expr(curr_node_index++, $1); }
           ;

argument_seq: expr                      { $$ = create_argument_seq(curr_node_index++, $1); }
            | argument_seq ',' expr     { $$ = append_argument_seq(curr_node_index++, $1, $3); }
            ;

expr: LITER_BOOLEAN                             { $$ = create_expr_liter_bool(curr_node_index++, $1); }
    | LITER_INTEGER                             { $$ = create_expr_liter_int (curr_node_index++, $1); }
    | LITER_CHAR                                { $$ = create_expr_liter_char(curr_node_index++, $1); }
    | LITER_STRING                              { $$ = create_expr_liter_str (curr_node_index++, $1); }
    | LITER_VOID                                { $$ = create_expr_liter_void(curr_node_index++); }

    | '(' expr ')'                              { $$ = $2; $$->is_parenthesized = 1; }
    | CURRENT									{ $$ = create_expr_current(curr_node_index++); }
    | ID                                      	{ $$ = create_expr_call(curr_node_index++, expr_call_selffeature, $1, NULL, 1); }
    | ID '(' ')'                                { $$ = create_expr_call(curr_node_index++, expr_call_selffeature, $1, NULL, 0); }
    | ID '(' argument_seq ')'                   { $$ = create_expr_call(curr_node_index++, expr_call_selffeature, $1, $3, 0); }
    | PRECURSOR                                 { $$ = create_expr_precursorcall(curr_node_index++, NULL, NULL); }
    | PRECURSOR '(' ')'                         { $$ = create_expr_precursorcall(curr_node_index++, NULL, NULL); }
    | PRECURSOR '(' argument_seq ')'            { $$ = create_expr_precursorcall(curr_node_index++, NULL, NULL); }
    | PRECURSOR '{' ID '}'                      { $$ = create_expr_precursorcall(curr_node_index++, $3, NULL); }
    | PRECURSOR '{' ID '}' '(' ')'              { $$ = create_expr_precursorcall(curr_node_index++, $3, NULL); }
    | PRECURSOR '{' ID '}' '(' argument_seq ')' { $$ = create_expr_precursorcall(curr_node_index++, $3, $6); }
    | expr '.' ID                               { $$ = create_expr_subcall(curr_node_index++, $1, $3, NULL, 1); }
    | expr '.' ID '(' ')'						{ $$ = create_expr_subcall(curr_node_index++, $1, $3, NULL, 0); }
    | expr '.' ID '(' argument_seq ')'          { $$ = create_expr_subcall(curr_node_index++, $1, $3, $5, 0); }

    | CREATE '{' type '}'                                 { $$ = create_expr_creation(curr_node_index++, $3, NULL, NULL); }
    | CREATE '{' type '}' '.' ID                          { $$ = create_expr_creation(curr_node_index++, $3, $6, NULL); }
    | CREATE '{' type '}' '.' ID '(' ')'                  { $$ = create_expr_creation(curr_node_index++, $3, $6, NULL); }
    | CREATE '{' type '}' '.' ID '(' argument_seq ')'     { $$ = create_expr_creation(curr_node_index++, $3, $6, $8); }

    | expr '@' expr                             { $$ = create_expr_operation(curr_node_index++, expr_arrelem, $1, $3); }
    | expr '+' expr                             { $$ = create_expr_operation(curr_node_index++, expr_plus, $1, $3); }
    | expr '-' expr                             { $$ = create_expr_operation(curr_node_index++, expr_bminus, $1, $3); }
    | expr '*' expr                             { $$ = create_expr_operation(curr_node_index++, expr_mul, $1, $3); }
    | expr INTEGER_DIVISION expr                { $$ = create_expr_operation(curr_node_index++, expr_idiv, $1, $3); }
    | '-' expr %prec UMINUS                     { $$ = create_expr_operation(curr_node_index++, expr_uminus, NULL, $2); }

    | expr '<' expr                             { $$ = create_expr_operation(curr_node_index++, expr_less, $1, $3); }
    | expr '>' expr                             { $$ = create_expr_operation(curr_node_index++, expr_great, $1, $3); }
    | expr LESS_EQUAL expr                      { $$ = create_expr_operation(curr_node_index++, expr_less_equal, $1, $3); }
    | expr GREAT_EQUAL expr                     { $$ = create_expr_operation(curr_node_index++, expr_great_equal, $1, $3); }
    | expr '=' expr                             { $$ = create_expr_operation(curr_node_index++, expr_equal, $1, $3); }
    | expr NOTEQUAL expr                        { $$ = create_expr_operation(curr_node_index++, expr_notequal, $1, $3); }

    | expr AND expr                             { $$ = create_expr_operation(curr_node_index++, expr_and, $1, $3); }
    | expr OR expr                              { $$ = create_expr_operation(curr_node_index++, expr_or, $1, $3); }
    | expr XOR expr                             { $$ = create_expr_operation(curr_node_index++, expr_xor, $1, $3); }
    | NOT expr                                  { $$ = create_expr_operation(curr_node_index++, expr_not, NULL, $2); }
    ;

%%
