 /***************************************************************************
 *	FILE: fileIO.c
 *	AUTHOR: Connor Beardsmore - 15504319
 *	UNIT: OS200 Assignment S1 - 2016
 *	PURPOSE: Perform reading of matrix elements from a file
 *	LAST MOD: 16/04/16
 *  REQUIRES: fileIO.h
 ***************************************************************************/

#include "fileIO.h"

//--------------------------------------------------------------------------
// FUNCTION: readFile()
// IMPORT: filename (char*), matrix (int*), rows (int), cols (int)
// EXPORT: status (int)
// PURPOSE: Read matrix from file and store its elements in an int array

int readFile( char* filename, int* matrix, int rows, int cols)
{
	int nRead;
	int offset = 0;
	int status = 0;

	// OPEN FILE AND CONFIRM NO ERRORS OCCURRED
	FILE* f = fopen( filename, "r" );
	if ( f == NULL )
	{
		perror( "ERROR - opening file!\n" );
		return -1;
	}

	// ITERATE TO FILL ALL MATRIX ROWS
	for ( int ii = 0; ii < rows; ii++ )
	{
		// ITERATE TO FILL ALL MATRIX ROWS
		offset = ii * cols;
		for ( int jj = 0; jj < cols; jj++ )
		{
			nRead = fscanf( f, "%d", ( &matrix[offset + jj] ) );
			if ( nRead < 0 )
			{
				// CHECK THAT ENOUGH VALUES HAVE BEEN READ
				if ( (offset + jj) < (rows * cols - 1) )
				{
					fprintf( stderr, "ERROR - not enough matrix values" );
					status = -1
				}
				// CHECK THAT NO ERROR FORCED EARLY EXIT
				else if ( ferror(f) )
				{
					perror("ERROR - reading matrix file!\n");
					status = -1;
				}
			}
		}
	}

	fclose(f);
	return status;
}
//--------------------------------------------------------------------------
