#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QFileDialog>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtGui>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVideoWidget *m_Video;
    QMediaPlayer *m_Player;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Open_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_fullScreen_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
