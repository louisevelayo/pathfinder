#ifndef HEALTHPACK_H
#define HEALTHPACK_H


class HealthPack
{
public:
    HealthPack(int xPosition, int yPosition, int healValue);
    int getXPos() const {return xPos;};
    int getYPos() const {return yPos;};
    int getHealth() const {return health;};
    void setXPos(int newPos) {xPos = newPos;};
    void setYPos(int newPos) {yPos = newPos;};
    void setHealth(int newHealth) {health = newHealth;};

protected:
    int xPos;
    int yPos;
    int health;
};

#endif // HEALTHPACK_H
