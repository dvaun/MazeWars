#ifndef POWERUP_CPP
#define POWERUP_CPP

struct PowerUp {
	//type is going to be an int ie(1:"Shield Bubble" 2:"Unlimited Ammo" 3:"Walk Through Walls" etc...)
	int type;
	int lifeSpan;
	//position[0] = X; position[1] = Y;
	int position[2];

	void operator=(int input){
		type = input;
		switch(input){
			//fill in info about lifespan, name, sprite, and other info here upon initialization
		}
	}
};

#endif
