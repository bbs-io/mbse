// Copyright 1997 - 2020, MBSE Development Team and its contributors
// SPDX-License-Identifier: GPL-2.0-only

// Author: Michael Dillon
// Created: December 8, 2020
//
// Moved extern definitions from mbselib.h

#include "mbselib.h"

int		Diw;			/* Day in week index	   */
int		Miy;			/* Month in year index	   */


struct	servicehdr	servhdr;		/* Services database	   */
struct	servicerec	servrec;

struct	sysrec		SYSINFO;		/* System info statistics  */

struct	prothdr		PROThdr;		/* Transfer protocols	   */
struct	prot		PROT;

struct	onelinehdr	olhdr;			/* Oneliner database	   */
struct	oneline		ol;

struct	fileareashdr	areahdr;		/* File areas		   */
struct	fileareas	area;
struct	OldFILERecord	oldfile;		/* Pre 0.51.2 structure	   */
struct	FILE_recordhdr	fdbhdr;    		/* Files database          */
struct	FILE_record	fdb;

struct	_ngrouphdr	ngrouphdr;		/* Newfiles groups	   */
struct	_ngroup		ngroup;	

struct	bbslisthdr	bbshdr;			/* BBS list		   */
struct	bbslist		bbs;

struct	lastcallershdr	LCALLhdr;		/* Lastcallers info	   */
struct	lastcallers	LCALL;

struct	sysconfig	CFG;			/* System configuration	   */

struct	limitshdr	LIMIThdr;		/* User limits		   */
struct	limits		LIMIT;

struct	menufile	menus;

struct	languagehdr	langhdr;		/* Language data	   */
struct	language	lang;			  			  
struct	langdata	ldata;

struct  domhdr		domainhdr;
struct  domrec		domtrans;

struct	_archiverhdr	archiverhdr;		/* Archivers		   */
struct	_archiver	archiver;

struct	_virscanhdr	virscanhdr;		/* Virus scanners	   */
struct	_virscan	virscan;

struct	_ttyinfohdr	ttyinfohdr;		/* TTY lines		   */
struct	_ttyinfo	ttyinfo;
struct	_modemhdr	modemhdr;		/* Modem models		   */
struct	_modem		modem;

struct	_hatchhdr	hatchhdr;		/* Hatch areas		   */
struct	_hatch		hatch;
struct	_magichdr	magichdr;		/* Magic areas		   */
struct	_magic		magic;

struct	_newfileshdr	newfileshdr;		/* New file reports	   */
struct	_newfiles	newfiles;

struct	_scanmgrhdr	scanmgrhdr;		/* Filefind areas	   */
struct	_scanmgr	scanmgr;

struct	_routehdr	routehdr;		/* Routing file		    */
struct	_route		route;

struct	_ibcsrvhdr	ibcsrvhdr;		/* IBC servers		    */
struct	_ibcsrv		ibcsrv;
