#include "snake.h"
#include "gamepainter.h"





Snake::Snake( QPoint _startPos )
{
    reset(_startPos);
}

void Snake::reset( QPoint _startPos)
{
    m_list.clear();
    m_list << QPoint( _startPos ) << QPoint( _startPos.x() - 1, _startPos.y() );
    m_direction = Snake::DN_RIGHT;
    m_state     = Snake::ST_PLAY;
}

void Snake::rotate( Direction _d )
{

    if(
            ( m_direction == Snake::DN_UP && _d == Snake::DN_DOWN )
            || ( m_direction == Snake::DN_DOWN && _d == Snake::DN_UP )
            || ( m_direction == Snake::DN_LEFT && _d == Snake::DN_RIGHT  )
            || ( m_direction == Snake::DN_RIGHT && _d == Snake::DN_LEFT  )
       )
    {
        return;
    }
    else
        m_direction = _d;


}


void Snake::grow( )
{
  // addBlock();
    QPoint oldPos = m_list.last();
    switch( m_direction )
    {
    case Snake::DN_UP:
         m_list.push_back( QPoint(oldPos.x(), oldPos.y()));
        break;
    case Snake::DN_DOWN:
         m_list.push_back( QPoint(oldPos.x(), oldPos.y()));
        break;
    case Snake::DN_RIGHT:
         m_list.push_back( QPoint(oldPos.x() , oldPos.y()));
        break;
    case Snake::DN_LEFT:
         m_list.push_back( QPoint(oldPos.x(), oldPos.y() ));
        break;
    }
}

void Snake::addBlock()
{
    QPoint oldPos = m_list.first();

    switch( m_direction )
    {
    case Snake::DN_UP:
         m_list.push_front( QPoint(oldPos.x(), oldPos.y() - 1 ));
        break;
    case Snake::DN_DOWN:
         m_list.push_front( QPoint(oldPos.x(), oldPos.y() + 1 ));
        break;
    case Snake::DN_RIGHT:
         m_list.push_front( QPoint(oldPos.x() + 1, oldPos.y()));
        break;
    case Snake::DN_LEFT:
         m_list.push_front( QPoint(oldPos.x() - 1, oldPos.y() ));
        break;
    }
}

void Snake::step()
{
    addBlock();
    emit newStep( m_list.last(), m_list.first() );
    m_list.pop_back();
}

void Snake::draw(GamePainter *_p)
{
    QPoint oldPos = m_list.last();
    m_list.pop_back();

    _p->drawFreeCell( oldPos );
    _p->drawSnakeCell( m_list.first() );
}
