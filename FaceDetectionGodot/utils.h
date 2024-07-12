#ifndef UTILS_H
#define UTILS_H

// #include <QJniObject>
// #include <QtCore/private/qandroidextras_p.h>
// #include <iomanip>
// #include <iostream>
#include <opencv2/opencv.hpp>
#define FILTER "RYU"
// #define PACKAGE_NAME  "package:org.qtproject.example" //"package:[project name in manifest.xml]"
#define LOG_C(x) std::cout<< __LINE__<< " " << FILTER << " "  << x  << std::endl;
#define CURRENT_MILIS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define NORM 0.003921569
class Utils
{
public:
    Utils();
    // static void openManageFileActivity();
};

#endif // UTILS_H
