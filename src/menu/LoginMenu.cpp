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

#include "LoginMenu.h"

#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../gui/Background.h"
#include "../gui/TextField.h"
#include "../gui/PasswordField.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/Texture.h"
#include "../gui/GraphicHandler.h"
#include "../protocol/Session.h"
#include "../exception/ExcSocketHTTPServerLoginFailed.h"
#include "../thread/HTTPSessionRefreshThread.h"

using namespace std;

LoginMenu *LoginMenu::loginMenu;

void LoginMenu::initialize() {
	LoginMenu::loginMenu = new LoginMenu();
}

void LoginMenu::deinitialize() {
	delete LoginMenu::loginMenu;
}

LoginMenu::LoginMenu() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->background = new Background("bildMenueHintergrund");
	this->background->setzeKeyboardAnzeigen(true);
	this->background->setzeCursorAnzeigen(true);

	Texture *bild = new Texture(144, 20, "logo");
	this->textError = new Text(250, 260, "");
	this->textError->setBackgroundColor(0xff33337f);
	this->textAnmelden = new Text(200, 160, "am Minecraft Server anmelden...");
	this->textAnmelden->visible(false);

	this->textUsername = new Text(250, 124, "Username:");
	this->textFieldUsername = new TextField(250, 140, "");
	this->textFieldUsername->setzeBeimKlicken(
			&LoginMenu::auswaehlenBunutzer);
	this->textPassword = new Text(250, 164, "Password:");
	this->textFieldPassword = new PasswordField(250, 180, "");
	this->textFieldPassword->setzeBeimKlicken(
			&LoginMenu::auswaehlenPasswort);
	this->buttonAnmelden = new Button(254, 220, "Anmelden");
	this->buttonAnmelden->setzeBeimKlicken(&LoginMenu::anmelden);

	this->background->fuegeUnterElementHinzu(bild);
	this->background->fuegeUnterElementHinzu(this->textError);
	this->background->fuegeUnterElementHinzu(this->textAnmelden);
	this->background->fuegeUnterElementHinzu(this->textUsername);
	this->background->fuegeUnterElementHinzu(this->textFieldUsername);
	this->background->fuegeUnterElementHinzu(this->textPassword);
	this->background->fuegeUnterElementHinzu(this->textFieldPassword);
	this->background->fuegeUnterElementHinzu(this->buttonAnmelden);
}

LoginMenu::~LoginMenu() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

void LoginMenu::zeigeAnmeldungMenue() {
	GraphicHandler::getGraphicHandler()->setzeAnzeigeElement(
			LoginMenu::loginMenu->background);
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			LoginMenu::loginMenu->textFieldUsername);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		LoginMenu::loginMenu->textFieldUsername->setText(input);

		input = "";
		getline(cin, input);
		LoginMenu::loginMenu->textFieldPassword->setText(input);

		LoginMenu::loginMenu->buttonAnmelden->beimKlicken(0);
#else
		pthread_mutex_lock(&LoginMenu::loginMenu->mutexwait);
		pthread_cond_wait(&LoginMenu::loginMenu->condwait,
				&LoginMenu::loginMenu->mutexwait);
		pthread_mutex_unlock(&LoginMenu::loginMenu->mutexwait);
#endif

		LoginMenu::loginMenu->background->setzeKeyboardAnzeigen(
				false);
		LoginMenu::loginMenu->textError->visible(false);
		LoginMenu::loginMenu->textUsername->visible(false);
		LoginMenu::loginMenu->textFieldUsername->visible(false);
		LoginMenu::loginMenu->textPassword->visible(false);
		LoginMenu::loginMenu->textFieldPassword->visible(false);
		LoginMenu::loginMenu->buttonAnmelden->visible(false);
		LoginMenu::loginMenu->textAnmelden->visible(true);

		try {
			Session::anmelden(
					LoginMenu::loginMenu->textFieldUsername->getText(),
					LoginMenu::loginMenu->textFieldPassword->getText());
		} catch (ExcSocketHTTPServerLoginFailed &exception) {

			LoginMenu::loginMenu->textError->setText(
					exception.getFehler());
			LoginMenu::loginMenu->background->setzeKeyboardAnzeigen(
					true);
			LoginMenu::loginMenu->textError->visible(true);
			LoginMenu::loginMenu->textUsername->visible(true);
			LoginMenu::loginMenu->textFieldUsername->visible(
					true);
			LoginMenu::loginMenu->textPassword->visible(true);
			LoginMenu::loginMenu->textFieldPassword->setText("");
			LoginMenu::loginMenu->textFieldPassword->visible(
					true);
			LoginMenu::loginMenu->buttonAnmelden->visible(true);
			LoginMenu::loginMenu->textAnmelden->visible(false);
			continue;
		}

		HTTPSessionRefreshThread::aktualisiereSessionRegelmaessig();

		break;
	}
}

void LoginMenu::anmelden() {
	pthread_mutex_lock(&LoginMenu::loginMenu->mutexwait);
	pthread_cond_signal(&LoginMenu::loginMenu->condwait);
	pthread_mutex_unlock(&LoginMenu::loginMenu->mutexwait);
}

void LoginMenu::auswaehlenBunutzer() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			LoginMenu::loginMenu->textFieldUsername);
}

void LoginMenu::auswaehlenPasswort() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			LoginMenu::loginMenu->textFieldPassword);
}
