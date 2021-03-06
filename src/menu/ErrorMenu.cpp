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

#include "ErrorMenu.h"

#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include <stdlib.h>
#include "../gui/Background.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/GraphicHandler.h"

using namespace std;

ErrorMenu *ErrorMenu::fehlerMenue;

void ErrorMenu::initialize(string fehlerText) {
	ErrorMenu::fehlerMenue = new ErrorMenu(fehlerText);
}

void ErrorMenu::deinitialize() {
	delete ErrorMenu::fehlerMenue;
}

ErrorMenu::ErrorMenu(string fehlerText) {
	pthread_mutex_init(&this->mutexWait, NULL);
	pthread_cond_init(&this->condWait, NULL);

	this->background = new Background("pictureMenueBackground");
	this->background->setzeCursorAnzeigen(true);

	this->textFehler = new Text(200, 160, fehlerText);
	this->textFehler->visible(true);

	this->buttonOk = new Button(254, 220, "Ok");
	this->buttonOk->setzeBeimKlicken(&ErrorMenu::ok);

	this->background->fuegeUnterElementHinzu(this->textFehler);
	this->background->fuegeUnterElementHinzu(this->buttonOk);
}

ErrorMenu::~ErrorMenu() {
	pthread_mutex_destroy(&this->mutexWait);
	pthread_cond_destroy(&this->condWait);
}

void ErrorMenu::showErrorMenu() {
	GraphicHandler::getGraphicHandler()->setzeAnzeigeElement(
			ErrorMenu::fehlerMenue->background);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		ErrorMenu::fehlerMenue->buttonOk->beimKlicken(0);
#else
		pthread_mutex_lock(&ErrorMenu::fehlerMenue->mutexWait);
		pthread_cond_wait(&ErrorMenu::fehlerMenue->condWait,
				&ErrorMenu::fehlerMenue->mutexWait);
		pthread_mutex_unlock(&ErrorMenu::fehlerMenue->mutexWait);
#endif

		ErrorMenu::fehlerMenue->background->setzeKeyboardAnzeigen(false);
		ErrorMenu::fehlerMenue->textFehler->visible(false);
		ErrorMenu::fehlerMenue->buttonOk->visible(false);

		exit(0);
	}
}

void ErrorMenu::ok() {
	pthread_mutex_lock(&ErrorMenu::fehlerMenue->mutexWait);
	pthread_cond_signal(&ErrorMenu::fehlerMenue->condWait);
	pthread_mutex_unlock(&ErrorMenu::fehlerMenue->mutexWait);
}
