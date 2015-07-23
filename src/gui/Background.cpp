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

#include "Background.h"

#include "GraphicHandler.h"
#include "Keyboard.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Background::Background() {
	ContainerElement::setzeStandardWerte();

	this->keyboard = Keyboard::getKeyboard();
	this->setX(0);
	this->setY(0);
	this->setHeight(480);
	this->setWidth(640);
	this->setzeKeyboardAnzeigen(false);

	this->fuegeUnterElementHinzu(this->keyboard);
}

Background::Background(string _texture) {
	ContainerElement::setzeStandardWerte();

	this->keyboard = Keyboard::getKeyboard();
	this->texture = _texture;
	this->setX(0);
	this->setY(0);
	this->setHeight(480);
	this->setWidth(640);
	this->setzeKeyboardAnzeigen(false);

	this->fuegeUnterElementHinzu(this->keyboard);
}

Background::~Background() {
}

void Background::drawElement() {
	if (this->isVisible()) {
		GRRLIB_2dMode();

		if (!this->texture.empty()) {
			for (int breite = -40; breite < (640 + 80); breite += 32) {
				for (int hoehe = -40; hoehe < (480 + 80); hoehe += 32) {
					GRRLIB_DrawImg(
							breite,
							hoehe,
							GraphicHandler::getGraphicHandler()->getTexture(
									this->texture), 0, 2, 2, 0xFFFFFFFF);
				}
			}
		} else {
			GRRLIB_FillScreen(0x000000ff);
		}

		this->zeichneUnterElement();

		if (this->istCursorAnzeigbar()) {
			this->zeichneCursor();
		}
	}
}

void Background::setzeKeyboardAnzeigen(bool _keyboardAnzeigen) {
	this->keyboard->visible(_keyboardAnzeigen);
}

bool Background::zeigeKeyboard() {
	return this->keyboard->isVisible();
}
