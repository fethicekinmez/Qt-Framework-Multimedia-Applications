#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
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

    QMediaPlayer *m_Player;
    QVideoWidget *m_Video;
    QAudioOutput *m_AudioOutput;
    double m_Volume;
    qint64 m_Duration;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_pushButton_Play_Pause_clicked();

    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

    void on_horizontalSlider_Duration_sliderPressed();

    void on_pushButton_SeekBackward_clicked();

    void on_pushButton_SeekForward_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Mute_clicked();

    void on_pushButton_Stop_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
