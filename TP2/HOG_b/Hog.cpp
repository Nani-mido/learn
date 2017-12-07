
/*
 * Hog.cpp
 *
 *  Created on: 21 janv. 2016
 *      Author: benoit
 */

#include "Hog.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

Hog::Hog(int cells, int blocks, int bins)
{
    if(cells < 1 || blocks < 1 || bins < 1)
    {
        cout << "Error bins, cells and blocks must be positive\n";
        exit (EXIT_FAILURE);
    }
    m_cells = sqrt(cells);
    m_blocks = sqrt(blocks);
    m_bins = bins;

    //m_vec_bins.resize(m_blocks);
    m_is_compute = false;
}

Hog::~Hog() {
    // TODO Auto-generated destructor stub
}


vector<double> Hog::compute(Mat img, const int rows, const int cols, Mat &grad)
{
    //cout << img.size() << endl;
    fill(m_vec_bins.begin(), m_vec_bins.end(), 0);
    resize(img, img, Size(cols, rows));
    /*const int cols = img.cols;
    const int rows = img.rows;*/
    grad.create(img.size(), CV_8UC1);
    m_mat_theta.create(img.size(), CV_8UC1);
    //cout << m_mat_theta.size() << endl;
    std::vector<cv::Mat> channels;
    bool color = false;
    if(img.channels() > 1)
    {
        color = true;
        split(img, channels);
    }
    else
        channels.push_back(img);

    uchar* pixel_r;//red or gray
    uchar* pixel_g;
    uchar* pixel_b;
    Point value_r;
    Point value_g;
    Point value_b;

    for(int i = 0; i < rows; ++i)
    {
        pixel_r = channels[0].ptr(i);
        if(color)
        {
            pixel_g = channels[1].ptr(i);
            pixel_b = channels[2].ptr(i);
        }
        for(int j = 0; j < cols; ++j)
        {
            //grad_x
            if(j == 0)
            {
                value_r.x = -((int)*pixel_r);
                pixel_r++;
                value_r.x += ((int)*pixel_r);
                pixel_r--;
                if(color)
                {
                    value_g.x = -((int)*pixel_g);
                    pixel_g++;
                    value_g.x += ((int)*pixel_g);
                    pixel_g--;
                    value_b.x = -((int)*pixel_b);
                    pixel_b++;
                    value_b.x += ((int)*pixel_b);
                    pixel_b--;
                }
            }
            if(j >= (cols-1))
            {
                value_r.x = ((int)*pixel_r);
                pixel_r--;
                value_r.x -= ((int)*pixel_r);
                pixel_r++;
                if(color)
                {
                    value_g.x = ((int)*pixel_g);
                    pixel_g--;
                    value_g.x -= ((int)*pixel_g);
                    pixel_g++;
                    value_b.x = ((int)*pixel_b);
                    pixel_b--;
                    value_b.x -= ((int)*pixel_b);
                    pixel_b++;
                }
            }
            if(j != 0 && j < (cols-1))
            {
                pixel_r--;
                value_r.x = -((int)*pixel_r);
                pixel_r+=2;
                value_r.x += ((int)*pixel_r);
                pixel_r--;
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
                if(color)
                {
                    pixel_g--;
                    value_g.x = -((int)*pixel_g);
                    pixel_g+=2;
                    value_g.x += ((int)*pixel_g);
                    pixel_g--;
                    pixel_b--;
                    value_b.x = -((int)*pixel_b);
                    pixel_b+=2;
                    value_b.x += ((int)*pixel_b);
                    pixel_b--;
                }
                #pragma GCC diagnostic pop
            }
            //grad_y
            if(i == 0)
            {
                value_r.y = -((int)*pixel_r);
                pixel_r = channels[0].ptr(i+1);
                pixel_r+=j;
                value_r.y += ((int)*pixel_r);
                pixel_r = channels[0].ptr(i);
                pixel_r+=j;
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
                if(color)
                {
                    value_g.y = -((int)*pixel_g);
                    pixel_g = channels[1].ptr(i+1);
                    pixel_g+=j;
                    value_g.y += ((int)*pixel_g);
                    pixel_g = channels[1].ptr(i);
                    pixel_g+=j;
                    value_b.y = -((int)*pixel_b);
                    pixel_b = channels[2].ptr(i+1);
                    pixel_b+=j;
                    value_b.y += ((int)*pixel_b);
                    pixel_b = channels[2].ptr(i);
                    pixel_b+=j;
                }
                #pragma GCC diagnostic pop
            }
            if(i >= rows-1)
            {
                value_r.y = ((int)*pixel_r);
                pixel_r = channels[0].ptr(i-1);
                pixel_r+=j;
                value_r.y -= ((int)*pixel_r);
                pixel_r = channels[0].ptr(i);
                pixel_r+=j;
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
                if(color)
                {
                    value_g.y = ((int)*pixel_g);
                    pixel_g = channels[1].ptr(i-1);
                    pixel_g+=j;
                    value_g.y -= ((int)*pixel_g);
                    pixel_g = channels[1].ptr(i);
                    pixel_g+=j;
                    value_b.y = ((int)*pixel_b);
                    pixel_b = channels[2].ptr(i-1);
                    pixel_b+=j;
                    value_b.y -= ((int)*pixel_b);
                    pixel_b = channels[2].ptr(i);
                    pixel_b+=j;
                }
                #pragma GCC diagnostic pop
            }
            if(i != 0 && i < rows-1)
            {
                pixel_r = channels[0].ptr(i-1);
                pixel_r+=j;
                value_r.y -= ((int)*pixel_r);
                pixel_r = channels[0].ptr(i+1);
                pixel_r+=j;
                value_r.y += ((int)*pixel_r);
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
                if(color)
                {
                    pixel_g = channels[1].ptr(i-1);
                    pixel_g+=j;
                    value_g.y -= ((int)*pixel_g);
                    pixel_g = channels[1].ptr(i+1);
                    pixel_g+=j;
                    value_g.y += ((int)*pixel_g);
                    pixel_b = channels[2].ptr(i-1);
                    pixel_b+=j;
                    value_b.y -= ((int)*pixel_b);
                    pixel_b = channels[2].ptr(i+1);
                    pixel_b+=j;
                    value_b.y += ((int)*pixel_b);
                }
                #pragma GCC diagnostic pop
            }
            int is_max_grad = 0;
            double max_grad = sqrt(pow(value_r.x,2) + pow(value_r.y,2));
            if(color)
            {
                if(max_grad < max(max_grad, sqrt(pow(value_g.x,2) + pow(value_g.y,2))))
                {
                    is_max_grad = 1;
                    max_grad = max(max_grad, sqrt(pow(value_g.x,2) + pow(value_g.y,2)));
                }
                if(max_grad < max(max_grad, sqrt(pow(value_b.x,2) + pow(value_b.y,2))))
                {
                    is_max_grad = 2;
                    max_grad = max(max_grad, sqrt(pow(value_b.x,2) + pow(value_b.y,2)));
                }
            }
            //cout << max_grad << endl;
            grad.at<uchar>(i,j) = max_grad;
            double theta = 0;
            switch(is_max_grad)
            {
            case 0:
                theta = atan2(value_r.y,value_r.x);
                break;
            case 1:
                theta = atan2(value_g.y,value_g.x);
                break;
            case 2:
                theta = atan2(value_b.y,value_b.x);
                break;
            }
            if(theta < 0)
            {
                theta += M_PI;
            }
            classify(theta, i, j);
            //Increment pixel
            pixel_r++;
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            if(color)
            {
                pixel_g++;
                pixel_b++;
            }
            #pragma GCC diagnostic pop
            //reinit
            value_r = Point(0,0);
            value_g = Point(0,0);
            value_b = Point(0,0);
        }
    }
    compute_cells(grad);
    compute_blocks();
    m_vec_bins.resize(m_vec_theta_blocks.size()*pow(m_blocks,2)*m_bins);
    for(uint i = 0; i < m_vec_theta_blocks.size(); ++i)
    {
        /*double max = 0;
        int pos = 0;*/
        for(uint j = 0; j < m_vec_theta_blocks[i].size(); ++j)
        {
            m_vec_bins[i*(pow(m_blocks,2)*m_bins)+j] = m_vec_theta_blocks[i][j];
            /*if(m_vec_theta_blocks[i][j] > max)
            {
                max = m_vec_theta_blocks[i][j];
                pos = j;
            }*/
        }
        //m_vec_bins[i] = pos;
    }
    /*int max = 0;
    for(int i = 0; i < m_vec_bins.size(); ++i)
    {
        if(max < m_vec_bins[i])
        {
            max = m_vec_bins[i];
        }
    }
    for(int i = 0; i < m_vec_bins.size(); ++i)
    {
        m_vec_bins[i]/=max;
    }*/
    m_is_compute = true;
    return m_vec_bins;
}


Mat Hog::draw()
{
    if(m_is_compute == false)
    {
        cout << "Error, use compute before draw" << endl;
        exit(-1);
    }

    Mat img(m_mat_theta.rows, m_mat_theta.cols, CV_8UC1, Scalar::all(0));
    vector< vector<double> > copy = m_vec_theta_cells;
    for(uint i = 0; i < m_vec_theta_cells.size(); ++i)
    {
        int max = 0;
        for(uint j = 0; j < m_vec_theta_cells[i].size(); ++j)
        {
            if(m_vec_theta_cells[i][j] > max)
                max = m_vec_theta_cells[i][j];
        }
        for(uint j = 0; j < m_vec_theta_cells[i].size(); ++j)
            copy[i][j]/=max;
    }
    int j = 0;
    int ii = 0;
    for(uint i = 0; i < m_vec_theta_cells.size(); ++i, ++ii)
    {
        if(i != 0 && i%(img.cols/m_cells) == 0)
        {
            j++;
            ii = 0;
        }
        for(uint l = 0; l < m_vec_theta_cells[i].size(); ++l)
        {
            double angle = l*M_PI/m_bins;
            double value = copy[i][l];
            float x = (ii+0.25)*(m_cells);
            float y = (j+0.25)*(m_cells);
            angle += (M_PI/2);
            Point pt1(x-5*cos(angle), y-5*sin(angle));
            Point pt2(x+5*cos(angle), y+5*sin(angle));
            //if(value >= 1)
            line(img, pt1, pt2, Scalar::all(value*255));
        }
    }
    return img;
}

void Hog::classify(double theta, int x, int y)
{
    double range = M_PI/m_bins;

    for(int i = 0; i < m_bins; ++i)
    {
        if(theta >= i*range && theta < (i+1)*range)
        {
            m_mat_theta.at<uchar>(x,y) = i;
        }
        if(theta == M_PI)
        {
            m_mat_theta.at<uchar>(x,y) = m_bins-1;
        }
    }
}

void Hog::compute_cells(const Mat grad)
{
    m_vec_theta_cells.clear();

    for(int h = 0; h < m_mat_theta.rows/m_cells; ++h)
    {
        for(int k = 0; k < m_mat_theta.cols/m_cells; ++k)
        {
            vector<double> local_hist(m_bins, 0);
            for(int i = 0; i < m_cells; ++i)
            {
                for(int j = 0; j < m_cells; ++j)
                {
                    int index = Scalar(m_mat_theta.at<uchar>(h*m_cells+i,k*m_cells+j))[0];
                    local_hist[index]+=Scalar(grad.at<uchar>(h*m_cells+i,k*m_cells+j))[0];
                }
            }
            m_vec_theta_cells.push_back(local_hist);

        }
    }

}

void Hog::compute_blocks()
{
    m_vec_theta_blocks.clear();
    int cols = m_mat_theta.cols/m_cells;
    for(int i = 0; (uint)i < m_vec_theta_cells.size()-(m_blocks-1)*cols; ++i)
    {
        vector<double> local_hist(pow(m_blocks,2)*m_bins, 0);
        if((i+(m_blocks-1))%cols >= (m_blocks-1))//condition aux limites
        {
            int cells = 0;
            for(int j = 0; j < m_blocks; ++j)//cols blocks
            {
                for(int jj = 0; jj < m_blocks; ++jj)//rows blocks
                {
                    for(int h = 0; h < m_bins; ++h)
                    {
                        local_hist[cells*m_bins+h] += m_vec_theta_cells[i+j+jj*cols][h];
                    }
                    cells++;
                }
            }

            double norm = 0;
            for(uint l = 0; l < local_hist.size(); ++l)
            {
                norm += pow(local_hist[l], 2);
            }
            norm = sqrt(norm);
            for(uint l = 0; l < local_hist.size(); ++l)
            {
                local_hist[l]/=(norm + std::numeric_limits<double>::epsilon());
            }
            m_vec_theta_blocks.push_back(local_hist);
        }
    }
}


