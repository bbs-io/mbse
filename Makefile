# Top-level makefile for MBSE BBS package
# $Id: Makefile,v 1.73 2007/09/01 15:35:47 mbse Exp $

include Makefile.global

OTHER		= AUTHORS ChangeLog COPYING DEBUG CRON.sh FILE_ID.DIZ.in \
		  INSTALL.in Makefile Makefile.global.in NEWS cpuflags \
                  README SETUP.sh TODO UPGRADE aclocal.m4 checkbasic \
	          config.h.in configure configure.ac paths.h.in README.Gentoo\
	      README.Ubuntu docs/mbse-1.odt docs/mbse-1.pdf
TARFILE		= ${PACKAGE}-${VERSION}.tar.bz2

###############################################################################


all depend:
		@if [ -z ${MBSE_ROOT} ] ; then \
			echo; echo " MBSE_ROOT is not set!"; echo; exit 3; \
		else \
			for d in ${SUBDIRS}; do (cd $$d && ${MAKE} $@) || exit; done; \
		fi

help:
		@echo "         Help for MBSE BBS make:"
		@echo ""
		@echo "make [all]                 Compile all sources"
		@echo "make install               Install everything (must be root)"
		@echo "make depend                Update source dependencies"
		@echo "make dist                  Create distribution archive"
		@echo "make clean                 Clean sourcetree and configuration"
		@echo "make crontab               Install default crontab for mbse"
		@echo "make filelist              Create filelist for make dist"
		@echo ""

install:
		@if [ "`id -un`" != "root" ] ; then \
			echo; echo " Must be root to install!"; echo; exit 3; \
		fi
		@if [ -z ${DESTDIR}${PREFIX} ] ; then \
			echo; echo "[DESTDIR]PREFIX is not set!"; echo; exit 3; \
		fi
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0755 ${DESTDIR}${PREFIX}
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/bin
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/etc
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/etc/dosemu
		@if [ -f ${DESTDIR}${PREFIX}/etc/lastcall.data ] ; then \
			chmod 0660 ${DESTDIR}${PREFIX}/etc/lastcall.data ; \
		fi
		@if [ -f ${DESTDIR}${PREFIX}/etc/sysinfo.data ] ; then \
			chmod 0660 ${DESTDIR}${PREFIX}/etc/sysinfo.data ; \
		fi
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/log
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/tmp
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/home
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0755 ${DESTDIR}${PREFIX}/share
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0755 ${DESTDIR}${PREFIX}/share/doc
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0755 ${DESTDIR}${PREFIX}/share/doc/html
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0755 ${DESTDIR}${PREFIX}/share/doc/tags
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/en
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/es
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/nl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/de
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/gl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/menus/zh
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/en
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/es
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/nl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/de
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/gl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/macro/zh
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/en
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/es
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/nl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/de
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/gl
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/share/int/txtfiles/zh
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0775 ${DESTDIR}${PREFIX}/ftp
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0775 ${DESTDIR}${PREFIX}/ftp/pub
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0775 ${DESTDIR}${PREFIX}/ftp/pub/local
		@${INSTALL} -d -o ${ROWNER} -g ${RGROUP} -m 0750 ${DESTDIR}${PREFIX}/ftp/incoming
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0775 ${DESTDIR}${PREFIX}/var
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/arealists
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/badtic
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/boxes
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/bso
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/bso/outbound
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/boxes
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/dosemu
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/dosemu/c
		@if [ ! -d ${DESTDIR}${PREFIX}/var/fdb ] && [ -d ${DESTDIR}${PREFIX}/fdb ]; then \
			echo "Migrate files database..." ; \
			${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/fdb ; \
			mv ${DESTDIR}${PREFIX}/fdb/file*.data ${DESTDIR}${PREFIX}/var/fdb ; \
			echo "...done. You may remove ${DESTDIR}${PREFIX}/fdb" ; \
		fi
		@if [ ! -d ${DESTDIR}${PREFIX}/var/magic ] && [ -d ${DESTDIR}${PREFIX}/magic ]; then \
			echo "Migrate magic filenames..." ; \
			${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/magic ; \
			mv ${DESTDIR}${PREFIX}/magic/* ${DESTDIR}${PREFIX}/var/magic ; \
			rmdir ${DESTDIR}${PREFIX}/magic ; \
			echo "...done." ; \
		fi
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/fdb
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/hatch
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/inbound
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/magic
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/mail
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/msgs
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/nodelist
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/queue
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/rules
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0770 ${DESTDIR}${PREFIX}/var/run
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0775 ${DESTDIR}${PREFIX}/var/sema
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/ticqueue
		@${INSTALL} -d -o ${OWNER} -g ${GROUP} -m 0750 ${DESTDIR}${PREFIX}/var/unknown
		@chmod 0775 ${DESTDIR}${PREFIX}/var
		@chmod 0775 ${DESTDIR}${PREFIX}/var/sema
		@if [ -x ${BINDIR}/mbtelnetd ]; then \
			rm ${BINDIR}/mbtelnetd ; \
			echo "removed ${BINDIR}/mbtelnetd"; \
		fi
		@for d in ${SUBDIRS}; do (cd $$d && ${MAKE} -w $@) || exit; done
		@if [ -d ${DESTDIR}${PREFIX}/doc ] ; then \
			echo; echo "If there is nothing important in ${DESTDIR}${PREFIX}/doc" ; \
			echo "you may remove that obsolete directory." ; \
		fi
		@for d in de en es fr gl it nl; do \
		    if [ -d ${DESTDIR}${PREFIX}/share/int/$$d ] ; then \
		    	rmdir ${DESTDIR}${PREFIX}/share/int/$$d ; \
			echo "Removed directory ${DESTDIR}${PREFIX}/share/int/$$d" ; \
		    fi ; \
		done
		@rm -f ${DESTDIR}${PREFIX}/etc/charset.bin
		@rm -f ${DESTDIR}${PREFIX}/bin/mbcharsetc
		@rm -rf ${DESTDIR}${PREFIX}/sema
		@rm -rf ${DESTDIR}${PREFIX}/tmp/arc


dist tar:	${TARFILE}

clean:
		rm -f .filelist core ${TARFILE} paths.h config.h
		rm -f FILE_ID.DIZ INSTALL config.log config.status stamp-h
		for d in ${SUBDIRS}; do (cd $$d && ${MAKE} $@) || exit; done;
		rm -f Makefile.global

${TARFILE}:	.filelist
		cd ..; ln -s ${PACKAGE} ${PACKAGE}-${VERSION} ; rm -f ${TARFILE}; \
		${TAR} cvTf ./${PACKAGE}-${VERSION}/.filelist - | bzip2 >${TARFILE} ; \
		rm -f ${PACKAGE}-${VERSION}

crontab:
		sh ./CRON.sh

.filelist filelist:
		(for f in ${OTHER} ;do echo ${PACKAGE}-${VERSION}/$$f; done) >.filelist
		for d in ${SUBDIRS}; do (cd $$d && ${MAKE} filelist && cat filelist >>../.filelist) || exit; done;

