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

#include "PasswordField.h"

#include <cmath>
#include "GraphicHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

PasswordField::PasswordField(float _x, float _y) {
	TextElement::setzeStandardWerte();

	this->setX(_x);
	this->setY(_y);
	this->berechneAusmasse();
	time(&this->cursorZeit);
}

PasswordField::PasswordField(float _x, float _y, string _text) {
	TextElement::setzeStandardWerte();

	this->setX(_x);
	this->setY(_y);
	this->berechneAusmasse();
	this->setText(_text);
	time(&this->cursorZeit);
}

PasswordField::~PasswordField() {
}

void PasswordField::berechneAusmasse() {
	this->setHeight(18);
	this->setWidth(104);
}

void PasswordField::drawElement() {
	if (this->isVisible()) {
		GRRLIB_2dMode();

		string _text;

		bool deaktiviert = this->istDeaktiviert();
		int textFarbe = 0xffffffff;
		int textFarbeSchatten = 0x383838ff;

		float _x = this->getX();
		float _y = this->getY();
		float _breite = this->getWidth();
		float _hoehe = this->getHeight();

		for (unsigned int i = 0; i < this->getText().size(); i++) {
			_text.append("*");
		}

		unsigned int zeichenPlatz = (unsigned int) floor(
				(_breite - 4.0 - 8.0) / 8.0);

		if (_text.size() > zeichenPlatz) {
			_text = _text.substr(_text.size() - zeichenPlatz);
		}

		if (this->istAusgewaehlt()) {
			time_t neueCursorZeit;
			time(&neueCursorZeit);

			if (((int) difftime(this->cursorZeit, neueCursorZeit) * -1) == 1) {
				_text.append("_");
			} else if (((int) difftime(this->cursorZeit, neueCursorZeit) * -1)
					> 1) {
				time(&this->cursorZeit);
			}
		}

		GRRLIB_Rectangle(_x, _y, _breite, _hoehe, 0xffffffff, 0);
		GRRLIB_Rectangle(_x + 1, _y + 1, _breite - 2, _hoehe - 2, 0x000000ff,
				1);

		if (_text.size() > 0) {
			// Textschatten
			if (!deaktiviert) {
				GRRLIB_Printf(_x + 3, _y + 5,
						GraphicHandler::getGraphicHandler()->getTexture("font"),
						textFarbeSchatten, 1, _text.data());
			}

			// Text
			GRRLIB_Printf(_x + 2, _y + 4,
					GraphicHandler::getGraphicHandler()->getTexture("font"),
					textFarbe, 1, _text.data());
		}
	}
}

