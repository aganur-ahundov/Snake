#ifndef FIELD_H
#define FIELD_H

#include <QWidget>

class QPoint;
class QPainter;
class QSize;
class GamePainter;

class Field
        : public QWidget
{
    Q_OBJECT
public:
    Field( int _w, int _h );
    ~Field();

    enum Cell
    {
        CELL_FREE,
        CELL_FOOD,
        CELL_WALL,
        CELL_SNAKE
    };

    struct PointsForDraw
    {
        QPoint m_tail;
        QPoint m_head;
        QPoint m_fruit;
    } help_drawer;


    QPoint getLastTailPos() const { return  help_drawer.m_tail; }
    QPoint getNewHeadPos() const { return  help_drawer.m_head; }

    QPoint getFoodPos() const;
    void   setFoodPos( int i, int j);
    Cell getCell( int i, int j ) const { return m_field[i][j]; }

    void draw( GamePainter* _p );
    void reset();

    int  getNumWCells() const;
    int  getNumHCells() const;

public slots:
    void snake_move( QPoint _tailPos, QPoint _headPos );

signals:
    void snake_dead();
    void snake_ate();


private:

    Cell** m_field;
    int    m_numWeightCells;
    int    m_numHeightCells;

};

inline int Field::getNumHCells() const
{
    return m_numHeightCells;
}

inline int Field::getNumWCells() const
{
    return m_numWeightCells;
}

inline void Field::setFoodPos(int i, int j)
{
    Q_ASSERT(i > 0 || i < m_numWeightCells );
    Q_ASSERT(j > 0 || j < m_numHeightCells );

    m_field[i][j] = CELL_FOOD;
    help_drawer.m_fruit = QPoint(i,j);
}

inline QPoint Field::getFoodPos() const
{
    return help_drawer.m_fruit;
}

#endif // FIELD_H
