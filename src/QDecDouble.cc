/** \file QDecDouble.cc
 * Definitions for the class QDecDouble.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "QDecDouble.hh"
extern "C" {
 #include "decimal64.h"
}
#include <stdlib.h>
#include <QTextStream>
#include "QDecNumber.hh"
#include "QDecPacked.hh"
#include "QDecSingle.hh"
#include "QDecQuad.hh"


QDecDouble& QDecDouble::fromDouble(double d)
{
  char str[MaxStrSize] = { 0 };

 #if defined(_MSC_VER)
  _snprintf(str, MaxStrSize, "%.*g", QDecNumDigits, d);
 #else
  snprintf(str, MaxStrSize, "%.*g", QDecNumDigits, d);
 #endif

  return fromString(str);
}

QDecDouble& QDecDouble::fromHexString(const char* str)
{
  QByteArray ba = QByteArray::fromHex(str);
  int size = sizeof(m_data);
  char* p = (char*)&m_data;
  int i = 0;
  int j = size-1;
  for(; i<size; i++,j--)
    p[j] = ba.at(i);

  return *this;
}

QDecDouble& QDecDouble::fromQDecSingle(const QDecSingle& s)
{
  decSingleToWider(s.data(), &m_data);
  return *this;
}

QDecDouble& QDecDouble::fromQDecNumber(const QDecNumber& n, QDecContext* c)
{
  decDoubleFromNumber(&m_data, n.data(), CXT(c));
  return *this;
}
  
QDecDouble& QDecDouble::fromQDecPacked(const QDecPacked& p)
{
  fromQDecNumber(p.toQDecNumber());
  return *this;
}

QDecDouble& QDecDouble::fromWider(const QDecQuad& q, QDecContext* c)
{
  decDoubleFromWider(&m_data, q.data(), CXT(c));
  return *this;
}

double QDecDouble::toDouble() const
{
  char str[MaxStrSize] = { 0 };
  decDoubleToString(&m_data, str);
  return strtod(str, 0);
}

QDecSingle QDecDouble::toQDecSingle(QDecContext* c) const
{
  decSingle s;
  return decSingleFromWider(&s, &m_data, CXT(c));
}

QDecQuad QDecDouble::toQDecQuad() const
{
  decQuad q;
  return decDoubleToWider(&m_data, &q);
}
  
QDecPacked QDecDouble::toQDecPacked() const
{
  return QDecPacked(toQDecNumber());
}  
  
QDecNumber QDecDouble::toQDecNumber() const
{
  decNumber n;
  return decDoubleToNumber(&m_data, &n);
}

QDecQuad QDecDouble::toWider() const
{
  decQuad q;
  return decDoubleToWider(&m_data, &q);
}

QTextStream& operator<<(QTextStream& ts, const QDecDouble& d)
{
  ts << d.toString();
  return ts;
}


