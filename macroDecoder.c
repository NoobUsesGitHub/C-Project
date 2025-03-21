#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"
#include "MacroListFuncs.h"
#include "FileListFuncs.h"

FileList *macroDecoder(FILE *fp, char *fileName)
{
    bool macroCollectionStarted = FALSE, skp = FALSE;
    MacroList *header, *curMacro;
    constMacroList(&header);
    char *pch = NULL, str[MAX_LINE_SIZE], temp[MAX_LINE_SIZE];
    char strNewName[strlen(fileName)];

    FileList *macroFileNode;
    constNode(&macroFileNode);
    strcpy(strNewName, fileName);
    strNewName[strlen(strNewName) - 1] = 'm';
    macroFileNode->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(macroFileNode->fileName, strNewName);
    macroFileNode->file = fopen(strNewName, "w+");
    if (fp == NULL || macroFileNode->file == NULL)
    {
        macroFileNode->file = NULL;
        fprintf(stdout, "%s: Couldn't create a decoded macro file",fileName);
        return macroFileNode;
    }

    while (fgets(str, MAX_LINE_SIZE, fp) != NULL)
    {
        strcpy(temp, str);
        pch = strtok(temp, delimints); /*start strtok*/

        if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
        {
            skp = TRUE;
            macroCollectionStarted = FALSE;
        }

        if (macroCollectionStarted == TRUE)
        {
            addLineToNode(curMacro, str);
            skp = TRUE;
        }

        while ((pch != NULL) && (skp != TRUE) && (macroCollectionStarted == FALSE))
        {
            /*checking for mactros*/
            if (strcmp(pch, "mcr") == 0)
            {
                macroCollectionStarted = TRUE;
                pch = strtok(NULL, delimints);
                curMacro = addMacroToList(header, pch, NULL);
                if (stringToOperatorType(pch) != -1)
                    fprintf(stdout, "%s: %s can't be a name of a macro!",fileName, pch);
                skp = TRUE;
            }

            if (skp == FALSE && massIsSpace(pch) == 0)
            {
                if (dumpIfexistsInMacro(header, hasher(pch), macroFileNode->file) == 0)
                {
                    if (pch[strlen(pch) - 1] != '\n')
                        fprintf(macroFileNode->file, "%s ", pch);
                    else
                        fprintf(macroFileNode->file, "%s", pch);
                }
            }

            pch = strtok(NULL, delimints);
        }
        skp = FALSE;
    }

    freeMacroList(header);
    rewind(macroFileNode->file);

    return macroFileNode;
}
