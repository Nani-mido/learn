#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/belarbi", tr("Image Files (*.png *.jpeg *.jpg *.bmp)"));
    QPixmap image(fileName);
    ui->label_2->setPixmap(image);

}

void MainWindow::on_pushButton_2_clicked()
{
    Mat image;
    image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    waitKey(0);
}
*/
void MainWindow::on_pushButton_3_clicked()
{
    Mat img;
    img = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
    //SHOWHISTOGRAM_H(image)

    int nb = 256;             // number of bins
        int nc = img.channels();    // number of channels

        vector<Mat> hist(nc);       // histogram arrays

        // Initalize histogram arrays
        for (int i = 0; i < hist.size(); i++)
            hist[i] = Mat::zeros(1, nb, CV_32SC1);//CV_32SC1 = 32-bits float

        // Calculate the histogram of the image
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)

            {
                for (int k = 0; k < nc; k++)
                {
                    if (nc==1)
                    uchar val = img.at<uchar>(i,j);
                    else{
                    uchar val = img.at<Vec3b>(i,j)[k];
                    hist[k].at<int>(val) += 1;
                    }
                }
            }
        }

        // For each histogram arrays, obtain the maximum (peak) value
        // Needed to normalize the display later
        int hmax[3] = {0,0,0};
        for (int i = 0; i < nc; i++)
        {
            for (int j = 0; j < nb-1; j++)
                hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
        }

        const char* wname[3] = { "blue", "green", "red" };
        Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

        vector<Mat> canvas(nc);

        // Display each histogram in a canvas
        for (int i = 0; i < nc; i++)
        {
            canvas[i] = Mat::ones(125, nb, CV_8UC3);

            for (int j = 0, rows = canvas[i].rows; j < nb; j++)
            {
                line(
                    canvas[i],
                    Point(j, rows),
                    Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                    nc == 1 ? Scalar(200,200,200) : colors[i],
                    1, 8, 0
                );
            }

            imshow(nc == 1 ? "value" : wname[i], canvas[i]);
        }


}



void MainWindow::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/belarbi", tr("Image Files (*.png *.jpeg *.jpg *.bmp)"));
    QPixmap image(fileName);
    ui->label->setPixmap(image);
}

void MainWindow::on_pushButton_2_clicked()
{
    Mat img;
    img = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", img );                   // Show our image inside it.
    waitKey(0);
    //////////////////////////
}
