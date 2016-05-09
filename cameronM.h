#ifndef CAMERON_H
#define CAMERON_H
void drawHealth(Player x);
void drawAmmo(Player x);
void drawDiamondBack(int x);
void drawDiamond(int x);
//void drawArtifacts(Player x);
void drawBackground();
void drawHUD(Player x);
struct HealthPack{
    Vec pos;
    int size;
};

#endif
