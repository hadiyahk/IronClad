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
#             @@@@|I R O N C L A D |@@@@          #
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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

  /* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/


/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
i32 line;								/* Current line number of the source code */
extern i32 errorNumber;				/* Defined in platy_st.c - run-time error number */

extern i32 stateType[NUM_STATES];
extern String keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern i32 transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */
#include "scanner.h" // Assuming scanner.h is included to access ScannerData and ReaderPointer

i32 startScanner(ReaderPointer psc_buf) {
	/* TO_DO: Start histogram */
	/* Basic scanner initialization */

	// Get a pointer to the ScannerData struct from the ReaderPointer
	//ScannerData* scannerData = (ScannerData*)psc_buf;

	// Initialize the histogram
	for (int i = 0; i < NUM_TOKENS; i++) {
		scData.scanHistogram[i] = 0;
	}

	/* in case the buffer has been read previously */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}


/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(Void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	i8 c;	/* input symbol */
	i32 state = 0;		/* initial state of the FSM */
	i32 lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	i32 lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	i32 lexLength;		/* token length */
	i32 i;				/* counter */
	/*
	i8 newc;			// new char
	*/

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

			/* Cases for spaces */
		case ' ':
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

			/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			return currentToken;
		case '{':
			currentToken.code = LB_T;
			return currentToken;
		case '}':
			currentToken.code = RB_T;
			return currentToken;
		case '.':
			currentToken.code = PR_T;
			return currentToken;
		case ',':

			currentToken.code = COM_T;
			return currentToken;
			/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;
		case '"': /* Double quote (") for string literals */
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
				lexEnd = readerGetPosRead(sourceBuffer);
				lexLength = lexEnd - lexStart;
				lexemeBuffer = readerCreate((i32)lexLength + 2, 0, MODE_FIXED);
				if (!lexemeBuffer) {
					fprintf(stderr, "Scanner error: Can not create buffer\n");
					exit(1);
				}
				readerRestore(sourceBuffer);
				for (i = 0; i < lexLength; i++)
					readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
				readerAddChar(lexemeBuffer, READER_TERMINATOR);
				currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
				readerRestore(lexemeBuffer);
				return currentToken;

		case '=':
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.code = REL_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_EQ;
			}
			else {
				currentToken.code = ASS_OP_T;
				scData.scanHistogram[currentToken.code]++;
			}
			return currentToken;

		case '!':
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.code = REL_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.relationalOperator = OP_NE;
			}
			else {
				currentToken.code = LOG_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_NOT;
			}
			return currentToken;
		case '>':
			currentToken.code = REL_OP_T;
			scData.scanHistogram[currentToken.code]++;
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.attribute.relationalOperator = OP_GE;
			}
			else {
				currentToken.attribute.relationalOperator = OP_GT;
			}
			return currentToken;
		case '<':
			currentToken.code = REL_OP_T;
			scData.scanHistogram[currentToken.code]++;
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.attribute.relationalOperator = OP_LE;
			}
			else {
				currentToken.attribute.relationalOperator = OP_LT;
			}
			return currentToken;

		case '&':
			if (readerGetChar(sourceBuffer) == '&') {
				currentToken.code = LOG_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_AND;
			}

			else
			{
				currentToken.code = ERR_T;
				scData.scanHistogram[currentToken.code]++;
				strcpy(currentToken.attribute.errLexeme, "Illegal statement.");
				return currentToken;
			}
			return currentToken;

		case '|':
			if (readerGetChar(sourceBuffer) == '|') {
				currentToken.code = LOG_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_OR;
			}
			else
			{
				currentToken.code = ERR_T;
				scData.scanHistogram[currentToken.code]++;
				strcpy(currentToken.attribute.errLexeme, "Illegal statement.");
				return currentToken;
			}

		case  '+':
			currentToken.code = ART_OP_T;
			scData.scanHistogram[currentToken.code]++;
			scData.scanHistogram[currentToken.code]++; OP_ADD;
			currentToken.attribute.arithmeticOperator = OP_ADD;

				return currentToken;

		case '-':
			currentToken.code = ART_OP_T;
			scData.scanHistogram[currentToken.code]++;
			scData.scanHistogram[currentToken.code]++; OP_SUB;
			currentToken.attribute.arithmeticOperator = OP_SUB;
				return currentToken;

		case '*':
			currentToken.code = ART_OP_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			return currentToken;


		case '/':
			if (readerGetChar(sourceBuffer) == '/') {
				readerGetChar(sourceBuffer);
				do {
					c = readerGetChar(sourceBuffer);
					if (c == '\n') {
						line++;
						break;
					}
				} while (1);
				currentToken.code = CMT_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
			else {
				currentToken.code = ART_OP_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.arithmeticOperator = OP_DIV;
				return currentToken;
			}


			/* ------------------------------------------------------------------------
				Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
				Note: Part 2 must follow Part 1 to catch the illegal symbols
				-----------------------------------------------------------------------
			*/

			/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((i32)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

i32 nextState(i32 state, i8 c) {
	i32 col;
	i32 next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}



/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
 /* TO_DO: Use your column configuration */

 /* Adjust the logic to return next column in TT */
	
i32 nextClass(i8 c) {
	i32 val = -1;
	switch (c) {
	case CHRCOL2:
		val = 2;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 5;
		break;

	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else
			val = 7;
	}
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	i32 isCMT = false;
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;

		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "RUN TIME ERROR");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	
	}

	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "RUN TIME ERROR");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	if (isCMT == true) {
		strcpy(currentToken.attribute.idLexeme , lexeme , VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}

	currentToken.code = CMT_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}



/*
 ************************************************************
 * Acceptance State Function IL
 *		Function responsible to identify IL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually,
 *   additional three dots (...) should be put in the output.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcIL(String lexeme) {
	Token currentToken = { 0 };
	i64 tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[FSNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = D_T;
			currentToken.attribute.intValue = (i32)tlong;
		}
		else {
			currentToken = (*finalStateTable[FSNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(String lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	i8 lastch = lexeme[length - 1];
	i32 isID = false;
	switch (lastch) {
	case MNID_SUF:
		currentToken.code = MNID_T;
		isID = true;
		break;
	default:
		// Test Keyword
		currentToken = (*finalStateTable[FSWR])(lexeme); // Handle error: Invalid identifier ending
		break;
	}
	if (isID == true) {

		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}

	return currentToken;
}




/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table
 *   (stringLiteralTable). You need to include the literals in
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
Token funcSL(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	// Terminate the string literal with a null character
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	line++; // Increment line count for the closing double quote
	currentToken.code = L_T;
	return currentToken;
}

Token funcVID(String lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	char lastch = lexeme[length - 1];
	i32 isVID = false;
	i32 vidindex = -1;
	i32 i = 0;

	for (i = 0; i < length; i++) {
		if (lexeme[i] < 0 || lexeme[i] >= 255) {
			isVID = false;
			break;
		}
		isVID = true;
	}

	if (isVID == true) {
		currentToken.code = VID_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	else {
		currentToken.code = ERR_T;
		scData.scanHistogram[currentToken.code]++;
	}
	return currentToken;
}
 





/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

/* TO_DO: Adjust the function for KEY */
Token funcKEY(String lexeme) {
	Token currentToken = { 0 };
	i32 kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		//currentToken = funcErr(lexeme);
	/*

		currentToken.code = VID_T;
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
		*/

		
		if (!strcmp(lexeme, "+")) {
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_ADD;
		}
		else if (!strcmp(lexeme, "-")) {
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_SUB;

		}
		else if (!strcmp(lexeme, "*")) {
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_MUL;

		}
		else if (!strcmp(lexeme, "/")) {
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_DIV;
		}

		else if (!strcmp(lexeme, "==")) {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_EQ;
		}
		else if (!strcmp(lexeme, "!=")) {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_NE;
		}
		else if (!strcmp(lexeme, ">")) {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_GT;

		}
		else if (!strcmp(lexeme, "<")) {
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_LT;
		}

		else if (!strcmp(lexeme, "&&")) {
			currentToken.code = LOG_OP_T;
			currentToken.attribute.logicalOperator = OP_AND;

		}
		else if (!strcmp(lexeme, "||")) {
			currentToken.code = LOG_OP_T;
			currentToken.attribute.logicalOperator = OP_OR;
		}
		else if (!strcmp(lexeme, "!")) {
			currentToken.code = LOG_OP_T;
			currentToken.attribute.logicalOperator = OP_NOT;
		}

		else {
			currentToken.code = VID_T;
			strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
			currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
		}

		if (!strcmp(lexeme, "=")) {
			currentToken.code = ASS_OP_T;
		}
		


	}
	return currentToken;
}
/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(String lexeme) {
	Token currentToken = { 0 };
	i32 i = 0, len = (i32)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

Void printToken(Token t) {
	extern String keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case L_T:
		printf("STR_T\t\t%d\t ", (i32)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (i32)t.attribute.codeType));
		break;
	case D_T:
		printf("D_T\t\t%d\t ", (i32)t.attribute.codeType);
		printf("%d\n", t.attribute.intValue);
		break;
	case VID_T:
		printf("VID_T\t\t%d\t ", (i32)t.attribute.codeType);
		printf("%d\n", t.attribute.intValue);
		break;
	case LPR_T:
		printf("LPR_T\t\t(\n");
		break;
	case RPR_T:
		printf("RPR_T\t\t)\n");
		break;
	case LB_T:
		printf("LBR_T\t\t}\n");
		break;
	case RB_T:
		printf("RBR_T\t\t{\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\t\t//\n");
		break;
	case EOS_T:
		printf("EOS_T\t\t;\n");
		break;
	case ART_OP_T:
		if (t.attribute.arithmeticOperator == OP_ADD) {
			printf("OP_ADD \t\t+\n");
		}
		else if (t.attribute.arithmeticOperator == OP_SUB) {
			printf("OP_SUB \t\t-\n");
		}
		else if (t.attribute.arithmeticOperator == OP_MUL) {
			printf("OP_MUL \t\t*\n");
		}
		else if (t.attribute.arithmeticOperator == OP_DIV) {
			printf("OP_DIV \t\t/\n");
		}
		break;

		case '==':
		printf("OP_EQ \t\t==\n");
		break;
		case REL_OP_T:
			if (t.attribute.arithmeticOperator == OP_NE) {
				printf("OP_NE \t\t!=\n");
			}
			else if (t.attribute.arithmeticOperator == OP_GT) {
				printf("OP_GT \t\t>\n");
			}
			else if (t.attribute.arithmeticOperator == OP_LT) {
				printf("OP_LT \t\t<\n");
			}
			else if (t.attribute.arithmeticOperator == OP_GE) {
				printf("OP_GE \t\t>=\n");
			}
			else if (t.attribute.arithmeticOperator == OP_LE) {
				printf("OP_LE \t\t<=\n");
			}
			break;
	
		case LOG_OP_T:
			if (t.attribute.arithmeticOperator == OP_AND) {
				printf("OP_AND \t\t&&\n");
			}
			else if (t.attribute.arithmeticOperator == OP_OR) {
				printf("OP_OR \t\t||\n");
			}
			else if (t.attribute.arithmeticOperator == OP_NOT) {
				printf("OP_NOT \t\t!\n");
			}
			break;
	case ASS_OP_T:
		printf("ASS_OP_T \t\t=\n");
		break;


	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
Void printScannerData(ScannerData scData) {

	/* TO_DO: Implement the function to print Scanner statistics */
	printf("Token statistics:\n");

	/* Define an array to store token names corresponding to the token codes */
	String tokenNames[NUM_TOKENS] = {
		"ERR_T", "MNID_T", "INL_T", "STR_T", "LPR_T", "RPR_T",
		"LBR_T", "RBR_T", "KW_T", "EOS_T", "RTE_T", "SEOF_T", "CMT_T"
	};

	/* Print the frequency count of each token type */
	for (i32 i = 0; i < NUM_TOKENS; i++) {
		printf("%-8s : %d\n", tokenNames[i], scData.scanHistogram[i]);
	}

}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
