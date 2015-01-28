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

#include "UpdateMenu.h"

#include <stdlib.h>
#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../gui/Background.h"
#include "../gui/Text.h"
#include "../gui/LoadingBar.h"
#include "../gui/Button.h"
#include "../gui/GraphicHandler.h"
#include "../util/UpdateHandler.h"
#include "../util/ControllerHandler.h"
#include "../exception/ExcSocketHTTPServerLoginFailed.h"

using namespace std;

UpdateMenu *UpdateMenu::updateMenu;

void UpdateMenu::initialize() {
	UpdateMenu::updateMenu = new UpdateMenu();
}

void UpdateMenu::deinitialize() {
	delete UpdateMenu::updateMenu;
}

UpdateMenu::UpdateMenu() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->updateHerunterlanden = false;

	this->background = new Background("bildMenueHintergrund");
	this->background->setzeCursorAnzeigen(true);

	this->text = new Text(250, 200, "Suche nach Update");
	this->loadingBar = new LoadingBar(270, 220);
	this->loadingBar->visible(false);

	this->buttonYes = new Button(250, 240, "Ja");
	this->buttonYes->visible(false);
	this->buttonYes->setzeBeimKlicken(&UpdateMenu::starteUpdate);

	this->buttonNo = new Button(300, 240, "Nein");
	this->buttonNo->visible(false);
	this->buttonNo->setzeBeimKlicken(&UpdateMenu::keinUpdate);

	this->background->fuegeUnterElementHinzu(this->text);
	this->background->fuegeUnterElementHinzu(this->loadingBar);
	this->background->fuegeUnterElementHinzu(this->buttonYes);
	this->background->fuegeUnterElementHinzu(this->buttonNo);
}

UpdateMenu::~UpdateMenu() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);

	delete this->background;

	delete this->text;
	delete this->loadingBar;
	delete this->buttonYes;
	delete this->buttonNo;
}

void UpdateMenu::showUpdateMenu() {
	GraphicHandler::getGraphicHandler()->setzeAnzeigeElement(
			UpdateMenu::updateMenu->background);

	bool updateVorhanden;
	try {
		updateVorhanden = UpdateHandler::istUpdateVorhanden();
	} catch (ExcSocketHTTPServerLoginFailed &exception) {
		updateVorhanden = false;
	}

	if (updateVorhanden) {
		UpdateMenu::updateMenu->text->setText(
				"Update gefunden. Soll es installiert werden?");
		UpdateMenu::updateMenu->buttonYes->visible(true);
		UpdateMenu::updateMenu->buttonNo->visible(true);
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		UpdateMenu::updateMenu->buttonNo->beimKlicken(0);
#else
		pthread_mutex_lock(&UpdateMenu::updateMenu->mutexwait);
		pthread_cond_wait(&UpdateMenu::updateMenu->condwait,
				&UpdateMenu::updateMenu->mutexwait);
		pthread_mutex_unlock(&UpdateMenu::updateMenu->mutexwait);
#endif
		if (UpdateMenu::updateMenu->updateHerunterlanden) {
			UpdateMenu::updateMenu->text->setText(
					"Update wird heruntergeladen");
			UpdateMenu::updateMenu->loadingBar->visible(true);
			UpdateMenu::updateMenu->buttonYes->visible(false);
			UpdateMenu::updateMenu->buttonNo->visible(false);

			UpdateHandler::ladeUpdate(UpdateMenu::updateMenu->loadingBar);

			GraphicHandler::getGraphicHandler()->stop();
			GraphicHandler::getGraphicHandler()->join();

			delete GraphicHandler::getGraphicHandler();
			delete ControllerHandler::getControllerHandler();

			exit(0);
		}
	}
}

void UpdateMenu::keinUpdate() {
	UpdateMenu::updateMenu->updateHerunterlanden = false;

	pthread_mutex_lock(&UpdateMenu::updateMenu->mutexwait);
	pthread_cond_signal(&UpdateMenu::updateMenu->condwait);
	pthread_mutex_unlock(&UpdateMenu::updateMenu->mutexwait);
}

void UpdateMenu::starteUpdate() {
	UpdateMenu::updateMenu->updateHerunterlanden = true;

	pthread_mutex_lock(&UpdateMenu::updateMenu->mutexwait);
	pthread_cond_signal(&UpdateMenu::updateMenu->condwait);
	pthread_mutex_unlock(&UpdateMenu::updateMenu->mutexwait);
}
