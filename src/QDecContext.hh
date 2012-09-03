#ifndef QDECCONTEXT_HH
#define QDECCONTEXT_HH

/** \file QDecContext.hh 
 * Declarations for the class QDecContext.
 *
 * (C) Copyright Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

extern "C" {
 #include "decContext.h"
}
#include "QDecFwd.hh"


// FORWARDS
class QByteArray;
class QTextStream;

/*! Default context type or kind, should be set to one of these:
 * DEC_INIT_BASE
 * DEC_INIT_DECIMAL32
 * DEC_INIT_DECIMAL64
 * DEC_INIT_DECIMAL128
 */
const int QDecContextDefKind = DEC_INIT_BASE;


//! Maximum precision allowed in precision (digits) field
const int32_t QDecMaxPrecision =  999999999;
const int32_t QDecMaxExponent  =  999999999;
const int32_t QDecMinExponent  = -999999999;

/*!
  \class QDecContext
   QDecContext encapsulates decContext structure as member and
   exposes free-standing functions as member functions.
   Most functions in the decNumber module take as an argument a
   decContext structure, which provides the context for operations
   (precision, rounding mode, etc.) and also controls the handling of
   exceptional conditions (corresponding to the flags and trap enablers
   in a hardware floating-point implementation).
 */
class QDECIMAL_EXPORT QDecContext
{
  // MEMBERS
  //! Embedded decContext structure
  decContext m_data;

 public:
  // TYPES
  typedef decContext* decContextPtr_t;
  typedef enum rounding Rounding_e;

  // CREATORS
  //! Default constructor
  QDecContext(int32_t kind = QDecContextDefKind);
  QDecContext(const decContext* cptr) : m_data(*cptr) {}
  QDecContext(const decContext& data) : m_data(data) {}
  // Default Copy Ctor and Dtor and Copy assignment are ok
  

  // ACCESSORS
  //! Get decContext member
  const decContext* data() const 
  { return &m_data; }

  //! Get clamp flag of the context (IEEE exponent clamp)
  uint8_t clamp() const
  { return m_data.clamp; }

  //! Get digits field of the context (working precision)
  int32_t digits() const
  { return m_data.digits; }

  //! Get emax field of the context (maximum positive exponent)
  int32_t emax() const
  { return m_data.emax; }

  //! Get emin field of the context (minimum negative exponent)
  int32_t emin() const
  { return m_data.emin; }

  //! Get extended flag of the context (special values)
  uint8_t extended() const;

  //! Get round field of the context (rounding mode)
  Rounding_e round() const
  { return m_data.round; }

  //! Get status flags of the context
  uint32_t status() const
  { return m_data.status; }

  //! Get trap-enabler flags of the context
  uint32_t traps() const
  { return m_data.traps; }


  // MODIFIERS
  //! Get decContext member
  decContext* data() 
  { return &m_data; }

  //! Set clamp flag of the context (IEEE exponent clamp)
  void setClamp(uint32_t clamp)
  { m_data.clamp = clamp; }

  //! Set digits field of the context (working precision)
  void setDigits(int32_t digits)
  { m_data.digits = digits; }

  //! Set emax field of the context (maximum positive exponent)
  void setEmax(int32_t emax)
  { m_data.emax = emax; }

  //! Set emin field of the context (minimum negative exponent)
  void setEmin(int32_t emin)
  { m_data.emin = emin; }

  //! Set extended flag of the context (special values)
  void setExtended(uint8_t ext);

  //! This function is used to return the round (rounding mode) field
  //! of a decContext.
  void setRound(Rounding_e round)
  { m_data.round = round; }

  void setTraps(uint32_t traps)
  { m_data.traps = traps; }

  /*!
    This function is used to set one or more status bits in the status
    field of a decContext. If any of the bits being set have the
    corresponding bit set in the traps field, a trap is raised
    (regardless of whether the bit is already set in the status field).
    Only one trap is raised even if more than one bit is being set.
  */
  void setStatus(uint32_t status = 0)
  { m_data.status = status; }

  //! This function is identical to setStatus except that
  //! the context traps field is ignored (i.e., no trap is raised).
  void setStatusQuiet(uint32_t status = 0)
  { decContextSetStatusQuiet(&m_data, status); }
  
  // ROUTINES
  //! This function is used to clear (set to zero) one or more status
  //! bits in the status field of a decContext.
  QDecContext& clearStatus(uint32_t status)
  { decContextClearStatus(&m_data, status); return *this; }

  //! This function is used to restore one or more status bits in
  //! the status field of a decContext from a saved status field.
  QDecContext& restoreStatus(uint32_t status, uint32_t mask)
  { decContextRestoreStatus(&m_data, status, mask); return *this; }

  /*!
    This function is used to initialize a decContext structure to
    default values. It is stongly recommended that this function always
    be used to initialize a decContext structure, even if most or all
    of the fields are to be set explicitly (in case new fields are added
    to a later version of the structure).
  */
  QDecContext& setDefault(int32_t kind = QDecContextDefKind)
  { decContextDefault(&m_data, kind); return *this; }

  //! This function is used to save one or more status bits from
  //! the status field of a decContext.
  uint32_t saveStatus(uint32_t mask) 
  { return decContextSaveStatus(&m_data, mask); }

  /*!
    This function is used to set a status bit in the status field of a
    decContext, using the name of the bit as returned by the
    decContextStatusToString function. If the bit being set has the
    corresponding bit set in the traps field, a trap is raised
    (regardless of whether the bit is already set in the status field).
  */
  QDecContext& setStatusFromString(const char* str) 
  { decContextSetStatusFromString(&m_data, str); return *this; }

  //! This function is identical to setStatusFromString except
  //! that the context traps field is ignored (i.e., no trap is raised).
  QDecContext& setStatusFromStringQuiet(const char* str) 
  { decContextSetStatusFromStringQuiet(&m_data, str); return *this; }

  //! This function returns a pointer (char *) to a human-readable
  //! description of a status bit. The string pointed to will be a constant.
  const char* statusToString() const
  { return decContextStatusToString(&m_data); }

  //! This function is used to test one or more status bits in a context.
  uint32_t testStatus(uint32_t mask) //const
  { return decContextTestStatus(&m_data, mask); }

  //! This function is used to clear (set to zero) all the
  //! status bits in the status field of a decContext.
  QDecContext& zeroStatus()
  { decContextZeroStatus(&m_data); return *this; }

  
  // UTILITY ROUTINES
  //! Get status flags (fields) in string form
  //! separated by | character
  QByteArray statusFlags() const;

  //! Throw exception if status flags are set.
  void throwOnError() const
  { if(m_data.status) throw(statusToString()); }

  //! Type conversion operator to decContext*
  operator decContextPtr_t() { return &m_data; }


  // STATIC FUNCTIONS
  //! This function checks that the DECLITEND tuning
  //! parameter is set correctly.
  //! Returns 0 if the DECLITEND parameter is correct,
  //! 1 if it is incorrect and should be set to 1, and
  //! -1 if it is incorrect and should be set to 0.
  static int TestEndian()
  { return decContextTestEndian(1 /*Quiet*/); }

  //! This function is used to test one or more status
  //! bits in a saved status field.
  static uint32_t TestSavedStatus(uint32_t status, uint32_t mask)
  { return decContextTestSavedStatus(status, mask); }
  

}; // end class


/*!
  QTextStream inserter to pretty-print QDecContext objects
  in the debug stream.
 */
QDECIMAL_EXPORT
QTextStream& operator<<(QTextStream& ts, const QDecContext);


//! Convience macro to extract decContext structure or
//! create one on stack to comply with callee signature.
#define CXT(cptr) ( cptr ? cptr->data() : QDecContext().data() )

#endif /* Include guard */
