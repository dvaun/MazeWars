class Player_Character{
    
    int pos_x;
    int pos_y;
    int max_health;
    int current_health;
    Powerup P_UP[3]; //array of powerups the player is/can use
    int NumP = 0; //Number of current Powerup to be replaced; if(none) put new one at index
    Weapon Player_Gun;

Public:
    
    void move(int x, int y){
        pos_x = x;
        pos_y = y;
    }
    void modifyHealth(int mod){
        health += mod;
        if(health <= 0)
            health = 0;
    }
    bool is_Dead(){
        return health;
    }
    void add_Powerup(Powerup PowNew){
        //make an assignment operator in the "Powerup" object
        P_UP[NumP] = PowNew;
        NumP = (NumP + 1) % 3;
    }
    void Change_Weapon(Weapon GunNew){
        //make an assignment operator in the "Weapon" object
        Player_Gun = GunNew;
    }
}Player_1;
