#include "message.h"
#include <QLabel>

// Base class Message implementation
Message::Message(const QString &textGeneral, QWidget *parent)
    : QLabel(parent)
{
}
void Message::changeText(const QString &newText)
{
    this->setText(newText);  // Update the text of the QLabel
}
// Derived class Warning implementation for the pure virtual function
WarningMessage::WarningMessage(QWidget *parent,const QString &textWarning)
    : Message(textWarning,parent)
{
    setStyleSheet("color: red; font-size: 12px; font-weight: bold;");
}
void WarningMessage::changeText(const QString &newText)
{
    setText(newText);  // Update the text
    setStyleSheet("color: red; font-size: 12px; font-weight: bold;");  // Reapply warning style
}
// Derived class Notification implementation for the pure virtual function
NotificationMessage::NotificationMessage(QWidget *parent, const QString &text)
    : Message(text, parent)
{
    setStyleSheet("color: yellow; font-size: 12px; font-weight: normal;");
}
void NotificationMessage::changeText(const QString &newText)
{
    setText(newText);  // Update the text
    setStyleSheet("color: yellow; font-size: 16px; font-weight: normal;");  // Reapply notification style
}
