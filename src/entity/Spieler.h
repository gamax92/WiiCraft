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

#ifndef SPIELER_H_
#define SPIELER_H_

#include "Entity.h"

namespace std {

class PlayerMotionSendingThread;

class Player: public Entity {
public:
	static void initializePlayer(int entityId);
	static Player *getPlayer();

	void setCoordinates(double _x, double _y, double _z);
	void setBlickfeld(float _winkel, float _abstand);
	void setHaltung(double _haltung);
	void setOnGround(bool _isOnGround);
	void setFaehigkeit(bool _isFlying, bool _isFliegenMoeglich,
			bool _isEinfachesAbbauenAktiv, bool _isInvulnerable);

	double getHaltung();
	float getWinkel();
	float getAbstand();
	bool getIsOnGround();
	bool getIsFlying();
	bool getIstFliegenMoeglich();
	bool getIsEinfachesAbbauenAktiv();
	bool getIsInvulnerable();

	void setzeLebensEnergie(short _lebensEnergie);
	void setzeSaettigung(short _saettigung);
	void setzeUeberSaettigung(float _ueberSaettigung);

	void setExperiencePointsCurrentLevel(
			float _experiencePointsCurrentLevel);
	void setzeLevel(short _level);
	void setExperiencePointsTotal(short _experiencePointsTotal);

private:
	static Player *player;

	PlayerMotionSendingThread *playerMotionSendingThread;
	bool playerMotionSendingThreadStarted;

	double haltung;
	float winkel;
	float abstand;
	bool isOnGround;

	bool isFlying;
	bool isFliegenMoeglich;
	bool isEinfachesAbbauenAktiv;
	bool isInvulnerable;

	short lebensEnergie;
	short saettigung;
	float ueberSaettigung;

	float experiencePointsCurrentLevel;
	short level;
	short experiencePointsTotal;

	Player(int entityId);
	~Player();
};
}
#endif /* SPIELER_H_ */
