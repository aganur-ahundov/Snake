#include "field.h"
#include "gamepainter.h"
#include <QPainter>





Field::Field( int _w, int _h )
{
    m_numHeightCells = _h;
    m_numWeightCells = _w;

    Q_ASSERT( _h > 10 && _w > 10 );

    m_field = new Cell*[ m_numWeightCells ];

    for(int i = 0; i < m_numWeightCells; i++ )
        m_field[i] = new Cell[m_numHeightCells];

    reset();
}


Field::~Field()
{
    for(int i = 0; i < m_numWeightCells; i++ )
        delete m_field[i];

    delete [] m_field;
}


void Field::reset()
{
    for( int i = 1; i < m_numWeightCells - 1; i++ )
    {
        for( int j = 1; j < m_numHeightCells - 1; j++ )
        {
            m_field[i][j] = Field::CELL_FREE;
        }
    }

    for( int k = 0; k < m_numHeightCells; k++ )
    {
        m_field[0][k] = Field::CELL_WALL;
        m_field[ m_numWeightCells - 1 ][k] = Field::CELL_WALL;
    }

    for( int k = 0; k < m_numWeightCells; k++ )
    {
        m_field[k][0] = Field::CELL_WALL;
        m_field[k][ m_numHeightCells - 1 ] = Field::CELL_WALL;
    }

    m_field[ m_numWeightCells/2 ][ m_numHeightCells/2 ] = Field::CELL_SNAKE;
    m_field[ m_numWeightCells/2 - 1 ][ m_numHeightCells/2 ] = Field::CELL_SNAKE;
    m_field[ m_numWeightCells/2 + 3 ][ 3 ] = Field::CELL_FOOD;

}


void Field::draw( GamePainter*_p )
{
    for( int i = 1; i < m_numWeightCells - 1; i++ )
    {
        for( int j = 1; j < m_numHeightCells - 1; j++ )
        {
            switch(m_field[i][j])
            {/*
            case CELL_WALL:
                _p->drawWallCell( QPoint( i, j) );
                break;*/
            case Field::CELL_SNAKE:
                    _p->drawSnakeCell( QPoint( i - 1, j - 1 ) );
                break;
            case Field::CELL_FOOD:
                _p->drawFoodCell( QPoint( i - 1, j - 1 ) );
                break;
            default:
                break;
            }
        }
    }
}


void Field::snake_move(QPoint _tailPos, QPoint _headPos)
{
    m_field[_tailPos.x()][_tailPos.y()] = CELL_FREE;

    if( m_field[ _headPos.x() ][ _headPos.y() ] == CELL_WALL)
    {
        emit snake_dead();
    }
    else if( m_field[ _headPos.x() ][ _headPos.y() ] == CELL_SNAKE )
    {
        emit snake_dead();
    }
    else if ( m_field[ _headPos.x() ][ _headPos.y() ] == CELL_FOOD  )
    {
        m_field[_headPos.x() ][_headPos.y()] = CELL_SNAKE;

        help_drawer.m_head = _headPos;
        help_drawer.m_tail = _tailPos;

        emit snake_ate();
    }
    else
       {
        m_field[_headPos.x() ][_headPos.y()] = CELL_SNAKE;

         help_drawer.m_head = _headPos;
         help_drawer.m_tail = _tailPos;
       }
}

