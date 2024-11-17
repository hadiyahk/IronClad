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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

 Void startParser() {
	/* TO_DO: Initialize Parser data */
	i32 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}



/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
 Void matchToken(i32 tokenCode, i32 tokenAttribute) {
	 i32 matchFlag = 1;
	 //printf(" %d", lookahead.code);
	 switch (lookahead.code) {
	 case KW_T:
		 if (lookahead.attribute.codeType != tokenAttribute)
			 matchFlag = 0;
		 break;  // Add a break statement here
	 case ASS_OP_T:  // Add this case
		 if (lookahead.code != tokenCode)
			 matchFlag = 0;
		 break;
	 default:
		 if (lookahead.code != tokenCode)
			 matchFlag = 0;
		 break;  // Add a break statement here
	 }

	 if (matchFlag && lookahead.code == SEOF_T)
		 return;

	 if (matchFlag) {
		 lookahead = tokenizer();
		 if (lookahead.code == ERR_T) {
			 printError();
			 lookahead = tokenizer();
			 syntaxErrorNumber++;
		 }
	 }
	 else {
		 syncErrorHandler(tokenCode);
	 }
 }


/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
Void syncErrorHandler(i32 syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
Void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case L_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LB_T:
		printf("LBR_T\n");
		break;
	case RB_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
Void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T: 
		matchToken(KW_T, KW_fn);
		

	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(RPR_T, NO_ATTR);
			matchToken(LB_T, NO_ATTR);
			optionalStatements();
			matchToken(RB_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
Void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 * 
 * no data session in ironClad 
 */


/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
Void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		switch (lookahead.code) {
		case ASS_OP_T:
			matchToken(ASS_OP_T, NO_ATTR);
			break;
		case ART_OP_T:
			switch (lookahead.attribute.arithmeticOperator) {
			case OP_ADD:
				matchToken(ART_OP_T, OP_ADD);
				break;
			case OP_SUB:
				matchToken(ART_OP_T, OP_SUB);
				break;
			case OP_MUL:
				matchToken(ART_OP_T, OP_MUL);
				break;
			case OP_DIV:
				matchToken(ART_OP_T, OP_DIV);
				break;
			default:
				printError(); // Handle invalid arithmetic operators
			}
			break;
		default:
			printError(); // Handle other cases
		}


		if (lookahead.code == 2) {
			matchToken(D_T, NO_ATTR);
		}
		else if (lookahead.code == 21) {
			matchToken(F_T, NO_ATTR);
		}
		else if (lookahead.code == 3) {
			matchToken(L_T, NO_ATTR);
		}
		else {
			printError();

		}
		matchToken(EOS_T, NO_ATTR);

		break;

	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 * 
 * no code session in ironclad
 */

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
Void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	case KW_T:

			statements();  
		break;

	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
Void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
Void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	case VID_T:
		statements();
		break;
	case CMT_T:
		comment();
	case KW_T:
		statements();
		break;

	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
Void statement() {
	printf("lookahead.code: %d, lookahead.attribute.codeType: %d\n", lookahead.code, lookahead.attribute.codeType);
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		assignmentStatement();
		break;
	case KW_T :
		switch (lookahead.attribute.codeType) {
		case KW_let:
			matchToken(KW_T, KW_let);
			optVarListDeclarations();
			break;
		case KW_if:
			matchToken(KW_T, KW_if);          // Match 'if'
			//matchToken(LPR_T, NO_ATTR);       // Match '('
			Relational_Expression();         // Parse optional variable declarations
			matchToken(LB_T, NO_ATTR);       // Match '{'
			statement();                      // Parse the statement inside the 'if' block
			matchToken(RB_T, NO_ATTR);       // Match '}'
			break;
		case KW_else:
			matchToken(KW_T, KW_else);		//match 'else'
			matchToken(LB_T, NO_ATTR);			//match '{
			statement();
			matchToken(RB_T, NO_ATTR);

			break;
		}

		
		break;

	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();

		}
		if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			inputStatement();

		}
		break;

	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
Void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);			//match '}'
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}


Void assignmentStatement() {
	psData.parsHistogram[BNF_assignmentStatement]++;
	matchToken(ASS_OP_T, NO_ATTR);
	outputVariableList();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": assignment statement parsed");

}



/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
Void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
		
	case L_T:
		matchToken(L_T, NO_ATTR);
		break;
	case D_T:
		matchToken(D_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
/*
*
*FOR if statment ([ggeri == 984)]
*/
Void Relational_Expression() {
	psData.parsHistogram[BNF_Relational_Expression]++;
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);

		switch (lookahead.attribute.relationalOperator) {
		case OP_EQ:
			matchToken(REL_OP_T, OP_EQ);
			break;
		case OP_NE:
			matchToken(REL_OP_T, OP_NE);
			break;
		case OP_GT:
			matchToken(REL_OP_T, OP_GT);
			break;
		case OP_LT:
			matchToken(REL_OP_T, OP_LT);
			break;
		case OP_GE:
			matchToken(REL_OP_T, OP_GE);
			break;
		case OP_LE:
			matchToken(REL_OP_T, OP_LE);
			break;
		default:
			printError(); // Handle invalid relational operators
		}

		if (lookahead.code == 2) {
			matchToken(D_T, NO_ATTR);
		}
		else if (lookahead.code == 21) {
			matchToken(F_T, NO_ATTR);
		}
		else if (lookahead.code == 3) {
			matchToken(L_T, NO_ATTR);
		}
		else {
			printError();
		}
		//matchToken(RPR_T, NO_ATTR); // )

		break;

	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Relational_Expression Declarations parsed");
}


/*
 * Input Statement
 * BNF: <input statement> -> input& (<input variable list>);
 * FIRST(<input statement>) = { MNID_T(input&) }
 */
Void inputStatement() {
	psData.parsHistogram[BNF_inputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	inputVariableList();
	matchToken(RPR_T, NO_ATTR); // Match ')'
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

/*
 * Input Variable List
 * BNF: <input variable list> -> <input variable> <input variable list'>
 * FIRST(<input variable list>) = { IVID_T }
 */
Void inputVariableList() {
	psData.parsHistogram[BNF_inputVariableList]++;
	inputVariable();
	inputVariableListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Input variable list parsed");
}

/*
 * Input Variable List Prime
 * BNF: <input variable list'> -> , <input variable list> | ϵ
 * FIRST(<input variable list'>) = { ',' }
 */
Void inputVariableListPrime() {
	psData.parsHistogram[BNF_inputVariableListPrime]++;
	if (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR); // Match ','
		inputVariableList();
	}
	// Empty
}

Void inputVariable() {
	psData.parsHistogram[BNF_inputVariable]++;

	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	case L_T:
		matchToken(L_T, NO_ATTR);
		break;
	case D_T:
		matchToken(D_T, NO_ATTR);
		break;
	default:
		printError();
	}

	printf("%s%s\n", STR_LANGNAME, ": Input variable parsed");
}






/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
mold_void printBNFData(ParserData psData) {
}
*/
Void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}
