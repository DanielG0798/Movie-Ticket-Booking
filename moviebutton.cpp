#include "moviebutton.h"

MovieButton::MovieButton(const QString &movieTitle,const QString &imagePath, QWidget *parent)
    : QPushButton(parent), title(movieTitle)
{
    movieImage.load(imagePath);
// Format the QPixmap once loaded
    QPixmap scaledPixmap = movieImage.scaled(250,250,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setIcon(scaledPixmap);
    this->setIconSize(scaledPixmap.size());
    this->resize(scaledPixmap.size());
    this->setFixedSize(210,310); // this changes the actual button size
    connect(this, &QPushButton::clicked, this, &::MovieButton::handleClick);

}
void MovieButton::handleClick()
{
    emit movieClicked(title);
}
