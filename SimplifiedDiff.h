/*
 * SimplifiedDiff.h
 *
 *  Created on: May 20, 2017
 *      Author: kchristopher
 */

#ifndef SIMPLIFIEDDIFF_H_
#define SIMPLIFIEDDIFF_H_

#include <stdio.h>

/// class to handle reading one of the input files character by character
class CFileReader
{
public:
    CFileReader():m_pFile(NULL){}
    int OpenFile(const char * pFileName);
    int ReadChar(char &nRead);
    void CloseFile();

    // get the next letter to diff in the file
    int GetNextLetter(char &nRead);
protected:
    FILE *m_pFile;
};


#endif /* SIMPLIFIEDDIFF_H_ */
