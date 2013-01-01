#include "k_means.h"
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <fstream>

#define MAXPIXEL 255

using namespace std;

KMeans::KMeans(double **matrix, int &a, int &b, int &c) {
    int index;
    point_num = a;
    dimension = b;
    k = c;
    clusters.resize(k);

    point_set = new double *[point_num];

    for (int i = 0; i < point_num; i++)
        point_set[i] = new double[dimension];
    
    if (point_set != NULL) {
        for (int i = 0; i < point_num; i++)
            for (int j = 0; j < dimension; j++)
                point_set[i][j] = matrix[i][j] / MAXPIXEL;
    }

    centroids       = new double *[k];
    copy_centroids  = new double *[k];

    srand(time(NULL));
    for (int i = 0; i < k; i++) {
        index = rand() % point_num; 

        centroids[i] = new double[dimension];
        copy_centroids[i] = new double[dimension];
    
        if (centroids != NULL && copy_centroids != NULL) {
            for (int j = 0; j < dimension; j++)
                centroids[i][j] = point_set[index][j];
        }
    }
}

KMeans::~KMeans() {
    for (int i = 0; i < point_num; i++) {
        delete [] point_set[i];
    }
    delete [] point_set;

    for (int i = 0; i < k; i++) {
        delete [] centroids[i]; 
    }
    delete [] centroids;

    for (int i = 0; i < k; i++) {
        delete [] copy_centroids[i]; 
    }
    delete [] copy_centroids;
}

double KMeans::euclidean_distance(double a_1, double b_1,
                                  double a_2, double b_2,
                                  double a_3, double b_3) {
    double distance = 0;

    distance = pow(fabs(a_1 - b_1), 2) + pow(fabs(a_2 - b_2), 2) + pow(fabs(a_3 - b_3), 2);

    return sqrt(distance);
}

void KMeans::clusterize(int &step) {
    int flag = true;
    int id = 0;
    double sum = 0;
    double min_distance = 0;
    double *distance = new double[k];
    
    while (flag) {
        step++;

        for (int j = 0; j < k; j++) {
            clusters[j].clear();
        }
        for (int i = 0; i < point_num; i++) {
            for (int j = 0; j < k; j++) {
                distance[j] = euclidean_distance(
                                point_set[i][0], centroids[j][0],
                                point_set[i][1], centroids[j][1],
                                point_set[i][2], centroids[j][2]);
            }
        
            id = 0;
            min_distance = distance[0];
            for (int j = 1; j < k; j++) {
                if (distance[j] < min_distance) {
                    min_distance = distance[j]; 
                    id = j;
                }
            }

            clusters[id].push_back(i);
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < dimension; j++) {
                copy_centroids[i][j] = centroids[i][j];
            }
        }

        update_centroid();

        sum = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < dimension; j++) {
                sum += copy_centroids[i][j] - centroids[i][j];
            }
        }
         
        if (sum == 0)
            flag = false;
    }
    
    output_data();

    delete [] distance;
}

void KMeans::update_centroid() {
    double sum = 0;

    for (int d = 0; d < dimension; d++) {
        for (int i = 0; i < k; i++) {
            sum = 0; 
            for (int j = 0; j < clusters[i].size(); j++) {
                sum += point_set[clusters[i][j]][d];
            }
            centroids[i][d] = sum / clusters[i].size();
        }
    }
}

void KMeans::output_data() {
    vector<int>::iterator p;
    fstream out_file("result.dat", ios::out);

    for (int i = 0; i < k; i++) {
        out_file << "> clustering result " << i << " "
                 << "size: " << clusters[i].size() << "\n\n";

        for (p = clusters[i].begin(); p < clusters[i].end(); p++) {
            out_file << *p << " " << point_set[*p][0] * MAXPIXEL << " "
                                  << point_set[*p][1] * MAXPIXEL << " "
                                  << point_set[*p][1] * MAXPIXEL << "\n";
        }

        out_file << "\n";
    }

    out_file.close();
}





