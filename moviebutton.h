#ifndef MOVIEBUTTON_H
#define MOVIEBUTTON_H

#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QWidget>

class MovieButton : public QPushButton
{
    Q_OBJECT
private:
    QString title;
    QPixmap movieImage; // the given image path for the button icon
public:
    explicit MovieButton(const QString &movieTitle,const QString &imagePath, QWidget *parent = nullptr);
signals:
    void movieClicked(const QString &title);
private slots:
    void handleClick();


};

#endif // MOVIEBUTTON_H
