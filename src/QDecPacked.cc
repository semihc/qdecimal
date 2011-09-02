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
{ *this = fromQDecNumber(QDecNumber().fromString(str)); }

QDecPacked::QDecPacked(double d)
{ *this = fromQDecNumber(QDecDouble(d).toQDecNumber()); }

QDecPacked::QDecPacked(const QDecSingle& s)
{ *this = s.toQDecPacked(); }

QDecPacked::QDecPacked(const QDecDouble& d)
{ *this = d.toQDecPacked(); }

QDecPacked::QDecPacked(const QDecQuad& q)
{ *this = q.toQDecPacked(); }


QDecPacked& QDecPacked::fromQDecNumber(const QDecNumber& d)
{
  setLength(DECNUMDIGITS);
  decPackedFromNumber(bytes(), length(), &m_scale, d.data());
  return *this;
}

QDecNumber QDecPacked::toQDecNumber() const
{
  decNumber n;
  return decPackedToNumber(bytes(), length(), &m_scale, &n);
}

