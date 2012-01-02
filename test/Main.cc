#include <QtTest/QtTest>

#include "QDecNumberTests.hh"

#if defined(__GNUC__)
# ident "$Id$"
#elif defined(__sun)
# pragma ident "$Id$"
#elif defined(_WIN32)
# pragma comment( user, __FILE__ " " __DATE__ " " __TIME__ "$Id$" )
#endif



void MessageOutput(QtMsgType type, const char *msg)
{
  switch (type) {
    case QtDebugMsg:
      fprintf(stderr, "%s\n", msg);
      break;
    case QtWarningMsg:
      fprintf(stderr, "Warn: %s\n", msg);
      break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s\n", msg);
      break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s\n", msg);
      abort();
  }
}



//QTEST_MAIN(QDecNumberTests) 

int main(int argc, char* argv[])
{
  qInstallMsgHandler(MessageOutput);
  QCoreApplication app(argc, argv);
  QStringList args = QCoreApplication::arguments();

  QRegExp flagre("--(\\w+)=.*");
  QStringList tc_args;
  QStringList qt_args;

  // Separate QTest arguments out of test class arguments
  QStringListIterator ai(args);
  while(ai.hasNext()) {
    QString item = ai.next();
    if(flagre.exactMatch(item))
      tc_args << item;
    else
      qt_args << item;
  }
  
  QDecNumberTests tc(tc_args);
  int rv;

  // Increase limit for warnings count
  qt_args << "-maxwarnings" << "9999999";
  rv = QTest::qExec(&tc, qt_args);

  return rv;
}

//include "moc_QDecNumberTests.cpp"
