/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: Hadiyah Khan
* Professors: Paulo Sousa
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#             @@@@|I R O N C L A D|@@@@           #
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152  Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */

#define FUL_FLAG 0x08               /* (0000.1000)_2 = (008)_10 */		// its full
#define EMP_FLAG 0x04               /* (0000.0100)_2 = (004)_10 */		// its empty
#define REL_FLAG 0x02               /* (0000.0010)_2 = (002)_10 */		// release condition
#define END_FLAG 0x01               /* (0000.0001)_2 = (001)_10 */		//end state


#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (IronClad) .................................. *
/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct offset {
	i32 mark  ;			/* the offset to the mark position (in chars) */
	i32 read;			/* the offset to the get a char position (in chars) */
	i32 wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */
typedef struct bufferReader {
String			content;			/* pointer to the beginning of character array (character buffer) */
i32				size;				/* current dynamic memory size (in bytes) allocated to character buffer */
i32				increment ;			/* character array increment factor */
i32				mode;				/* operational mode indicator */
i8				flags;				/* contains character array reallocation flag and end-of-buffer flag */
Offset			offset;				/* Offset / position field */
i8				histogram[NCHAR] ;	/* Statistics of chars */
i32				numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * 	ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer		readerCreate		(i32, i32, i32);
ReaderPointer		readerAddChar		(ReaderPointer const, i8);
Bool				readerClear					(ReaderPointer const);
Bool				readerFree						 (ReaderPointer const);
Bool				readerIsFull						(ReaderPointer const);
Bool				readerIsEmpty		(ReaderPointer const);
Bool				readerSetMark	(ReaderPointer const, i32);
i32					readerPrint	    (ReaderPointer const);
i32					readerLoad		(ReaderPointer const, FILE* const);
Bool				readerRecover		(ReaderPointer const);
Bool				readerRetract		(ReaderPointer const);
Bool				readerRestore		(ReaderPointer const);
/* Getters */
i8			readerGetChar 				(ReaderPointer const);
String		readerGetContent			(ReaderPointer const, i32);
i32			readerGetPosRead			(ReaderPointer const);
i32			readerGetPosWrte			(ReaderPointer const);
i32			readerGetPosMark			(ReaderPointer const);
i32			readerGetSize				(ReaderPointer const);
i32			readerGetInc				(ReaderPointer const);
i32			readerGetMode				(ReaderPointer const);
i32			readerGetFlags				(ReaderPointer const);
Void		readerPrintStat				 (ReaderPointer const);
i32			readerNumErrors				(ReaderPointer const);

#endif
