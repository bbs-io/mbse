/*****************************************************************************
 *
 * $Id: m_domalias.c,v 1.18 2008/02/28 22:05:14 mbse Exp $
 * Purpose ...............: FTN Domain Alias Setup
 *
 *****************************************************************************
 * Copyright (C) 1997-2008
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
 * MB BBS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MB BBS; see the file COPYING.  If not, write to the Free
 * Software Foundation, 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *****************************************************************************/

#include "../config.h"
#include "../lib/mbselib.h"
#include "../lib/mbsedb.h"
#include "../lib/users.h"
#include "screen.h"
#include "mutil.h"
#include "ledit.h"
#include "m_global.h"
#include "m_menu.h"
#include "m_domalias.h"


int	DomAliasUpdated;


/*
 * Count nr of domalias records in the database.
 * Creates the database if it doesn't exist.
 */
int CountDomAlias(void)
{
	FILE	*fil;
	char	ffile[PATH_MAX];
	int	count;

	snprintf(ffile, PATH_MAX, "%s/etc/domalias.data", getenv("MBSE_ROOT"));
	if ((fil = fopen(ffile, "r")) == NULL) {
		if ((fil = fopen(ffile, "a+")) != NULL) {
			Syslog('+', "Created new %s", ffile);
			domaliashdr.hdrsize = sizeof(domaliashdr);
			domaliashdr.recsize = sizeof(domalias);
			fwrite(&domaliashdr, sizeof(domaliashdr), 1, fil);
			memset(&domalias, 0, sizeof(domalias));
			domalias.active = TRUE;
			snprintf(domalias.alias, 20, "fidonet.org");
			snprintf(domalias.domain, 13, "fidonet");
			fwrite(&domalias, sizeof(domalias), 1, fil);
			fclose(fil);
			chmod(ffile, 0640);
			return 1;
		} else
			return -1;
	}

	fread(&domaliashdr, sizeof(domaliashdr), 1, fil);
	fseek(fil, 0, SEEK_END);
	count = (ftell(fil) - domaliashdr.hdrsize) / domaliashdr.recsize;
	fclose(fil);

	return count;
}



/*
 * Open database for editing. The datafile is copied, if the format
 * is changed it will be converted on the fly. All editing must be 
 * done on the copied file.
 */
int OpenDomAlias(void);
int OpenDomAlias(void)
{
	FILE	*fin, *fout;
	char	fnin[PATH_MAX], fnout[PATH_MAX];
	int	oldsize;

	snprintf(fnin,  PATH_MAX, "%s/etc/domalias.data", getenv("MBSE_ROOT"));
	snprintf(fnout, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
	if ((fin = fopen(fnin, "r")) != NULL) {
		if ((fout = fopen(fnout, "w")) != NULL) {
			fread(&domaliashdr, sizeof(domaliashdr), 1, fin);
			/*
			 * In case we are automatic upgrading the data format
			 * we save the old format. If it is changed, the
			 * database must always be updated.
			 */
			oldsize    = domaliashdr.recsize;
			if (oldsize != sizeof(domalias)) {
				DomAliasUpdated = 1;
				Syslog('+', "Updated %s to new format", fnin);
			} else
				DomAliasUpdated = 0;
			domaliashdr.hdrsize = sizeof(domaliashdr);
			domaliashdr.recsize = sizeof(domalias);
			fwrite(&domaliashdr, sizeof(domaliashdr), 1, fout);

			/*
			 * The datarecord is filled with zero's before each
			 * read, so if the format changed, the new fields
			 * will be empty.
			 */
			memset(&domalias, 0, sizeof(domalias));
			while (fread(&domalias, oldsize, 1, fin) == 1) {
				fwrite(&domalias, sizeof(domalias), 1, fout);
				memset(&domalias, 0, sizeof(domalias));
			}
			fclose(fin);
			fclose(fout);
			return 0;
		} else
			return -1;
	}
	return -1;
}



void CloseDomAlias(int);
void CloseDomAlias(int force)
{
	char	fin[PATH_MAX], fout[PATH_MAX];
	FILE	*fi, *fo;

	snprintf(fin,  PATH_MAX, "%s/etc/domalias.data", getenv("MBSE_ROOT"));
	snprintf(fout, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));

	if (DomAliasUpdated == 1) {
		if (force || (yes_no((char *)"Database is changed, save changes") == 1)) {
			working(1, 0, 0);
			fi = fopen(fout, "r");
			fo = fopen(fin,  "w");
			fread(&domaliashdr, domaliashdr.hdrsize, 1, fi);
			fwrite(&domaliashdr, domaliashdr.hdrsize, 1, fo);

			while (fread(&domalias, domaliashdr.recsize, 1, fi) == 1) {
				if (!domalias.deleted)
					fwrite(&domalias, domaliashdr.recsize, 1, fo);
			}

			fclose(fi);
			fclose(fo);
			unlink(fout);
			chmod(fin, 0640);
			Syslog('+', "Updated \"domalias.data\"");
			if (!force)
			    working(6, 0, 0);
			return;
		}
	}
	chmod(fin, 0640);
	working(1, 0, 0);
	unlink(fout); 
}



int AppendDomAlias(void)
{
	FILE	*fil;
	char	ffile[PATH_MAX];

	snprintf(ffile, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
	if ((fil = fopen(ffile, "a")) != NULL) {
		memset(&domalias, 0, sizeof(domalias));
		/*
		 * Fill in default values
		 */
		fwrite(&domalias, sizeof(domalias), 1, fil);
		fclose(fil);
		DomAliasUpdated = 1;
		return 0;
	} else
		return -1;
}



void DomAliasScreen(void)
{
	clr_index();
	set_color(WHITE, BLACK);
	mbse_mvprintw( 5, 2, "23.  EDIT FTN DOMAIN ALIASES");
	set_color(CYAN, BLACK);
	mbse_mvprintw( 7, 2, "1.  Alias");
	mbse_mvprintw( 8, 2, "2.  Domain");
	mbse_mvprintw( 9, 2, "3.  Active");
	mbse_mvprintw(10, 2, "4.  Deleted");
}



/*
 * Edit one record, return -1 if record doesn't exist, 0 if ok.
 */
int EditDomAliasRec(int Area)
{
	FILE		*fil;
	char		mfile[PATH_MAX];
	int		offset;
	unsigned int	crc, crc1;

	clr_index();
	working(1, 0, 0);
	IsDoing("Edit DomAlias");

	snprintf(mfile, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
	if ((fil = fopen(mfile, "r")) == NULL) {
		working(2, 0, 0);
		return -1;
	}

	fread(&domaliashdr, sizeof(domaliashdr), 1, fil);
	offset = domaliashdr.hdrsize + ((Area -1) * domaliashdr.recsize);
	if (fseek(fil, offset, 0) != 0) {
		working(2, 0, 0);
		return -1;
	}

	fread(&domalias, domaliashdr.recsize, 1, fil);
	fclose(fil);
	crc = 0xffffffff;
	crc = upd_crc32((char *)&domalias, crc, domaliashdr.recsize);

	for (;;) {
		DomAliasScreen();
		set_color(WHITE, BLACK);
		show_str(  7,18,60, domalias.alias);
		show_str(  8,18,60, domalias.domain);
		show_bool( 9,18,    domalias.active);
		show_bool(10,18,    domalias.deleted);

		switch(select_menu(4)) {
		case 0:
			crc1 = 0xffffffff;
			crc1 = upd_crc32((char *)&domalias, crc1, domaliashdr.recsize);
			if (crc != crc1) {
				if (yes_no((char *)"Record is changed, save") == 1) {
					working(1, 0, 0);
					if ((fil = fopen(mfile, "r+")) == NULL) {
						working(2, 0, 0);
						return -1;
					}
					fseek(fil, offset, 0);
					fwrite(&domalias, domaliashdr.recsize, 1, fil);
					fclose(fil);
					DomAliasUpdated = 1;
					working(6, 0, 0);
				}
			}
			IsDoing("Browsing Menu");
			return 0;

		case 1:	E_STR(  7,18,60, domalias.alias,    "Enter the ^Alias^ of this ^domain^.")
		case 2: E_STR(  8,18,60, domalias.domain,    "Enter the ^FTN Domain^ for this ^domain^.")
		case 3: E_BOOL( 9,18,    domalias.active,    "If this domain is ^active^")
		case 4: E_BOOL(10,18,    domalias.deleted,   "If this record is ^Deleted^")
		}
	}
}



void EditDomAlias(void)
{
	int		records, i, o, y, from, too;
	char		pick[12];
	FILE		*fil;
	char		temp[PATH_MAX];
	int		offset;
	struct _domalias	tdomalias;

	if (! check_free())
	    return;
		
	clr_index();
	working(1, 0, 0);
	IsDoing("Browsing Menu");
	if (config_read() == -1) {
		working(2, 0, 0);
		return;
	}

	records = CountDomAlias();
	if (records == -1) {
		working(2, 0, 0);
		return;
	}

	if (OpenDomAlias() == -1) {
		working(2, 0, 0);
		return;
	}
	o = 0;

	for (;;) {
		clr_index();
		set_color(WHITE, BLACK);
		mbse_mvprintw( 5, 4, "23.   FTN DOMAIN ALIAS MANAGER");
		set_color(CYAN, BLACK);
		if (records != 0) {
			snprintf(temp, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
			working(1, 0, 0);
			if ((fil = fopen(temp, "r")) != NULL) {
				fread(&domaliashdr, sizeof(domaliashdr), 1, fil);
				y = 7;
				set_color(CYAN, BLACK);
				for (i = 1; i <= 10; i++) {
					if ((o + i) <= records) {
						offset = sizeof(domaliashdr) + (((o + i) - 1) * domaliashdr.recsize);
						fseek(fil, offset, 0);
						fread(&domalias, domaliashdr.recsize, 1, fil);
						if (domalias.deleted)
							set_color(LIGHTRED, BLACK);
						else if (domalias.active)
							set_color(CYAN, BLACK);
						else
							set_color(LIGHTBLUE, BLACK);
						snprintf(temp, 81, "%3d.  %-31s  %-31s", o+i, domalias.alias, domalias.domain);
						temp[75] = 0;
						mbse_mvprintw(y, 3, temp);
						y++;
					}
				}
				fclose(fil);
			}
		}
		strcpy(pick, select_menurec(records));
		
		if (strncmp(pick, "-", 1) == 0) {
			open_bbs();
			CloseDomAlias(FALSE);
			return;
		}

		if (strncmp(pick, "A", 1) == 0) {
			working(1, 0, 0);
			if (AppendDomAlias() == 0) {
				records++;
				working(1, 0, 0);
			} else
				working(2, 0, 0);
		}

		if (strncmp(pick, "D", 1) == 0) {
			mbse_mvprintw(LINES -3, 6, "Enter domain number (1..%d) to delete >", records);
			y = 0;
			y = edit_int(LINES -3, 44, y, (char *)"Enter record number");
			if ((y > 0) && (y <= records) && yes_no((char *)"Remove record")) {
				snprintf(temp, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
				if ((fil = fopen(temp, "r+")) != NULL) {
					offset = ((y - 1) * domaliashdr.recsize) + domaliashdr.hdrsize;
					fseek(fil, offset, SEEK_SET);
					fread(&domalias, domaliashdr.recsize, 1, fil);
					domalias.deleted = TRUE;
					fseek(fil, offset, SEEK_SET);
					fwrite(&domalias, domaliashdr.recsize, 1, fil);
					DomAliasUpdated = TRUE;
					fclose(fil);
				}
			}
		}

		if (strncmp(pick, "M", 1) == 0) {
			from = too = 0;
			mbse_mvprintw(LINES -3, 6, "Enter domain number (1..%d) to move >", records);
			from = edit_int(LINES -3, 42, from, (char *)"Enter record number");
			mbse_locate(LINES -3, 6);
			clrtoeol();
			mbse_mvprintw(LINES -3, 6, "Enter new position (1..%d) >", records);
			too = edit_int(LINES -3, 36, too, (char *)"Enter destination record number, other will move away");
			if ((from == too) || (from == 0) || (too == 0) || (from > records) || (too > records)) {
				errmsg("That makes no sense");
			} else if (yes_no((char *)"Proceed move")) {
				snprintf(temp, PATH_MAX, "%s/etc/domalias.temp", getenv("MBSE_ROOT"));
				if ((fil = fopen(temp, "r+")) != NULL) {
					fseek(fil, ((from -1) * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
					fread(&tdomalias, domaliashdr.recsize, 1, fil);
					if (from > too) {
						for (i = from; i > too; i--) {
							fseek(fil, ((i -2) * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
							fread(&domalias, domaliashdr.recsize, 1, fil);
							fseek(fil, ((i -1) * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
							fwrite(&domalias, domaliashdr.recsize, 1, fil);
						}
					} else {
						for (i = from; i < too; i++) {
							fseek(fil, (i * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
							fread(&domalias, domaliashdr.recsize, 1, fil);
							fseek(fil, ((i -1) * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
							fwrite(&domalias, domaliashdr.recsize, 1, fil);
						}
					}
					fseek(fil, ((too -1) * domaliashdr.recsize) + domaliashdr.hdrsize, SEEK_SET);
					fwrite(&tdomalias, domaliashdr.recsize, 1, fil);
					fclose(fil);
					DomAliasUpdated = TRUE;
				}
			}
		}

		if (strncmp(pick, "N", 1) == 0) 
			if ((o + 10) < records) 
				o = o + 10;

		if (strncmp(pick, "P", 1) == 0)
			if ((o - 10) >= 0)
				o = o - 10;

		if ((atoi(pick) >= 1) && (atoi(pick) <= records)) {
			EditDomAliasRec(atoi(pick));
			o = ((atoi(pick) - 1) / 10) * 10;
		}
	}
}



void InitDomAlias(void)
{
    CountDomAlias();
    OpenDomAlias();
    CloseDomAlias(TRUE);
}



int domalias_doc(FILE *fp, FILE *toc, int page)
{
	char		temp[PATH_MAX];
	FILE		*no, *wp;
	int		j;

	snprintf(temp, PATH_MAX, "%s/etc/domalias.data", getenv("MBSE_ROOT"));
	if ((no = fopen(temp, "r")) == NULL)
		return page;

	page = newpage(fp, page);
	addtoc(fp, toc, 17, 0, page, (char *)"Domain alias manager");
	j = 0;

	wp = open_webdoc((char *)"domalias.html", (char *)"Domain Translation", NULL);
	fprintf(wp, "<A HREF=\"index.html\">Main</A>\n");
	fprintf(wp, "<P>\n");
	fprintf(wp, "<TABLE width='400' border='0' cellspacing='0' cellpadding='2'>\n");
//	fprintf(wp, "<COL width='40%%'><COL width='40%%'><COL width='20%%'>\n");
	fprintf(wp, "<TBODY>\n");
	fprintf(wp, "<TR><TH align='left'>Alias</TH><TH align='left'>Domain</TH><TH align='left'>Active</TH></TR>\n");

	fprintf(fp, "\n");
	fprintf(fp, "     Alias                           Domain                          Active\n");
	fprintf(fp, "     ------------------------------  ------------------------------  ------\n");
	fread(&domaliashdr, sizeof(domaliashdr), 1, no);

	while ((fread(&domalias, domaliashdr.recsize, 1, no)) == 1) {

		if (j == 50) {
			page = newpage(fp, page);
			fprintf(fp, "\n");
			fprintf(fp, "     Alias                           Domain                          Active\n");
			fprintf(fp, "     ------------------------------  ------------------------------  ------\n");
			j = 0;
		}

		fprintf(wp, "<TR><TD>%s</TD><TD>%s</TD><TD>%s</TD></TR>\n", 
			domalias.alias, domalias.domain, getboolean(domalias.active));
		fprintf(fp, "     %-30s  %-30s  %s\n", domalias.alias, domalias.domain, getboolean(domalias.active));
		j++;
	}

	fprintf(wp, "</TBODY>\n");
	fprintf(wp, "</TABLE>\n");
	close_webdoc(wp);
	fclose(no);
	return page;
}
