// Copyright 1997 - 2020, MBSE Development Team and its contributors
// SPDX-License-Identifier: GPL-2.0-only

// Author: Michael Dillon
// Created: December 8, 2020
// 
// Moved extern definitions from mbsedb.h

#include "mbselib.h"
#include "mbsedb.h"
#include "users.h"

/*
 * Fidonet database
 */
struct _fidonethdr  fidonethdr;		    /* Header record		    */
struct _fidonet	    fidonet;		    /* Fidonet datarecord	    */
int		    fidonet_cnt;	    /* Fidonet records in database  */
char		    fidonet_fil[PATH_MAX];  /* Fidonet database filename    */

/*
 * Domain alias database
 */
 
struct _domaliashdr domaliashdr;            /* Header record                */
struct _domalias    domalias;               /* Domain alias datarecord      */
int                 domalias_cnt;           /* Domain alias records in db   */
char                domalias_fil[PATH_MAX]; /* Domain alias db filename     */

/*
 * Nodes database
 */
struct	_nodeshdr	nodeshdr;	/* Header record		    */
struct	_nodes		nodes;		/* Nodes datarecord		    */
int			nodes_cnt;	/* Node records in database	    */

/*
 * TIC area database
 */
struct	_tichdr		tichdr;		/* Header record		    */
struct	_tic		tic;		/* Tics datarecord		    */
struct	_fgrouphdr	fgrouphdr;	/* Group header record		    */
struct	_fgroup		fgroup;		/* Group record			    */
int			tic_cnt;	/* Tic records in database	    */

/*
 * User records
 */
struct	userhdr	    usrhdr;		/* Header record		    */
struct	userrec	    usr;		/* User datarecord		    */
int		    usr_cnt;		/* User records in database	    */
char		    usr_fil[PATH_MAX];	/* User database filename	    */

/*
 * From users.h
 */
struct  userhdr         usrconfighdr;           /* Users database          */
struct  userrec         usrconfig;
struct  userrec         exitinfo;               /* Users online data       */


/*
 * Message areas database
 */
struct  msgareashdr     msgshdr;        /* Header record                    */
struct  msgareas        msgs;           /* Msgss datarecord                 */
struct  _mgrouphdr      mgrouphdr;      /* Group header record              */
struct  _mgroup         mgroup;         /* Group record                     */
int                     msgs_cnt;       /* Msgs records in database         */


