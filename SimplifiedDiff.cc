/*
 ============================================================================
 Name        : TestProgram.c
 Author      : Kevin Christopher
 Version     :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "SimplifiedDiff.h"


/// CFileReader::GetNextLetter(char &nRead)
/// \brief get the next letter to diff in the file
/// \param nRead - return by reference the next letter
/// \return - status -1 = error
int CFileReader::GetNextLetter(char &nRead)
{
    int nStatus = 0;
    // need to have a search that covers any file size
    while(nStatus >=0 )
    {
        nStatus = ReadChar(nRead);
        if(nStatus<0)
        {
            return nStatus;
        }
        // if upper case shift to lower case
        if (isupper(nRead))
        {
            nRead=tolower(nRead);
        }
        // TODO what to do if the file has a non supported character?
        // Assuming everything that is not a letter is white space
        // skip white space
        if(islower(nRead))
        {
            return 1;
        }
    }
    return -1;
}

/// CFileReader::OpenFile(const char * pFileName)
/// \brief Open the given file for reading
/// \param pFileName - file name and path to open
/// \return - status -1 = error
int CFileReader::OpenFile(const char * pFileName)
{
    // open the file read only
    m_pFile = fopen(pFileName, "r");
    // make sure the file was opened
    if(m_pFile == NULL)
    {
        return -1;
    }
    return 0;
}

/// CFileReader::ReadChar(char &nRead)
/// \brief Read the next character
/// \param nRead - return by reference the next character
/// \return - status -1 = error
int CFileReader::ReadChar(char &nRead)
{
    // check that the file is open before reading
    if(m_pFile == NULL)
    {
        return -1;
    }
    nRead = (char)fgetc(m_pFile);
    if(nRead == EOF)
    {
        // once complete reading close the file
        CloseFile();
        return -1;
    }
    return 0;
}

/// CFileReader::CloseFile()
/// \brief Close the file
void CFileReader::CloseFile()
{
    if(m_pFile != NULL)
    {
        fclose(m_pFile);
        m_pFile=NULL;
    }
}



// inputs file_name1, file_name2
int main (int argc, char *argv[])
{
    //check that there are the correct number of arguments
    if(argc < 3)
    {
        printf("not enough arguments\n./TestProgram file_name1 file_name2\n");
        return EXIT_SUCCESS;
    }
    char *FileName1 = argv[1];
    char *FileName2 = argv[2];

    int nStatus1=0;
    int nStatus2=0;

    CFileReader nReader1;
    CFileReader nReader2;

    nStatus1 = nReader1.OpenFile(FileName1);
    if(nStatus1<0)
    {
        printf("Error opening %s\n",FileName1);
        nReader1.CloseFile();
        return EXIT_SUCCESS;
    }
    nStatus2 = nReader2.OpenFile(FileName2);
    if(nStatus2<0)
    {
        printf("Error opening %s\n",FileName2);
        nReader2.CloseFile();
        return EXIT_SUCCESS;
    }

    char nRead1=0;
    char nRead2=0;
    //continue checking until all characters have been read
    while(1)
    {
        nStatus1 = nReader1.GetNextLetter(nRead1);
        nStatus2 = nReader2.GetNextLetter(nRead2);
        //printf("status %d, %d, read %c, %c\n",nStatus1,nStatus2,nRead1,nRead2);
        if((nStatus1<0) && (nStatus2<0))
        {
            // completed checking print new line after the answer
            printf("\n");
            return EXIT_SUCCESS;
        }
        // if only one character is available print that character
        if(nStatus1<0)
        {
            printf("%c",nRead2);
        }
        else if(nStatus2<0)
        {
            printf("%c",nRead1);
        }
        else if(nRead1 != nRead2)
        {
            char nDiff = nRead1 - nRead2 + 96;
            if(nDiff < 'a')
            {
                nDiff += 27;
            }
            printf("%c",nDiff);
        }
    }




    return EXIT_SUCCESS;
}

