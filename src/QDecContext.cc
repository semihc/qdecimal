/** \file DeciContext.cc
 * Definitions for the class QDecContext.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "QDecContext.hh"
//include <sstream>
#include <QtGlobal>
#include <QByteArray>
#include <QTextStream>
#include "QDecFwd.hh"

using namespace std;


QDecContext::QDecContext(int32_t kind)
{
  switch(kind) {
  case DEC_INIT_BASE:
  case DEC_INIT_DECIMAL32:
  case DEC_INIT_DECIMAL64:
  case DEC_INIT_DECIMAL128:
    // Above kinds must be specified
    break;

  default:
    // Invalid kind
    throw("Invalid QDecContext kind");
  }

  decContextDefault(&m_data, kind);

  // No SIGFPE trap is allowed by default
  // as this will disrupt most calculations.
  m_data.traps = 0;

  // By default allow maximum allowable precision
  setDigits(QDecNumDigits);
}


QByteArray QDecContext::statusFlags() const
{
  uint32_t status = m_data.status;
  QByteArray str;
  QTextStream os(&str);
  //ostringstream os;
  const char sep = '|'; // Separator

  if(status & DEC_Conversion_syntax) 
    os << DEC_Condition_CS << sep;
  if(status & DEC_Division_by_zero)
    os << DEC_Condition_DZ << sep;
  if(status & DEC_Division_impossible)
    os << DEC_Condition_DI << sep;
  if(status & DEC_Division_undefined)
    os << DEC_Condition_DU << sep;
  if(status & DEC_Inexact)
    os << DEC_Condition_IE << sep;
  if(status & DEC_Invalid_context)
    os << DEC_Condition_IC << sep;
  if(status & DEC_Insufficient_storage)
    os << DEC_Condition_IS << sep;
  if(status & DEC_Invalid_operation)
    os << DEC_Condition_IO << sep;
#if DECSUBSET  
  if(status & DEC_Lost_digits)
    os << DEC_Condition_LD << sep;
#endif  
  if(status & DEC_Overflow)
    os << DEC_Condition_OV << sep;
  if(status & DEC_Clamped)
    os << DEC_Condition_PA << sep;
  if(status & DEC_Rounded)
    os << DEC_Condition_RO << sep;
  if(status & DEC_Subnormal)
    os << DEC_Condition_SU << sep;
  if(status & DEC_Underflow)
    os << DEC_Condition_UN << sep;
  if(0==status)
    os << DEC_Condition_ZE << sep;
  
  os << "0x" << hex << status;

  os.flush();
    //return os.str().c_str();
  return str;
}


uint8_t QDecContext::extended() const
{
#if DECSUBSET
  return m_data.extended;
#else
  return 0;
#endif
}


void QDecContext::setExtended(uint8_t ext)
{
#if DECSUBSET
  m_data.extended = ext;
#else
  (void)ext; // To disable compiler warning
#endif
}


QTextStream& operator<<(QTextStream& ts, const QDecContext ctx)
{
  char c = ' ';
  ts << "digits=" << ctx.digits()
     << c << "emax=" << ctx.emax()
     << c << "emin=" << ctx.emin()
     << c << "extended=" << ctx.extended()
     << c << "clamp=" << ctx.clamp()
     << c << "round=" << ctx.round()
     << c << "traps=" << ctx.traps()
     << c << "status=" << ctx.status()
     << c << ctx.statusToString();
  
  return ts;
}
