#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "k_means.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    IplImage    *img = NULL;
    double      **point_set = NULL;
    int         point_num = 0;
    int         k = 5;
    int         step = 0;
    int         wid, hei, dim;

    if (argc == 1) {
        cout << "No input file!\nUsage: " << argv[0]
             << " [FILENAME] " << " k " << std::endl;
    } else if (argc >= 2 && (img = cvLoadImage(argv[1], 1)) != 0) {
        if (argv[2] != 0)
            k = atoi(argv[2]);
        wid = img->width;
        hei = img->height;
        dim = img->nChannels;
        point_num = wid * hei;

        point_set = new double*[point_num];

        for (int i = 0; i < point_num; i++)
            point_set[i] = new double[dim];

        for (int i = 0; i < hei; i++) {
            for (int j = 0; j < wid; j++) {
                CvScalar pixel = cvGet2D(img, i, j);
                for (int n = 0; n < dim; n++) {
                    point_set[i*wid + j][n] = pixel.val[n];
                }
            }
        }
        
        cout << "start clustring......" << "\n";
        KMeans cluster(point_set, point_num, dim, k); 
        cluster.clusterize(step);
        cout << "Output information: " << "\n";
        cout << "> Number of point: " << point_num << "\n";
        cout << "> Number of cluster: " << k << "\n";
        cout << "> Number of iteration: " << step << "\n";
    }          

    for (int i = 0; i < point_num; i++) {
        delete [] point_set[i];
    }
    delete [] point_set;

    cvReleaseImage(&img);

    return 0;
}

