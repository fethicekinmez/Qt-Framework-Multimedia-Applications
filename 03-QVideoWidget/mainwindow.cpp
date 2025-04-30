#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_Open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.MP4)"));
    m_Player = new QMediaPlayer();
    QFileInfo File(fileName);
    ui->label_FileNameValue->setText(File.fileName());
    m_Player->setSource(QUrl(fileName));

    m_Video = new QVideoWidget();
    m_Video->setGeometry(20,20,640,480);
    m_Player->setVideoOutput(m_Video);

    QAudioOutput *m_audioOutput;
    m_audioOutput = new QAudioOutput;
    m_Player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5);
}


void MainWindow::on_pushButton_Play_clicked()
{
    m_Video->show();
    m_Player->play();
    m_Video->setAspectRatioMode(Qt::AspectRatioMode::KeepAspectRatioByExpanding);

}

void MainWindow::on_pushButton_Pause_clicked()
{
    m_Player->pause();
    qDebug() << m_Video->aspectRatioMode();
}


void MainWindow::on_pushButton_fullScreen_clicked()
{
    if(!m_Video->isFullScreen()){
        m_Video->setFullScreen(true);
    }
    else{
        m_Video->setFullScreen(false);
    }

}

