#ifndef WEAPON_H
#define WEAPON_H


enum class Weapon_type{none, pistol, shotgun, machine_gun, rail_gun, num_weapons};

class Weapon
{
    public:
        Weapon(Weapon_type type, double damage,
                       double shoot_delay, double spawn_probability);

        double damage(){return damage_;}
        void set_damage(double damage){damage_ = damage;}
        int Getshoot_delay(){return shoot_delay_;}
        void set_shoot_delay(int shoot_delay){shoot_delay_ = shoot_delay;}
        Weapon_type type(){return type_;}
        void set_type(Weapon_type type){type_ = type;}

    private:
        double damage_;
        int shoot_delay_;
        Weapon_type type_;
        double spawn_probability_;
};

#endif // WEAPON_H
