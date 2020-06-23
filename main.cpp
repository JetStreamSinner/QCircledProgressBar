#include <QApplication>
#include "CircledProgressBar.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    CircledProgressBar progressBar;
    progressBar.setRange(0, 50);
    progressBar.setValue(0);
    progressBar.show();
    return app.exec();
}
