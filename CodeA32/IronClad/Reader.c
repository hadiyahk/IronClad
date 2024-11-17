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
#  @@@@@@@@                  @@    @@             @@@@      @@@@@@  #
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

/*                 ,
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/
#define REALLOC_FLAG 0x10	/* (0001.0000)_2 = (016)_10 */ 	// New flag for reallocation


ReaderPointer readerCreate(i32 size, i32 increment, i32 mode) {
   ReaderPointer readerPointer;
    
    /* TO_DO: Defensive programming */
   if (size < 0 || increment < 0){
	return NULL;
   }
    
    /* TO_DO: Adjust the values according to parameters */
	if (size == 0){
		size = READER_DEFAULT_SIZE;
	}  
	if (increment == 0){
		increment = READER_DEFAULT_INCREMENT;
	}
	/*CHECK IF MODE IS SILL VLAID */
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI){
		mode = MODE_FIXED;
	}

	  readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer){
		return NULL;
	}
	readerPointer ->content = (String)malloc(size);
	if(!readerPointer-> content){
		free(readerPointer);
		return NULL;
	}
    
    /* TO_DO: Initialize the histogram */
    readerPointer->size = size;
    readerPointer->increment = increment;
    readerPointer->mode = mode;
    
    // Initialize the histogram array
    for (int i = 0; i < NCHAR; i++) {
        readerPointer->histogram[i] = 0;
    }
    
    /* TO_DO: Initialize flags */
    readerPointer->flags = READER_DEFAULT_FLAG;  /* Set the default flags */
    
    /* TO_DO: The created flag must be signaled as EMP */
    readerPointer->flags |= EMP_FLAG;
    
    return readerPointer;
}




/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, char ch) {
	String tempReader = NULL;
	i32 newSize = 0;
	/* TO_DO: Defensive programming */
		if (readerPointer == NULL || readerPointer-> content == NULL){
			return NULL;
		}
		if (ch<0 || ch>NCHAR)
			return NULL;

	/* TO_DO: Reset Realocation */

		readerPointer->flags &= ~REALLOC_FLAG;

	/* TO_DO: Test the inclusion of chars */
	

	if (readerPointer->offset.wrte * (i32)sizeof(char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= ~FUL_FLAG;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;

			/* TO_DO: Defensive programming */
			/* Check if new size is valid (not negative and lower than READER_MAX_SIZE) */
			if (newSize < 0 || newSize >= READER_MAX_SIZE) {
				readerPointer->flags |= FUL_FLAG; // Set the FULL flag if the new size is invalid
				return NULL; // Return NULL (error condition)
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			/*check if new size is valid (not negative , loweer then READER_MAX_SIZE)*/
			if (newSize < 0 || newSize >= READER_MAX_SIZE){
				readerPointer ->flags |= FUL_FLAG; //set flag id new size is invlaid 
				return NULL; // (ERROR CONDIIOTN)
			}
			break;
		default:
			return NULL; // if mode is not recognized, return null(another error condition)
		}
		/* TO_DO: New reader allocation */

		tempReader = (String)realloc(readerPointer->content, newSize * sizeof(char));
		/* TO_DO: Defensive programming */
		if (tempReader == NULL) {
		readerPointer->flags |= FUL_FLAG; //SET THE FULL FLAG IF THE REALLOC FIALS 
		return NULL; 
	}

		

		/* TO_DO: Check Relocation */
			if (tempReader != readerPointer -> content){
				readerPointer->flags |= REALLOC_FLAG; // set the flag if the memory adrss has changes
			}
			readerPointer -> content = tempReader;  	// update the content pointer with the new allocated memory
			readerPointer -> size = newSize; 		// update the size with new size

	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->offset.wrte++] = ch;
	/* TO_DO: Updates histogram */
	if (ch >= 0 && ch < NCHAR){
		// INCREMEMTN THE FREQUENCY COUNT OF  THE CHARACTER 
		readerPointer->histogram[ch]++;
	}
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer -> content== NULL){
		return false; // invalid reader or conent pointer, return false 

	}
	/*reset offsets*/
	readerPointer -> offset.read = 0;
	readerPointer -> offset.mark = 0;
	readerPointer-> offset.wrte = 0;

	/*Reset flags */
	readerPointer -> flags = 0;
	/* TO_DO: Adjust flags original */
/* Adjust flags original (if needed) */
/* Adjust flags original */
readerPointer->flags &= ~(FUL_FLAG | EMP_FLAG | REL_FLAG | END_FLAG);

	return true;


}


/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL){
		return false; 			// invalid reader pointer, return false
	}

	/* TO_DO: Free pointers */
	if (readerPointer-> content != NULL){
		return false;
	}
	free(readerPointer);
	return true;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL){
		return false; 		//Invalid reader pointer, reutrn FALSE
	}
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer -> flags & FUL_FLAG){
		return true;		//Bugger is full, reutrn true
	}

	return false;			// buffer is not full, return FALSE
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL){
		return false; //invlid reader pointer, rreturn false 

	}

	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer -> flags & EMP_FLAG){
		return true;  	//buffer is empty, return TRUE
	}
	return false;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerSetMark(ReaderPointer const readerPointer, i32 mark ) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || mark < 0 || mark > readerPointer -> offset.wrte){
		return false; 		// invlaid reader pointe ror mark value, return FALSE 

	}
	
	/* TO_DO: Adjust mark */
	readerPointer-> offset.mark= mark;
	return true;		//mark set successfully, return true
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your L
ANGUAGE.
*************************************************************
*/
i32 readerPrint(ReaderPointer const readerPointer) {
	i32 cont = 0;
	char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (readerPointer == NULL){
		return cont; // return 0 if readerPoitner is null 
	}
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (!(readerPointer->flags & END_FLAG)) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	i32 size = 0;
	char c;
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || fileDescriptor == NULL){
		return READER_ERROR; 		// return arror value if reader or filedescirpr is null 
	}
	c = (char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	if (ferror(fileDescriptor)){
		return READER_ERROR;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL){
		return false;
	}
	/* TO_DO: Recover positions */
	readerPointer -> offset.read = 0;
	readerPointer ->offset.mark = 0;
	return true;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL ){
		return false;
	}
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer -> offset.read > 0){
		readerPointer-> offset.read--;
	}
	return true;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Bool readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL){
		return false;
	}
	/* TO_DO: Restore positions (read/mark) */
	readerPointer-> offset.read = readerPointer->offset.mark;
	return true;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i8 readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer-> content == NULL){
		return '\0';
	}
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->offset.read == readerPointer->offset.wrte) {
		/*set EOB flag*/
		readerPointer->flags |= END_FLAG;
	}
	else {
			/*reset EOB flag*/
			readerPointer -> flags &= ~END_FLAG;

		}
		
	return readerPointer->content[readerPointer->offset.read++];
}



/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
String readerGetContent(ReaderPointer const readerPointer, i32 pos) {
    /* Defensive programming */
    if (readerPointer == NULL || readerPointer->content == NULL || pos < 0 || pos >= readerPointer->offset.wrte) {
        return NULL; // Return NULL if readerPointer is NULL, content is NULL, or pos is out of bounds
    }

    return &(readerPointer->content[pos]);
}




/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosRead(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }

    return readerPointer->offset.read;
}



/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }
	/* TO_DO: Return wrte */
	 return readerPointer->offset.wrte;
	
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetPosMark(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }

    return readerPointer->offset.mark;
}



/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetSize(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }

    return readerPointer->size;
}


/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetInc(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }

    return readerPointer->increment;
}


/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetMode(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return -1; // Return -1 to indicate an error if readerPointer is NULL
    }

    return readerPointer->mode;
}



/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerGetFlags(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return 0; // Return 0 to indicate an error if readerPointer is NULL
    }

    return readerPointer->flags;
}




/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
Void readerPrintStat(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return; // Return if readerPointer is NULL
    }

    printf("Histogram:\n");
    for (int i = 0; i < NCHAR; i++) {
		printf("Character '%d': Count = %d\n", i, readerPointer->histogram[i]);
    }
}


/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
i32 readerNumErrors(ReaderPointer const readerPointer) {
    /* TO_DO: Defensive programming */
    if (readerPointer == NULL) {
        return 0; // Return 0 if readerPointer is NULL
    }

    i32 numErrors = 0;
    for (int i = 0; i < readerPointer->offset.wrte; i++) {
        char c = readerPointer->content[i];
        if (c < 0 || c >= NCHAR) {
            numErrors++;
        }
    }

    return numErrors;
}


































