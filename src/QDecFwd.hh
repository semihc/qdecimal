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

// Work with up to 34 digits
#ifndef DECNUMDIGITS
# define DECNUMDIGITS 34
#endif

const int QDecNumDigits = DECNUMDIGITS;

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
