#include <QApplication>
#include "toolbutton.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ToolButton button;
    button.show();
    return app.exec();
}