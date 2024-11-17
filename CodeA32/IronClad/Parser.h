/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#              @@|  I R O N C L A D |@@             #
#           @@@@@@@@-----------@@@@@@@@@@          #
#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #
#       @@@@@@@@@@@@@      @@@       @@@@@@       #
#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #
#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #
#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #
#  @@@@@@@@@@    @@             @@@@      @@@@@@  #
#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #
# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #
# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #
# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #
#  @@@@     @@@@@@@              @@@@@    @@@@@@  #
#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #
#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #
#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #
#     @@@@@@@@@       @@@        @@@@@@@@@@@      #
#       @@@@@@         @@         @@@@@@@@@       #
#         @@@@@       @@@@@     @@@@@@@@@         #
#            @@@@@@@@@@@@@@@@@@@@@@@@@            #
#               @@@@@@@@@@@@@@@@@@@               #
#  COMPILERS        @@@@@@@@@@@        2023-S     #
#                                                 #
###################################################
*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferReader* stringLiteralTable;
extern i32				line;
extern Token			tokenizer(Void);
extern String			keywordTable[KWT_SIZE];
static i32			syntaxErrorNumber = 0;

#define LANG_WRTE		"println("
#define LANG_READ		"read_Line("
#define LANG_MAIN		"main()"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_if,  //0
	KW_else,  //1
	KW_fn, // 2
	KW_struct, //3
	KW_enum,  //4
	KW_for, //5
	KW_as,  //6
	KW_break,  //7
	KW_const,  //8
	KW_continue,  //9
	KW_false, //10
	KW_impl, //11
	KW_let,  //12
	KW_in,  //13
	KW_loop,  //14
	KW_match,  //15
	KW_mod,  //16
	KW_move, //17
	KW_mut,  //18
	KW_pub,  //19
	KW_ref,  //20
	KW_return, //21
	KW_Self,  //22
	KW_self,  //23
	KW_super,  //24
	KW_true,  //25
	KW_type,  //26
	KW_use,  //27
	KW_where,  //28
	KW_bool,  //29
	KW_i32, //30
	KW_String, //31
	KW_i8, //32
	KW_i64, //33
	KW_real, //34
	KW_f64, //35
	KW_Void //36

};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 16

/* Parser */
typedef struct parserData {
	i32 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
i32 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
Void startParser();
Void matchToken(i32, i32);
Void syncErrorHandler(i32);
Void printError();
Void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_comment,									/*  1 */
	BNF_optVarListDeclarations,						/*  2 */
	BNF_optionalStatements,							/*  3 */
	BNF_outputStatement,							/*  4 */
	BNF_outputVariableList,							/*  5 */
	BNF_program,									/*  6 */
	BNF_statement,									/*  7 */
	BNF_statements,									/*  8 */
	BNF_statementsPrime,							/*  9 */
	BNF_assignmentStatement,				    	/*  10*/
	BNF_Relational_Expression,						/*  11 */
	BNF_inputStatement,								/*  12 */
	BNF_inputVariableList,						    /*  13 */
	BNF_inputVariableListPrime	,					/*  14 */
	BNF_inputVariable								/*  15*/
};


/* TO_DO: Define the list of keywords */
static String BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_comment",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime",
	"BNF_assignmentStatement",
	"BNF_Relational_Expression",
	"BNF_inputStatement",								/*  12 */
	"BNF_inputVariableList",						    /*  13 */
	"BNF_inputVariableListPrime",
	"BNF_inputVariable"



};

/* TO_DO: Place ALL non-terminal function declarations */
Void comment();
Void optVarListDeclarations();
Void optionalStatements();
Void outputStatement();
Void outputVariableList();
Void program();
Void statement();
Void statements();
Void statementsPrime();
Void assignmentStatement();
Void Relational_Expression();
Void inputStatement();
Void inputVariableList();
Void inputVariableListPrime();
Void inputVariable();

#endif