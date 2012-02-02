/** \file QDecSingle.cc
 * Definitions for the class QDecSingle.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "QDecSingle.hh"
extern "C" {
 #include "decimal32.h"
}
#include <stdlib.h>
#include <QTextStream>
#include "QDecNumber.hh"
#include "QDecPacked.hh"
#include "QDecDouble.hh"


QDecSingle& QDecSingle::fromDouble(double d)
{
  char str[MaxStrSize] = {0};

 #if defined(_MSC_VER)
  _snprintf(str, MaxStrSize, "%.*g", QDecNumDigits, d);
 #else
  snprintf(str, MaxStrSize, "%.*g", QDecNumDigits, d);
 #endif

  return fromString(str);
}

QDecSingle& QDecSingle::fromHexString(const char* str)
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


QDecSingle& QDecSingle::fromQDecNumber(const QDecNumber& n, QDecContext* c)
{
  decSingleFromNumber(&m_data, n.data(), CXT(c));
  return *this;
}
  
QDecSingle& QDecSingle::fromQDecPacked(const QDecPacked& p)
{
  fromQDecNumber(p.toQDecNumber());
  return *this;
}
  
QDecSingle& QDecSingle::fromWider(const QDecDouble& d, QDecContext* c)
{
  decSingleFromWider(&m_data, d.data(), CXT(c));
  return *this;
}


double QDecSingle::toDouble() const
{
  char str[MaxStrSize] = {0};
  decSingleToString(&m_data, str);
  return strtod(str, 0);
}

QDecDouble QDecSingle::toQDecDouble() const
{
  return toWider();
}
  
QDecPacked QDecSingle::toQDecPacked() const
{
  return QDecPacked(toQDecNumber());
}
  
QDecNumber QDecSingle::toQDecNumber() const
{
  decNumber n;
  return decSingleToNumber(&m_data, &n);
}

QDecDouble QDecSingle::toWider() const
{
  decDouble d;
  return decSingleToWider(&m_data, &d);
}

QTextStream& operator<<(QTextStream& ts, const QDecSingle& d)
{
  ts << d.toString();
  return ts;
}
