#include "AK.h"

AK::AK()
    : Weapon("AK.png")
{
    id = 2;
    chargerNb = 2;
    chargerSize = 20;
    currentAmmo = chargerSize;
    reloadTime = 3;
    timeBetweenShoot = 100;
    bulletSpeed = 25;
    precision = 3;
    name = "AK";
    infoRectangle.setText("AK");
    degat = 27;
}
