#pragma once

/*! \file Hog.hpp
 * Calcul les caractéristiques de HOG
 *
 *  \date 21 janvier 2016
 *      \author Benoit Braeckeveldt
 * \class Hog
 *
 * Calcul les caractéristiques de HOG
 *
 *  \date 21 janvier 2016
 *      \author Benoit Braeckeveldt
 */



//OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
//C++
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits>
#include <omp.h>

using namespace cv;
using namespace std;



class Hog {
public:
    Hog(int cells, int blocks, int bins);/**<Constructeur.<BR>
    * \param cells nombre de pixels par cellules
    * \param blocks nombre de cellules par blocs
    * \param bins nombre de catégories d'histogramme
    */
    virtual ~Hog();

    vector<double> compute(Mat img, const int rows, const int cols, Mat &grad);/**<Calcul l'histogramme normalisé.<BR>
    * \param img image à traiter</li>
    * \param rows nombre de lignes pour le redimensionnement
    * \param cols nombre de colonnes pour le redimensionnement
    * \param grad image de retour contenant l'intensité des gradients
    * \return Vecteur contenant l'histogrammes normaliés des blocs.
    */

    Mat draw();/**<Dessin de l'histogramme des gradients par bloc.<BR>
    *  \return Matrice contenant les histogrammes par bloc.<BR>
    *  <em>Notes</em> : exécuter au préalable Hog::compute*/

private:
    bool m_is_compute;/**<Test si la fonction compute a déjà été utilisé.*/
    int m_cells;/**<Taille des cellules (en pixel) pour les caractéristiques de HOG.*/
    int m_blocks;/**<Taille des blocs (en cellule) pour les caractéristiques de HOG.*/
    int m_bins;/**<Nombre de catégories d'histogrammes pour les caractéristiques de HOG.*/
    vector<double> m_vec_bins;/**<Vecteur normalisé de l'histogramme.*/
    Mat m_mat_theta;/**<Angle calculé pour tout pixel.*/
    vector< vector<double> > m_vec_theta_cells;/**<Histogramme par cellules.*/
    vector< vector<double> > m_vec_theta_blocks;/**<Histogramme par blocs.*/

    void classify(double theta, int i, int j);/**<Classification des angles dans une matrice (Hog::m_mat_theta).<BR>
    * \param theta angle à classifier
    * \param i ligne de la matrice où l'on place la catégorie de l'angle
    * \param j ligne de la matrice où l'on place la catégorie de l'angle*/
    void compute_cells(const Mat grad);/**<Classification des angles par cellules.<BR>
    * \param grad matrice d'intensité des gradients*/
    void compute_blocks();/**<Classification des angles par blocs.*/
};


