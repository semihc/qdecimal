#ifndef QDECFWD_HH
#define QDECFWD_HH

/** \file QDecFwd.hh 
 * Forward declarations for QDecimal types
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include <QtCore/QtGlobal>

#ifndef DECNUMDIGITS
//! Work with up to 80 digits as default, resulting in 64 bytes
//! decNumber structure.
# define DECNUMDIGITS 80
#endif

//! Digits of decimal precision for QDecNumber, decNumber.
//! This is set at compile time via DECNUMDIGITS macro.
const int QDecNumDigits = DECNUMDIGITS;

//! Digits of decimal precision for QDecSingle, decSingle, decimal32
const int QDecSingleDigits = 7;

//! Digits of decimal precision for QDecDouble, decDouble, decimal64
const int QDecDoubleDigits = 16;

//! Digits of decimal precision for QDecQuad, decQuad, decimal128
const int QDecQuadDigits = 34;

#ifndef QDECMAXSTRSIZE
//! Maximum length of a conversion string
# define QDECMAXSTRSIZE 512
#endif


extern "C" {
 #if !defined(int32_t)
  #if defined(_MSC_VER) 
   /* MS Visual C */
   #include <VCpp_stdint.h>
  #else
   /* C99 standard integers */
   #include <stdint.h>      
   /* For unknown compilers, you can use portable stdint.h */
   //include <Port_stdint.h> 
  #endif
 #endif

 #include "decContext.h"
 #include "decNumber.h"
}

// Prepare for shared library usage.
// See Q_DEC_EXPORT from Qt documentation for details.

#ifdef QDECIMAL_SHARED
# if(QDECIMAL_SHARED > 1)
#  define QDECIMAL_EXPORT Q_DECL_EXPORT
# else
#  define QDECIMAL_EXPORT Q_DECL_IMPORT
# endif
#else
# define QDECIMAL_EXPORT /* no-op */
#endif

class QDECIMAL_EXPORT QDecContext;
class QDECIMAL_EXPORT QDecNumber;
class QDECIMAL_EXPORT QDecPacked;
class QDECIMAL_EXPORT QDecSingle;
class QDECIMAL_EXPORT QDecDouble;
class QDECIMAL_EXPORT QDecQuad;

#endif /* Include guard */
