#ifndef SNAKE_H
#define SNAKE_H


#include <QList>
#include <QWidget>
#include <QPoint>

class GamePainter;


class Snake
        :public QWidget
{
    Q_OBJECT
public:
    Snake( QPoint _startPos );

public:

    enum State
    {
        ST_PLAY,
        ST_DEAD
    };

    enum Direction
    {
        DN_UP,
        DN_DOWN,
        DN_LEFT,
        DN_RIGHT
    };

public:
    void step();
    void draw( GamePainter* _p );

    State       getState() const;
    void        setState( State _s );

    Direction   getDirection() const;
    void        rotate( Direction _d );

    void        reset( QPoint );

    int         getLength() const;

public slots:
    void  grow();

signals:
    void newStep( QPoint _oldZone, QPoint _newZone );

private:

    QList < QPoint >    m_list;

    State               m_state;
    Direction           m_direction;

private:
    void addBlock();

};

inline Snake::State Snake::getState() const
{
    return m_state;
}

inline void Snake::setState( Snake::State _s )
{
    m_state = _s;
}

inline Snake::Direction Snake::getDirection() const
{
    return m_direction;
}

inline int Snake::getLength() const
{
    return m_list.length();
}

#endif // SNAKE_H
