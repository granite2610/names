#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <list>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("Names");
    ui->setupUi(this);
    input = ui->textEdit->toPlainText();
    connect( ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(computeSlot()) );
    //connect( ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(changeHistory()) );
    QCoreApplication::setOrganizationName("Nathan_Robertson");
    QCoreApplication::setApplicationName("Names");

    // Set text from previously entered text.
    settings = new QSettings;
    QString text = settings->value("name").toString();
    ui->textEdit->setText(text);
}


/**
 * @brief MainWindow::~MainWindow
 * @pre Must have completed all necessary programming tasks
 * @post Program is ready to shut down.
 * Save text in settings and delete ui.
 */
MainWindow::~MainWindow()
{
    delete ui;
}



/**
 * @brief MainWindow::computeSlot
 * This slot is triggered when the user clicks on the "Compute" button.
 */
void MainWindow::computeSlot()
{
    settings->setValue("name", ui->textEdit->toPlainText());
    input = ui->textEdit->toPlainText();
    NameShuffler shuffle;
    QString names = shuffle.get_names( input );
    ui->Output->setText(names);
}



/**
 * @brief MainWindow::changeHistory
 * This slot is trigerred whenever the input text changes.
 */
void MainWindow::changeHistory()
{
    // Get current history values
    QVector<QString> curr;
    int size = settings->beginReadArray("history");
    for ( int i = 0 ; i < size; i++ )  {
        settings->setArrayIndex(i);
        curr.push_back( settings->value( "name" ).toString() );
    }

    // Get names in current program.
    QString text = ui->textEdit->toPlainText();
    std::list<QString> names = text.split("\n").toStdList();

    // Remove unwanted names from history.
    for ( int i = 0; i < curr.size(); i++ ) {
        if (!std::binary_search( names.begin(), names.end(), curr.at(i) ))
            curr.removeAt(i);
    }
}
