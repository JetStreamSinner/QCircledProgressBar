#include <QApplication>
#include "CircledProgressBar.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    CircledProgressBar progressBar;
    progressBar.setRange(0, 1200);
    progressBar.setValue(462);
    progressBar.show();
    return app.exec();
}
