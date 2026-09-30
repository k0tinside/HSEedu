#include <QApplication>
#include <QToolButton>
#include <QIcon>
#include <QMenu>

class Menus: public QMenu {
public:
    explicit Menus(QWidget *parent = nullptr) : QMenu(parent) {
        addAction("skb");
        // connect(&skbAct, &QAction::triggered, this, &Menus::skbFun);
        
        addAction("option");
        // connect(&skbAct, &QAction::triggered, this, &Menus::optionFun);
    }

// private:
    // QAction skbAct = QAction("skb", this);
    // void skbFun() {}
    
    // QAction optionAct = QAction("option", this);
    // void optionFun() {}
};

class ToolButton: public QToolButton {
public:
    explicit ToolButton(QWidget *parent = nullptr) : QToolButton(parent) {
        setMinimumSize(QSize(128, 128));
        setCheckable(true);
        setIcon(iconDefault);
        setIconSize(QSize(128, 128));
        connect(this, &ToolButton::toggled, this, &ToolButton::reactToToggle);
        menus = new Menus(this);
        setMenu(menus);
        setPopupMode(QToolButton::InstantPopup);
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
    Menus *menus = nullptr;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ToolButton button;
    button.show();

    return app.exec();
}