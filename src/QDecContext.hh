#ifndef QDECCONTEXT_HH
#define QDECCONTEXT_HH

/** \file QDecContext.hh 
 * Declarations for the class QDecContext.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

extern "C" {
 #include "decContext.h"
}

// FORWARDS
class QByteArray;
class QTextStream;

//! Default context type or kind
const int QDecContextDefKind = DEC_INIT_BASE;

//! Maximum precision allowed in precision (digits) field
const int32_t QDecMaxPrecision =  999999999;
const int32_t QDecMaxExponent  =  999999999;
const int32_t QDecMinExponent  = -999999999;

/**
   
 */
class QDecContext
{
  // MEMBERS
  decContext m_data;

 public:
  // TYPES
  typedef decContext* decContextPtr_t;
  typedef enum rounding Rounding_e;

  // CREATORS
  QDecContext(int32_t kind = QDecContextDefKind);
  QDecContext(const decContext* cptr) : m_data(*cptr) {}
  QDecContext(const decContext& data) : m_data(data) {}

  // Default Copy Ctor and Dtor and Copy assignment are ok

  // ACCESSORS
  const decContext* data() const 
  { return &m_data; }

  uint8_t clamp() const
  { return m_data.clamp; }

  int32_t digits() const
  { return m_data.digits; }

  int32_t emax() const
  { return m_data.emax; }

  int32_t emin() const
  { return m_data.emin; }

  uint8_t extended() const;
  
  Rounding_e round() const
  { return m_data.round; }

  uint32_t status() const
  { return m_data.status; }

  uint32_t traps() const
  { return m_data.traps; }


  // MODIFIERS
  decContext* data() 
  { return &m_data; }

  void setClamp(uint32_t clamp)
  { m_data.clamp = clamp; }

  void setDigits(int32_t digits)
  { m_data.digits = digits; }

  void setEmax(int32_t emax)
  { m_data.emax = emax; }

  void setEmin(int32_t emin)
  { m_data.emin = emin; }

  void setExtended(uint8_t ext);

  void setRound(Rounding_e round)
  { m_data.round = round; }

  void setTraps(uint32_t traps)
  { m_data.traps = traps; }

  void setStatus(uint32_t status = 0)
  { m_data.status = status; }

  void setStatusQuiet(uint32_t status = 0)
  { decContextSetStatusQuiet(&m_data, status); }
  
  // ROUTINES
  QDecContext& clearStatus(uint32_t status)
  { decContextClearStatus(&m_data, status); return *this; }

  QDecContext& restoreStatus(uint32_t status, uint32_t mask)
  { decContextRestoreStatus(&m_data, status, mask); return *this; }
  
  QDecContext& setDefault(int32_t kind = QDecContextDefKind)
  { decContextDefault(&m_data, kind); return *this; }

  uint32_t saveStatus(uint32_t mask) 
  { return decContextSaveStatus(&m_data, mask); }
  
  QDecContext& setStatusFromString(const char* str) 
  { decContextSetStatusFromString(&m_data, str); return *this; }

  QDecContext& setStatusFromStringQuiet(const char* str) 
  { decContextSetStatusFromStringQuiet(&m_data, str); return *this; }

  const char* statusToString() const
  { return decContextStatusToString(&m_data); }

  uint32_t testStatus(uint32_t mask) //const
  { return decContextTestStatus(&m_data, mask); }
  
  QDecContext& zeroStatus()
  { decContextZeroStatus(&m_data); return *this; }


  
  // UTILITY ROUTINES
  //! Get status flags (fields) in string form
  //! separated by | character
  QByteArray statusFlags() const;
  
  void throwOnError() const
  { if(m_data.status) throw(statusToString()); }

  //! Type conversion operator to decContext*
  operator decContextPtr_t() { return &m_data; }


  // STATIC FUNCTIONS
  static int TestEndian()
  { return decContextTestEndian(1 /*Quiet*/); }

  static uint32_t TestSavedStatus(uint32_t status, uint32_t mask)
  { return decContextTestSavedStatus(status, mask); }
  

}; // end class


QTextStream& operator<<(QTextStream& ts, const QDecContext);

// Convience macro to extract decContext structure or
// create one on stack to comply with callee signature.
#define CXT(cptr) ( cptr ? cptr->data() : QDecContext().data() )

#endif /* Include guard */
