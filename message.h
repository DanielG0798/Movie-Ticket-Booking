#ifndef MESSAGE_H
#define MESSAGE_H

#include <QLabel>      // Include QLabel to make sure it's recognized as a base class
#include <QString>
// Inheritance(Warning and Notification inherit from Message class)
// Message class inherits from QLabel
class Message : public QLabel
{
    Q_OBJECT

public:
    explicit Message(const QString &textGeneral = "",QWidget *parent = nullptr);
    virtual ~Message() {}

    virtual void changeText(const QString &newText) = 0; // Pure virtual and polymorphic function
};
class WarningMessage : public Message
{
public:
    WarningMessage(QWidget *parent = nullptr,const QString&textWarning = "");
    virtual void changeText(const QString &newText) override;
};
class NotificationMessage : public Message
{
public:
    NotificationMessage(QWidget *parent = nullptr, const QString &text = "");
    virtual void changeText(const QString &newText) override;
};

#endif // MESSAGE_H
