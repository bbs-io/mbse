// Copyright 1997 - 2020, MBSE Development Team and its contributors
// SPDX-License-Identifier: GPL-2.0-only

// Author: Michael Dillon
// Created: December 8, 2020
//
// Moved extern definitions from mbse.h

/*
 * This file contains concrete definitions for the library; declarations
 * are found in mbse.h
 */
#include "mbselib.h"
#include "mbse.h"

/*
 * File Areas
 */
int	iAreaNumber;		/* Current File Area -1			   */
char	sAreaDesc[PATH_MAX];	/* Current File Area Name		   */
char	sAreaPath[PATH_MAX];	/* Current File Area path		   */
FILE	*pTagList;		/* Tagged files for download		   */
_Tag	Tag;			/* Tag record				   */



/*
 * Msg Areas
 */
int	iMsgAreaNumber;		/* Current Message Area number -1	   */
int	iMsgAreaType;		/* Current Message Area Type		   */
char	sMsgAreaDesc[PATH_MAX];	/* Current Message Area Name		   */
char	sMsgAreaBase[PATH_MAX];	/* Current Message Area Base		   */
char	sMailbox[21];		/* Current e-mail mailbox		   */
char	sMailpath[PATH_MAX];	/* Current e-mail path			   */



/* 
 * Protocols
 */
char	sProtName[21];		/* Current Transfer Protocol name	   */
char	sProtUp[51];		/* Upload path & binary			   */
char	sProtDn[51];		/* Download path & binary		   */
char	sProtAdvice[31];	/* Advice for protocol			   */
unsigned uProtInternal;		/* Internal protocol			   */
int	iProtEfficiency;	/* Protocol efficiency			   */



/* 
 * Global variables
 */
char  	*mLanguage[LANG];	/* Define LANG=nnn Language Variables	   */
char	*mKeystroke[LANG];	/* Possible keystrokes			   */
char	*Date1, *Date2;		/* Result from function SwapDate()	   */
char	*pTTY;			/* Current tty name			   */
char  	sUserTimeleft[7];	/* Global Time Left Variable		   */
int	iUserTimeLeft;		/* Global Time Left Variable		   */
char	LastLoginDate[12];	/* Last login date			   */
char	LastLoginTime[9];	/* Last login time			   */
char	LastCaller[36];		/* Last caller on system name		   */
time_t	LastCallerTime;		/* Last caller on system time		   */
char  	FirstName[20];		/* Users First name			   */
char  	LastName[30];		/* Users Last name			   */ 
int	UserAge;		/* Users age				   */
int	grecno;			/* User's Record Number in user file	   */
int	SYSOP;			/* Int to see if user is Sysop		   */
int	iLineCount;		/* Line Counter				   */
int	iExpired;		/* Check if users time ran out		   */
char	sUnixName[9];		/* Unix login name			   */
time_t	Time2Go;		/* Calculated time to force logout	   */
struct	tm *l_date;		/* Structure for Date			   */

time_t	ltime;
time_t	Time_Now;

char	current_language[10];	/* Current language of the user		   */
int	utf8;
