#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_SeekBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_SeekForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    m_Player = new QMediaPlayer();
    audioOutput = new QAudioOutput;
    m_Player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.1);

    //QObject::connect(m_Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    //QObject::connect(m_Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

   // ui->horizontalSlider_Duration->setRange(0, m_Player->duration() / 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::updateDuration(qint64 duration)
{
    QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
    QTime totalTime((m_Duration / 3600) & 60, (m_Duration / 60) % 60, (m_Duration % 60), (m_Duration * 1000) % 1000);
    QString format = "mm:ss";
    if(m_Duration > 3600){
        format = "hh:mm:ss";
    }
    ui->label_valueStart->setText(CurrentTime.toString(format));
    ui->label_valueEnd->setText(totalTime.toString(format));

}

void MainWindow::durationChanged(qint64 duration)
{
    m_Duration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(m_Duration);
}

void MainWindow::positionChanged(qint64 progress)
{
    if(!ui->horizontalSlider_Duration->isSliderDown()){
        ui->horizontalSlider_Duration->setValue(progress/1000);
    }

    updateDuration(progress/1000);
}



void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    m_Player->setPosition(value * 1000);
}
*/
void MainWindow::on_pushButton_SeekForward_clicked()
{

}

void MainWindow::on_pushButton_SeekBackward_clicked()
{

}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.MP3)"));
    QFileInfo File(filename);
    ui->label_FileName->setText(File.fileName());
    m_Player->setSource(QUrl(filename));
    m_Player->play();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    if(m_Player->isPlaying()){
        m_Player->stop();
        qDebug() << "Stopped!";
    }
    else{
        qDebug() << "Already Stopped!";
    }

}


void MainWindow::on_pushButton_Pause_clicked()
{
    if(m_Player->isPlaying()){
        m_Player->pause();
        qDebug() << "Paused!";
    }
    else{
        qDebug() << "Already Paused!";
    }

}


void MainWindow::on_pushButton_Play_clicked()
{
    if(!m_Player->isPlaying()){
        m_Player->play();
        qDebug() << "Playing...";
    }
    else{
        qDebug() << "Already Playing...";
    }
}



void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    double volume = double(ui->horizontalSlider_Volume->value())/100;
    audioOutput->setVolume(volume);
    qDebug() << "Volume Changed" << volume << " - " << audioOutput->volume();
}




void MainWindow::on_pushButton_Mute_clicked()
{
    if(isMuted){
        audioOutput->setMuted(false);
        ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        ui->horizontalSlider_Volume->setValue(10);
        isMuted = false;
    }else{
        audioOutput->setMuted(true);
        ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        ui->horizontalSlider_Volume->setValue(0);
        isMuted = true;
    }
    qDebug() << "Is Muted: " << audioOutput->isMuted() << " - " << isMuted;
}




