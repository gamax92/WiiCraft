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

#include "SpielerBewegungSendenThread.h"

#include <unistd.h>
#include "../entity/Player.h"
#include "../world/ChunkLaden.h"
#include "../protocol/PacketClient.h"
#include "../protocol/packet/Packet0APlayer.h"
#include "../protocol/packet/Packet0BPlayerPosition.h"
#include "../protocol/packet/Packet0CPlayerLook.h"
#include "../protocol/packet/Packet0DPlayerPositionLook.h"
#include "../protocol/packet/PacketCAPlayerAbilities.h"
#include "../protocol/Verbindung.h"
#include "../util/Debug.h"

using namespace std;

PlayerMotionSendingThread::PlayerMotionSendingThread(Player *_spieler,
		double initialX, double initialY, double initialZ,
		double initialHaltung, float initialWinkel, float initialAbstand,
		bool initialIstAufBoden, bool initialIstFliegend) {

	this->spieler = _spieler;
	this->zuletztUebertragenX = initialX;
	this->zuletztUebertragenY = initialY;
	this->zuletztUebertragenZ = initialZ;
	this->zuletztUebertragenHaltung = initialHaltung;
	this->zuletztUebertragenWinkel = initialWinkel;
	this->zuletztUebertragenAbstand = initialAbstand;
	this->zuletztUebertragenIstAufBoden = initialIstAufBoden;
	this->zuletztUebertragenIstFliegend = initialIstFliegend;

	this->gestoppt = false;

	pthread_mutex_init(&this->mutexStop, NULL);
	pthread_mutex_init(&this->mutexWait, NULL);
	pthread_cond_init(&this->condWait, NULL);
}

PlayerMotionSendingThread::~PlayerMotionSendingThread() {
	pthread_mutex_destroy(&this->mutexStop);
	pthread_mutex_destroy(&this->mutexWait);
	pthread_cond_destroy(&this->condWait);
}

int PlayerMotionSendingThread::exec() {
	pthread_mutex_lock(&this->mutexWait);
	pthread_cond_wait(&this->condWait, &this->mutexWait);
	pthread_mutex_unlock(&this->mutexWait);

	do {
		if (this->istGestopped()) {
			break;
		}

		double aktuellX = this->spieler->getX();
		double aktuellY = this->spieler->getY();
		double aktuellZ = this->spieler->getZ();
		double aktuellHaltung = this->spieler->getHaltung();
		float aktuellWinkel = this->spieler->getWinkel();
		float aktuellAbstand = this->spieler->getAbstand();
		bool aktuellIstAufBoden = this->spieler->getIsOnGround();

		// Position und Blickwinkel geaendert
		if ((aktuellX != this->zuletztUebertragenX
				|| aktuellY != this->zuletztUebertragenY
				|| aktuellZ != this->zuletztUebertragenZ
				|| aktuellHaltung != this->zuletztUebertragenHaltung)
				&& (aktuellWinkel != this->zuletztUebertragenWinkel
						|| aktuellAbstand != this->zuletztUebertragenAbstand)) {
			PacketClient *p = new Packet0DPlayerPositionLook(aktuellX, aktuellY,
					aktuellHaltung, aktuellZ, aktuellWinkel, aktuellAbstand,
					aktuellIstAufBoden);
			Verbindung::zuVerschickendenPacketenHinzufuegen(p);

			this->zuletztUebertragenX = aktuellX;
			this->zuletztUebertragenY = aktuellY;
			this->zuletztUebertragenZ = aktuellZ;
			this->zuletztUebertragenHaltung = aktuellHaltung;
			this->zuletztUebertragenWinkel = aktuellWinkel;
			this->zuletztUebertragenAbstand = aktuellAbstand;
			this->zuletztUebertragenIstAufBoden = aktuellIstAufBoden;

			// Position geaendert
		} else if (aktuellX != this->zuletztUebertragenX
				|| aktuellY != this->zuletztUebertragenY
				|| aktuellZ != this->zuletztUebertragenZ
				|| aktuellHaltung != this->zuletztUebertragenHaltung) {
			PacketClient *p = new Packet0BPlayerPosition(aktuellX, aktuellY,
					aktuellHaltung, aktuellZ, aktuellIstAufBoden);
			Verbindung::zuVerschickendenPacketenHinzufuegen(p);

			this->zuletztUebertragenX = aktuellX;
			this->zuletztUebertragenY = aktuellY;
			this->zuletztUebertragenZ = aktuellZ;
			this->zuletztUebertragenHaltung = aktuellHaltung;
			this->zuletztUebertragenIstAufBoden = aktuellIstAufBoden;

			// Blickwinkel geaendert
		} else if (aktuellWinkel != this->zuletztUebertragenWinkel
				|| aktuellAbstand != this->zuletztUebertragenAbstand) {
			PacketClient *p = new Packet0CPlayerLook(aktuellWinkel,
					aktuellAbstand, aktuellIstAufBoden);
			Verbindung::zuVerschickendenPacketenHinzufuegen(p);

			this->zuletztUebertragenWinkel = aktuellWinkel;
			this->zuletztUebertragenAbstand = aktuellAbstand;
			this->zuletztUebertragenIstAufBoden = aktuellIstAufBoden;

			// keine Bewegung des Players
		} else {
			PacketClient *p = new Packet0APlayer(aktuellIstAufBoden);
			Verbindung::zuVerschickendenPacketenHinzufuegen(p);

			this->zuletztUebertragenIstAufBoden = aktuellIstAufBoden;
		}

		bool aktuellIstFliegend = this->spieler->getIsFlying();
		bool aktuellIstFliegenMoeglich =
				this->spieler->getIstFliegenMoeglich();
		bool aktuellIstEinfachesAbbauenAktiv =
				this->spieler->getIsEinfachesAbbauenAktiv();
		bool aktuellIstUnverwundbar = this->spieler->getIsInvulnerable();

		if (aktuellIstFliegend != this->zuletztUebertragenIstFliegend) {
			PacketClient *p = new PacketCAPlayerAbilities(aktuellIstUnverwundbar,
					aktuellIstFliegend, aktuellIstFliegenMoeglich,
					aktuellIstEinfachesAbbauenAktiv);
			Verbindung::zuVerschickendenPacketenHinzufuegen(p);

			this->zuletztUebertragenIstFliegend = aktuellIstFliegend;
		}

		int aktuellChunkX = this->spieler->getChunkX();
		int aktuellChunkZ = this->spieler->getChunkZ();

		if (aktuellChunkX != this->zuletztChunkX
				|| aktuellChunkZ != this->zuletztChunkZ) {
			ChunkLaden::gebeChunkLaden()->aktualisiereChunks(aktuellChunkX,
					aktuellChunkZ);

			this->zuletztChunkX = aktuellChunkX;
			this->zuletztChunkZ = aktuellChunkZ;
		}

		// 50 Milli-Sekunden
		usleep(50000);
	} while (true);

#ifdef DEBUG_ON
	Debug::schreibeLog("sd:/apps/WiiCraft/Packet.log", "Bewegen gestoppt\n",
			Debug::DATEI_ERWEITERN);
#endif

	return 0;
}

void PlayerMotionSendingThread::stop() {
	pthread_mutex_lock(&this->mutexStop);
	this->gestoppt = true;
	pthread_mutex_unlock(&this->mutexStop);
}

bool PlayerMotionSendingThread::istGestopped() {
	bool b = false;

	pthread_mutex_lock(&this->mutexStop);
	b = this->gestoppt;
	pthread_mutex_unlock(&this->mutexStop);

	return b;
}

void PlayerMotionSendingThread::update() {
	pthread_mutex_lock(&this->mutexWait);
	pthread_cond_signal(&this->condWait);
	pthread_mutex_unlock(&this->mutexWait);
}
