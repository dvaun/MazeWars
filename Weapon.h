//test
class Weapon{
    int max_ammo;
    int current_ammo;
    int range;
    int reload_speed;
    int bullet_speed;
    int base_dmg;    
    string name;
    
    public:

    bool is_empty(){
        return(current_ammo);
    }
};

class Sniper : Weapon{
    Sniper(){
        range *= 2;
    }
};
