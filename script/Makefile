# Makefile for MBSE BBS under Linux
# $Id: Makefile,v 1.23 2005/08/17 18:55:16 mbse Exp $

include ../Makefile.global

OTHER		= Makefile README maint midnight weekly monthly installinit.sh setup.mbse \
		  bbsdoor.sh rundoor.sh runvirtual.sh init.Debian init.RedHat init.FreeBSD init.NetBSD \
		  init.Slackware init.SuSE init.Gentoo init.Devuan hatch editor.in bbsjoerc bbsjmacsrc \
		  doors.bat mbsedos

####################################################################################################

all:

clean:
		rm -f core filelist Makefile.bak
		rm -f editor

install:
		@if [ "`id -un`" != "root" ] ; then \
			echo; echo " Must be root to install!"; echo; exit 3; \
		fi
		@if [ ! -x ${DESTDIR}${ETCDIR}/maint ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 maint       ${DESTDIR}${ETCDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 maint       ${DESTDIR}${ETCDIR}" ; \
		else \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 maint       ${DESTDIR}${ETCDIR}/maint.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 maint       ${DESTDIR}${ETCDIR}/maint.new" ; \
		fi
		@if [ ! -x ${DESTDIR}${ETCDIR}/midnight ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 midnight    ${DESTDIR}${ETCDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 midnight    ${DESTDIR}${ETCDIR}" ; \
		else \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 midnight    ${DESTDIR}${ETCDIR}/midnight.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 midnight    ${DESTDIR}${ETCDIR}/midnight.new" ; \
		fi
		@if [ ! -x ${DESTDIR}${ETCDIR}/weekly ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 weekly      ${DESTDIR}${ETCDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 weekly      ${DESTDIR}${ETCDIR}" ; \
		else \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 weekly      ${DESTDIR}${ETCDIR}/weekly.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 weekly      ${DESTDIR}${ETCDIR}/weekly.new" ; \
		fi
		@if [ ! -x ${DESTDIR}${ETCDIR}/monthly ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 monthly     ${DESTDIR}${ETCDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 monthly     ${DESTDIR}${ETCDIR}" ; \
		else \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 monthly     ${DESTDIR}${ETCDIR}/monthly.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 monthly     ${DESTDIR}${ETCDIR}/monthly.new" ; \
		fi
		@if [ ! -x ${DESTDIR}${BINDIR}/hatch ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 hatch       ${DESTDIR}${BINDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 hatch       ${DESTDIR}${BINDIR}" ; \
		else  \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 hatch       ${DESTDIR}${BINDIR}/hatch.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 hatch       ${DESTDIR}${BINDIR}/hatch/new" ; \
		fi
		@if [ -x ${JOEBIN}/joe ]; then \
			echo "Installing support for joe editor" ; \
			rm -f ${DESTDIR}${JOEBIN}/bbsjoe ; \
			rm -f ${DESTDIR}${JOEBIN}/bbsjmacs ; \
			mkdir -p ${DESTDIR}${JOEBIN} ; \
			echo "${LN_S} ${JOEBIN}/joe ${DESTDIR}${JOEBIN}/bbsjoe" ; \
			${LN_S} ${JOEBIN}/joe ${DESTDIR}${JOEBIN}/bbsjoe ; \
			echo "${LN_S} ${JOEBIN}/joe ${DESTDIR}${JOEBIN}/bbsjmacs" ; \
			${LN_S} ${JOEBIN}/joe ${DESTDIR}${JOEBIN}/bbsjmacs ; \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0550 editor      ${DESTDIR}${BINDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0550 editor      ${DESTDIR}${BINDIR}" ; \
		fi
		@if [ -d ${JOELIB} ]; then \
			mkdir -p ${DESTDIR}${JOELIB} ; \
			${INSTALL} -c -o ${ROWNER} -g ${RGROUP} -m 0644 bbsjoerc    ${DESTDIR}${JOELIB} ; \
			echo "${INSTALL} -c -o ${ROWNER} -g ${RGROUP} -m 0644 bbsjoerc    ${DESTDIR}${JOELIB}" ; \
			${INSTALL} -c -o ${ROWNER} -g ${RGROUP} -m 0644 bbsjmacsrc  ${DESTDIR}${JOELIB} ; \
			echo "${INSTALL} -c -o ${ROWNER} -g ${RGROUP} -m 0644 bbsjmacsrc  ${DESTDIR}${JOELIB}" ; \
		fi
		@if [ ! -x ${DESTDIR}${BINDIR}/bbsdoor.sh ]; then \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 bbsdoor.sh  ${DESTDIR}${BINDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 bbsdoor.sh  ${DESTDIR}${BINDIR}" ; \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 rundoor.sh  ${DESTDIR}${BINDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 rundoor.sh  ${DESTDIR}${BINDIR}" ; \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 runvirtual.sh  ${DESTDIR}${BINDIR} ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 runvirtual.sh  ${DESTDIR}${BINDIR}" ; \
		else \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 bbsdoor.sh  ${DESTDIR}${BINDIR}/bbsdoor.sh.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 bbsdoor.sh  ${DESTDIR}${BINDIR}/bbsdoor.sh.new" ; \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 rundoor.sh  ${DESTDIR}${BINDIR}/rundoor.sh.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 rundoor.sh  ${DESTDIR}${BINDIR}/rundoor.sh.new" ; \
			${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 runvirtual.sh  ${DESTDIR}${BINDIR}/runvirtual.sh.new ; \
			echo "${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0750 runvirtual.sh  ${DESTDIR}${BINDIR}/runvirtual.sh.new" ; \
		fi
		${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0640 doors.bat    ${DESTDIR}${VARDIR}/dosemu/c
		${INSTALL} -c -o ${OWNER} -g ${GROUP}  -m 0500 mbsedos      ${DESTDIR}${BINDIR}
		@bash ./installinit.sh

filelist:	Makefile
		BASE=`pwd`; \
		BASE=`basename $${BASE}`; \
		(for f in ${OTHER} ;do echo ${PACKAGE}-${VERSION}/$${BASE}/$$f; done) >filelist

depend:

