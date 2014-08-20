#pragma once

#include <Gunship.h>

void MakePlayer( GameObject& player, GameObject& target );
void MakeCamera( GameObject& camera, GameObject& cameraAnchor, GameObject& player );
void MakeBullet( GameObject bullet, Ogre::Vector3 start, Ogre::Vector3 dir );
void MakeEnemy( GameObject enemy, GameObject& player, Ogre::Vector3 start);
