#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <QIcon>

class QMenu; // why

class ToolButton : public QToolButton
{
    Q_OBJECT //why

public:
    enum class IconType {
        star,
        face
    };
    explicit ToolButton(QWidget *parent = nullptr);
    void reactToToggle(bool checked);

private:
    IconType m_iconType = IconType::star; 
    QIcon m_starDefault;
    QIcon m_starChecked;
    QIcon m_faceDefault;
    QIcon m_faceChecked;
    QMenu* m_menu = nullptr;
    void setStar();
    void setFace();

};

#endif // TOOLBUTTON_H