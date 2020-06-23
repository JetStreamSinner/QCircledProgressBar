#include <QApplication>
#include "CircledProgressBar.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    CircledProgressBar progressBar;
    progressBar.show();
    return app.exec();
}
