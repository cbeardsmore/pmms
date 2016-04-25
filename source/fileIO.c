 /***************************************************************************
 *	FILE: fileIO.c							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Perform reading of matrix elements from a file
 *	LAST MOD: 16/04/16	
 *  REQUIRES: stdio.h, fileIO.h	   
 ***************************************************************************/

#include <stdio.h>
#include "fileIO.h"

//--------------------------------------------------------------------------
// FUNCTION: readFile()
// IMPORT: filename (char*), matrix (int*)
// EXPORT: status (int)
// PURPOSE: Read matrix from file and store its elements in a Matrix struct 

int readFile( char* filename, int* matrix, int rows, int cols)
{
	int nRead;
	int offset = 0;

	// ENSURE FILE OPENED CORRECTLY
	FILE* f = fopen( filename, "r" );

	if ( f == NULL )
	{
		perror( "ERROR opening file!\n" );
		return -1;
	}

	for ( int ii = 0; ii < rows; ii++ )
	{	
		offset = ii * cols;
		for ( int jj = 0; jj < cols; jj++ )
		{	
			nRead = fscanf( f, "%d", ( &matrix[offset + jj] ) );
		}
	}

	fclose(f);
	return 0;
}
//-------------------------------------------------------------------------- 