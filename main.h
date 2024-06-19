#ifdef MAIN_HEADER
#error THE MAIN HEADER ONLY CAN INCLUDE ONCE
#else
#define MAIN_HEADER

// include the requirable headers for components and widgets
#include <Pages/codeverifier.h>
#include <Pages/completeprofile.h>
#include <Pages/loginsignin.h>
#include <Pages/mainwindow.h>
#include <Pages/splashscreen.h>

// database init and user configurations headers
#include <database/dbinit.h>
#include <database/user.h>

// utils headers
#include <utils/Util.h>
#include <utils/waitformorefeature.h>

// Qt reuqired libraries include
#include <QApplication>
#include <QMessageBox>

// test headers
#include <test/test_captcha.h>

#endif // MAIN_HEADER
