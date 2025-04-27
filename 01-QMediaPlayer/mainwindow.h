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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_volumeUp_clicked();

    void on_pushButton_volumeDown_clicked();

    void on_checkBox_Mute_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_Player;
    QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H
