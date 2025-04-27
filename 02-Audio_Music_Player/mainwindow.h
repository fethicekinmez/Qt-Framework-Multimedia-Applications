#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
#include <QFile>
#include <QStyle>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void updateDuration(qint64 duration);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //void durationChanged(qint64 duration);
    //void positionChanged(qint64 progress);

    void on_actionOpen_File_triggered();

    void on_pushButton_SeekBackward_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_SeekForward_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Mute_clicked();

   // void on_horizontalSlider_Duration_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_Player;
    QAudioOutput *audioOutput;

    bool isMuted = false;
    qint64 m_Duration;
};
#endif // MAINWINDOW_H
