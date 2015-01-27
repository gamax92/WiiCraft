/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Player.h"

#include <stdlib.h>
#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#else
#include "../util/pthread.h"
#endif
#include "../thread/PlayerMovementSendingThread.h"

using namespace std;

Player *Player::player = NULL;

Player::Player(int entityId) {
	pthread_mutex_init(&this->mutex, NULL);

	this->setId(entityId);

	Entity::setCoordinates(0, 0, 0);

	this->winkel = 0;
	this->abstand = 0;
	this->haltung = 0;
	this->isOnGround = false;
	this->isFlying = false;
	this->isFliegenMoeglich = false;
	this->isEinfachesAbbauenAktiv = false;

	this->isInvulnerable = false;
	this->lebensEnergie = 0;
	this->saettigung = 0;
	this->ueberSaettigung = 0;

	this->experiencePointsCurrentLevel = 0;
	this->level = 0;
	this->experiencePointsTotal = 0;

	this->playerMotionSendingThread = new PlayerMotionSendingThread(this,
			this->x, this->y, this->z, this->winkel, this->abstand,
			this->haltung, this->isOnGround, this->isFlying);
	this->playerMotionSendingThread->start();

	Entity::setEntity(this);
}

Player::~Player() {
	this->playerMotionSendingThread->stop();
	this->playerMotionSendingThread->join();

	pthread_mutex_destroy(&this->mutex);
}

Player *Player::getPlayer() {
	return Player::player;
}

void Player::initializePlayer(int entityId) {
	if (Player::player != NULL) {
		delete Player::player;
		Entity::deinitialize();
	}

	Entity::initialize();
	Player::player = new Player(entityId);
}

void Player::setCoordinates(double _x, double _y, double _z) {
	Entity::setCoordinates(_x, _y, _z);

	this->playerMotionSendingThread->update();
}

void Player::setBlickfeld(float _winkel, float _abstand) {
	pthread_mutex_lock(&this->mutex);
	this->winkel = _winkel;
	this->abstand = _abstand;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setHaltung(double _haltung) {
	pthread_mutex_lock(&this->mutex);
	this->haltung = _haltung;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setOnGround(bool _isOnGround) {
	pthread_mutex_lock(&this->mutex);
	this->isOnGround = _isOnGround;
	pthread_mutex_unlock(&this->mutex);
}

double Player::getHaltung() {
	pthread_mutex_lock(&this->mutex);
	double _haltung = this->haltung;
	pthread_mutex_unlock(&this->mutex);

	return _haltung;
}

float Player::getWinkel() {
	pthread_mutex_lock(&this->mutex);
	float _winkel = this->winkel;
	pthread_mutex_unlock(&this->mutex);

	return _winkel;
}

float Player::getAbstand() {
	pthread_mutex_lock(&this->mutex);
	double _abstand = this->abstand;
	pthread_mutex_unlock(&this->mutex);

	return _abstand;
}

bool Player::getIsOnGround() {
	pthread_mutex_lock(&this->mutex);
	bool _isOnGround = this->isOnGround;
	pthread_mutex_unlock(&this->mutex);

	return _isOnGround;
}

bool Player::getIsFlying() {
	pthread_mutex_lock(&this->mutex);
	bool _isFlying = this->isFlying;
	pthread_mutex_unlock(&this->mutex);

	return _isFlying;
}

bool Player::getIstFliegenMoeglich() {
	pthread_mutex_lock(&this->mutex);
	bool _isFliegenMoeglich = this->isFliegenMoeglich;
	pthread_mutex_unlock(&this->mutex);

	return _isFliegenMoeglich;
}

bool Player::getIsEinfachesAbbauenAktiv() {
	pthread_mutex_lock(&this->mutex);
	bool _isEinfachesAbbauenAktiv = this->isEinfachesAbbauenAktiv;
	pthread_mutex_unlock(&this->mutex);

	return _isEinfachesAbbauenAktiv;
}

bool Player::getIsInvulnerable() {
	pthread_mutex_lock(&this->mutex);
	bool _isInvulnerable = this->isInvulnerable;
	pthread_mutex_unlock(&this->mutex);

	return _isInvulnerable;
}

void Player::setFaehigkeit(bool _isFlying, bool _isFliegenMoeglich,
		bool _isEinfachesAbbauenAktiv, bool _isInvulnerable) {
	pthread_mutex_lock(&this->mutex);
	this->isFlying = _isFlying;
	this->isFliegenMoeglich = _isFliegenMoeglich;
	this->isEinfachesAbbauenAktiv = _isEinfachesAbbauenAktiv;
	this->isInvulnerable = _isInvulnerable;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setzeLebensEnergie(short _lebensEnergie) {
	pthread_mutex_lock(&this->mutex);
	this->lebensEnergie = _lebensEnergie;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setzeSaettigung(short _saettigung) {
	pthread_mutex_lock(&this->mutex);
	this->saettigung = _saettigung;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setzeUeberSaettigung(float _ueberSaettigung) {
	pthread_mutex_lock(&this->mutex);
	this->ueberSaettigung = _ueberSaettigung;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setExperiencePointsCurrentLevel(
		float _experiencePointsCurrentLevel) {
	pthread_mutex_lock(&this->mutex);
	this->experiencePointsCurrentLevel = _experiencePointsCurrentLevel;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setzeLevel(short _level) {
	pthread_mutex_lock(&this->mutex);
	this->level = _level;
	pthread_mutex_unlock(&this->mutex);
}

void Player::setExperiencePointsTotal(short _experiencePointsTotal) {
	pthread_mutex_lock(&this->mutex);
	this->experiencePointsTotal = _experiencePointsTotal;
	pthread_mutex_unlock(&this->mutex);
}
