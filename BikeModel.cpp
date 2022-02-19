#include <iostream>
#include <string>
#include <math.h>

float rho = 1.22601 ;
const float grav = 9.801 ;
const float drivetrain_loss = 0.02 ;

class rider {
    // Records current state of rider
    public:
        std::string name ;
        float mass_kg, Crr, CdA ; // combined mass of rider and bike, coefficient of rolling resistance, and coefficient of air resistance
        float pos_x, pos_y ; // x and y positions
        float vel ; // velocity along road
        float power ; // power output in watts
        float gradient ; // expressed as ratio, not as percentage
        float time ;

        rider (std::string& ridername, float ridermass, float Crr_def = 0.004, float Cda_def = 0.4) {
            name = ridername ;
            mass_kg = ridermass ;
            Crr = Crr_def , CdA = Cda_def ;
            pos_x = 0 , pos_y = 0 ;
            vel = 0 ;
            power = 0 ;
            gradient = 0 ;
            time = 0 ;
        }

        float power_at_wheel() {
            return (1-drivetrain_loss)*power ;
        }

        float lost_power_to_drag() {
            return 0.5*CdA*rho*vel*vel*vel ;
        }

        float lost_power_to_rolling() {
            float angle_correction = 1 / (1 + gradient*gradient) ; // equal to cos(arctan(gradient))
            return grav*mass_kg*Crr*vel*angle_correction ;
        }

        float lost_power_to_gravity() {
            float angle_factor = gradient / (1 + gradient*gradient) ; // equal to sin(arctan(gradient))
            return grav*mass_kg*vel*angle_factor ;
        }

        void update(float time_step=1) {
            float power_added = power_at_wheel() - lost_power_to_drag() - lost_power_to_rolling() - lost_power_to_gravity();
            time += time_step ;
            pos_x += vel*time_step*(1/(1+gradient*gradient)) ;
            pos_y += vel*time_step*(gradient/(1+gradient*gradient)) ;
            vel = sqrt(vel*vel + 2*(power_added/mass_kg)) ;
        }

        void reset(bool reset_power = true) {
            // resets rider to initial conditions, setting velocity, power, gradient, time, and position to 0.
            vel = 0 ;
            gradient = 0 ;
            time = 0 ;
            pos_x = 0 , pos_y = 0 ;
            if (reset_power) {
                power = 0 ;
            }
        }
} ;


int main () {
    // std::string nameA = "A",
    //             nameB = "B",
    //             nameC = "C",
    //             nameD = "D" ;
    // rider testriders[] = {rider(nameA, 80),
    //                       rider(nameB, 120),
    //                       rider(nameC, 80),
    //                       rider(nameD, 120)} ;
    // testriders[0].power = 200 ;
    // testriders[1].power = 200 ;
    // testriders[2].power = 300 ;
    // testriders[3].power = 300 ;
    // float grad_step = 0.01 ;
    // float speed_results[4][15] ;
    //
    // for (short i = 0; i < 15; i++) {
    //     for (short rider_ind = 0; rider_ind < 4; rider_ind++) {
    //         testriders[rider_ind].gradient = i*grad_step ;
    //         for (short t = 0; t < 60; t++) {
    //             testriders[rider_ind].update() ;
    //         }
    //         speed_results[rider_ind][i] = testriders[rider_ind].vel*3.6 ;
    //         if (rider_ind != 0) {
    //             std::cout << ", " ;
    //         }
    //         std::cout << testriders[rider_ind].vel*3.6 ;
    //         testriders[rider_ind].reset(false) ;
    //     }
    //     std::cout << "\n" ;
    // }


    return 0 ;
}
