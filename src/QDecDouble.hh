#ifndef QDECDOUBLE_HH
#define QDECDOUBLE_HH

/** \file QDecDouble.hh 
 * Declarations for the class QDecDouble.
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
 #include "decDouble.h"
}

// FORWARDS
QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE


/*!
  \class QDecDouble
  QDecDouble encapsulates decDouble and provides decNumber library
  functions that operates upon decSingle as member functions with the same name.
  decimal64 is a 64-bit decimal floating-point representation which
  provides 16 decimal digits of precision in a compressed format.
  decDouble module provides the functions for the decimal64 format;
  this format is an IEEE 754 basic format and so a full set of arithmetic
  and other functions is included.
 */
class QDECIMAL_EXPORT QDecDouble
{
  // MEMBERS
  //! Embedded decDouble structure
  decDouble m_data;

 public:
  // TYPES
  typedef decDouble* decDoublePtr_t;
  enum {
    MaxStrSize = QDECMAXSTRSIZE
  };


  // CREATORS
  //! Default constructor
  QDecDouble() { decDoubleZero(&m_data); }

  // Default Dtor and Copy Ctor are ok

  // Constructors using decDouble structure
  QDecDouble(decDouble d) : m_data(d) {}
  QDecDouble(const decDouble* p) : m_data(*p) {}

  // Conversion constructors using simple types
  QDecDouble(const char* str) { fromString(str); }
  QDecDouble(int32_t i) { fromInt32(i); }
  QDecDouble(uint32_t i) { fromUInt32(i); }
  QDecDouble(double d) { fromDouble(d); }
  

  // Conversion constructors using composite types
  QDecDouble(const QDecQuad& q) { fromQDecQuad(q); }
  QDecDouble(const QDecSingle& s) { fromQDecSingle(s); }
  QDecDouble(const QDecPacked& p) { fromQDecPacked(p); }
  QDecDouble(const QDecNumber& n) { fromQDecNumber(n); }

  
  //! Copy assignment
  QDecDouble& operator=(const QDecDouble& o)
  { return (this != &o ? copy(o) : *this); }

  //! Conversion operator to decDouble*
  operator decDoublePtr_t() { return &m_data; }

  
  // ACCESSORS
  const decDouble* data() const
  { return &m_data; }

  // MODIFIERS
  decDouble* data()
  { return &m_data; }

  // UTILITIES & CONVERSIONS
  QDecDouble& fromBCD(int32_t exp, const QByteArray& bcd, int32_t sign) {
    decDoubleFromBCD(&m_data, exp, (const uint8_t*)bcd.data(), sign);
    return *this;
  }

  QDecDouble& fromDouble(double d);

  QDecDouble& fromInt32(int32_t i)
  { decDoubleFromInt32(&m_data, i); return *this; }

  QDecDouble& fromPacked(int32_t exp, const QByteArray& pack) {
    decDoubleFromPacked(&m_data, exp, (const uint8_t*)pack.data());
    return *this;
  }
  
  QDecDouble& fromPackedChecked(int32_t exp, const QByteArray& pack) {
    decDoubleFromPackedChecked(&m_data, exp, (const uint8_t*)pack.data());
    return *this;
  }
  
  QDecDouble& fromString(const char* str, QDecContext* c = 0)
  { decDoubleFromString(&m_data, str, CXT(c)); return *this; }

  //! Hexadecimal string in network byte order
  QDecDouble& fromHexString(const char* str);

  QDecDouble& fromQDecSingle(const QDecSingle& s);

  QDecDouble& fromQDecQuad(const QDecQuad& q, QDecContext* c = 0)
  { return fromWider(q, c); }
  
  QDecDouble& fromQDecNumber(const QDecNumber& n, QDecContext* c = 0);
  
  QDecDouble& fromQDecPacked(const QDecPacked& p);
  
  QDecDouble& fromUInt32(uint32_t i)
  { decDoubleFromUInt32(&m_data, i); return *this; }

  QDecDouble& fromWider(const QDecQuad& q, QDecContext* c = 0);
  
  int32_t getCoefficient(QByteArray& bcd) const {
    bcd.resize(DECDOUBLE_Pmax);
    return decDoubleGetCoefficient(&m_data, (uint8_t*)bcd.data());
  }

  QDecDouble& setCoefficient(const QByteArray& bcd, int32_t sign) {
    decDoubleSetCoefficient(&m_data, (const uint8_t*)bcd.data(), sign);
    return *this;
  }
  
  QDecDouble& setExponent(int32_t exp, QDecContext* c = 0 ) {
    decDoubleSetExponent(&m_data, CXT(c), exp);
    return *this;
  }
  
  int32_t toBCD(int32_t& exp, QByteArray& bcd) {
    bcd.resize(DECDOUBLE_Pmax);
    return decDoubleToBCD(&m_data, &exp, (uint8_t*)bcd.data());
  }

  double toDouble() const;
    
  QByteArray toEngString() const {
    char str[MaxStrSize] = { 0 };
    return decDoubleToEngString(&m_data, str);
  }

  int32_t toPacked(int32_t& exp, QByteArray& pack) {
    pack.resize(DECDOUBLE_Pmax);
    return decDoubleToPacked(&m_data, &exp, (uint8_t*)pack.data());
  }
  
  QByteArray toString() const {
    char str[MaxStrSize] = { 0 };
    return decDoubleToString(&m_data, str);
  }

  QDecSingle toQDecSingle(QDecContext* c = 0) const;

  QDecQuad toQDecQuad() const;
  
  QDecPacked toQDecPacked() const;
  
  QDecNumber toQDecNumber() const;

  QDecQuad toWider() const;

  QDecDouble& zero()
  { decDoubleZero(&m_data); return *this; }

 
  // COMPUTATIONAL
  //! Returns the absolute value
  QDecDouble abs(QDecContext* c = 0) const
  { decDouble d; return decDoubleAbs(&d, &m_data, CXT(c)); }

  QDecDouble add(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleAdd(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble digitAnd(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleAnd(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble divide(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleDivide(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble divideInteger(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleDivideInteger(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble fma(const QDecDouble& o, const QDecDouble& o2,
                 QDecContext* c = 0) const
  { decDouble d; return decDoubleFMA(&d, &m_data, &o.m_data, &o2.m_data, CXT(c)); }

  QDecDouble invert(QDecContext* c = 0) const
  { decDouble d; return decDoubleInvert(&d, &m_data, CXT(c)); }

  QDecDouble logB(QDecContext* c = 0) const
  { decDouble d; return decDoubleLogB(&d, &m_data, CXT(c)); }

  QDecDouble max(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleMax(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble maxMag(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleMaxMag(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble minus(QDecContext* c = 0) const
  { decDouble d; return decDoubleMinus(&d, &m_data, CXT(c)); }

  QDecDouble multiply(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleMultiply(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble nextMinus(QDecContext* c = 0) const
  { decDouble d; return decDoubleNextMinus(&d, &m_data, CXT(c)); }

  QDecDouble nextPlus(QDecContext* c = 0) const
  { decDouble d; return decDoubleNextPlus(&d, &m_data, CXT(c)); }

  QDecDouble nextToward(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleNextToward(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble digitOr(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleOr(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble plus(QDecContext* c = 0) const
  { decDouble d; return decDoublePlus(&d, &m_data, CXT(c)); }

  QDecDouble quantize(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleQuantize(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble reduce(QDecContext* c = 0) const
  { decDouble d; return decDoubleReduce(&d, &m_data, CXT(c)); }
  
  QDecDouble remainder(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleRemainder(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble remainderNear(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleRemainderNear(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble rotate(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleRotate(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble scaleB(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleScaleB(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble shift(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleShift(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble subtract(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleSubtract(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble toIntegralValue(enum rounding r, QDecContext* c = 0) const
  { decDouble d; return decDoubleToIntegralValue(&d, &m_data, CXT(c), r); }

  QDecDouble toIntegralExact(QDecContext* c = 0) const
  { decDouble d; return decDoubleToIntegralExact(&d, &m_data, CXT(c)); }

  QDecDouble digitXor(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleXor(&d, &m_data, &o.m_data, CXT(c)); }


  // COMPARISONS
  QDecDouble compare(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleCompare(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble compareSignal(const QDecDouble& o, QDecContext* c = 0) const
  { decDouble d; return decDoubleCompareSignal(&d, &m_data, &o.m_data, CXT(c)); }

  QDecDouble compareTotal(const QDecDouble& o) const
  { decDouble d; return decDoubleCompareTotal(&d, &m_data, &o.m_data); }

  QDecDouble compareTotalMag(const QDecDouble& o) const
  { decDouble d; return decDoubleCompareTotalMag(&d, &m_data, &o.m_data); }

  
  // COPIES
  QDecDouble& canonical(const QDecDouble& d)
  { decDoubleCanonical(&m_data, &d.m_data); return *this; }

  QDecDouble& copy(const QDecDouble& d)
  { decDoubleCopy(&m_data, &d.m_data); return *this; }

  QDecDouble& copyAbs(const QDecDouble& d)
  { decDoubleCopyAbs(&m_data, &d.m_data); return *this; }

  QDecDouble& copyNegate(const QDecDouble& d)
  { decDoubleCopyNegate(&m_data, &d.m_data); return *this; }

  QDecDouble& copySign(const QDecDouble& d, const QDecDouble& sd)
  { decDoubleCopySign(&m_data, &d.m_data, &sd.m_data); return *this; }

  
  // NON-COMPUTATIONAL
  // "class" is a reserved word in C++
  enum decClass classification() const
  { return decDoubleClass(&m_data); }

  const char* classString() const
  { return decDoubleClassString(&m_data); }

  uint32_t digits() const
  { return decDoubleDigits(&m_data); }

  bool isCanonical() const
  { return decDoubleIsCanonical(&m_data); }

  bool isFinite() const
  { return decDoubleIsFinite(&m_data); }
  
  bool isInteger() const
  { return decDoubleIsInteger(&m_data); }

  bool isLogical() const
  { return decDoubleIsLogical(&m_data); }

  bool isInfinite() const
  { return decDoubleIsInfinite(&m_data); }

  bool isNaN() const
  { return decDoubleIsNaN(&m_data); }

  bool isNegative() const
  { return decDoubleIsNegative(&m_data); }

  bool isNormal() const
  { return decDoubleIsNormal(&m_data); }

  bool isPositive() const
  { return decDoubleIsPositive(&m_data); }

  bool isSignaling() const
  { return decDoubleIsSignaling(&m_data); }

  bool isSignalling() const
  { return decDoubleIsSignalling(&m_data); }

  bool isSigned() const
  { return decDoubleIsSigned(&m_data); }

  bool isSubnormal() const
  { return decDoubleIsSubnormal(&m_data); }
  
  bool isZero() const
  { return decDoubleIsZero(&m_data); }
  
  uint32_t radix() const
  { return decDoubleRadix(&m_data); }
  
  const char* version() const
  { return decDoubleVersion(); }


  // RELATIONAL AND LOGICAL OPERATORS
  bool operator==(const QDecDouble& o) const
  { return compare(o).isZero(); }

  bool operator!=(const QDecDouble& o) const
  { return !(this->operator==(o)); }

  bool operator<(const QDecDouble& o) const
  { return compare(o).isNegative(); }

  bool operator<=(const QDecDouble& o) const
  { 
    const QDecDouble& r = compare(o);
    return r.isNegative() || r.isZero(); 
  }

  bool operator>(const QDecDouble& o) const
  { return !(this->operator<=(o)); }

  bool operator>=(const QDecDouble& o) const
  { 
    const QDecDouble& r = compare(o);
    return !r.isNegative() || r.isZero(); 
  }

  // BITWISE OPERATORS
  QDecDouble operator&(const QDecDouble& o) const
  { return digitAnd(o); }

  QDecDouble operator|(const QDecDouble& o) const
  { return digitOr(o); }

  QDecDouble operator^(const QDecDouble& o) const
  { return digitXor(o); }

  
  // ARITHMETIC OPERATORS
  QDecDouble operator+(const QDecDouble& o) const
  { return add(o); }

  QDecDouble operator-(const QDecDouble& o) const
  { return subtract(o); }

  QDecDouble operator*(const QDecDouble& o) const
  { return multiply(o); }

  QDecDouble operator/(const QDecDouble& o) const
  { return divide(o); }

  QDecDouble operator%(const QDecDouble& o) const
  { return remainder(o); }


  // COMPOUND ASSIGNMENT OPERATORS
  QDecDouble& operator+=(const QDecDouble& o)
  { return copy(add(o)); }

  QDecDouble& operator-=(const QDecDouble& o)
  { return copy(subtract(o)); }

  QDecDouble& operator*=(const QDecDouble& o)
  { return copy(multiply(o)); }

  QDecDouble& operator/=(const QDecDouble& o)
  { return copy(divide(o)); }

  QDecDouble& operator%=(const QDecDouble& o)
  { return copy(remainder(o)); }

  QDecDouble& operator&=(const QDecDouble& o)
  { return copy(digitAnd(o)); }

  QDecDouble& operator|=(const QDecDouble& o)
  { return copy(digitOr(o)); }

  QDecDouble& operator^=(const QDecDouble& o)
  { return copy(digitXor(o)); }

  
}; // end class


Q_DECLARE_METATYPE(QDecDouble);


QDECIMAL_EXPORT
QTextStream& operator<<(QTextStream& ts, const QDecDouble& d);


#endif /* Include guard */
