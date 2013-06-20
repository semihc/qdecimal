* The QDecimal Library
~~~~~~~~~~~~~~~~~~~~~~

Overview
~~~~~~~~

The QDecimal is a thin layer around IBM's decNumber library which implements the General Decimal Arithmetic Specification in ANSI C. [1]
This specification defines a decimal arithmetic which meets the requirements of commercial, financial, and human-oriented applications. It also matches the decimal arithmetic in the IEEE 754 Standard for Floating Point Arithmetic.
The decNumber library also matches the decimal arithmetic in the IEEE 754 Standard for Floating Point Arithmetic.

The QDecimal/decNumberlibrary [2] fully implements the specification, and hence supports integer, fixed-point, and floating-point decimal numbers directly, including infinite, NaN (Not a Number), and subnormal values. Both arbitrary-precision and fixed-size representations are supported.


The aim of the QDecimal library is to extend decNumber functionality to C++ language and Qt framework by using idioms, tecniques and best practices in both tecnologies. For instance, inline functions are used heavily to aid optimization, operator overloading and conversion operators are defined to aid type casting in between the types defined by QDecimal. Further these types are integrated with Qt object model by introducing them to Qt meta type system.

Following classes are defined by QDecimal library:


QDecNumber (based on decNumber):

decNumber module uses an arbitrary-precision decimal number representation designed for efficient computation in software and implements the arithmetic and logical operations, together with a number of conversions and utilities. Once a number is held as a decNumber, no further conversions are necessary to carry out arithmetic.
The decNumber representation is variable-length and machine-dependent (for example, it contains integers which may be big-endian or little-endian).
QDecNumber encapsulates decNumber and reimplements global functions that operates upon decNumber as member functions with the same name.


QDecContext (based on decContext):

Most functions in the decNumber module take as an argument a decContext structure, which provides the context for operations (precision, rounding mode, etc.) and also controls the handling of exceptional conditions (corresponding to the flags and trap enablers in a hardware floating-point implementation).


QDecSingle (based on decSingle/decimal32):

decimal32 is a 32-bit decimal floating-point representation which provides 7 decimal digits of precision in a compressed format.
decSingle module provides the functions for the decimal32 format; this format is intended for storage and interchange only and so the module provides utilities and conversions but no arithmetic functions.
QDecSingle encapsulates decSingle and provides decNumber library functions that operates upon decSingle as member functions with the same name.


QDecDouble (based on decDouble/decimal64):

decimal64 is a 64-bit decimal floating-point representation which provides 16 decimal digits of precision in a compressed format.
decDouble module provides the functions for the decimal64 format; this format is an IEEE 754 basic format and so a full set of arithmetic and other functions is included.
QDecDouble encapsulates decDouble and provides decNumber library functions that operates upon decSingle as member functions with the same name.


QDecQuad (based on decQuad/decimal128):

decimal128 is a 128-bit decimal floating-point representation which provides 34 decimal digits of precision in a compressed format.
decQuad module provides the functions for the decimal128 format; this format is an IEEE 754 basic format; it contains the same set of functions as decDouble.
QDecQuad encapsulates decQuad and provides decNumber library functions that operates upon decSingle as member functions with the same name.


QDecPacked (based on decPacked):

The decPacked format is the classic packed decimal format implemented by IBM S/360 and later machines, where each digit is encoded as a 4-bit binary sequence (BCD) and a number is ended by a 4-bit sign indicator. The decPacked module accepts variable lengths, allowing for very large numbers (up to a billion digits), and also allows the specification of a scale.
QDecPacked augments decPacked by encapsulating reference counted byte
array and scale of the decimal point as members variables, thus, freeing up
user of this class from memory management and keeping track of scale value.


License
~~~~~~~
QDecimal is under the terms of the LGPL v2.1.
decNumber is under the terms of ICU v1.8.1
See COPYRIGHT file for terms of the these licenses.

Platforms
~~~~~~~~~
QDecimal should be usable in all platforms that Qt supports.
We regularly test on following platforms:
Solaris 11 x86 (sun studio 12.5)
Linux (Ubuntu x64 - gcc)
Linux (Ubuntu x86 - gcc)
Windows XP (msvc 2008)


Installation
~~~~~~~~~~~~~~
Read INSTALL.txt to build and install QDecimal.

Copyright
~~~~~~~~~
Copyright (C) 2012-2013 Semih Cemiloglu
Copyright (c) IBM Corporation, 2000, 2010.  All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details (COPYRIGHT.txt).

The decNumber library has separate license terms, which is governed by
ICU License -- ICU 1.8.1 and later.    


Credits
~~~~~~~
We are grateful to Mike Cowlishaw et al. from IBM for making decNumber package
available. Mr. Cowlishaw has kindly helped while making QDecimal production 
ready.


In memoriam
~~~~~~~~~~~
QDecimal library is dedicated to cherished memory of my late uncle:

Muharrem Saffet Bozkurt

He is sadly missed.

