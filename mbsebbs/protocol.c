// Copyright 1997 - 2020, MBSE Development Team and its contributors
// SPDX-License-Identifier: GPL-2.0-only

#include "protocol.h"

/* Author: Michael Dillon
 * Created: December 8, 2020
 * 
 * This file was created to allow the definition to exist for openport.c
 * and the actual protocols.  mbnewusr requests openport but not the
 * protocols so this definition was no longer properly included.
 */

/* Defines the protocol in use, global variable */
enum zm_type_enum protocol;
