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
} ;


int main () {
    // std::string name = "Me" ;
    // rider myrider (name, 75);
    // myrider.power = 200 ;
    // myrider.gradient = 0.085 ;
    // while (myrider.pos_y < 1046) {
    //     myrider.update();
    // }
    // std::cout << "Time: " ;
    // std::cout << (myrider.time)/60 << std::endl ;
    // std::cout << "Speed: " ;
    // std::cout << (myrider.vel)*3.6 << std::endl ;

    return 0 ;
}
