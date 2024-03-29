# Makefile for the library files.
# Copyright (c) 1997, 2001 by M. Broek.
# $Id: Makefile,v 1.53 2008/02/17 16:10:18 mbse Exp $

include ../Makefile.global


COMMON_SRCS	= clcomm.c client.c crc.c semafore.c signame.c charset.c remask.c \
		  attach.c falists.c hdr.c parsedate.c rfcmsg.c unpacker.c rearc.c \
		  batchrd.c ftn.c pktname.c mangle.c sectest.c proglock.c magic.c \
		  dostran.c ftnmsg.c mbfile.c nodelock.c rawio.c strcasestr.c \
		  execute.c expipe.c getheader.c noderecord.c rfcaddr.c strutil.c \
		  faddr.c gmtoffset.c packet.c rfcdate.c term.c endian.c timers.c \
		  pidinfo.c tmpwork.c virscan.c mbse.c mbsedb.c mbselib.c
COMMON_OBJS	= clcomm.o client.o crc.o semafore.o signame.o charset.o remask.o \
		  ftscprod.o attach.o falists.o hdr.o parsedate.o rfcmsg.o unpacker.o \
		  batchrd.o ftn.o pktname.o mangle.o sectest.o proglock.o rearc.o \
		  dostran.o ftnmsg.o mbfile.o nodelock.o rawio.o strcasestr.o magic.o \
		  execute.o expipe.o getheader.o noderecord.o rfcaddr.o strutil.o \
		  faddr.o gmtoffset.o packet.o rfcdate.o term.o endian.o timers.o \
		  pidinfo.o tmpwork.o virscan.o mbse.o mbsedb.o mbselib.o
COMMON_HDRS	= mbselib.h
NODELIST_SRCS	= nodelist.c
NODELIST_OBJS	= nodelist.o
NODELIST_HDRS	= nodelist.h
DBASE_SRCS	= dbcfg.c dbdupe.c dbftn.c dbmsgs.c dbnode.c dbtic.c dbuser.c dbfdb.c mbsedb.c
DBASE_OBJS	= dbcfg.o dbdupe.o dbftn.o dbmsgs.o dbnode.o dbtic.o dbuser.o dbfdb.o mbsedb.o
DBASE_HDRS	= mbsedb.h
MSGBASE_SRCS	= jammsg.c msg.c msgtext.c
MSGBASE_OBJS	= jammsg.o msg.o msgtext.o
MSGBASE_HDRS	= jam.h jammsg.h jamsys.h msg.h msgtext.h
MBINET_SRCS	= nntp.c pop3.c smtp.c
MBINET_OBJS	= nntp.o pop3.o smtp.o
MBINET_HDRS	= mbinet.h
DIESEL_SRCS	= diesel.c mbdiesel.c strcasestr.c
DIESEL_HDRS	= diesel.h
DIESEL_OBJS	= diesel.o mbdiesel.o strcasestr.o
OTHER_HDRS	= bluewave.h mbse.h users.h
SRCS		= ${COMMON_SRCS} ${DBASE_SRCS} ${MSGBASE_SRCS} ${MBINET_SRCS} \
		  ${DIESEL_SRCS} ${NODELIST_SRCS} ${CHC_SRCS}
OBJS		= ${COMMON_OBJS} ${DBASE_OBJS} ${MSGBASE_OBJS} ${MBINET_OBJS} \
		  ${DIESEL_OBJS} ${NODELIST_OBJS} ${CHC_OBJS}
HDRS		= ${COMMON_HDRS} ${DBASE_HDRS} ${MSGBASE_HDRS} ${MBINET_HDRS} \
		  ${DIESEL_HDRS} ${NODELIST_HDRS} ${CHC_HDRS} ${OTHER_HDRS}
OTHER		= Makefile README ftscprod.019 mkprod.awk \
		  README.diesel README.macro Diesel.doc nodelist.conf
TARGET		= libmbse.a libdbase.a libmsgbase.a libmbinet.a libdiesel.a \
		  libnodelist.a
SLIBS		= ../lib/libmbse.a

#############################################################################

.c.o:
		${CC} ${CFLAGS} ${INCLUDES} ${DEFINES} -c $<

all:		${TARGET}

ftscprod.c:	ftscprod.??? mkprod.awk
		${AWK} -F, -f mkprod.awk ftscprod.??? >ftscprod.c

libmbse.a:	${COMMON_OBJS}
		ar r $@ $?
		${RANLIB} $@

libdbase.a:	${DBASE_OBJS}
		ar r $@ $?
		${RANLIB} $@

libmsgbase.a:	${MSGBASE_OBJS}
		ar r $@ $?
		${RANLIB} $@

libmbinet.a:	${MBINET_OBJS}
		ar r $@ $?
		${RANLIB} $@

libdiesel.a:	${DIESEL_OBJS}
		ar r $@ $?
		${RANLIB} $@

libnodelist.a:	${NODELIST_OBJS}
		ar r $@ $?
		${RANLIB} $@

install:	all
		${INSTALL} -c -o ${OWNER} -g ${GROUP} -m 0444 nodelist.conf ${DESTDIR}${ETCDIR}

clean:
		rm -f ${TARGET} *.o *.h~ *.c~ ftscprod.c core filelist Makefile.bak

filelist:	Makefile
		BASE=`pwd`; \
		BASE=`basename $${BASE}`; \
		(for f in ${SRCS} ${HDRS} ${OTHER} ${MAPS} ;do echo ${PACKAGE}-${VERSION}/$${BASE}/$$f; done) >filelist

depend:		ftscprod.c
		@rm -f Makefile.bak; \
		mv Makefile Makefile.bak; \
		sed -e '/^# DO NOT DELETE/,$$d' Makefile.bak >Makefile; \
		${ECHO} '# DO NOT DELETE THIS LINE - MAKE DEPEND RELIES ON IT' >>Makefile; \
		${ECHO} '# Dependencies generated by make depend' >>Makefile; \
		for f in ${SRCS} ftscprod.c; \
		do \
			${ECHO} "Dependencies for $$f:\c"; \
			${ECHO} "`basename $$f .c`.o:\c" >>Makefile; \
			for h in `sed -n -e \
				's/^#[ 	]*include[ 	]*"\([^"]*\)".*/\1/p' $$f`; \
			do \
				${ECHO} " $$h\c"; \
				${ECHO} " $$h\c" >>Makefile; \
			done; \
			${ECHO} " done."; \
			${ECHO} "" >>Makefile; \
		done; \
		${ECHO} '# End of generated dependencies' >>Makefile

# DO NOT DELETE THIS LINE - MAKE DEPEND RELIES ON IT
# Dependencies generated by make depend
clcomm.o: ../config.h mbselib.h
client.o: ../config.h mbselib.h
crc.o: ../config.h mbselib.h
semafore.o: ../config.h mbselib.h
signame.o: ../config.h mbselib.h
charset.o: ../config.h mbselib.h
remask.o: ../config.h mbselib.h
attach.o: ../config.h mbselib.h
falists.o: ../config.h mbselib.h
hdr.o: ../config.h mbselib.h
parsedate.o: ../config.h mbselib.h
rfcmsg.o: ../config.h mbselib.h
unpacker.o: ../config.h mbselib.h
rearc.o: ../config.h mbselib.h
batchrd.o: ../config.h mbselib.h
ftn.o: ../config.h mbselib.h users.h mbsedb.h
pktname.o: ../config.h mbselib.h users.h mbsedb.h
mangle.o: ../config.h mbselib.h
sectest.o: ../config.h mbselib.h
proglock.o: ../config.h mbselib.h
magic.o: ../config.h mbselib.h
dostran.o: ../config.h mbselib.h
ftnmsg.o: ../config.h mbselib.h
mbfile.o: ../config.h mbselib.h
nodelock.o: ../config.h mbselib.h
rawio.o: ../config.h mbselib.h
strcasestr.o: ../config.h mbselib.h
execute.o: ../config.h mbselib.h
expipe.o: ../config.h mbselib.h
getheader.o: ../config.h mbselib.h
noderecord.o: ../config.h mbselib.h users.h mbsedb.h
rfcaddr.o: ../config.h mbselib.h
strutil.o: ../config.h mbselib.h
faddr.o: ../config.h mbselib.h
gmtoffset.o: ../config.h mbselib.h
packet.o: ../config.h mbselib.h users.h mbsedb.h
rfcdate.o: ../config.h mbselib.h
term.o: ../config.h mbselib.h users.h
endian.o: ../config.h mbselib.h
timers.o: ../config.h mbselib.h
pidinfo.o: ../config.h mbselib.h
tmpwork.o: ../config.h mbselib.h
virscan.o: ../config.h mbselib.h
mbse.o: mbselib.h mbse.h
mbsedb.o: mbselib.h mbsedb.h users.h
mbselib.o: mbselib.h
dbcfg.o: ../config.h mbselib.h mbse.h users.h mbsedb.h
dbdupe.o: ../config.h mbselib.h mbse.h users.h mbsedb.h
dbftn.o: ../config.h mbselib.h users.h mbsedb.h
dbmsgs.o: ../config.h mbselib.h users.h mbsedb.h
dbnode.o: ../config.h mbselib.h users.h mbsedb.h
dbtic.o: ../config.h mbselib.h users.h mbsedb.h
dbuser.o: ../config.h mbselib.h users.h mbsedb.h
dbfdb.o: ../config.h mbselib.h users.h mbsedb.h
mbsedb.o: mbselib.h mbsedb.h users.h
jammsg.o: ../config.h mbselib.h msgtext.h msg.h jam.h jammsg.h users.h
msg.o: ../config.h mbselib.h msgtext.h msg.h jammsg.h
msgtext.o: ../config.h mbselib.h msgtext.h msg.h
nntp.o: ../config.h mbselib.h mbinet.h
pop3.o: ../config.h mbselib.h mbinet.h
smtp.o: ../config.h mbselib.h mbinet.h
diesel.o: ../config.h mbselib.h diesel.h
mbdiesel.o: ../config.h mbselib.h diesel.h
strcasestr.o: ../config.h mbselib.h
nodelist.o: ../config.h mbselib.h nodelist.h
ftscprod.o: ../config.h mbselib.h
# End of generated dependencies
