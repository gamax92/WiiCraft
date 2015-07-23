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
#include "../entity/Player.h"
#include "../world/ChunkLoader.h"

using namespace std;

GameThread::GameThread() {
}

GameThread::~GameThread() {
}

int GameThread::exec() {
	Intro::showIntro();

	UpdateMenu::initialize();
	UpdateMenu::showUpdateMenu();

	LoginMenu::initialize();
	LoginMenu::zeigeLoginMenu();

	UpdateMenu::deinitialize();

	ServerSelectionMenu::initialize();
	ServerSelectionMenu::zeigeServerSelectionMenu();
	LoginMenu::deinitialize();

	// Chunks im vorraus laden
	while (true) {
		World *world = World::getWorld();
		if (world != 0) {
			ChunkLoader::getChunkLoader()->updateChunks(
					Player::getPlayer()->getChunkX(),
					Player::getPlayer()->getChunkZ());

			if (world->getNumberLoadedChunks()
					== ChunkLoader::getMaximumLoadedChunks()) {
				break;
			}
		}
		usleep(50);
	}

	Display3D::initialize();
	Display3D::zeigeDisplay3D();
	ServerSelectionMenu::deinitialize();

	Connection::warte();

	return 0;
}
