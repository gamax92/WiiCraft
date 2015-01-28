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

#include "GraphicHandler.h"

#include <cmath>
#include <sstream>
#include "../exception/ExcGraphicNotFound.h"
#include "Background.h"
#include "BlockEngine.h"
#include "pictures/pictureMenuBackground.h"
#include "pictures/terrain.h"
#include "pictures/logo_orbitalfrosch.h"
#include "pictures/logo.h"
#include "pictures/font.h"
#include "pictures/cursor1.h"
#include "pictures/cursor2.h"
#include "pictures/cursor3.h"
#include "pictures/cursor4.h"
#include "pictures/picture_loadingbar.h"
#include "pictures/picture_button.h"
#include "../util/ControllerHandler.h"

#ifdef DEBUG_ON
#include <time.h>
#include "../world/World.h"
#include "../entity/Player.h"
#endif

using namespace std;

GraphicHandler *GraphicHandler::grafikHandler;
#ifdef DEBUG_ON
int GraphicHandler::blockAnzahl = 0;
#endif

void GraphicHandler::initialize() {
	GraphicHandler::grafikHandler = new GraphicHandler();
	GraphicHandler::grafikHandler->start();
}

GraphicHandler *GraphicHandler::getGraphicHandler() {
	return GraphicHandler::grafikHandler;
}

GraphicHandler::GraphicHandler() {
	this->stopped = false;
	this->element = new Background();
	this->selectedElement = this->element;

	pthread_mutex_init(&this->mutexStop, NULL);
	pthread_mutex_init(&this->mutexZeichne, NULL);

	GRRLIB_Init();
	GRRLIB_SetAntiAliasing(false);

	this->ladeBilder();
	this->loadTextureMatrix();

	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xff);
}

GraphicHandler::~GraphicHandler() {
	GRRLIB_Exit();

	pthread_mutex_destroy(&this->mutexStop);
	pthread_mutex_destroy(&this->mutexZeichne);
}

int GraphicHandler::exec() {
#ifdef DEBUG_ON
	int fps = 0;
	int fpsNeu = 0;
	time_t alteZeit;
	time_t neueZeit;
	time(&alteZeit);
	time(&neueZeit);
#endif

	while (!this->isStopped()) {
		ControllerHandler::getControllerHandler()->aktualisiere();

		pthread_mutex_lock(&this->mutexZeichne);
		this->element->drawElement();
		pthread_mutex_unlock(&this->mutexZeichne);

#ifdef DEBUG_ON
		GRRLIB_2dMode();
		GRRLIB_Printf(0, 20,
				GraphicHandler::getGraphicHandler()->getTexture("font"),
				0xffffffff, 1, "FPS: %i", fps);
		GRRLIB_Printf(0, 30,
				GraphicHandler::getGraphicHandler()->getTexture("font"),
				0xffffffff, 1, "Bloecke: %i", GraphicHandler::blockAnzahl);
		GraphicHandler::blockAnzahl = 0;

		World *world = World::getWorld();
		if (world != 0) {
			string chunks = "Chunks: ";
			ostringstream stream;

			if (stream << world->getNumberLoadedChunks()) {
			} else {
				stream << "0";
			}
			stream << "/";
			if (stream << world->getNumberChunks()) {
			} else {
				stream << "0";
			}
			chunks.append(stream.str().data());

			string uhrzeit = "Uhrzeit: ";
			uhrzeit.append(world->getTimeString());

			GRRLIB_Printf(0, 40,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, chunks.data());

			GRRLIB_Printf(0, 50,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, uhrzeit.data());
		}

		Player *player = Player::getPlayer();
		if (player != 0) {
			string x_str = "x: ";
			string y_str = "y: ";
			string z_str = "z: ";
			ostringstream x_stream;
			ostringstream y_stream;
			ostringstream z_stream;

			x_stream << (float) player->getX();
			y_stream << (float) player->getY() + 1.62f;
			z_stream << (float) player->getZ();

			x_str.append(x_stream.str().data());
			y_str.append(y_stream.str().data());
			z_str.append(z_stream.str().data());

			GRRLIB_Printf(0, 60,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, x_str.data());
			GRRLIB_Printf(0, 70,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, y_str.data());
			GRRLIB_Printf(0, 80,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, z_str.data());
			GRRLIB_Printf(0, 90,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, "Chunk X: %i", player->getChunkX());
			GRRLIB_Printf(0, 100,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, "Chunk Z: %i", player->getChunkZ());

			float pitch = player->getAbstand();
			float yaw = player->getWinkel();

			float viewX = -cos(pitch) * sin(yaw);
			float viewY = -sin(pitch);
			float viewZ = cos(pitch) * cos(yaw);

			string abstand_str = "Abstand: ";
			string winkel_str = "Winkel: ";
			string camera_x_str = "Camera X: ";
			string camera_y_str = "Camera Y: ";
			string camera_z_str = "Camera Z: ";
			string view_x_str = "View X: ";
			string view_y_str = "View Y: ";
			string view_z_str = "View Z: ";
			ostringstream abstand_stream;
			ostringstream winkel_stream;
			ostringstream camera_x_stream;
			ostringstream camera_y_stream;
			ostringstream camera_z_stream;
			ostringstream view_x_stream;
			ostringstream view_y_stream;
			ostringstream view_z_stream;

			abstand_stream << pitch;
			winkel_stream << yaw;
			camera_x_stream << (float) player->getX() + viewX;
			camera_y_stream << (float) player->getY() + viewY + 1.62f;
			camera_z_stream << (float) player->getZ() + viewZ;
			view_x_stream << viewX;
			view_y_stream << viewY;
			view_z_stream << viewZ;

			abstand_str.append(abstand_stream.str().data());
			winkel_str.append(winkel_stream.str().data());
			camera_x_str.append(camera_x_stream.str().data());
			camera_y_str.append(camera_y_stream.str().data());
			camera_z_str.append(camera_z_stream.str().data());
			view_x_str.append(view_x_stream.str().data());
			view_y_str.append(view_y_stream.str().data());
			view_z_str.append(view_z_stream.str().data());

			GRRLIB_Printf(0, 110,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, abstand_str.data());
			GRRLIB_Printf(0, 120,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, winkel_str.data());

			GRRLIB_Printf(0, 130,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, camera_x_str.data());
			GRRLIB_Printf(0, 140,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, camera_y_str.data());
			GRRLIB_Printf(0, 150,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, camera_z_str.data());
			GRRLIB_Printf(0, 160,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, view_x_str.data());
			GRRLIB_Printf(0, 170,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, view_y_str.data());
			GRRLIB_Printf(0, 180,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					0xffffffff, 1, view_z_str.data());

		}

		fpsNeu++;
		time(&neueZeit);
		if (((int) difftime(alteZeit, neueZeit) * -1) > 1) {
			time(&alteZeit);
			fps = fpsNeu / 2;
			fpsNeu = 0;
		}
#endif

		GRRLIB_Render();
	}
	return 0;
}

void GraphicHandler::stop() {
	pthread_mutex_lock(&this->mutexStop);
	this->stopped = true;
	pthread_mutex_unlock(&this->mutexStop);
}

bool GraphicHandler::isStopped() {
	bool b = false;

	pthread_mutex_lock(&this->mutexStop);
	b = this->stopped;
	pthread_mutex_unlock(&this->mutexStop);

	return b;
}

void GraphicHandler::setzeAnzeigeElement(GraphicElement *newElement) {
	pthread_mutex_lock(&this->mutexZeichne);
	this->element = newElement;
	this->setSelectedElement(this->element);
	pthread_mutex_unlock(&this->mutexZeichne);
}

void GraphicHandler::ladeBilder() {
	this->textures["bildMenueHintergrund"] = GRRLIB_LoadTexture(
			bildMenueHintergrund);
	this->textures["terrain"] = GRRLIB_LoadTexture(terrain);
	GRRLIB_InitTileSet(this->textures["terrain"], 16, 16, 0);
	this->textures["logo_orbitalfrosch"] = GRRLIB_LoadTexture(logo_orbitalfrosch);
	this->textures["logo"] = GRRLIB_LoadTexture(logo);
	this->textures["font"] = GRRLIB_LoadTexture(font);
	GRRLIB_InitTileSet(this->textures["font"], 8, 8, 0);
	this->textures["cursor1"] = GRRLIB_LoadTexture(cursor1);
	this->textures["cursor2"] = GRRLIB_LoadTexture(cursor2);
	this->textures["cursor3"] = GRRLIB_LoadTexture(cursor3);
	this->textures["cursor4"] = GRRLIB_LoadTexture(cursor4);
	this->textures["bild_ladebalken"] = GRRLIB_LoadTexture(bild_ladebalken);
	GRRLIB_InitTileSet(this->textures["bild_ladebalken"], 100, 4, 0);
	this->textures["bild_button"] = GRRLIB_LoadTexture(bild_button);
	GRRLIB_InitTileSet(this->textures["bild_button"], 16, 16, 0);
}

void GraphicHandler::loadTextureMatrix() {
	GRRLIB_texImg *terrain = this->getTexture("terrain");
	this->textureMatrix = new TextureMatrix[256];
	for (short nr = 0; nr < 256; nr++) {
		this->textureMatrix[nr].s1 = (nr % terrain->nbtilew)
				* terrain->ofnormaltexx;
		this->textureMatrix[nr].s2 = this->textureMatrix[nr].s1
				+ terrain->ofnormaltexx;
		this->textureMatrix[nr].t1 = (int) (nr / terrain->nbtilew)
				* terrain->ofnormaltexy;
		this->textureMatrix[nr].t2 = this->textureMatrix[nr].t1
				+ terrain->ofnormaltexy;
	}
}

TextureMatrix GraphicHandler::getTextureMatrix(int nr) {
	return this->textureMatrix[nr];
}

GRRLIB_texImg *GraphicHandler::getTexture(string name) {
	return this->textures[name];
}

void GraphicHandler::setCursorPosition(float x, float y, float angle) {
	BlockEngine *blockEngine = dynamic_cast<BlockEngine *>(this->element);
	if (blockEngine != 0) {
		blockEngine->setCursorPosition(x, y, angle);
	} else {
		((ContainerElement *) this->element)->setCursorPosition(x, y, angle);
	}
}

void GraphicHandler::gedrueckt(u32 gedrueckt) {
	((ContainerElement *) this->element)->gedrueckt(gedrueckt);
}

void GraphicHandler::setSelectedElement(
		GraphicElement *_selectedElement) {
	this->selectedElement->selected(false);
	this->selectedElement = _selectedElement;
	this->selectedElement->selected(true);
}

GraphicElement *GraphicHandler::getSelectedElement() {
	return this->selectedElement;
}
