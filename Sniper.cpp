#include "Sniper.h"

Sniper::Sniper()
    : Weapon("sniper.png")
{
    id = 1;
    chargerNb = 10;
    chargerSize = 1;
    currentAmmo = chargerSize;
    reloadTime = 2.f;
    timeBetweenShoot = 100;
    bulletSpeed = 50;
    precision = 0;
    name = "Sniper";
    infoRectangle.setText(name);
    degat = 100;
}
