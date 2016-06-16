#include "gamepainter.h"
#include "field.h"
#include "snake.h"
#include <QTimer>
#include <QKeyEvent>
#include <time.h>
#include <QThread>
#include <QLabel>
#include <QIcon>
#include <QSettings>


GamePainter::GamePainter(QWidget *parent) : QWidget(parent)
{
    m_cellSize = QSize( 30, 30 );
    m_field    = new Field( 15, 15 );
    m_snake    = new Snake( QPoint( 7, 7) );
    m_IsPlay   = false;
    m_gameTimer = new QTimer;
    m_gameSpeed = 160;
    m_score     = 0;

    resize( m_cellSize.width() * ( m_field->getNumWCells() - 2 )
            , m_cellSize.height() * (m_field->getNumHCells() - 2 ) + 30 );


    QPixmap background("../snake_work_version/background.jpg" );
    background.scaled( this->size() );

    QPalette p;
    p.setBrush( this->backgroundRole(), QBrush( background ) );
    this->setPalette(p);

    QIcon windowIcon("../snake_work_version/icon1.png");
    window()->setWindowTitle("Snake");
    window()->setWindowIcon( windowIcon );

    connect( m_snake, SIGNAL(newStep(QPoint,QPoint)), m_field, SLOT(snake_move(QPoint,QPoint)) );
    connect( m_field, SIGNAL(snake_dead()), SLOT(snake_die()) );
    connect( m_field, SIGNAL(snake_ate()), SLOT(snake_eat()));
    connect( m_gameTimer, SIGNAL(timeout()), SLOT(game()) );

    m_settings  = new QSettings( "HOME", "Snake" );
    m_highScore = m_settings->value( HIGH_SCORE_KEY, 0 ).toInt() ;


    QLabel* high_score = new QLabel("<font face=\"mv boli\" color=#40E0D0><strong>High Score: </strong></font>", this );
    high_score->move( 20, -160  );
    high_score->resize( 300, 350 );

    QLabel* score = new QLabel("<font face=\"mv boli\" color=#40E0D0><strong>Score: </strong></font>", this );
    score->move( width() - 100, -160  );
    score->resize( 300, 350 );

    srand(time(0));
}

GamePainter::~GamePainter()
{
    m_settings->setValue( HIGH_SCORE_KEY, m_highScore );

    delete m_snake;
    delete m_field;
    delete m_settings;
    delete m_gameTimer;
}


void GamePainter::paintEvent(QPaintEvent *_e)
{

   m_painter.begin(this);
   m_painter.setRenderHint( QPainter::Antialiasing, true );

   if(!m_IsPlay)
    {
       m_field->draw( this );
       drawScoreLine();
    }
   else
   {
       reDrawSnake();
       drawFoodCell( m_field->getFoodPos() );
       drawScoreLine();
   }
        m_painter.end();

}


void GamePainter::drawScoreLine()
{

    m_painter.setPen( QColor( 64, 224, 208 ) );
    m_painter.drawLine( QPoint( 0, m_cellSize.height() - 1 ), QPoint( size().width(), m_cellSize.height() - 1 ) );
    m_painter.drawText( QPoint( size().width() - 50, m_cellSize.height()/2 + 5 )
                        , QString::number( m_score ) );
    m_painter.drawText( QPoint( 100, m_cellSize.height()/2 + 5 )
                        , QString::number( m_highScore ) );

}


void GamePainter::reDrawSnake()
{
    drawFreeCell( m_field->getLastTailPos() );
    drawSnakeCell( m_field->getNewHeadPos() );
}


void GamePainter::drawFoodCell(QPoint _pos)
{
    QBrush food( Qt::red );
    m_painter.setBrush( food );

    m_painter.drawEllipse( _pos.x() * m_cellSize.width() + 5
                           , _pos.y() * m_cellSize.height() + 37
                           , m_cellSize.width()/2
                           , m_cellSize.height()/2
                           );
}


void GamePainter::drawWallCell(QPoint _pos)
{
    QBrush wall( Qt::black );
    m_painter.setBrush( wall );

    m_painter.drawRect( _pos.x() * m_cellSize.width()
                           , _pos.y() * m_cellSize.height() + 30
                           , m_cellSize.width()
                           , m_cellSize.height()
                           );
}


void GamePainter::drawSnakeCell(QPoint _pos)
{
    QBrush snake( QColor(0,200, 0), Qt::Dense2Pattern );
    m_painter.setBrush( snake );

    m_painter.drawEllipse( _pos.x() * m_cellSize.width()
                           , _pos.y() * m_cellSize.height() + 30
                           , m_cellSize.width() + 3
                           , m_cellSize.height() + 3
                           );
}


void GamePainter::drawFreeCell(QPoint _pos)
{
    QBrush freeZone( Qt::gray );
    m_painter.setBrush( freeZone );

    m_painter.drawRect( _pos.x() * m_cellSize.width()
                           , _pos.y() * m_cellSize.height() + 30
                           , m_cellSize.width()
                           , m_cellSize.height()
                           );
}


void GamePainter::snake_die()
{
    if( m_score > m_highScore )
        m_highScore = m_score;

    QThread::msleep(400);
    m_snake->setState( Snake::ST_DEAD );
    m_field->reset();
    gameOver();
}


void GamePainter::snake_eat()
{
    m_score += (m_snake->getLength()% 5) + 5;
    m_snake->grow();

    int foodPosY = 0;
    int foodPosX = 0;

    do
    {
        foodPosX = rand()%(m_field->getNumWCells() - 2) + 1;
        foodPosY = rand()%(m_field->getNumHCells() - 2) + 1;
    }while( m_field->getCell( foodPosX, foodPosY ) == Field::CELL_SNAKE
            ||  m_field->getCell( foodPosX + 1, foodPosY ) == Field::CELL_SNAKE
            || m_field->getCell( foodPosX - 1, foodPosY ) == Field::CELL_SNAKE
            || m_field->getCell( foodPosX, foodPosY + 1 ) == Field::CELL_SNAKE
            || m_field->getCell( foodPosX + 1, foodPosY - 1 ) == Field::CELL_SNAKE
            );

    m_field->setFoodPos( foodPosX, foodPosY);
    Q_ASSERT( m_field->getCell(foodPosX, foodPosY) == Field::CELL_FOOD );
}


void GamePainter::game()
{
      m_snake->step();

      if( m_snake->getState() == Snake::ST_DEAD )
          m_gameTimer->stop();
      else
          repaint();
}


void GamePainter::start_game()
{
    m_gameTimer->start( m_gameSpeed );
}


void GamePainter::pause()
{

    hide();
    m_gameTimer->stop();

    emit game_on_pause();
}


void GamePainter::continue_game()
{
   show();
   m_gameTimer->start( m_gameSpeed );

}


void GamePainter::restart_game()
{
    m_score = 0;
    show();
    m_field->reset();
    m_snake->reset( QPoint(7,7) );
    m_gameTimer->start( m_gameSpeed );
}


void GamePainter::gameOver()
{
    hide();
    m_IsPlay = false;
    m_gameTimer->stop();

    emit game_is_over( m_score );
}


void GamePainter::keyPressEvent( QKeyEvent* _pe )
{
    switch (_pe->key())
    {
    case Qt::Key_Up:
        m_snake->rotate( Snake::DN_UP );
        break;
    case Qt::Key_Down:
        m_snake->rotate( Snake::DN_DOWN );
        break;
    case Qt::Key_Left:
        m_snake->rotate( Snake::DN_LEFT );
        break;
    case Qt::Key_Right:
        m_snake->rotate( Snake::DN_RIGHT );
        break;
    case Qt::Key_Escape:
        pause();
    default:
        break;
    }
}
