/*****************************************************************************
 *
 * $Id$
 * Purpose: File Database Maintenance - Check filebase
 *
 *****************************************************************************
 * Copyright (C) 1997-2001
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
 * Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *****************************************************************************/

#include "../lib/libs.h"
#include "../lib/structs.h"
#include "../lib/records.h"
#include "../lib/common.h"
#include "../lib/clcomm.h"
#include "../lib/dbcfg.h"
#include "mbfutil.h"
#include "mbfcheck.h"



extern int	do_quiet;		/* Supress screen output	    */
extern int	do_pack;		/* Pack filebase		    */



/*
 *  Check file database integrity, all files in the file database must
 *  exist in real, the size and date/time must match, the files crc is
 *  checked, and if anything is wrong, the file database is updated.
 *  If the file is missing the entry is marked as deleted. With the
 *  pack option that record will be removed.
 *  After these checks, de database is checked for missing records, if
 *  there are files on disk but not in the directory these files are 
 *  deleted. System files (beginning with a dot) are left alone and
 *  the files 'files.bbs', 'files.bak', '00index', 'header' 'readme' 
 *  and 'index.html' too.
 *
 *  Remarks:  Maybe if the crc check fails, and the date and time are
 *            ok, the file is damaged and must be made unavailable.
 */
void Check(void)
{
	FILE	*pAreas, *pFile;
	int	i, iAreas, iAreasNew = 0;
	int	iTotal = 0, iErrors =  0;
	char	*sAreas, *fAreas, *newdir;
	DIR	*dp;
	struct	dirent	*de;
	int	Found, Update;
	char	fn[PATH_MAX];
	struct	stat stb;

	sAreas = calloc(PATH_MAX, sizeof(char));
	fAreas = calloc(PATH_MAX, sizeof(char));
	newdir = calloc(PATH_MAX, sizeof(char));

	if (!do_quiet) {
		colour(3, 0);
		printf("Checking file database...\n");
	}

	sprintf(sAreas, "%s/etc/fareas.data", getenv("MBSE_ROOT"));

	if ((pAreas = fopen (sAreas, "r")) == NULL) {
		WriteError("Can't open %s", sAreas);
		die(0);
	}

	fread(&areahdr, sizeof(areahdr), 1, pAreas);
	fseek(pAreas, 0, SEEK_END);
	iAreas = (ftell(pAreas) - areahdr.hdrsize) / areahdr.recsize;

	for (i = 1; i <= iAreas; i++) {

		fseek(pAreas, ((i-1) * areahdr.recsize) + areahdr.hdrsize, SEEK_SET);
		fread(&area, areahdr.recsize, 1, pAreas);

		if (area.Available) {

			IsDoing("Check area %d", i);

			if (!do_quiet) {
				printf("\r%4d => %-44s    \b\b\b\b", i, area.Name);
				fflush(stdout);
			}

			/*
			 * Check if download directory exists, 
			 * if not, create the directory.
			 */
			if (access(area.Path, R_OK) == -1) {
				Syslog('!', "No dir: %s", area.Path);
				sprintf(newdir, "%s/foobar", area.Path);
				mkdirs(newdir);
			}

			sprintf(fAreas, "%s/fdb/fdb%d.data", getenv("MBSE_ROOT"), i);

			/*
			 * Open the file database, if it doesn't exist,
			 * create an empty one.
			 */
			if ((pFile = fopen(fAreas, "r+")) == NULL) {
				Syslog('!', "Creating new %s", fAreas);
				if ((pFile = fopen(fAreas, "a+")) == NULL) {
					WriteError("$Can't create %s", fAreas);
					die(0);
				}
			} 

			/*
			 * Now start checking the files in the filedatabase
			 * against the contents of the directory.
			 */
			while (fread(&file, sizeof(file), 1, pFile) == 1) {

				iTotal++;
				sprintf(newdir, "%s/%s", area.Path, file.LName);

				if (file_exist(newdir, R_OK)) {
					Syslog('+', "File %s area %d not on disk.", newdir, i);
					if (!file.NoKill) {
						file.Deleted = TRUE;
						do_pack = TRUE;
					}
					iErrors++;
					file.Missing = TRUE;
					fseek(pFile, - sizeof(file), SEEK_CUR);
					fwrite(&file, sizeof(file), 1, pFile);
				} else {
					/*
					 * File exists, now check the file.
					 */
					Marker();
					Update = FALSE;
					if (file_time(newdir) != file.FileDate) {
						Syslog('!', "Date mismatch area %d file %s", i, file.LName);
						file.FileDate = file_time(newdir);
						iErrors++;
						Update = TRUE;
					}
					if (file_size(newdir) != file.Size) {
						Syslog('!', "Size mismatch area %d file %s", i, file.LName);
						file.Size = file_size(newdir);
						iErrors++;
						Update = TRUE;
					}
					if (file_crc(newdir, CFG.slow_util && do_quiet) != file.Crc32) {
						Syslog('!', "CRC error area %d, file %s", i, file.LName);
						file.Crc32 = file_crc(newdir, CFG.slow_util && do_quiet);
						iErrors++;
						Update = TRUE;
					}
					Marker();
					if (Update) {
						fseek(pFile, - sizeof(file), SEEK_CUR);
						fwrite(&file, sizeof(file), 1, pFile);
					}
				}
			}

			/*
			 * Check files in the directory against the database.
			 * This test is skipped for CD-rom.
			 */
			if (!area.CDrom) {
				if ((dp = opendir(area.Path)) != NULL) {
					while ((de = readdir(dp)) != NULL) {
						if (de->d_name[0] != '.') {
							Marker();
							Found = FALSE;
							rewind(pFile);
							while (fread(&file, sizeof(file), 1, pFile) == 1) {
								if (strcmp(file.LName, de->d_name) == 0) {
									Found = TRUE;
									break;
								}
							}
							if ((!Found) && 
							    (strncmp(de->d_name, "files.bbs", 9)) &&
							    (strncmp(de->d_name, "files.bak", 9)) &&
							    (strncmp(de->d_name, "00index", 7)) &&
							    (strncmp(de->d_name, "header", 6)) &&
							    (strncmp(de->d_name, "index", 5)) &&
							    (strncmp(de->d_name, "readme", 6))) {
								sprintf(fn, "%s/%s", area.Path, de->d_name);
								if (stat(fn, &stb) == 0)
									if (S_ISREG(stb.st_mode)) {
										if (unlink(fn) == 0) {
											Syslog('!', "%s not in fdb, deleted from disk", fn);
											iErrors++;
										} else {
											WriteError("$%s not in fdb, cannot delete", fn);
										}
									}
							}
						}
					}
					closedir(dp);
				} else {
					WriteError("Can't open %s", area.Path);
				}
			}

			fclose(pFile);
			chmod(fAreas, 0660);
			iAreasNew++;

		} /* if area.Available */
	}

	fclose(pAreas);
	if (!do_quiet) {
		printf("\r                                                                  \r");
		fflush(stdout);
	}

	free(newdir);
	free(sAreas);
	free(fAreas);

	Syslog('+', "Check Areas [%5d] Files [%5d]  Errors [%5d]", iAreasNew, iTotal, iErrors);
}



