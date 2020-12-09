/* Copyright 1997 - 2020, MBSE Development Team and its contributors */
/* SPDX-License-Identifier: GPL-2.0-only */

/* Author: Michael Dillon
 * Created: December 8, 2020
 */

/* Transfer protocol being used */

#ifndef MBSE_MBSEBBS_PROTOCOL_H
#define MBSE_MBSEBBS_PROTOCOL_H 1

enum zm_type_enum {
    ZM_XMODEM,
    ZM_YMODEM,
    ZM_ZMODEM
};

extern enum zm_type_enum protocol;

#endif /* MBSE_MBSEBBS_PROTOCOL_H */