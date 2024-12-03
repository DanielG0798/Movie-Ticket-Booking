#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <moviebutton.h>
#include <message.h>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
// Movie poster click
    void onMovieButtonClicked(const QString &movieTitle);
// Back buttons for navigation
    void selectionBackClicked();
    void cartBackClicked();
    void backPaymentClicked();
// Date and Time selections
    void dateChanged(const QDate &date); 
    void timeChanged(const QTime &time);
// Ticket selections from QSpinbox or from changing text
    void adultTicketTextChanged(const QString &arg1);
    void adultTicketsValueChanged(int value);
    void childTicketsTextChanged(const QString &arg1);
    void childTicketsValueChanged(int value);
// Add to cart, cart being clicked, empty cart button
    void addCartClicked();
    void cartClicked();
    void emptyCartClicked();
// Payment page buttons
    void paymentClicked();
    void submitPayClicked();

    void checkSelectionFields(); // used for control structure
    // bool paymentFilled(); // future use
private:
    Ui::MainWindow *ui;
// Movie poster button pointers
    MovieButton *movieButton1;
    MovieButton *movieButton2;
    MovieButton *movieButton3;
    MovieButton *movieButton4;
    MovieButton *movieButton5;
    MovieButton *movieButton6;
// Derived classes from Message class Warning/Notification
    WarningMessage *payWarn;
    WarningMessage *warnLabels[4];
    NotificationMessage *notice[2];
// Functions used for pricing, resetting, updating selections,
    QString totalPricePayment();
    void resetSelect();
    void changeSelections();
    QString getTicketInfo(int ticketAmount, int ticketPrice);
    bool checkSelectionPage[4] = {false, false, false, false};
};
#endif // MAINWINDOW_H
