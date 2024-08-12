#include "limits_of_detection.hpp"
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <iostream>

namespace LOD {

float calculateActivityLLD(float detector_surface_area, float LLD){
    return (detector_surface_area*LLD)/60;
}


float calculateDwellTime(float activityLLD, float efficiency, float relative_std){
    return 1 / (activityLLD * efficiency * std::pow(relative_std,2));
}


float calculateDetectorVelocity(float activityLLD, float efficiency, float detector_length, float relative_std){
    return (activityLLD * efficiency * detector_length* std::pow(relative_std,2));
}


float calculateLC(float alpha, float bckg_count_rate, float bckg_count_time){
    const boost::math::normal_distribution<> norm_dist(0, 1);
    const double K_alpha = std::abs(boost::math::quantile(norm_dist, alpha/100));
    return bckg_count_rate + (K_alpha * sqrt(bckg_count_rate/bckg_count_time));
}


float calculateLD(float Lc, float alpha, float beta, float measured_dwell_time){
    const boost::math::normal_distribution<> norm_dist(0, 1);
    const double K_alpha = std::abs(boost::math::quantile(norm_dist, alpha/100));
    const double K_beta = std::abs(boost::math::quantile(norm_dist, beta/100));

    // Terms used in calculating the Limit of Detection
    const float first = (std::pow(K_beta,2))/2;
    const float second_third = 1/measured_dwell_time;   // same term is used in the second and third
    const float fourth = (4*Lc) / ( (std::pow(K_beta,2)) * measured_dwell_time);
    const float fifth = ( 4*(std::pow(Lc,2)) ) / ((std::pow(K_alpha*K_beta,2)) );

    return Lc + first * (second_third + sqrt(second_third + fourth + fifth));
}

}   // LOD namespace
