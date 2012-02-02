/** \file QDecPacked.cc
 * Definitions for the class QDecPacked.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "QDecPacked.hh"
#include "QDecNumber.hh"
#include "QDecSingle.hh"
#include "QDecDouble.hh"
#include "QDecQuad.hh"

QDecPacked::QDecPacked(const char* str)
{ *this = fromQDecNumber(QDecNumber(str)); }

QDecPacked::QDecPacked(double d)
{ *this = fromQDecNumber(QDecNumber(d)); }

QDecPacked::QDecPacked(const QDecSingle& s)
{ *this = s.toQDecPacked(); }

QDecPacked::QDecPacked(const QDecDouble& d)
{ *this = d.toQDecPacked(); }

QDecPacked::QDecPacked(const QDecQuad& q)
{ *this = q.toQDecPacked(); }


QDecPacked& QDecPacked::fromQDecNumber(const QDecNumber& d)
{
  uint8_t bfr[QDecNumDigits] = { 0 };
  int32_t scale = 0;

  uint8_t* rv = decPackedFromNumber(bfr, QDecNumDigits, &scale, d.data());

  if(rv) {
    m_scale = scale;
    
    char* p = (char*)bfr;
    int i = 0;
    // Skip null bytes at the left
    for(; p[i] == '\0' || i==QDecNumDigits; ++i);

    // Construct byte array from the beginning of BCD bytes
    m_bytes = QByteArray(&p[i], QDecNumDigits-i);
  }

  return *this;
}

QDecNumber QDecPacked::toQDecNumber() const
{
  if(length() > 0) {
    decNumber n;
    return decPackedToNumber(bytesRaw(), length(), &m_scale, &n);
  }
  else
    // Not initialized, return default QDecNumber value
    return QDecNumber();
}

QDecPacked& QDecPacked::fromDouble(double d)
{
  *this = fromQDecNumber(QDecNumber(d));
  return *this;
}

QDecPacked& QDecPacked::fromString(const char* str)
{
  *this = fromQDecNumber(QDecNumber(str));
  return *this;
}

QByteArray QDecPacked::toString() const
{
  return toQDecNumber().toString();
}

