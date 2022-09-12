qt_add_library(qdecimal  
 STATIC
  QDecContext.cc
  QDecPacked.cc
  QDecNumber.cc
  QDecSingle.cc
  QDecDouble.cc
  QDecQuad.cc
)
  
target_include_directories(qdecimal PUBLIC . ../decnumber)
target_link_libraries(qdecimal 
 PRIVATE Qt6::Core
)
