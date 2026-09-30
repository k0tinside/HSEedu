#include <QApplication>
#include <QToolButton>
#include <QIcon>
#include <QMenu>

class ToolButton: public QToolButton {
public:
    explicit ToolButton(QWidget *parent = nullptr) : QToolButton(parent) {
        setMinimumSize(QSize(128, 128));
        setCheckable(true);
        setIcon(iconDefault);
        setIconSize(QSize(128, 128));
        connect(this, &ToolButton::toggled, this, &ToolButton::reactToToggle);
    }

    void reactToToggle(bool checked) {
        if (checked) {
            setIcon(iconChecked);
        } else {
            setIcon(iconDefault);
        }
    }

private:
    QIcon iconDefault = QIcon("icons/non-starred.svg");
    QIcon iconChecked = QIcon("icons/starred.svg");
};

class Menus: public QMenu {
public:
    explicit Menus(QWidget *parent = nullptr) : QMenu(parent) {
        addAction("skbAct");
        // connect(&skbAct, &QAction::triggered, this, &Menus::skbFun);
        
        addAction("optionAct");
        // connect(&skbAct, &QAction::triggered, this, &Menus::optionFun);
    }

// private:
    // QAction skbAct = QAction("skb", this);
    // void skbFun() {}
    
    // QAction optionAct = QAction("option", this);
    // void optionFun() {}
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ToolButton button;
    button.show();

    Menus menus(&button);
    menus.show();

    return app.exec();
}