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

#include "LoadingBar.h"

#include "GraphicHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

LoadingBar::LoadingBar(float _x, float _y) {
	this->setzeStandardWerte();

	pthread_mutex_init(&this->mutexfortschritt, NULL);

	this->setX(_x);
	this->setY(_y);
	this->setHeight(4);
	this->setWidth(100);
	this->setzeFortschritt(0);
}

LoadingBar::~LoadingBar() {
	pthread_mutex_destroy(&this->mutexfortschritt);
}

void LoadingBar::drawElement() {
	if (this->isVisible()) {
		float _x = this->getX();
		float _y = this->getY();
		float _hoehe = this->getHeight();
		float _breite = this->getWidth();
		int _fortschritt = this->gebeFortschritt();

		GRRLIB_2dMode();

		// zeichne LoadingBar Background
		GRRLIB_Rectangle(_x, _y, _breite, _hoehe, 0x000000ff, 1);

		// zeichne LoadingBar fortschritt, anhand des Tiles
		if (_fortschritt > 0 && _fortschritt <= 100) {
			GRRLIB_DrawTile(_x, _y,
					GraphicHandler::getGraphicHandler()->getTexture(
							"picture_loadingbar"), 0, _breite / 100.0,
					_hoehe / 4.0, 0xffffffff, _fortschritt);
		}
	}
}

void LoadingBar::setzeFortschritt(int _fortschritt) {
	pthread_mutex_lock(&this->mutexfortschritt);
	this->fortschritt = _fortschritt;
	pthread_mutex_unlock(&this->mutexfortschritt);
}

int LoadingBar::gebeFortschritt() {
	pthread_mutex_lock(&this->mutexfortschritt);
	int _fortschritt = this->fortschritt;
	pthread_mutex_unlock(&this->mutexfortschritt);

	return _fortschritt;
}
