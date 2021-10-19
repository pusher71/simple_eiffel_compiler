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
    struct inheritance_block_strct* inheritance_block_field;

    struct parent_seq_strct*    parent_seq_field;
    struct parent_strct*        parent_field;
    struct parent_info_strct*   parent_info_field;
    struct rename_seq_strct*    rename_seq_field;

    // Creators block
    struct creators_block_strct*            creators_block_field;
    struct nonempty_creators_block_strct*   nonempty_creators_block_field;

    // Features block
    struct features_block_strct*                features_block_field;
    struct nonempty_features_block_strct*       nonempty_features_block_field;

    struct feature_decl_seq_strct*              feature_decl_seq_field;
    struct nonempty_feature_decl_seq_strct*     nonempty_feature_decl_seq_field;
    struct feature_decl_strct*                  feature_decl_field;

    struct ids_with_type_seq_strct*             ids_with_type_seq_field;
    struct nonempty_ids_with_type_seq_strct*    nonempty_ids_with_type_seq_field;
    struct ids_with_type_strct*                 ids_with_type_field;
    struct type_strct* type_field;

    struct routine_decl_body_strct* routine_decl_body_field;

    /* Constants */
    short				liter_boolean_field;
    long int 			liter_integer_field;
    char				liter_char_field;
    CharArray* 			liter_string_field;

    char*  				id_field;
}

// ================== TOKENS =================
// -------------- BASIC TOKENS --------------
%start program

%token<id_field> ID
%token CLASS
%token END

// --------------- DATA TYPES ---------------
%token DATATYPE_BOOLEAN
%token DATATYPE_CHARACTER
%token DATATYPE_INTEGER_8
%token DATATYPE_INTEGER_16
%token DATATYPE_INTEGER_32
%token DATATYPE_INTEGER_64
%token DATATYPE_NATURAL_8
%token DATATYPE_NATURAL_16
%token DATATYPE_NATURAL_32
%token DATATYPE_NATURAL_64
%token DATATYPE_STRING

// ---------------- LITERALS ----------------
%token<liter_boolean_field> LITER_BOOLEAN
%token<liter_integer_field> LITER_INTEGER
%token<liter_char_field>    LITER_CHAR
%token<liter_string_field>  LITER_STRING

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
%type<inheritance_block_field>  inheritance_block;

%type<parent_seq_field>     parent_seq;
%type<parent_field>         parent;
%type<parent_info_field>    parent_info;
%type<rename_seq_field>     rename_seq;

// Creators block
%type<creators_block_field>             creators_block;
%type<nonempty_creators_block_field>    nonempty_creators_block;

// Features block
%type<features_block_field>             features_block;
%type<nonempty_features_block_field>    nonempty_features_block;

%type<feature_decl_seq_field>           feature_decl_seq;
%type<nonempty_feature_decl_seq_field>  nonempty_feature_decl_seq;
%type<feature_decl_field>               feature_decl;

%type<ids_with_type_seq_field>          ids_with_type_seq;
%type<nonempty_ids_with_type_seq_field> nonempty_ids_with_type_seq;
%type<ids_with_type_field>              ids_with_type;
%type<type_field>                       type;

%type<routine_decl_body_field>          routine_decl_body;

%%

program: class_decl_seq { $$ = create_program(curr_node_index++, $1); tree_root = $$; }
       ;

class_decl_seq: class_decl                  { $$ = create_class_decl_seq(curr_node_index++, $1); }
              | class_decl_seq class_decl   { $$ = append_class_decl_seq(curr_node_index++, $1, $2); }
			  ;

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

// CLASS DECLARATION ...
class_decl: CLASS ID inheritance_block creators_block features_block END { $$ = create_class_decl(curr_node_index++, $2, $3, $4, $5); }
		  ;

// ... INHERITANCE BLOCK
inheritance_block: /* EMPTY */          { $$ = NULL; }
                 | INHERIT parent_seq   { $$ = create_inheritance_block(curr_node_index++, $2); }
				 ;

parent_seq: parent opt_semicolon                { $$ = create_parent_seq(curr_node_index++, $1); }
          | parent_seq parent opt_semicolon     { $$ = append_parent_seq(curr_node_index++, $1, $2); }
		  ;

parent: ID                  { $$ = create_parent(curr_node_index++, $1, NULL); }
      | ID parent_info END  { $$ = create_parent(curr_node_index++, $1, $2); }
	  ;

parent_info: RENAME rename_seq UNDEFINE identifiers_comma_seq REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq       { $$ = create_parent_info(curr_node_index++, $2, $4, $6, $8); }
           | UNDEFINE identifiers_comma_seq REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq                         { $$ = create_parent_info(curr_node_index++, NULL, $2, $4, $6); }
           | RENAME rename_seq REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq                                      { $$ = create_parent_info(curr_node_index++, $2, NULL, $4, $6); }
           | REDEFINE identifiers_comma_seq SELECT identifiers_comma_seq                                                        { $$ = create_parent_info(curr_node_index++, NULL, NULL, $2, $4); }

           | RENAME rename_seq UNDEFINE identifiers_comma_seq SELECT identifiers_comma_seq                                      { $$ = create_parent_info(curr_node_index++, $2, $4, NULL, $6); }
           | UNDEFINE identifiers_comma_seq SELECT identifiers_comma_seq                                                        { $$ = create_parent_info(curr_node_index++, NULL, $2, NULL, $4); }
           | RENAME rename_seq SELECT identifiers_comma_seq                                                                     { $$ = create_parent_info(curr_node_index++, $2, NULL, NULL, $4); }
           | SELECT identifiers_comma_seq                                                                                       { $$ = create_parent_info(curr_node_index++, NULL, NULL, NULL, $2); }

           | RENAME rename_seq UNDEFINE identifiers_comma_seq REDEFINE identifiers_comma_seq                                    { $$ = create_parent_info(curr_node_index++, $2, $4, $6, NULL); }
           | UNDEFINE identifiers_comma_seq REDEFINE identifiers_comma_seq                                                      { $$ = create_parent_info(curr_node_index++, NULL, $2, $4, NULL); }
           | RENAME rename_seq REDEFINE identifiers_comma_seq                                                                   { $$ = create_parent_info(curr_node_index++, $2, NULL, $4, NULL); }
           | REDEFINE identifiers_comma_seq                                                                                     { $$ = create_parent_info(curr_node_index++, NULL, NULL, $2, NULL); }

           | RENAME rename_seq UNDEFINE identifiers_comma_seq                                                                   { $$ = create_parent_info(curr_node_index++, $2, $4, NULL, NULL); }
           | UNDEFINE identifiers_comma_seq                                                                                     { $$ = create_parent_info(curr_node_index++, NULL, $2, NULL, NULL); }
           | RENAME rename_seq                                                                                                  { $$ = create_parent_info(curr_node_index++, $2, NULL, NULL, NULL); }
           ;

rename_seq: ID AS ID                    { $$ = create_rename_seq(curr_node_index++, $1, $3); }
          | rename_seq ',' ID AS ID     { $$ = append_rename_seq(curr_node_index++, $1, $3, $5); }
		  ;

// ... CREATORS BLOCK
creators_block: /* EMPTY */                 { $$ = NULL; }
              | nonempty_creators_block     { $$ = create_creators_block(curr_node_index++, $1); }
			  ;

nonempty_creators_block: CREATE identifiers_comma_seq                           { $$ = create_nonempty_creators_block(curr_node_index++, $2); }
                       | nonempty_creators_block CREATE identifiers_comma_seq   { $$ = append_nonempty_creators_block(curr_node_index++, $1, $3); }
					   ;

// ... FEATURES BLOCK
features_block: /* EMPTY */                 { $$ = NULL; }
              | nonempty_features_block     { $$ = create_features_block(curr_node_index++, $1); }
			  ;

nonempty_features_block: FEATURE feature_decl_seq                           { $$ = create_nonempty_features_block(curr_node_index++, $2); }
                       | nonempty_features_block FEATURE feature_decl_seq   { $$ = append_nonempty_features_block(curr_node_index++, $1, $3); }
					   ;

feature_decl_seq: /* EMPTY */                   { $$ = NULL; }
                | nonempty_feature_decl_seq     { $$ = create_feature_decl_seq(curr_node_index++, $1); }
				;

nonempty_feature_decl_seq: feature_decl opt_semicolon_seq                               { $$ = create_nonempty_feature_decl_seq(curr_node_index++, $1); }
                         | nonempty_feature_decl_seq feature_decl opt_semicolon_seq     { $$ = append_nonempty_feature_decl_seq(curr_node_index++, $1, $2); }
						 ;

feature_decl: identifiers_comma_seq ':' type                                                { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, NULL); }
            | identifiers_comma_seq ':' type routine_decl_body                              { $$ = create_feature_decl(curr_node_index++, $1, $3, NULL, $4); }
            | identifiers_comma_seq routine_decl_body                                       { $$ = create_feature_decl(curr_node_index++, $1, NULL, NULL, $2); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' ':' type routine_decl_body    { $$ = create_feature_decl(curr_node_index++, $1, $6, $3, $7); }
            | identifiers_comma_seq '(' ids_with_type_seq ')' routine_decl_body             { $$ = create_feature_decl(curr_node_index++, $1, NULL, $3, $5); }
            ;

ids_with_type_seq: /* EMPTY */                  { $$ = NULL; }
                 | nonempty_ids_with_type_seq   { $$ = create_ids_with_type_seq(curr_node_index++, $1); }
                 ;

nonempty_ids_with_type_seq: ids_with_type opt_semicolon                             { $$ = create_nonempty_ids_with_type_seq(curr_node_index++, $1); }
                          | nonempty_ids_with_type_seq ids_with_type opt_semicolon  { $$ = append_nonempty_ids_with_type_seq(curr_node_index++, $1, $2); }
                          ;

ids_with_type: identifiers_comma_seq ':' type   { $$ = create_ids_with_type(curr_node_index++, $1, $3); }
			 ;

routine_decl_body: local_decl DO opt_semicolon_seq instruction_seq END  { $$ = create_routine_decl_body(curr_node_index++); }
                 | local_decl DO opt_semicolon_seq END                  { $$ = create_routine_decl_body(curr_node_index++); }
				 ;

local_decl: /* EMPTY */
          | LOCAL ids_with_type_seq
		  ;

instruction_seq: instruction opt_semicolon_seq
                        | instruction_seq instruction opt_semicolon_seq
                        ;


instruction: CREATE ID
		   | CREATE ID '.' ID '(' argument_seq ')'
           | call
           ;

call: ID
    | ID '(' argument_seq ')'
    | ID '.' call_sub_seq
    | ID '(' argument_seq ')' '.' call_sub_seq
    | CURRENT '.' call_sub_seq
    | RESULT '.' call_sub_seq
    | '(' expr ')' '.' call_sub_seq
    | PRECURSOR
    | PRECURSOR '(' argument_seq ')'
    | PRECURSOR '{' ID '}'
    | PRECURSOR '{' ID '}' '(' argument_seq ')'
    | PRECURSOR '.' call_sub_seq
    | PRECURSOR '(' argument_seq ')' '.' call_sub_seq
    | PRECURSOR '{' ID '}' '.' call_sub_seq
    | PRECURSOR '{' ID '}' '(' argument_seq ')' '.' call_sub_seq
    ;

call_sub_seq: ID
            | ID '(' argument_seq ')'
            | call_sub_seq '.' ID
            | call_sub_seq '.' ID '(' argument_seq ')'
            ;

argument_seq: /* EMPTY */
			| nonempty_argument_seq
			;

nonempty_argument_seq: expr
		    		 | nonempty_argument_seq ',' expr
					 ;

expr: call
    | '(' expr ')'
    | LITER_BOOLEAN
    | LITER_INTEGER
    | LITER_CHAR
    | LITER_STRING
    ;

// DATA TYPES
type: ID                    { $$ = create_type(curr_node_index++, dtype_user_defined, $1); }
    | DATATYPE_BOOLEAN      { $$ = create_type(curr_node_index++, dtype_boolean, NULL); }
    | DATATYPE_CHARACTER    { $$ = create_type(curr_node_index++, dtype_character, NULL); }
    | DATATYPE_INTEGER_8    { $$ = create_type(curr_node_index++, dtype_integer_8,  NULL); }
    | DATATYPE_INTEGER_16   { $$ = create_type(curr_node_index++, dtype_integer_16, NULL); }
    | DATATYPE_INTEGER_32   { $$ = create_type(curr_node_index++, dtype_integer_32, NULL); }
    | DATATYPE_INTEGER_64   { $$ = create_type(curr_node_index++, dtype_integer_64, NULL); }
    | DATATYPE_NATURAL_8    { $$ = create_type(curr_node_index++, dtype_natural_8,  NULL); }
    | DATATYPE_NATURAL_16   { $$ = create_type(curr_node_index++, dtype_natural_16, NULL); }
    | DATATYPE_NATURAL_32   { $$ = create_type(curr_node_index++, dtype_natural_32, NULL); }
    | DATATYPE_NATURAL_64   { $$ = create_type(curr_node_index++, dtype_natural_64, NULL); }
    | DATATYPE_STRING       { $$ = create_type(curr_node_index++, dtype_string, NULL); }
    ;

%%
