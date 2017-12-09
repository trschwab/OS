#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"
#include "dlist.h"
#include <math.h>

#define R 50
#define tVal 1.675

double trial(int alg, int seed, int requests);
double average(double *list);
double standardDev(double *list, double mean);
double lowC(double mean, double z, double s, double n);
double highC(double mean, double z, double s, double n);

int main(int argc, char *argv[]) { 

    if (argc != 4) {
        printf("Usage: ./frag-eval [algorithm] [seed] [requests]\n");// [trials]\n");
        return(-1);
    }

    //int alg = atoi(argv[1]);
    int seed = atoi(argv[2]);
    int requests = atoi(argv[3]);
    //int trials = atoi(argv[4]); 

    char *filename;
    filename = "./bin/exp-results.csv";
    FILE *f = fopen("./bin/exp-results.csv", "w+");
    fprintf(f, "Algorithm, Seed, Requests, Value");
    int trials;
    double listZ[R];
    double listO[R];
    double listT[R];
    int two = 2;
    while (two >= 0) {
        trials = R; 
        while (trials != 0) { 
            double value = trial(two, seed, requests);
            fprintf(f, "\n%d, %d, %d, %f", two, seed, requests, value);
            seed ++;  
            if (two == 2) {
                listT[trials] = value;
            } else if (two == 1) {
                listO[trials] = value;
            } else {
                listZ[trials] = value;
            }
            trials--;
        }
        --two;
    }
 
    double AO = average(listO);
    double AT = average(listT);
    double AZ = average(listZ);
    fprintf(f, "\nAverage0, Average1, Average2");
    fprintf(f, "\n%f, %f, %f", AZ, AO, AT);

    double SO = standardDev(listO, AO);
    double ST = standardDev(listT, AT);
    double SZ = standardDev(listZ, AZ);
    fprintf(f, "\nSx0, Sx1, Sx2");
    fprintf(f, "\n%f, %f, %f", SZ, SO, ST);


    printf("CI0 %f to %f\n", lowC(AO, tVal, SO, R), highC(AO, tVal, SO, R));
    printf("CIT %f to %f\n", lowC(AT, tVal, ST, R), highC(AT, tVal, ST, R));
    printf("CIZ %f to %f\n", lowC(AZ, tVal, SZ, R), highC(AZ, tVal, SZ, R));
    fprintf(f, "\nConfidence Interval Algorithm Zero, %f, %f", lowC(AZ, tVal, SZ, R), highC(AZ, tVal, SZ, R));
    fprintf(f, "\nConfidence Interval Algorithm One, %f, %f", lowC(AO, tVal, SO, R), highC(AO, tVal, SO, R));
    fprintf(f, "\nConfidence Interval Algorithm Two, %f, %f", lowC(AT, tVal, ST, R), highC(AT, tVal, ST, R));

    fclose(f);
    return(0);
}

double lowC(double mean, double z, double s, double n) {
    return( (mean - z * (s / sqrt( (double) n)) ) );
}

double highC(double mean, double z, double s, double n) {
    return( (mean + z * (s / sqrt( (double) n)) ) );
}

double standardDev(double *list, double mean) {
    int n = R - 1;
    double sum = 0;
    while (n >= 0) {
        double a = pow((list[n] - mean), 2); 
        sum += a;
        n--;
    }
    return( sqrt(sum * (1/ (double) R)));
}

double average(double *list) { 
    int n = R - 1;
    double sum = 0;
    while (n >= 0) { 
        sum += list[n];
        n --;
    }
    return(sum / R);
}

double trial(int alg, int seed, int requests) {
    struct dnode *requestsAllo[requests];

    int i;
    for (i = 0; i < requests ; i++ ){
        requestsAllo[i] = NULL;
    }

    srand(seed);

    int r = 0;
    int s;
    int d;
    struct dnode *p;

    allocator_init(10240, alg);

    while( r < requests) {
        s = (rand() % 900) + 101;
        d = s % requests;
        p = allocate(s);
        if (requestsAllo[d] != NULL) {
            deallocate(requestsAllo[d]->data);
            requestsAllo[d] = NULL;
        }
        r++;
    }
    return( average_frag() );
}
