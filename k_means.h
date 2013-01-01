#ifndef K_MEANS_H
#define K_MEANS_H

#include <vector>

class KMeans {
public:
    KMeans(double **matrix, int &a, int &b, int &c);

    ~KMeans();

    void clusterize(int &step);

    // calculation dissimilarity between points with euclidean disatnce 
    double euclidean_distance(double a_1, double b_1, 
                              double a_2, double b_2,
                              double a_3, double b_3);

    void update_centroid();

    void output_data();

private:
    // the number of clusters
    int     k;

    // the dimension of data
    int     dimension;

    // the sum number of point
    int     point_num;
    
    // all points extract from image
    double  **point_set;

    // store centroid information B G R value
    double  **centroids;

    double  **copy_centroids;

    // store cluster points
    std::vector< std::vector<int> > clusters;
};

#endif
