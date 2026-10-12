#include "toolbutton.h"

#include <QMenu>
#include <QAction>

ToolButton::ToolButton(QWidget *parent) : QToolButton(parent) {
    m_starDefault = QIcon(":/icons/star-default.svg");
    m_starChecked = QIcon(":/icons/star-checked.svg");
    m_faceDefault = QIcon(":/icons/face-angel.svg");
    m_faceChecked = QIcon(":/icons/face-devilish.svg");

    setMinimumSize(QSize(128, 128));
    setIconSize(QSize(128, 128));

    setCheckable(true);
    setIcon(m_starDefault);

    m_menu = new QMenu(this);
    setMenu(m_menu);

    QAction* starAction = m_menu->addAction("star");
    QAction* faceAction = m_menu->addAction("face");

    setPopupMode(QToolButton::MenuButtonPopup);

    connect(this, &ToolButton::toggled, this, &ToolButton::reactToToggle);
    connect(starAction, &QAction::triggered, this, &ToolButton::setStar);
    connect(faceAction, &QAction::triggered, this, &ToolButton::setFace);

};


void ToolButton::reactToToggle(bool checked) {
    if (checked) {
        if (m_iconType == IconType::star) {
            setIcon(m_starChecked);
        } else {
            setIcon(m_faceChecked);
        }
    } else {
        if (m_iconType == IconType::star) {
            setIcon(m_starDefault);
        } else {
            setIcon(m_faceDefault);
        }
    }
}

void ToolButton::setStar() {
    if (m_iconType == IconType::face) {
        if (this->isChecked()) {
            setIcon(m_starChecked);
        } else {
            setIcon(m_starDefault);
        }
        m_iconType = IconType::star;
    }
}

void ToolButton::setFace() {
    if (m_iconType == IconType::star) {
        if (this->isChecked()) {
            setIcon(m_faceChecked);
        } else {
            setIcon(m_faceDefault);
        }
        m_iconType = IconType::face;
    }
}
