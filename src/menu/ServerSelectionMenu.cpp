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

#include "ServerSelectionMenu.h"

#include <cstdlib>
#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../protocol/Connection.h"
#include "../protocol/packet/Packet02Handshake.h"
#include "../gui/Background.h"
#include "../gui/TextField.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/Texture.h"
#include "../gui/GraphicHandler.h"
#include "../protocol/Session.h"
#include "../exception/ExcSocketHTTPServerLoginFailed.h"

using namespace std;

ServerSelectionMenu *ServerSelectionMenu::serverAuswahlMenue;

void ServerSelectionMenu::initialize() {
	ServerSelectionMenu::serverAuswahlMenue = new ServerSelectionMenu();
}

void ServerSelectionMenu::deinitialize() {
	delete ServerSelectionMenu::serverAuswahlMenue;
}

ServerSelectionMenu::ServerSelectionMenu() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->background = new Background("pictureMenueBackground");
	this->background->setzeKeyboardAnzeigen(true);
	this->background->setzeCursorAnzeigen(true);

	Texture *picture = new Texture(144, 20, "logo");
	this->textFehler = new Text(250, 260, "");
	this->textFehler->setBackgroundColor(0xff33337f);
	this->textBetreten = new Text(200, 160, "Server betreten...");
	this->textBetreten->visible(false);

	this->textServer = new Text(250, 124, "Server:");
	this->textFeldServer = new TextField(250, 140, "");
	this->textFeldServer->setzeBeimKlicken(
			&ServerSelectionMenu::auswaehlenServer);
	this->textPort = new Text(250, 164, "Port:");
	this->textFeldPort = new TextField(250, 180, "25565");
	this->textFeldPort->setzeBeimKlicken(&ServerSelectionMenu::auswaehlenPort);
	this->buttonBetreten = new Button(254, 220, "Betreten");
	this->buttonBetreten->setzeBeimKlicken(&ServerSelectionMenu::betreten);

	this->background->fuegeUnterElementHinzu(picture);
	this->background->fuegeUnterElementHinzu(this->textFehler);
	this->background->fuegeUnterElementHinzu(this->textBetreten);
	this->background->fuegeUnterElementHinzu(this->textServer);
	this->background->fuegeUnterElementHinzu(this->textFeldServer);
	this->background->fuegeUnterElementHinzu(this->textPort);
	this->background->fuegeUnterElementHinzu(this->textFeldPort);
	this->background->fuegeUnterElementHinzu(this->buttonBetreten);
}

ServerSelectionMenu::~ServerSelectionMenu() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

void ServerSelectionMenu::zeigeServerSelectionMenu() {
	GraphicHandler::getGraphicHandler()->setzeAnzeigeElement(
			ServerSelectionMenu::serverAuswahlMenue->background);
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerSelectionMenu::serverAuswahlMenue->textFeldServer);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		ServerSelectionMenu::serverAuswahlMenue->textFeldServer->setText(
				input);

		input = "";
		getline(cin, input);

		ServerSelectionMenu::serverAuswahlMenue->textFeldPort->setText(
				input);

		ServerSelectionMenu::serverAuswahlMenue->buttonBetreten->beimKlicken(0);
#else
		pthread_mutex_lock(&ServerSelectionMenu::serverAuswahlMenue->mutexwait);
		pthread_cond_wait(&ServerSelectionMenu::serverAuswahlMenue->condwait,
				&ServerSelectionMenu::serverAuswahlMenue->mutexwait);
		pthread_mutex_unlock(
				&ServerSelectionMenu::serverAuswahlMenue->mutexwait);
#endif
		ServerSelectionMenu::serverAuswahlMenue->background->setzeKeyboardAnzeigen(
				false);
		ServerSelectionMenu::serverAuswahlMenue->textFehler->visible(false);
		ServerSelectionMenu::serverAuswahlMenue->textServer->visible(false);
		ServerSelectionMenu::serverAuswahlMenue->textFeldServer->visible(
				false);
		ServerSelectionMenu::serverAuswahlMenue->textPort->visible(false);
		ServerSelectionMenu::serverAuswahlMenue->textFeldPort->visible(
				false);
		ServerSelectionMenu::serverAuswahlMenue->buttonBetreten->visible(
				false);
		ServerSelectionMenu::serverAuswahlMenue->textBetreten->visible(
				true);

		try {
			string _server =
					ServerSelectionMenu::serverAuswahlMenue->textFeldServer->getText();
			string _portString =
					ServerSelectionMenu::serverAuswahlMenue->textFeldPort->getText();
			int _portInt = atoi(_portString.c_str());
			bool verbunden = Connection::verbinde(_server, _portInt);

			if (verbunden) {
				Connection::starteSchnittstelle();

				string usernameAndHost;
				usernameAndHost.append(Session::getUsername());
				usernameAndHost.append(";");
				usernameAndHost.append(_server);
				usernameAndHost.append(";");
				usernameAndHost.append(_portString);

				PacketClient *p = new Packet02Handshake(usernameAndHost);
				Connection::zuVerschickendenPacketenHinzufuegen(p);
			} else {
				throw ExcSocketHTTPServerLoginFailed(
						"Connection zum Server konnte nicht hergestellt werden.");
			}
		} catch (ExcSocketHTTPServerLoginFailed &exception) {

			ServerSelectionMenu::serverAuswahlMenue->textFehler->setText(
					exception.getFehler());
			ServerSelectionMenu::serverAuswahlMenue->background->setzeKeyboardAnzeigen(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textFehler->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textServer->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textFeldServer->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textPort->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textFeldPort->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->buttonBetreten->visible(
					true);
			ServerSelectionMenu::serverAuswahlMenue->textBetreten->visible(
					false);
			continue;
		}
		break;
	}
}

void ServerSelectionMenu::betreten() {
	pthread_mutex_lock(&ServerSelectionMenu::serverAuswahlMenue->mutexwait);
	pthread_cond_signal(&ServerSelectionMenu::serverAuswahlMenue->condwait);
	pthread_mutex_unlock(&ServerSelectionMenu::serverAuswahlMenue->mutexwait);
}

void ServerSelectionMenu::auswaehlenServer() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerSelectionMenu::serverAuswahlMenue->textFeldServer);
}

void ServerSelectionMenu::auswaehlenPort() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerSelectionMenu::serverAuswahlMenue->textFeldPort);
}
