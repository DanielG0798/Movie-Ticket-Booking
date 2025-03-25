#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <message.h>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{// Setting "this" keyword as parent for ui elements to deallocate memory later
    ui->setupUi(this); // "this" is MainWindow
// Warning labels
    payWarn = ui->NoItemsWarn;
    payWarn->changeText("Please Add Items To Cart To Continue");
    payWarn->setVisible(false); // hiding in ui
    warnLabels[0] = ui->AdultWarning;
    warnLabels[1] = ui->DateWarning;
    warnLabels[2] = ui->TimeWarning;
    warnLabels[3] = ui->addToCartNotify;
    for(int i = 0; i<3 ; i++){
        // Using polymorphic function to change text and style
        warnLabels[i]->changeText("Please Fill This In");
        warnLabels[i]->setVisible(false); // hiding in ui
    }
// Notification Labels for Payment Page
    notice[0] = ui->PaymentSubmitted;
    notice[0]->changeText("Payment Submitted Successfully!");
    notice[0]->setVisible(false);
    notice[1] = ui->EmailSent;
    notice[1]->changeText("Email Receipt Sent");
    notice[1]->setVisible(false);
// QPixmaps for circle and cart buttons
    QPixmap circleCart(":/images/Images/red-circle.png");
    int w = ui->circleCart->width();
    int h = ui->circleCart->height();
    ui->circleCart->setPixmap(circleCart.scaled(w,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->circleCart->setVisible(false); // hiding the indicator until add to cart is clicked
    int e = ui->cart->width();
    int d = ui->cart->height();
    QPixmap cartIcon(":/images/Images/cart.png");
    QPixmap cartButton = cartIcon.scaled(e,d,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->cart->setIcon(cartButton);
    ui->cart->setIconSize(cartButton.size());
    ui->cart->resize(cartButton.size());
    ui->cart->setFixedSize(45,45);
// Image paths for constuction of MovieButton taken from image path relative to ImagesTicketBooking.qrc
    QString imagePath1 = ":/images/Images/lordofthebling.jpg";
    QString imagePath2 = ":/images/Images/terminator.jpg";
    QString imagePath3 = ":/images/Images/matrix.jpg";
    QString imagePath4 = ":/images/Images/western.jpg";
    QString imagePath5 = ":/images/Images/beasts.jpg";
    QString imagePath6 = ":/images/Images/solarbabies.jpg";
// MovieButton objects
    movieButton1 = new MovieButton("Lord of The Bling",imagePath1,this);
    movieButton2 = new MovieButton("The Terminator",imagePath2,this);
    movieButton3 = new MovieButton("The Matrix",imagePath3,this);
    movieButton4 = new MovieButton("Alvarez Kelly",imagePath4,this);
    movieButton5 = new MovieButton("Wild Beasts",imagePath5,this);
    movieButton6 = new MovieButton("Solarbabies",imagePath6,this);
// Connections (signals and slots)
    // Movie Buttons
    connect(movieButton1, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    connect(movieButton2, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    connect(movieButton3, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    connect(movieButton4, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    connect(movieButton5, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    connect(movieButton6, &MovieButton::movieClicked, this, &MainWindow::onMovieButtonClicked);
    // UI Connections
    connect(ui->BackPayment, &QPushButton::clicked, this, &MainWindow::backPaymentClicked);
    connect(ui->payment, &QPushButton::clicked, this, &MainWindow::paymentClicked);
    connect(ui->BackSelection, &QPushButton::clicked, this, &MainWindow::selectionBackClicked);
    connect(ui->BackCheckOut, &QPushButton::clicked, this, &MainWindow::cartBackClicked);
    connect(ui->AddtoCart, &QPushButton::clicked, this, &MainWindow::addCartClicked);
    connect(ui->cart, &QPushButton::clicked, this, &MainWindow::cartClicked);
    connect(ui->dateEdit, &QDateEdit::userDateChanged, this, &MainWindow::dateChanged);
    connect(ui->timeEdit, &QTimeEdit::userTimeChanged, this, &MainWindow::timeChanged);
    connect(ui->EmptyCart, &QPushButton::clicked, this, &MainWindow::emptyCartClicked);
    connect(ui->AdultTicketAmount, &QSpinBox::textChanged, this, &MainWindow::adultTicketTextChanged);
    connect(ui->AdultTicketAmount, &QSpinBox::valueChanged, this, &MainWindow::adultTicketsValueChanged);
    connect(ui->ChildTicketAmount, &QSpinBox::textChanged, this, &MainWindow::childTicketsTextChanged);
    connect(ui->ChildTicketAmount, &QSpinBox::valueChanged, this, &MainWindow::childTicketsValueChanged);
    connect(ui->SubmitPay, &QPushButton::clicked, this, &MainWindow::submitPayClicked);
// Layout for Movie Selection Screen
    QLabel *pageTitle = new QLabel("Movie Selection", this);
    pageTitle->setAlignment(Qt::AlignCenter);
    pageTitle->setStyleSheet("font-size: 50px; font-weight: bold;");
    QWidget *frontPage = new QWidget(this);
    QGridLayout *layout = new QGridLayout(frontPage);
    layout->addWidget(pageTitle,0,0,1,3); // (row,column, taking space in 1 row and 3 columns)
// 2 rows 3 columns for movies
    layout->addWidget(movieButton1,1,0);
    layout->addWidget(movieButton2,1,1);
    layout->addWidget(movieButton3,1,2);
    layout->addWidget(movieButton4,3,0);
    layout->addWidget(movieButton5,3,1);
    layout->addWidget(movieButton6,3,2);
// Adjustments for the spacing between buttons
    layout->setVerticalSpacing(25);
    layout->setContentsMargins(20, 10, 20, 10);
    frontPage->setLayout(layout);
    ui->stackedPages->insertWidget(0, frontPage);
    ui->stackedPages->setCurrentIndex(0);
} // End of ui
// Variables
    bool cartHasItems = false;
    bool allFieldsFilled = false;
    bool smallSelection = false;
    bool noAdult = true;
    int totalAdultTickets;
    int totalChildTickets;
    QString chosenMovie;
    QString stringAdultTotal;
    QString stringChildTotal;
    QString stringTotal;
    QTime givenTime;
    QDate givenDate;
// Using price in pennies then converting to dollar amount
    const int adultTicketPrice = 1255;
    const int childTicketPrice = 500;
// MainWindow Functions
    MainWindow::~MainWindow()
    {
        delete ui; // Deleting UI::MainWindow which deallocates widgets and other UI objects
    }
// Movie poster gets selected then it updates ui and variables
    void MainWindow::onMovieButtonClicked(const QString &movieTitle)
    {   chosenMovie = movieTitle;
        ui->MovieSelected->setText(movieTitle); // Movie poster title set on selection page
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime::currentTime());
        // reset initial modification of fields to false
        for (int i = 0; i < 4; ++i) {
            checkSelectionPage[i] = false;
        }
        ui->stackedPages->setCurrentIndex(2);
    }
    void MainWindow::selectionBackClicked()
    {
        ui->stackedPages->setCurrentIndex(0);
        resetSelect();
    }
// Cart related functions
    void MainWindow::cartClicked()    // View Cart
    {
        ui->stackedPages->setCurrentIndex(3);
    }
    void MainWindow::addCartClicked()
    {
        checkSelectionFields();
        if (allFieldsFilled)
        {   cartHasItems = true;
            ui->NoItemsWarn->setVisible(false);
            ui->circleCart->setVisible(true);
            ui->MovieSelectedCart->setText(chosenMovie);
            ui->AdultTickets->setText(QVariant(totalAdultTickets).toString()+"x at $12.55 ea");
            ui->AdultTotalSum->setText("$"+stringAdultTotal);
            ui->ChildTickets->setText(QVariant(totalChildTickets).toString()+"x at $5.00 ea");
            ui->ChildTotalSum->setText("$"+stringChildTotal);
            ui->TimeGiven->setText(givenTime.toString("h:mm AP"));
            ui->DateGiven->setText(givenDate.toString("MM-dd-yyyy"));
        }else if(smallSelection)
        {   cartHasItems = true;
            ui->NoItemsWarn->setVisible(false);
            QString movieTitle = ui->MovieSelected->text();
            ui->circleCart->setVisible(true);
            ui->MovieSelectedCart->setText(movieTitle);
            ui->AdultTickets->setText(QVariant(totalAdultTickets).toString()+"x at $12.55 ea");
            ui->AdultTotalSum->setText("$"+stringAdultTotal);
            ui->TimeGiven->setText(givenTime.toString("h:mm AP"));
            ui->DateGiven->setText(givenDate.toString("MM-dd-yyyy"));
        }else{
            ui->NoItemsWarn->changeText("Please Add Additional Items");
            ui->NoItemsWarn->setVisible(true);
        }
    }
    void MainWindow::cartBackClicked()
    {
        ui->stackedPages->setCurrentIndex(2);
    }
// Resets ui elements to default values when needed
    void MainWindow::resetSelect()
    {
        cartHasItems = false;
        ui->DateGiven->setText("No Date Selected");
        ui->TimeGiven->setText("No Selected Time");
        ui->AdultTickets->setText("(None Selected)");
        ui->ChildTickets->setText("(None Selected)");
        ui->AdultTotalSum->setText("$");
        ui->ChildTotalSum->setText("$");
        ui->MovieSelectedCart->setText("Cart is Empty");
        ui->circleCart->setVisible(false);
        ui->AdultTicketAmount->setValue(0);
        ui->ChildTicketAmount->setValue(0);
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeEdit->setTime(QTime::currentTime());
        ui->CardName->clear();
        ui->CardNumber->clear();
        ui->NameEdit->clear();
        ui->EmailEdit->clear();
        for (int i = 0; i < 4; ++i) {
            checkSelectionPage[i] = false;
        }
        for (int i = 0; i < 4; ++i) {
            warnLabels[i]->setVisible(false);
        }
    }
// Resets the cart selections
    void MainWindow::emptyCartClicked()
    {
        resetSelect();
    }
// Pricing function for tickets turning pennies to dollars for user display
    QString MainWindow::getTicketInfo(int ticketAmount, int ticketPrice)
    {
        int totalPrice;
        QString totalStringPrice;
        totalPrice = ticketAmount * ticketPrice;
        double totalInDollars = totalPrice / 100.0f;  // Dollar amount
        totalStringPrice = QString::number(totalInDollars, 'f', 2);
        return totalStringPrice;
    }
// Selection page value changes
    void MainWindow::dateChanged(const QDate &date)
    {
        givenDate = date;
        warnLabels[1]->setVisible(false);
        checkSelectionPage[1] = true;
    }
    void MainWindow::timeChanged(const QTime &time)
    {
        givenTime = time;
        warnLabels[2]->setVisible(false);
        checkSelectionPage[2] = true;
    }
    void MainWindow::adultTicketTextChanged(const QString &value)
    {
        int valueNum = QVariant(value).toInt();
        warnLabels[0]->setVisible(false);
        checkSelectionPage[0] = (valueNum > 0);
        totalAdultTickets = valueNum;
        stringAdultTotal = getTicketInfo(valueNum, adultTicketPrice);
    }
    void MainWindow::adultTicketsValueChanged(int value) // if up/down arrows are used to make a change
    {
        warnLabels[0]->setVisible(false);
        checkSelectionPage[0] = (value > 0);
        totalAdultTickets = value;
        stringAdultTotal = getTicketInfo(value, adultTicketPrice);
    }
    void MainWindow::childTicketsTextChanged(const QString &value)
    {
        int valueNum = QVariant(value).toInt();
        checkSelectionPage[3] = (valueNum > 0);
        totalChildTickets = valueNum;
        stringChildTotal = getTicketInfo(valueNum, childTicketPrice);
    }
    void MainWindow::childTicketsValueChanged(int value) // if up/down arrows are used to make a change
    {
        checkSelectionPage[3] = (value > 0);
        totalChildTickets = value;
        stringChildTotal = getTicketInfo(value, childTicketPrice);
    }
// Control Structure with an array for checking if required fields are filled
    void MainWindow::checkSelectionFields()
    {
        int fields = 0;
        allFieldsFilled = false;
        smallSelection = false;
        for (int i = 0; i < 4; ++i) {
            /*qDebug() << checkSelectionPage[i];*/ // for demo
            if (checkSelectionPage[i] == true){
                fields++;
            }
            if (fields == 4){
                allFieldsFilled = true;
            }else if(fields == 0){
                allFieldsFilled = false;
                warnLabels[i]->setVisible(true);
            }else if(fields == 3 && checkSelectionPage[3] == false){
                smallSelection = true;
            }else{
                smallSelection = false;
                warnLabels[i]->setVisible(!checkSelectionPage[i]);
            }
        }
    // Throw catch for invalid add to cart
        try{
            if(checkSelectionPage[3] == true && checkSelectionPage[0] == false){
                throw false;
            }
        }
        catch (bool adultAdded) {
            if(adultAdded == false){
                QMessageBox::warning(this, "Movie Ticket Booking",
                                     "You must have one Adult ticket to add a Child ticket");
            }
        }
        // for demo
        // qDebug() << fields;
        // qDebug() << smallSelection;
        // qDebug() << allFieldsFilled;
    }
// Total price calculation from pennies to dollars to avoid float math problems
    QString MainWindow::totalPricePayment () // Calculations done in pennies
    {
        int adultTotal, childTotal, sumTotals;
        adultTotal = totalAdultTickets * adultTicketPrice;
        childTotal = totalChildTickets * childTicketPrice;
        sumTotals = adultTotal + childTotal;
        double totalInDollars = sumTotals / 100.0f;  // Dollar amount conversion
        stringTotal = QString::number(totalInDollars, 'f', 2);
        return stringTotal;
    }
// Payment page
    void MainWindow::paymentClicked()
    {
        if(cartHasItems){
            ui->stackedPages->setCurrentIndex(4);
            ui->Movietitleconfirm->setText(chosenMovie);
            ui->TotalSumCalc->setText("$"+totalPricePayment());
            ui->AdultTickets_2->setText(QVariant(totalAdultTickets).toString()+"x at $12.55 ea");
            ui->AdultTotalSum_2->setText("$"+stringAdultTotal);
            ui->ChildTickets_2->setText(QVariant(totalChildTickets).toString()+"x at $5.00 ea");
            ui->ChildTotalSum_2->setText("$"+stringChildTotal);
        }else{
            ui->NoItemsWarn->setVisible(true);
        }
    }
    void MainWindow::backPaymentClicked()
    {
        ui->stackedPages->setCurrentIndex(3);
        notice[0]->setVisible(false);
        notice[1]->setVisible(false);
    }
    // later implementation
    // bool MainWindow::paymentFilled()
    // {
    // }
    void MainWindow::submitPayClicked()
    {
        notice[0]->setVisible(true);
        notice[1]->setVisible(true);
    }


