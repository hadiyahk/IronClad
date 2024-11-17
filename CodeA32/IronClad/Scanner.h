/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#               @@@@|I R O N C L A D|@@@@         #
#            @@@@@@@@-----------@@@@@@@@          #
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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ï¿½ Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */


/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 23

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: '(' ) */
	D_T,		/*  2: Integer literal token   D1 */
	L_T,		/*  3: String literal token   L */
	LPR_T,		/*  4: Left parenthesis token   P (parenthesis) */
	RPR_T,		/*  5: Right parenthesis token */
	LB_T,		/*  6: Left brace token  */
	RB_T,		/*  7: Right brace token	 */
	KW_T,		/*  8: Keyword token		KW */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token	RTE */
	SEOF_T,		/* 11: Source end-of-file token		 */
	CMT_T,	    /* 12: Comment token '/'       */
	Q1_T,		/* 13: qotation token */
	PR_T,		/* 14: Period token    D3*/
	O_T,		/* 15: other token   O*/
	VID_T,			//16
	ART_OP_T,		//17
	REL_OP_T,		//18
	LOG_OP_T,		//19
	ASS_OP_T,		//20
	F_T	,			//21
	COM_T


};

/* TO_DO: Define the list of keywords */
static String tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"D_T",
	"L_T",
	"LPR_T",
	"RPR_T",
	"LB_T",
	"RB_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"Q1_T",
	"PR_T",
	"O_T",
	"VID_T",
	"ART_OP_T",
	"REL_OP_T",
	"LOG_OP_T",
	"ASS_OP_T",
	"F_T",
	"COM_T"



};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT, OP_GE, OP_LE } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	i32 codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	i32 intValue;						/* integer literal attribute (value) */
	i32 keywordIndex;					/* keyword index in the keyword table */
	i32 contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	real floatValue;					/* floating-point literal attribute (value) */
	i8 idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	i8 errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	Byte flags;			/* Flags information */
	union {
		i32 intValue;				/* Integer value */
		real floatValue;			/* Float value */
		String stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	i32 code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	i32 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '\"'
#define CHRCOL6 '/'


/* These constants will be used on VID / MID function */
#define MNID_SUF '('
#define COMM_SYM '/'

/* TO_DO: Error states and illegal state */
#define ESNR	6		/* Error state with no retract */
#define ESWR	7		/* Error state with retract */
#define FS		8		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		12
#define CHAR_CLASSES	9

static i32 transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*
	   L(0), D(1), U(2), M(3), Q1(4), E(5), C(6), O(7), \n(8)  */
	{     1,   10, ESNR, ESNR,    4, ESWR,	  6, ESWR, ESNR},	// S0:  NOAS
	{     1,    1,    1,    2,	  3,    3,    3,    3,    3},	// S1:  NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS, ESWR,   FS},	// S2:  ASNR (MVID)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,   FS},	// S3:  ASWR (KEY)
	{     4,    4,    4,    4,    5,   4,	  4,    4,    4},	// S4:  NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,   FS},	// S5:  ASNR (SL)
	{  ESNR, ESNR,  ESNR,ESNR, ESNR, ESWR,	  7, ESWR,  ESNR},	// S6:  NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,   FS},	// S7:  ASNR (COM)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,   FS},	// S8:  ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,   FS},   // S9:  ASWR (ER)
	{    11,   10,   11,   11,   11,   11,   11,   11,   11},   // S10: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS}    // S11: ASWR (IL)

};








/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static i32 stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR, /* 09 (Err2 - retract) */
	NOFS, /* 10 */
	FSWR  /* 11 */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
i32			startScanner(ReaderPointer psc_buf);
static i32	nextClass(i8 c);					/* character class function */
static i32	nextState(i32, i8);		/* state machine function */
Void			printScannerData(ScannerData scData);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(String lexeme);

/* Declare accepting states functions */
Token funcSL(String lexeme);
Token funcIL(String lexeme);
Token funcID(String lexeme);
Token funcCMT(String lexeme);
Token funcKEY(String lexeme);
Token funcErr(String lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [08] */
	funcIL,		/* ERR2 [09] */
	NULL,		/* -    [10] */
	funcIL	    /* IL   [11] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 37

/* TO_DO: Define the list of keywords */
static String keywordTable[KWT_SIZE] = {
   "if",  //0
   "else",  //1
   "fn", // 2
   "struct", //3
   "enum",  //4
   "for", //5
   "as",  //6
   "break",  //7
   "const",  //8
   "continue",  //9
	"false", //10
	"impl", //11
	"let",  //12
	"in",  //13
	"loop",  //14
	"match",  //15
	"mod",  //16
	"move", //17
	"mut",  //18
	"pub",  //19
	"ref",  //20
	"return", //21
	"Self",  //22
	"self",  //23
	"super",  //24
	"true",  //25
	"type",  //26
	"use",  //27
	"where",  //28
	"bool",  //29
	"i32", //30
	"String", //31
	"i8", //32
	"i64", //33
	"real", //34
	"f64", //35
	"Void" //36
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	i8 indentationCharType;
	i32 indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */

	i32 lineNumber;            /* The current line number being processed */
	i32 columnNumber;          /* The current column number being processed */
	i32 currentScope;          /* The current scope level */
	/* ... (add any other attributes specific to your language) ... */
	i32 prefixCount;           /* The count of prefix symbols encountered */
	i32 suffixCount;
} LanguageAttributes;

/* Number of errors */
i32 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif