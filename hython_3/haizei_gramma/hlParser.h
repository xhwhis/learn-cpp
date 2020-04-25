/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : ./thirdpart/hl.g
 *     -                            On : 2020-04-14 19:12:08
 *     -                for the parser : hlParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
hlParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef phlParser, which is returned from a call to hlParserNew().
 *
 * The methods in phlParser are  as follows:
 *
 *  - 
 hlParser_defid_expr_return
      phlParser->defid_expr(phlParser)
 *  - 
 hlParser_defid_return
      phlParser->defid(phlParser)
 *  - 
 hlParser_expr_return
      phlParser->expr(phlParser)
 *  - 
 hlParser_multExpr_return
      phlParser->multExpr(phlParser)
 *  - 
 hlParser_invoExpr_return
      phlParser->invoExpr(phlParser)
 *  - 
 hlParser_atom_return
      phlParser->atom(phlParser)
 *  - 
 hlParser_list_atom_return
      phlParser->list_atom(phlParser)
 *  - 
 hlParser_exprs_return
      phlParser->exprs(phlParser)
 *  - 
 hlParser_if_expr_return
      phlParser->if_expr(phlParser)
 *  - 
 hlParser_for_expr_return
      phlParser->for_expr(phlParser)
 *  - 
 hlParser_while_expr_return
      phlParser->while_expr(phlParser)
 *  - 
 hlParser_init_expr_return
      phlParser->init_expr(phlParser)
 *  - 
 hlParser_for_do_expr_return
      phlParser->for_do_expr(phlParser)
 *  - 
 hlParser_switch_expr_return
      phlParser->switch_expr(phlParser)
 *  - 
 hlParser_case_expr_return
      phlParser->case_expr(phlParser)
 *  - 
 hlParser_default_expr_return
      phlParser->default_expr(phlParser)
 *  - 
 hlParser_condition_expr_return
      phlParser->condition_expr(phlParser)
 *  - 
 hlParser_andExpr_return
      phlParser->andExpr(phlParser)
 *  - 
 hlParser_cmp_atom_return
      phlParser->cmp_atom(phlParser)
 *  - 
 hlParser_cond_atom_return
      phlParser->cond_atom(phlParser)
 *  - 
 hlParser_block_return
      phlParser->block(phlParser)
 *  - 
 hlParser_block_expr_return
      phlParser->block_expr(phlParser)
 *  - 
 hlParser_print_atom_return
      phlParser->print_atom(phlParser)
 *  - 
 hlParser_expr_stmt_return
      phlParser->expr_stmt(phlParser)
 *  - 
 hlParser_control_stmt_return
      phlParser->control_stmt(phlParser)
 *  - 
 hlParser_def_param_expr_return
      phlParser->def_param_expr(phlParser)
 *  - 
 hlParser_param_return
      phlParser->param(phlParser)
 *  - 
 hlParser_param_sub_expr_return
      phlParser->param_sub_expr(phlParser)
 *  - 
 hlParser_param_expr_return
      phlParser->param_expr(phlParser)
 *  - 
 hlParser_func_stmt_return
      phlParser->func_stmt(phlParser)
 *  - 
 hlParser_func_call_return
      phlParser->func_call(phlParser)
 *  - 
 hlParser_stmt_return
      phlParser->stmt(phlParser)
 *  - 
 hlParser_prog_return
      phlParser->prog(phlParser)
 * 
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_hlParser_H
#define _hlParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct hlParser_Ctx_struct hlParser, * phlParser;



    #include <assert.h>


#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */

typedef struct hlParser_defid_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_defid_expr_return;



typedef struct hlParser_defid_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_defid_return;



typedef struct hlParser_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_expr_return;



typedef struct hlParser_multExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_multExpr_return;



typedef struct hlParser_invoExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_invoExpr_return;



typedef struct hlParser_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_atom_return;



typedef struct hlParser_list_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_list_atom_return;



typedef struct hlParser_exprs_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_exprs_return;



typedef struct hlParser_if_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_if_expr_return;



typedef struct hlParser_for_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_for_expr_return;



typedef struct hlParser_while_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_while_expr_return;



typedef struct hlParser_init_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_init_expr_return;



typedef struct hlParser_for_do_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_for_do_expr_return;



typedef struct hlParser_switch_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_switch_expr_return;



typedef struct hlParser_case_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_case_expr_return;



typedef struct hlParser_default_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_default_expr_return;



typedef struct hlParser_condition_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_condition_expr_return;



typedef struct hlParser_andExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_andExpr_return;



typedef struct hlParser_cmp_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_cmp_atom_return;



typedef struct hlParser_cond_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_cond_atom_return;



typedef struct hlParser_block_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_block_return;



typedef struct hlParser_block_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_block_expr_return;



typedef struct hlParser_print_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_print_atom_return;



typedef struct hlParser_expr_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_expr_stmt_return;



typedef struct hlParser_control_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_control_stmt_return;



typedef struct hlParser_def_param_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_def_param_expr_return;



typedef struct hlParser_param_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_param_return;



typedef struct hlParser_param_sub_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_param_sub_expr_return;



typedef struct hlParser_param_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_param_expr_return;



typedef struct hlParser_func_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_func_stmt_return;



typedef struct hlParser_func_call_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_func_call_return;



typedef struct hlParser_stmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_stmt_return;



typedef struct hlParser_prog_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    hlParser_prog_return;




/** Context tracking structure for 
hlParser

 */
struct hlParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     hlParser_defid_expr_return
     (*defid_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_defid_return
     (*defid)	(struct hlParser_Ctx_struct * ctx);

     hlParser_expr_return
     (*expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_multExpr_return
     (*multExpr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_invoExpr_return
     (*invoExpr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_atom_return
     (*atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_list_atom_return
     (*list_atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_exprs_return
     (*exprs)	(struct hlParser_Ctx_struct * ctx);

     hlParser_if_expr_return
     (*if_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_for_expr_return
     (*for_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_while_expr_return
     (*while_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_init_expr_return
     (*init_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_for_do_expr_return
     (*for_do_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_switch_expr_return
     (*switch_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_case_expr_return
     (*case_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_default_expr_return
     (*default_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_condition_expr_return
     (*condition_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_andExpr_return
     (*andExpr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_cmp_atom_return
     (*cmp_atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_cond_atom_return
     (*cond_atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_block_return
     (*block)	(struct hlParser_Ctx_struct * ctx);

     hlParser_block_expr_return
     (*block_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_print_atom_return
     (*print_atom)	(struct hlParser_Ctx_struct * ctx);

     hlParser_expr_stmt_return
     (*expr_stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_control_stmt_return
     (*control_stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_def_param_expr_return
     (*def_param_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_param_return
     (*param)	(struct hlParser_Ctx_struct * ctx);

     hlParser_param_sub_expr_return
     (*param_sub_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_param_expr_return
     (*param_expr)	(struct hlParser_Ctx_struct * ctx);

     hlParser_func_stmt_return
     (*func_stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_func_call_return
     (*func_call)	(struct hlParser_Ctx_struct * ctx);

     hlParser_stmt_return
     (*stmt)	(struct hlParser_Ctx_struct * ctx);

     hlParser_prog_return
     (*prog)	(struct hlParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred1_hl)	(struct hlParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct hlParser_Ctx_struct * ctx);
    void	    (*free)   (struct hlParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API phlParser hlParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API phlParser hlParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__51      51
#define T__52      52
#define T__53      53
#define T__54      54
#define T__55      55
#define T__56      56
#define T__57      57
#define T__58      58
#define AND      4
#define ASSIGN      5
#define BLOCK      6
#define BREAK      7
#define CASE      8
#define COMMENT      9
#define CONTINUE      10
#define DEF      11
#define DEFAULT      12
#define DIV      13
#define DO      14
#define DOT      15
#define DOWHILE      16
#define ELSE      17
#define EQ      18
#define ESC_SEQ      19
#define EXPONENT      20
#define FLOAT      21
#define FOR      22
#define FUNC      23
#define FUNC_CALL      24
#define GE      25
#define GT      26
#define HEX_DIGIT      27
#define ID      28
#define IF      29
#define INT      30
#define LE      31
#define LIST      32
#define LITTLE      33
#define MINUS      34
#define MOD      35
#define NE      36
#define NOPE      37
#define OCTAL_ESC      38
#define OR      39
#define PARAM      40
#define PLUS      41
#define POWER      42
#define PRINT      43
#define RETURN      44
#define STRING      45
#define SWITCH      46
#define TIMES      47
#define UNICODE_ESC      48
#define WHILE      49
#define WS      50
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for hlParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
