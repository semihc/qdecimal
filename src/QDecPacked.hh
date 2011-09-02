#ifndef QDECPACKED_HH
#define QDECPACKED_HH

/** \file QDecPacked.hh 
 * Declarations for the class QDecPacked.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include <QByteArray>

#include "QDecFwd.hh"
extern "C" {
 #include "decPacked.h"
}


class QDecPacked
{
  // MEMBERS
  QByteArray m_bytes;
  int32_t m_scale;

 public:
  // CREATORS
  //! Default constructor
  QDecPacked() : m_scale(0) {}
  QDecPacked(int32_t length, int32_t scale = 0)
      : m_bytes(length,'\0'), m_scale(scale)  {}
  QDecPacked(const QByteArray& bytes, int32_t scale = 0)
      : m_bytes(bytes), m_scale(scale) {}

  // Default copy constructor and destructor are ok to use
  
  // Conversion constructors using simple types
  QDecPacked(const char* str);
  QDecPacked(double d);
  
  // Conversion constructors using composite types
  QDecPacked(const QDecNumber& d)  { fromQDecNumber(d); }
  QDecPacked(const QDecSingle& s);
  QDecPacked(const QDecDouble& d);
  QDecPacked(const QDecQuad& d);

  // ACCESSORS
  const char* data() const
  { return m_bytes.data(); }

  const uint8_t* bytes() const
  { return reinterpret_cast<const uint8_t*>(m_bytes.data()); }

  int32_t length() const
  { return m_bytes.size(); }
    
  int32_t scale() const
  { return m_scale; }


  // MODIFIERS
  uint8_t* bytes()
  { return reinterpret_cast<uint8_t*>(m_bytes.data()); }

  void setLength(int32_t length)
  { m_bytes.resize(length); }
  
  void setScale(int32_t scale)
  { m_scale = scale; }

  // CONVERSIONS
  QDecNumber toQDecNumber() const;
  QDecPacked& fromQDecNumber(const QDecNumber& d);


}; // end class





#endif /* Include guard */
