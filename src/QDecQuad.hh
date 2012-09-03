#ifndef QDECQUAD_HH
#define QDECQUAD_HH

/** \file QDecQuad.hh 
 * Declarations for the class QDecQuad.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include <QByteArray>
#include <QMetaType>

#include "QDecFwd.hh"
#include "QDecContext.hh"
extern "C" {
 #include "decQuad.h"
}

// FORWARDS
QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE


/*!
  \class QDecQuad
  QDecQuad encapsulates decQuad and provides decNumber library functions
  that operates upon decSingle as member functions with the same name.
  decimal128 is a 128-bit decimal floating-point representation which
  provides 34 decimal digits of precision in a compressed format.
  decQuad module provides the functions for the decimal128 format;
  this format is an IEEE 754 basic format; it contains the same set of
  functions as decDouble.
 */
class QDECIMAL_EXPORT QDecQuad
{
  // MEMBERS
  //! Embedded decQuad structure
  decQuad m_data;
  
 public:
  // TYPES
  typedef decQuad* decQuadPtr_t;
  enum {
    MaxStrSize = QDECMAXSTRSIZE
  };

  // CREATORS
  //! Default constructor
  QDecQuad() { decQuadZero(&m_data); }

  // Default Dtor and Copy Ctor are ok

  // Constructors using decQuad structure
  QDecQuad(decQuad d) : m_data(d) {}
  QDecQuad(const decQuad* p) : m_data(*p) {}

  // Conversion constructors using simple types
  QDecQuad(const char* str) { fromString(str); }
  QDecQuad(int32_t i) { fromInt32(i); }
  QDecQuad(uint32_t i) { fromUInt32(i); }
  QDecQuad(double d) { fromDouble(d); }
  

  // Conversion constructors using composite types
  QDecQuad(const QDecDouble& d) { fromQDecDouble(d); }
  QDecQuad(const QDecPacked& p) { fromQDecPacked(p); }
  QDecQuad(const QDecNumber& n) { fromQDecNumber(n); }

  
  //! Copy assignment
  QDecQuad& operator=(const QDecQuad& o)
  { return (this != &o ? copy(o) : *this); }

  //! Conversion operator to decQuad*
  operator decQuadPtr_t() { return &m_data; }


  // ACCESSORS
  const decQuad* data() const
  { return &m_data; }

  // MODIFIERS
  decQuad* data()
  { return &m_data; }

  // UTILITIES & CONVERSIONS
  QDecQuad& fromBCD(int32_t exp, const QByteArray& bcd, int32_t sign) {
    decQuadFromBCD(&m_data, exp, (const uint8_t*)bcd.data(), sign);
    return *this;
  }

  QDecQuad& fromDouble(double d);

  QDecQuad& fromInt32(int32_t i)
  { decQuadFromInt32(&m_data, i); return *this; }

  QDecQuad& fromPacked(int32_t exp, const QByteArray& pack) {
    decQuadFromPacked(&m_data, exp, (const uint8_t*)pack.data());
    return *this;
  }
  
  QDecQuad& fromPackedChecked(int32_t exp, const QByteArray& pack) {
    decQuadFromPackedChecked(&m_data, exp, (const uint8_t*)pack.data());
    return *this;
  }
  
  QDecQuad& fromString(const char* str, QDecContext* c = 0)
  { decQuadFromString(&m_data, str, CXT(c)); return *this; }

  //! Hexadecimal string in network byte order
  QDecQuad& fromHexString(const char* str);
  
  QDecQuad& fromQDecDouble(const QDecDouble& d);

  QDecQuad& fromQDecNumber(const QDecNumber& n, QDecContext* c = 0);
  
  QDecQuad& fromQDecPacked(const QDecPacked& p);
  
  QDecQuad& fromUInt32(uint32_t i)
  { decQuadFromUInt32(&m_data, i); return *this; }

  int32_t getCoefficient(QByteArray& bcd) const {
    bcd.resize(DECQUAD_Pmax);
    return decQuadGetCoefficient(&m_data, (uint8_t*)bcd.data());
  }

  QDecQuad& setCoefficient(const QByteArray& bcd, int32_t sign) {
    decQuadSetCoefficient(&m_data, (const uint8_t*)bcd.data(), sign);
    return *this;
  }
  
  QDecQuad& setExponent(int32_t exp, QDecContext* c = 0) {
    decQuadSetExponent(&m_data, CXT(c), exp);
    return *this;
  }
  
  int32_t toBCD(int32_t& exp, QByteArray& bcd) {
    bcd.resize(DECQUAD_Pmax);
    return decQuadToBCD(&m_data, &exp, (uint8_t*)bcd.data());
  }

  double toDouble() const;
    
  QByteArray toEngString() const {
    char str[MaxStrSize] = { 0 };
    return decQuadToEngString(&m_data, str);
  }

  int32_t toPacked(int32_t& exp, QByteArray& pack) {
    pack.resize(DECQUAD_Pmax);
    return decQuadToPacked(&m_data, &exp, (uint8_t*)pack.data());
  }
  
  QByteArray toString() const {
    char str[MaxStrSize] = { 0 };
    return decQuadToString(&m_data, str);
  }

  QDecDouble toQDecDouble(QDecContext* c = 0) const;
  
  QDecPacked toQDecPacked() const;
  
  QDecNumber toQDecNumber() const;
  
  QDecQuad& zero()
  { decQuadZero(&m_data); return *this; }

 
  // COMPUTATIONAL
  QDecQuad abs(QDecContext* c = 0) const
  { decQuad q; return decQuadAbs(&q, &m_data, CXT(c)); }

  QDecQuad add(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadAdd(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad digitAnd(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadAnd(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad divide(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadDivide(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad divideInteger(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadDivideInteger(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad fma(const QDecQuad& o, const QDecQuad& o2,
               QDecContext* c = 0) const
  { decQuad q; return decQuadFMA(&q, &m_data, &o.m_data, &o2.m_data, CXT(c)); }

  QDecQuad invert(QDecContext* c = 0) const
  { decQuad q; return decQuadInvert(&q, &m_data, CXT(c)); }

  QDecQuad logB(QDecContext* c = 0) const
  { decQuad q; return decQuadLogB(&q, &m_data, CXT(c)); }

  QDecQuad max(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadMax(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad maxMag(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadMaxMag(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad minus(QDecContext* c = 0) const
  { decQuad q; return decQuadMinus(&q, &m_data, CXT(c)); }

  QDecQuad multiply(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadMultiply(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad nextMinus(QDecContext* c = 0) const
  { decQuad q; return decQuadNextMinus(&q, &m_data, CXT(c)); }

  QDecQuad nextPlus(QDecContext* c = 0) const
  { decQuad q; return decQuadNextPlus(&q, &m_data, CXT(c)); }

  QDecQuad nextToward(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadNextToward(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad digitOr(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadOr(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad plus(QDecContext* c = 0) const
  { decQuad q; return decQuadPlus(&q, &m_data, CXT(c)); }

  QDecQuad quantize(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadQuantize(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad reduce(QDecContext* c = 0) const
  { decQuad q; return decQuadReduce(&q, &m_data, CXT(c)); }
  
  QDecQuad remainder(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadRemainder(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad remainderNear(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadRemainderNear(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad rotate(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadRotate(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad scaleB(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadScaleB(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad shift(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadShift(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad subtract(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadSubtract(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad toIntegralValue(enum rounding r, QDecContext* c = 0) const
  { decQuad q; return decQuadToIntegralValue(&q, &m_data, CXT(c), r); }

  QDecQuad toIntegralExact(QDecContext* c = 0) const
  { decQuad q; return decQuadToIntegralExact(&q, &m_data, CXT(c)); }

  QDecQuad digitXor(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadXor(&q, &m_data, &o.m_data, CXT(c)); }


  // COMPARISONS
  QDecQuad compare(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadCompare(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad compareSignal(const QDecQuad& o, QDecContext* c = 0) const
  { decQuad q; return decQuadCompareSignal(&q, &m_data, &o.m_data, CXT(c)); }

  QDecQuad compareTotal(const QDecQuad& o) const
  { decQuad q; return decQuadCompareTotal(&q, &m_data, &o.m_data); }

  QDecQuad compareTotalMag(const QDecQuad& o) const
  { decQuad q; return decQuadCompareTotalMag(&q, &m_data, &o.m_data); }

  
  // COPIES
  QDecQuad& canonical(const QDecQuad& d)
  { decQuadCanonical(&m_data, &d.m_data); return *this; }

  QDecQuad& copy(const QDecQuad& d)
  { decQuadCopy(&m_data, &d.m_data); return *this; }

  QDecQuad& copyAbs(const QDecQuad& d)
  { decQuadCopyAbs(&m_data, &d.m_data); return *this; }

  QDecQuad& copyNegate(const QDecQuad& d)
  { decQuadCopyNegate(&m_data, &d.m_data); return *this; }

  QDecQuad& copySign(const QDecQuad& d, const QDecQuad& sd)
  { decQuadCopySign(&m_data, &d.m_data, &sd.m_data); return *this; }

  
  // NON-COMPUTATIONAL
  // "class" is a reserved word in C++
  enum decClass classification() const
  { return decQuadClass(&m_data); }

  const char* classString() const
  { return decQuadClassString(&m_data); }

  uint32_t digits() const
  { return decQuadDigits(&m_data); }

  bool isCanonical() const
  { return decQuadIsCanonical(&m_data); }

  bool isFinite() const
  { return decQuadIsFinite(&m_data); }
  
  bool isInteger() const
  { return decQuadIsInteger(&m_data); }

  bool isLogical() const
  { return decQuadIsLogical(&m_data); }

  bool isInfinite() const
  { return decQuadIsInfinite(&m_data); }

  bool isNaN() const
  { return decQuadIsNaN(&m_data); }

  bool isNegative() const
  { return decQuadIsNegative(&m_data); }

  bool isNormal() const
  { return decQuadIsNormal(&m_data); }

  bool isPositive() const
  { return decQuadIsPositive(&m_data); }

  bool isSignaling() const
  { return decQuadIsSignaling(&m_data); }

  bool isSignalling() const
  { return decQuadIsSignalling(&m_data); }

  bool isSigned() const
  { return decQuadIsSigned(&m_data); }

  bool isSubnormal() const
  { return decQuadIsSubnormal(&m_data); }
  
  bool isZero() const
  { return decQuadIsZero(&m_data); }
  
  uint32_t radix() const
  { return decQuadRadix(&m_data); }
  
  const char* version() const
  { return decQuadVersion(); }


  // RELATIONAL AND LOGICAL OPERATORS
  bool operator==(const QDecQuad& o) const
  { return compare(o).isZero(); }

  bool operator!=(const QDecQuad& o) const
  { return !(this->operator==(o)); }

  bool operator<(const QDecQuad& o) const
  { return compare(o).isNegative(); }

  bool operator<=(const QDecQuad& o) const
  { 
    const QDecQuad& r = compare(o);
    return r.isNegative() || r.isZero(); 
  }

  bool operator>(const QDecQuad& o) const
  { return !(this->operator<=(o)); }

  bool operator>=(const QDecQuad& o) const
  { 
    const QDecQuad& r = compare(o);
    return !r.isNegative() || r.isZero(); 
  }

  // BITWISE OPERATORS
  QDecQuad operator&(const QDecQuad& o) const
  { return digitAnd(o); }

  QDecQuad operator|(const QDecQuad& o) const
  { return digitOr(o); }

  QDecQuad operator^(const QDecQuad& o) const
  { return digitXor(o); }

  
  // ARITHMETIC OPERATORS
  QDecQuad operator+(const QDecQuad& o) const
  { return add(o); }

  QDecQuad operator-(const QDecQuad& o) const
  { return subtract(o); }

  QDecQuad operator*(const QDecQuad& o) const
  { return multiply(o); }

  QDecQuad operator/(const QDecQuad& o) const
  { return divide(o); }

  QDecQuad operator%(const QDecQuad& o) const
  { return remainder(o); }


  // COMPOUND ASSIGNMENT OPERATORS
  QDecQuad& operator+=(const QDecQuad& o)
  { return copy(add(o)); }

  QDecQuad& operator-=(const QDecQuad& o)
  { return copy(subtract(o)); }

  QDecQuad& operator*=(const QDecQuad& o)
  { return copy(multiply(o)); }

  QDecQuad& operator/=(const QDecQuad& o)
  { return copy(divide(o)); }

  QDecQuad& operator%=(const QDecQuad& o)
  { return copy(remainder(o)); }

  QDecQuad& operator&=(const QDecQuad& o)
  { return copy(digitAnd(o)); }

  QDecQuad& operator|=(const QDecQuad& o)
  { return copy(digitOr(o)); }

  QDecQuad& operator^=(const QDecQuad& o)
  { return copy(digitXor(o)); }

  
}; // end class


Q_DECLARE_METATYPE(QDecQuad);


QDECIMAL_EXPORT
QTextStream& operator<<(QTextStream& ts, const QDecQuad& d);


#endif /* Include guard */
