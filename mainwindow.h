#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GamePainter;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createGameOverMenu();
    void createPauseMenu();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void show_pause();
    void show_over(int);

private:
    Ui::MainWindow *ui;
    GamePainter*    m_painter;

    QWidget*        m_pauseMenu;
    QWidget*        m_gameOverMenu;
    QLabel*         m_score;
    QIcon           m_gameIcon;

};

#endif // MAINWINDOW_H
