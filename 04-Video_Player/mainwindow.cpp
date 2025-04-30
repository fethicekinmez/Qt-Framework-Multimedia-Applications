#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_SeekBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_SeekForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    m_Player = new QMediaPlayer(this);

    QObject::connect(m_Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    QObject::connect(m_Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));
    QFileInfo File(fileName);
    m_Player->setSource(QUrl(fileName));

    m_Video = new QVideoWidget();
    m_Video->setParent(ui->groupBox_Video);
    m_Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
    m_Player->setVideoOutput(m_Video);
    m_Video->setVisible(true);
    m_Video->show();

    m_AudioOutput = new QAudioOutput;
    m_Player->setAudioOutput(m_AudioOutput);
    m_Volume = 0.5;
    ui->horizontalSlider_Volume->setValue(50);
    m_AudioOutput->setVolume(m_Volume);


}

void MainWindow::on_pushButton_Play_Pause_clicked(){
    if(m_Player->isPlaying()){
        m_Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        qDebug() << "Paused!";
    }
    else{
        m_Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        qDebug() << "Playing...";
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    if(m_Player->isPlaying()){
        m_Player->stop();
    }
    else{
        qDebug() << "Already Stopped!!";
    }
}

void MainWindow::durationChanged(qint64 duration)
{
    m_Duration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(duration);
    QTime totalTime((m_Duration / 3600) % 60, (m_Duration / 60) % 60, (m_Duration % 60), (m_Duration * 1000) % 1000);
    QString format = "mm:ss";
    if(m_Duration > 3600){
        format = "hh:mm:ss";
    }
    ui->label_totalTime->setText(totalTime.toString(format));
}

void MainWindow::positionChanged(qint64 progress)
{
    progress = progress / 1000;
    QTime CurrentTime((progress / 3600) % 60, (progress / 60) % 60, (progress % 60), (progress * 1000) % 1000);
    //qDebug() << CurrentTime;
    QString format = "mm:ss";
    if(m_Duration > 3600){
        format = "hh:mm:ss";
    }
    ui->label_positionTime->setText(CurrentTime.toString(format));

    if(!ui->horizontalSlider_Duration->isSliderDown()){
        ui->horizontalSlider_Duration->setValue(progress*1000);
    }
}

void MainWindow::on_horizontalSlider_Duration_sliderPressed()
{
    qint64 value = ui->horizontalSlider_Duration->value();
    m_Player->setPosition(value);
}

void MainWindow::on_pushButton_SeekBackward_clicked()
{
    qint64 value = m_Player->position();
    m_Player->setPosition(value - 1000);
}


void MainWindow::on_pushButton_SeekForward_clicked()
{
    qint64 value = m_Player->position();
    m_Player->setPosition(value + 1000);
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    m_Volume = double(value)/100;
    m_AudioOutput->setVolume(m_Volume);
    qDebug() << "Volume: " << m_Volume;
}


void MainWindow::on_pushButton_Mute_clicked()
{
    if(m_AudioOutput->isMuted()){
        m_AudioOutput->setMuted(false);
        ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        qDebug() << "Unmuted";
    }
    else{
        m_AudioOutput->setMuted(true);
        ui->pushButton_Mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        qDebug() << "Muted";
    }
}

