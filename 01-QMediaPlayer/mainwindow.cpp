#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_volumeUp->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    ui->pushButton_volumeDown->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

    m_Player = new QMediaPlayer();
    audioOutput = new QAudioOutput;
    m_Player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.MP3)"));
    QFileInfo File(filename);
    ui->label_File_Name_Value->setText(File.fileName());
    m_Player->setSource(QUrl(filename));
    m_Player->play();
}


void MainWindow::on_pushButton_Play_clicked()
{
    m_Player->play();
    qDebug() << "Playing..";
}


void MainWindow::on_pushButton_Pause_clicked()
{
    m_Player->pause();
    qDebug() << "Pause!";
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "Volume changed " << audioOutput->volume() << " to " << double(value)/100;
    audioOutput->setVolume(double(value)/100);

}


void MainWindow::on_pushButton_volumeUp_clicked()
{
    double volume = audioOutput->volume();
    audioOutput->setVolume(volume + 0.1);
    ui->horizontalSlider->setValue((volume + 0.1)*100);
    qDebug() << "Volume changed " << volume << " to " << audioOutput->volume();
}


void MainWindow::on_pushButton_volumeDown_clicked()
{
    double volume = audioOutput->volume();
    audioOutput->setVolume(volume - 0.1);
    ui->horizontalSlider->setValue((volume - 0.1)*100);
    qDebug() << "Volume changed " << volume << " to " << audioOutput->volume();
}


void MainWindow::on_checkBox_Mute_stateChanged(int arg1)
{
    if(arg1 == 0){
        audioOutput->setMuted(false);
    }else{
        audioOutput->setMuted(true);
    }
    qDebug() << "is muted: " << audioOutput->isMuted();

}

