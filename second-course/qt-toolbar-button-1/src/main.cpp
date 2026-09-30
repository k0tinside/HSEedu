#include <QApplication>
#include <QToolButton>
#include <QIcon>

class ToolButton: public QToolButton {
public:
    explicit ToolButton(QWidget *parent = nullptr) : QToolButton(parent) {
        setMinimumSize(QSize(64, 64));
        setCheckable(true);
        setIcon(iconDefault);
        setIconSize(QSize(64, 64));
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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ToolButton button;
    button.show();

    return app.exec();
}