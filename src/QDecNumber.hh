#ifndef QDECNUMBER_HH
#define QDECNUMBER_HH

/** \file QDecNumber.hh 
 * Declarations for the class QDecNumber.
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

// FORWARDS
QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE


/*!
  \class QDecNumber
  QDecNumber encapsulates decNumber and reimplements global functions
  that operates upon decNumber as member functions with the same name.
  decNumber module uses an arbitrary-precision decimal number representation
  designed for efficient computation in software and implements the
  arithmetic and logical operations, together with a number of conversions
  and utilities. Once a number is held as a decNumber, no further conversions
  are necessary to carry out arithmetic.
  The decNumber representation is variable-length and machine-dependent
  (for example, it contains integers which may be big-endian or little-endian).
 */
class QDECIMAL_EXPORT QDecNumber
{
  // MEMBERS
  //! Embedded decNumber structure
  decNumber m_data;
  
public:
  // TYPES
  typedef decNumber* decNumberPtr_t;
  enum {
    MaxStrSize = QDECMAXSTRSIZE
  };
    
  // CREATORS
  //! Default constructor
  QDecNumber()  { decNumberZero(&m_data); }

  // Constructors using decNumber structure
  QDecNumber(const decNumber& d) : m_data(d) {}
  QDecNumber(const decNumber* p) : m_data(*p) {}

  // Conversion constructors using simple types
  QDecNumber(const char* str) { fromString(str); }
  // m_data must have space for the digits needed to represent
  // the value of val, which may need up to ten digits.
  QDecNumber(uint32_t val) { fromUInt32(val); }
  QDecNumber(int32_t val) { fromInt32(val); }
  QDecNumber(double d) { fromDouble(d); }

  // Conversion constructors using composite types
  QDecNumber(const QDecSingle& s);
  QDecNumber(const QDecDouble& d);
  QDecNumber(const QDecQuad& q);
  QDecNumber(const QDecPacked& p);
  
  //! Copy constructor
  QDecNumber(const QDecNumber& o)
  { decNumberCopy(&m_data, &o.m_data); }

  //! Copy assignment
  QDecNumber& operator=(const QDecNumber& o)
  { if(this != &o) decNumberCopy(&m_data, &o.m_data); return *this; }

  //! Type conversion operator to decNumber*
  operator decNumberPtr_t() { return &m_data; }


  // ACCESSORS
  const decNumber* data() const
  { return &m_data; }

  // MODIFIERS
  decNumber* data() 
  { return &m_data; }


  // CONVERSIONS
  QDecNumber& fromBCD(QByteArray& bcd) {
    decNumberSetBCD(&m_data, (const uint8_t*)bcd.data(), bcd.size());
    return *this;
  }

  QDecNumber& fromDouble(double d);
  
  QDecNumber& fromInt32(int32_t val)
  { decNumberFromInt32(&m_data, val); return *this; }

  QDecNumber& fromUInt32(uint32_t val)
  { decNumberFromUInt32(&m_data, val); return *this; }

  QDecNumber& fromString(const char* str, QDecContext* c = 0)
  { decNumberFromString(&m_data, str, CXT(c)); return *this; }

  QByteArray toBCD() const {
    QByteArray bcd(m_data.digits+1, '\0');
    decNumberGetBCD(&m_data, (uint8_t*)bcd.data());
    return bcd;
  }

  double toDouble() const;
      
  QByteArray toEngString() const {
    char str[MaxStrSize] = { 0 };
    return decNumberToEngString(&m_data, str);
  }

  QByteArray toString() const {
    char str[MaxStrSize] = { 0 };
    return decNumberToString(&m_data, str);
  }

  int32_t toInt32(QDecContext* c = 0) const
  { return decNumberToInt32(&m_data, CXT(c)); }
  
  uint32_t toUInt32(QDecContext* c = 0) const
  { return decNumberToUInt32(&m_data, CXT(c)); }

  
  // COMPUTATIONAL FUNCTIONS
  QDecNumber abs(QDecContext* c = 0) const
  { decNumber n; return decNumberAbs(&n, &m_data, CXT(c)); }

  QDecNumber add(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberAdd(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber digitAnd(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberAnd(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber compare(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberCompare(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber compareSignal(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberCompareSignal(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber compareTotal(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberCompareTotal(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber compareTotalMag(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberCompareTotalMag(&n, &m_data, &o.m_data, CXT(c)); }
  
  QDecNumber divide(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberDivide(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber divideInteger(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberDivideInteger(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber exp(QDecContext* c = 0) const
  { decNumber n; return decNumberExp(&n, &m_data, CXT(c)); }

  QDecNumber fma(const QDecNumber& mo, const QDecNumber& ao,
                 QDecContext* c = 0) const {
    decNumber n; 
    return decNumberFMA(&n, &m_data, &mo.m_data, &ao.m_data, CXT(c));
  }

  QDecNumber invert(QDecContext* c = 0) const
  { decNumber n; return decNumberInvert(&n, &m_data, CXT(c));  }

  QDecNumber ln(QDecContext* c = 0) const
  { decNumber n; return decNumberLn(&n, &m_data, CXT(c));  }

  QDecNumber logB(QDecContext* c = 0) const
  { decNumber n; return decNumberLogB(&n, &m_data, CXT(c));  }

  QDecNumber log10(QDecContext* c = 0) const
  { decNumber n; return decNumberLog10(&n, &m_data, CXT(c));  }

  QDecNumber max(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberMax(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber maxMag(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberMaxMag(&n, &m_data, &o.m_data, CXT(c)); }
  
  QDecNumber min(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberMin(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber minMag(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberMinMag(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber minus(QDecContext* c = 0) const
  { decNumber n; return decNumberMinus(&n, &m_data, CXT(c)); }

  QDecNumber multiply(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberMultiply(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber nextMinus(QDecContext* c = 0)
  { decNumber n; return decNumberNextMinus(&n, &m_data, CXT(c)); }
  
  QDecNumber nextPlus(QDecContext* c = 0)
  { decNumber n; return decNumberNextPlus(&n, &m_data, CXT(c)); } 

  QDecNumber nextToward(const QDecNumber& o, QDecContext* c = 0)
  { decNumber n; return decNumberNextToward(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber normalize(QDecContext* c = 0) const
  { decNumber n; return decNumberNormalize(&n, &m_data, CXT(c));  }

  QDecNumber digitOr(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberOr(&n, &m_data, &o.m_data, CXT(c)); } 
  
  QDecNumber plus(QDecContext* c = 0) const
  { decNumber n; return decNumberPlus(&n, &m_data, CXT(c)); }

  QDecNumber power(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberPower(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber quantize(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberQuantize(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber reduce(QDecContext* c = 0) const
  { decNumber n; return decNumberReduce(&n, &m_data, CXT(c)); }
  
  QDecNumber remainder(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberRemainder(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber remainderNear(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberRemainderNear(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber rescale(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberRescale(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber rotate(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberRotate(&n, &m_data, &o.m_data, CXT(c)); }
  
  bool sameQuantum(const QDecNumber& o) const {
    decNumber n; 
    QDecNumber r = decNumberSameQuantum(&n, data(), o.data());
    return !r.isZero();
  }

  QDecNumber scaleB(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberScaleB(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber shift(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberShift(&n, &m_data, &o.m_data, CXT(c)); }
  
  QDecNumber squareRoot(QDecContext* c = 0) const
  { decNumber n; return decNumberSquareRoot(&n, &m_data, CXT(c));  }

  QDecNumber subtract(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberSubtract(&n, &m_data, &o.m_data, CXT(c)); }

  QDecNumber toIntegralExact(QDecContext* c = 0) const
  { decNumber n; return decNumberToIntegralExact(&n, &m_data, CXT(c)); }

  QDecNumber toIntegralValue(QDecContext* c = 0) const
  { decNumber n; return decNumberToIntegralValue(&n, &m_data, CXT(c)); }

  QDecNumber digitXor(const QDecNumber& o, QDecContext* c = 0) const
  { decNumber n; return decNumberXor(&n, &m_data, &o.m_data, CXT(c)); } 

  
  // TESTING FUNCTIONS
  bool isCanonical() const
  { return decNumberIsCanonical(&m_data); }

  bool isFinite() const
  { return decNumberIsFinite(&m_data); }

  bool isInfinite() const
  { return decNumberIsInfinite(&m_data); }

  bool isNaN() const
  { return decNumberIsNaN(&m_data); }

  bool isNegative() const
  { return decNumberIsNegative(&m_data); }

  bool isQNaN() const
  { return decNumberIsQNaN(&m_data); }

  bool isSNaN() const
  { return decNumberIsSNaN(&m_data); }

  bool isSpecial() const
  { return decNumberIsSpecial(&m_data); }

  bool isZero() const
  { return decNumberIsZero(&m_data); }
  

  // TEST FUNCTIONS (CONTEXT DEPENDENT)
  bool isNormal(QDecContext* c = 0) const
  { return decNumberIsNormal(&m_data, CXT(c)); }

  bool isSubnormal(QDecContext* c = 0) const
  { return decNumberIsSubnormal(&m_data, CXT(c)); }

  

  // UTILITIES
  enum decClass toClass(QDecContext* c = 0) const
  { return decNumberClass(&m_data, CXT(c)); }

  QDecNumber& copy(const QDecNumber& o)
  { decNumberCopy(&m_data, &o.m_data); return *this; }

  QDecNumber& copyAbs(const QDecNumber& o)
  { decNumberCopyAbs(&m_data, &o.m_data); return *this; }
    
  QDecNumber& copyNegate(const QDecNumber& o)
  { decNumberCopyNegate(&m_data, &o.m_data); return *this; }

  QDecNumber& copySign(const QDecNumber& o, const QDecNumber& so)
  { decNumberCopySign(&m_data, &o.m_data, &so.m_data); return *this; }

  uint32_t radix() const
  { return decNumberRadix(&m_data); }
  
  QDecNumber& trim()
  { decNumberTrim(&m_data); return *this; }

  const char* version() const
  { return decNumberVersion(); }

  QDecNumber& zero()
  { decNumberZero(&m_data); return *this; }

  
  // STATIC FUNCTIONS (UTILITIES)
  static const char* ClassToString(enum decClass dc)
  { return decNumberClassToString(dc); }
  
  static const char* Version()
  { return decNumberVersion(); }


  // RELATIONAL AND LOGICAL OPERATORS
  bool operator==(const QDecNumber& o) const
  { return compare(o).isZero(); }

  bool operator!=(const QDecNumber& o) const
  { return !(this->operator==(o)); }

  bool operator<(const QDecNumber& o) const
  { return compare(o).isNegative(); }

  bool operator<=(const QDecNumber& o) const
  { 
    const QDecNumber& r = compare(o);
    return r.isNegative() || r.isZero(); 
  }

  bool operator>(const QDecNumber& o) const
  { return !(this->operator<=(o)); }

  bool operator>=(const QDecNumber& o) const
  { 
    const QDecNumber& r = compare(o);
    return !r.isNegative() || r.isZero(); 
  }

  // BITWISE OPERATORS
  QDecNumber operator&(const QDecNumber& o) const
  { return digitAnd(o); }

  QDecNumber operator|(const QDecNumber& o) const
  { return digitOr(o); }

  QDecNumber operator^(const QDecNumber& o) const
  { return digitXor(o); }


  // ARITHMETIC OPERATORS
  QDecNumber operator+(const QDecNumber& o) const
  { return add(o); }

  QDecNumber operator-(const QDecNumber& o) const
  { return subtract(o); }

  QDecNumber operator*(const QDecNumber& o) const
  { return multiply(o); }

  QDecNumber operator/(const QDecNumber& o) const
  { return divide(o); }

  QDecNumber operator%(const QDecNumber& o) const
  { return remainder(o); }


  // COMPOUND ASSIGNMENT OPERATORS
  QDecNumber& operator+=(const QDecNumber& o)
  { return copy(add(o)); }

  QDecNumber& operator-=(const QDecNumber& o)
  { return copy(subtract(o)); }

  QDecNumber& operator*=(const QDecNumber& o)
  { return copy(multiply(o)); }

  QDecNumber& operator/=(const QDecNumber& o)
  { return copy(divide(o)); }

  QDecNumber& operator%=(const QDecNumber& o)
  { return copy(remainder(o)); }

  QDecNumber& operator&=(const QDecNumber& o)
  { return copy(digitAnd(o)); }

  QDecNumber& operator|=(const QDecNumber& o)
  { return copy(digitOr(o)); }

  QDecNumber& operator^=(const QDecNumber& o)
  { return copy(digitXor(o)); }


}; // end class


Q_DECLARE_METATYPE(QDecNumber);

QDECIMAL_EXPORT
QTextStream& operator<<(QTextStream& ts, const QDecNumber& n);

#endif /* Include guard */
