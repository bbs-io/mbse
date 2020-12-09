/*****************************************************************************
 *
 * $Id: mbse.h,v 1.16 2007/02/20 20:24:06 mbse Exp $
 * Purpose ...............: Global variables for MBSE BBS
 *
 *****************************************************************************
 * Copyright (C) 1997-2007
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

#ifndef _MBSE_H
#define _MBSE_H

#define LANG 500		/* Amount of Language Entries		   */



typedef	struct _TagRec {
	int		Area;		/* File Area number		   */
	int		Active;		/* Not deleted from taglist	   */
	int		Cost;		/* Free download		   */
	unsigned int	Size;		/* File Size			   */
	char		SFile[13];	/* Short File Name		   */
	char		LFile[81];	/* Long FIle Name		   */
} _Tag;



/*
 * File Areas 
 */
extern int	iAreaNumber;		/* Current File Area -1			   */
extern char	sAreaDesc[PATH_MAX];	/* Current File Area Name		   */
extern char	sAreaPath[PATH_MAX];	/* Current File Area path		   */
extern FILE	*pTagList;		/* Tagged files for download		   */
extern _Tag	Tag;			/* Tag record				   */

/*
 * Msg Areas 
 */
extern int	iMsgAreaNumber;		/* Current Message Area number -1	   */
extern int	iMsgAreaType;		/* Current Message Area Type		   */
extern char	sMsgAreaDesc[PATH_MAX];	/* Current Message Area Name		   */
extern char	sMsgAreaBase[PATH_MAX];	/* Current Message Area Base		   */
extern char	sMailbox[21];		/* Current e-mail mailbox		   */
extern char	sMailpath[PATH_MAX];	/* Current e-mail path			   */


/* 
 * Protocols 
 */
extern char	sProtName[21];		/* Current Transfer Protocol name	   */
extern char	sProtUp[51];		/* Upload path & binary			   */
extern char	sProtDn[51];		/* Download path & binary		   */
extern char	sProtAdvice[31];	/* Advice for protocol			   */
extern unsigned uProtInternal;		/* Internal protocol			   */
extern int	iProtEfficiency;	/* Protocol efficiency			   */

/* 
 * Global variables
 */
extern char  	*mLanguage[LANG];	/* Define LANG=nnn Language Variables	   */
extern char	*mKeystroke[LANG];	/* Possible keystrokes			   */
extern char	*Date1, *Date2;		/* Result from function SwapDate()	   */
extern char	*pTTY;			/* Current tty name			   */
extern char  	sUserTimeleft[7];	/* Global Time Left Variable		   */
extern int	iUserTimeLeft;		/* Global Time Left Variable		   */
extern char	LastLoginDate[12];	/* Last login date			   */
extern char	LastLoginTime[9];	/* Last login time			   */
extern char	LastCaller[36];		/* Last caller on system name		   */
extern time_t	LastCallerTime;		/* Last caller on system time		   */
extern char  	FirstName[20];		/* Users First name			   */
extern char  	LastName[30];		/* Users Last name			   */ 
extern int	UserAge;		/* Users age				   */
extern int	grecno;			/* User's Record Number in user file	   */
extern int	SYSOP;			/* Int to see if user is Sysop		   */
extern int	iLineCount;		/* Line Counter				   */
extern int	iExpired;		/* Check if users time ran out		   */
extern char	sUnixName[9];		/* Unix login name			   */
extern time_t	Time2Go;		/* Calculated time to force logout	   */
extern struct	tm *l_date;		/* Structure for Date			   */
extern time_t	ltime;
extern time_t	Time_Now;
extern char	current_language[10];	/* Current language of the user		   */
extern int	utf8;


#endif
