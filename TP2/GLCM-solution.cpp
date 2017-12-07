#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void glcm(Mat &img, const int &msize);
string type2str(int type);

int main()
{

    Mat img=imread("593.jpg",CV_LOAD_IMAGE_COLOR);            //input image


    if(img.empty())
    {
        cout<<"no image";
        return 0;
    }

    namedWindow("Image",CV_WINDOW_AUTOSIZE);
    imshow("Image",img);

   cvtColor(img, img, CV_BGR2GRAY);

    glcm(img, 8);

    waitKey(0);
    return 0;

}


void glcm(Mat &img, const int &msize )

{cout<<"\n\n==============================================="<<endl;
    cout << "The size of the GLCM : " <<msize<<endl;
     cout << "The image type : " << type2str(img.type()) <<endl;

    float energy=0, contrast=0, homogenity=0, dissimilarity=0, correlation=0, clustershade=0, IDM=0,entropy=0,mean1=0;
    int row=img.rows,col=img.cols;

    Mat gl=Mat::zeros(msize,msize,CV_32FC1);

    //creating glcm matrix with msize levels,radius=1 and in the horizontal direction
    for(int i=0;i<row;i++)
        for(int j=0;j<col-1;j++){

            int v0 = (int)( (double)msize * (uchar)img.at<uchar>(i, j)    / 256.0 ) ;
            int v1 = (int)( (double)msize * (uchar)img.at<uchar>(i, j+1)  / 256.0 ) ;

            gl.at<float>(v0, v1)++;

        }

    // normalizing glcm matrix for parameter determination
    //gl=gl+gl.t();
    gl=gl/sum(gl)[0];



    // calculate mean and standard deviation using opencv function
    Scalar mean0, stdv;

    cv::meanStdDev(gl,mean0,stdv);
    cout << "Mean\t\t\tStdv"<<endl;
    cout << mean0 << "\t" << stdv<<endl;


    for(int i=0;i<msize;i++)
        for(int j=0;j<msize;j++)
        {

            energy += pow(gl.at<float>(i,j), 2);

            contrast += (i-j)*(i-j) * gl.at<float>(i,j);

            homogenity += gl.at<float>(i,j) / (1.0 + (abs(i - j))) ;

            dissimilarity += ( gl.at<float>(i,j) * abs(i-j));

            correlation += (i*j) * ( gl.at<float>(i,j) - (mean0[0]*mean0[0]));

            if(gl.at<float>(i,j)!=0)
                entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));

            mean1=mean1+0.5*(i*gl.at<float>(i,j)+j*gl.at<float>(i,j));

            clustershade += pow((float)((i - mean0[0]) + (j - mean0[0])),3) * gl.at<float>(i,j);

            if(i!=j)
                IDM=IDM+gl.at<float>(i,j)/((i-j)*(i-j));
        }

    cout<<"\n\n";
    cout<<"moyenne=\t\t"<<mean0(0)<<endl;
    cout<<"standard deviation=\t"<<stdv(0)<<endl;
    cout<<"energy=\t\t\t"<<energy<<endl;
    cout<<"contrast=\t\t"<<contrast<<endl;
    cout<<"homogenity=\t\t"<<homogenity<<endl;
    cout<<"dissimilarity=\t\t"<<dissimilarity<<endl;
    cout<<"correlation=\t\t"<<correlation<<endl;
    cout<<"entropy=\t\t"<<entropy<<endl;

    cout<<"clustershade=\t\t"<<clustershade<<endl;
    cout<<"mean1=\t\t\t"<<mean1<<endl;

    cout<<"IDM=\t\t\t"<<IDM<<endl;


    cout<<"\n\n";
}


string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}