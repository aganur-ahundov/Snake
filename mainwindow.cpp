#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamepainter.h"
#include <QPixmap>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gameIcon("../snake_work_version/icon1.png")
{
    ui->setupUi(this);

    QPixmap background("../snake_work_version/mainWindow.jpg");
    background = background.scaled( size() );
    Q_ASSERT( !background.isNull() );

    QPalette p;
    p.setBrush( this->backgroundRole(), QBrush(background) );

    setPalette(p);

    m_painter = new GamePainter;

   createGameOverMenu();
   createPauseMenu();


   m_score = new QLabel( m_gameOverMenu );
   m_score->move( 150, 160 );
   m_score->resize( 200, 60 );


   connect( m_painter, SIGNAL(game_is_over(int)), SLOT(show_over(int)) );
   connect( m_painter, SIGNAL(game_on_pause()), SLOT(show_pause()) );

   window()->setWindowTitle("Snake");
   window()->setWindowIcon( m_gameIcon );

}


void MainWindow::createGameOverMenu()
{
    m_gameOverMenu = new QWidget();
    m_gameOverMenu->resize( 400, 400 );


    QPushButton* restart  = new QPushButton( "Restart", m_gameOverMenu );
    QPushButton* exit     = new QPushButton( "Exit", m_gameOverMenu );

    QPixmap      gameOver( "../snake_work_version/GameOver.png" );
    QLabel*      pixmapGO = new QLabel( m_gameOverMenu );



    Q_ASSERT( !gameOver.isNull() );
    gameOver = gameOver.scaled( 200, 150 );
    pixmapGO->setPixmap( gameOver );

    restart->setDefault(true);


    pixmapGO->move( 100, 0 );

    restart->resize( 150, 50 );
    exit->resize( 150, 50);

    restart->move( 125, 220 );
    exit->move( 124, 300 );

    connect( exit, SIGNAL(clicked(bool)), m_gameOverMenu, SLOT(close()) );
    connect( restart, SIGNAL(clicked(bool)), m_painter, SLOT(restart_game()) );
    connect( restart, SIGNAL(clicked(bool)), m_gameOverMenu, SLOT( hide() ) );

     m_gameOverMenu->setWindowTitle("Snake");
     m_gameOverMenu->window()->setWindowIcon( m_gameIcon );
}


void MainWindow::createPauseMenu()
{
    m_pauseMenu = new QWidget();
    m_pauseMenu->resize( 400, 400 );

    QPushButton* restart        = new QPushButton( "Restart", m_pauseMenu );
    QPushButton* continueGame   = new QPushButton( "Continue", m_pauseMenu );
    QPushButton* exit           = new QPushButton( "Exit", m_pauseMenu );

    continueGame->setDefault(true);

    restart->resize( 150, 50 );
    continueGame->resize(150, 50);
    exit->resize( 150, 50);

    continueGame->move( 125, 90 );
    restart->move( 125, 170 );
    exit->move( 125, 250 );


    connect( exit, SIGNAL(clicked(bool)), m_pauseMenu, SLOT(close()) );

    connect( restart, SIGNAL(clicked(bool)), m_painter, SLOT(restart_game()) );
    connect( restart, SIGNAL(clicked(bool)), m_pauseMenu, SLOT( hide() ) );

    connect( continueGame, SIGNAL(clicked(bool)), m_painter, SLOT(continue_game()) );
    connect( continueGame, SIGNAL(clicked(bool)), m_pauseMenu, SLOT(hide()) );

    m_pauseMenu->window()->setWindowIcon( m_gameIcon );
    m_pauseMenu->setWindowTitle("Snake");
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_painter;
    delete m_gameOverMenu;
    delete m_pauseMenu;
}


void MainWindow::on_pushButton_clicked()
{

    m_painter->show();
    m_painter->start_game();
    hide();
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}


void MainWindow::show_pause()
{
    m_pauseMenu->show();
    m_painter->hide();
}


void MainWindow::show_over(int _score)
{
    m_score->setText( "<h3><font face=\"mv boli\"><strong>Your score: "
                          + QString::number(_score)
                          + "</strong></font></h3>" );
    m_gameOverMenu->show();
    m_painter->hide();
}
