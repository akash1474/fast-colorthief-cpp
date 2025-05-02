#pragma once
#include "vector"
#include "constants.hpp"


int get_color_index(int r, int g, int b);

class VBox {
public:
    VBox(int r1, int r2, int g1, int g2, int b1, int b2, std::vector<int>& histo) :
        r1(r1), r2(r2), g1(g1), g2(g2), b1(b1), b2(b2), histo(histo),
        avg_initialized(false), count_initialized(false) {}

    
    VBox& operator=(const VBox& other) {
        r1 = other.r1;
        g1 = other.g1;
        b1 = other.b1;
        r2 = other.r2;
        g2 = other.g2;
        b2 = other.b2;
        // ignore histo, it is always the same

        avg_cache = other.avg_cache;
        avg_initialized = other.avg_initialized;
        count_cache = other.count_cache;
        count_initialized = other.count_initialized;
        return *this;
    }
    

    int volume() {
        int sub_r = r2 - r1;
        int sub_g = g2 - g1;
        int sub_b = b2 - b1;
        return (sub_r + 1) * (sub_g + 1) * (sub_b + 1);
    }

    VBox copy() {return VBox(r1, r2, g1, g2, b1, b2, histo);}

    color_t avg() {if (!avg_initialized) {init_avg();} return avg_cache;}

    int count() {if (!count_initialized) {init_count();} return count_cache;}

    void init_avg() {
        int ntot = 0;
        int mult = 1 << (8 - SIGBITS);
        double r_sum = 0;
        double g_sum = 0;
        double b_sum = 0;

        for (int i=r1; i<r2 + 1; i++) {
            for (int j=g1; j<g2 + 1; j++) {
                for (int k=b1; k<b2 + 1; k++) {
                    int histoindex = get_color_index(i, j, k);
                    int hval = histo[histoindex];
                    ntot += hval;
                    r_sum += hval * (i + 0.5) * mult;
                    g_sum += hval * (j + 0.5) * mult;
                    b_sum += hval * (k + 0.5) * mult;
                }
            }
        }

        int r_avg;
        int g_avg;
        int b_avg;

        if (ntot > 0) {
            r_avg = int(r_sum / ntot);
            g_avg = int(g_sum / ntot);
            b_avg = int(b_sum / ntot);
        } else {
            r_avg = int(mult * (r1 + r2 + 1) / 2.0);
            g_avg = int(mult * (g1 + g2 + 1) / 2.0);
            b_avg = int(mult * (b1 + b2 + 1) / 2.0);
        }

        avg_cache = {uint8_t(r_avg), uint8_t(g_avg), uint8_t(b_avg)};
        avg_initialized = true;
    }

    void init_count() {
        int npix = 0;
        for (int i=r1; i<r2 + 1; i++) {
            for (int j=g1; j<g2 + 1; j++) {
                for (int k=b1; k<b2 + 1; k++) {
                    int index = get_color_index(i, j, k);
                    npix += histo[index];
                }
            }
        }
        count_cache = npix;
        count_initialized = true;
    }

    int r1;
    int r2;
    int g1;
    int g2;
    int b1;
    int b2;
    std::vector<int>& histo;

    color_t avg_cache;
    bool avg_initialized;
    int count_cache;
    bool count_initialized;
};