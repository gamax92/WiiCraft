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

#include "GameThread.h"

#include <unistd.h>
#include "../protocol/Connection.h"
#include "../menu/Intro.h"
#include "../menu/UpdateMenu.h"
#include "../menu/LoginMenu.h"
#include "../menu/ServerSelectionMenu.h"
#include "../menu/Display3D.h"
#include "../world/World.h"
#include "../world/ChunkLoading.h"
#include "../entity/Player.h"

using namespace std;

SpielThread::SpielThread() {
}

SpielThread::~SpielThread() {
}

int SpielThread::exec() {
	Intro::zeigeIntro();

	UpdateMenue::initialize();
	UpdateMenue::zeigeUpdateMenue();

	AnmeldungMenue::initialize();
	AnmeldungMenue::zeigeAnmeldungMenue();

	UpdateMenue::deinitialize();

	ServerAuswahlMenue::initialize();
	ServerAuswahlMenue::zeigeServerAuswahlMenue();
	AnmeldungMenue::deinitialize();

	// Chunks im vorraus laden
	while (true) {
		World *world = World::getWorld();
		if (world != 0) {
			ChunkLaden::gebeChunkLaden()->aktualisiereChunks(
					Player::getPlayer()->getChunkX(),
					Player::getPlayer()->getChunkZ());

			if (world->gebeAnzahlGeladeneChunks()
					== ChunkLaden::gebeMaximaleAnzahlGeladeneChunks()) {
				break;
			}
		}
		usleep(50);
	}

	Anzeige3D::initialize();
	Anzeige3D::zeigeAnzeige3D();
	ServerAuswahlMenue::deinitialize();

	Verbindung::warte();

	return 0;
}
