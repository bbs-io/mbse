/*****************************************************************************
 *
 * $Id$
 * Purpose ...............: Language functions.
 *
 *****************************************************************************
 * Copyright (C) 1997-2002
 *   
 * Michiel Broek		FIDO:		2:280/2802
 * Beekmansbos 10
 * 1971 BV IJmuiden
 * the Netherlands
 *
 * This file is part of MBSE BBS.
 *
 * This BBS is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * MBSE BBS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MBSE BBS; see the file COPYING.  If not, write to the Free
 * Software Foundation, 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *****************************************************************************/

#include "../config.h"
#include "../lib/libs.h"
#include "../lib/memwatch.h"
#include "../lib/mbse.h"
#include "../lib/structs.h"
#include "../lib/users.h"
#include "../lib/records.h"
#include "../lib/common.h"
#include "../lib/clcomm.h"
#include "../lib/mberrors.h"
#include "input.h"
#include "language.h"




/*
 * Function will print text in language file
 * Forground Colour, Background Colour, Record Number
 */
void language(int fg, int bg, int lRecord)
{
	pout(fg, bg, *(mLanguage + lRecord));
}



/*
 * Function will return line for output
 */
char *Language(int lRecord)
{
	/*
	 * Return language string
	 */
	return (*(mLanguage + lRecord));
}



int Keystroke(int lRecord, int Pos)
{
	char	temp[30];

	memset(&temp, 0, sizeof(temp));
	sprintf(temp, "%s", *(mKeystroke + lRecord));

	if ((Pos < 0) || (Pos > strlen(temp))) {
		WriteError("Keystroke(%d, %d): Range Error", lRecord, Pos);
		return '\0';
	} else {
		return temp[Pos];
	}
}



/*
 * Function will set up the necessary language paths and names
 */
void Set_Language(int iLanguage)
{
	FILE	*pLang;
	char	*temp;

	temp = calloc(PATH_MAX, sizeof(char));
	sprintf(temp, "%s/etc/language.data", getenv("MBSE_ROOT"));

	if ((pLang = fopen(temp, "rb")) == NULL) {
		WriteError("Language: Can't open file: %s", temp);
		printf("\nLanguage: Can't open language file\n\n");
		free(temp);
		Pause();
		return;
	}

	fread(&langhdr, sizeof(langhdr), 1, pLang);
	while (fread(&lang, langhdr.recsize, 1, pLang) == 1) {
		if ((lang.LangKey[0] == iLanguage) && (lang.Available)) {
			strcpy(CFG.current_language, lang.Filename);
			break;
		}
	}

	free(temp);
	fclose(pLang);
}



/*
 * Function will initialize language variables and load them into
 * memory for speed
 */
void InitLanguage()
{
	FILE	*pLang;
	int	iLang = 0;
 	char	*temp;

	temp = calloc(PATH_MAX, sizeof(char));

	sprintf(temp, "%s/etc/%s", getenv("MBSE_ROOT"), CFG.current_language);
	if ((pLang = fopen(temp, "rb")) == NULL) {
		WriteError("$FATAL: Can't open %s", temp);
		ExitClient(MBERR_INIT_ERROR);
	}

	while (fread(&ldata, sizeof(ldata), 1, pLang) == 1) {
		*(mLanguage + iLang) = (char *) calloc(strlen(ldata.sString) + 1, sizeof(char));
		*(mKeystroke + iLang) = (char *) calloc(strlen(ldata.sKey) + 1, sizeof(char));  
		strcpy(mLanguage[iLang], ldata.sString);
		strcpy(mKeystroke[iLang], ldata.sKey);
		iLang++;

		if(iLang >= LANG) {
			printf("FATAL: Language file has to many lines in it");
			ExitClient(MBERR_INIT_ERROR);
		}
	}

	fclose(pLang);
	Syslog('b', "%d language lines read (%s)", iLang, CFG.current_language);
	free(temp);
}



void Free_Language()
{
	int	i;

	for (i = 0; i < LANG; i++) {
		if (*(mLanguage + i))
			free(*(mLanguage + i));
		if (*(mKeystroke + i))
			free(*(mKeystroke + i));
	}
}



