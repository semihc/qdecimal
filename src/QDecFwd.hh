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

#ifndef DECNUMDIGITS
//! Work with up to 80 digits as default, resulting in 64 bytes
//! decNumber structure.
# define DECNUMDIGITS 80
#endif

const int QDecNumDigits = DECNUMDIGITS;

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

class QDecContext;
class QDecNumber;
class QDecPacked;
class QDecSingle;
class QDecDouble;
class QDecQuad;

#endif /* Include guard */
