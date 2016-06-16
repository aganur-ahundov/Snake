#ifndef GAMEPAINTER_H
#define GAMEPAINTER_H

#include <QWidget>
#include <QPainter>

class QSettings;
class Snake;
class Field;

class GamePainter : public QWidget
{
    Q_OBJECT
public:
    explicit GamePainter(QWidget *parent = 0);
    ~GamePainter();

public slots:
    void snake_die();
    void snake_eat();
    void game();
    void start_game();
    void continue_game();
    void restart_game();

signals:
    void game_on_pause();
    void game_is_over(int);

public:
    void drawWallCell ( QPoint _pos );
    void drawSnakeCell( QPoint _pos );
    void drawFoodCell ( QPoint _pos );
    void drawFreeCell ( QPoint _pos );
    void drawScoreLine();

    void reDrawSnake();
    void newFood();

    void pause();
    void gameOver();


protected:
    void paintEvent( QPaintEvent* _e );
    void keyPressEvent( QKeyEvent* _e );

private:

    QPainter m_painter;
    QPainter m_snakePainter;
    QSize    m_cellSize;

    Snake*   m_snake;
    Field*   m_field;

    QTimer*  m_gameTimer;
    int      m_gameSpeed;
    int      m_score;
    int      m_highScore;

    bool     m_IsPlay;

private:
    QSettings* m_settings;
    const char* HIGH_SCORE_KEY = "SNAKE_HIGH_SCORE";
};

#endif // GAMEPAINTER_H
