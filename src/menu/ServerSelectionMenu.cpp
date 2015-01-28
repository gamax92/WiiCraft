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

ServerAuswahlMenue *ServerAuswahlMenue::serverAuswahlMenue;

void ServerAuswahlMenue::initialize() {
	ServerAuswahlMenue::serverAuswahlMenue = new ServerAuswahlMenue();
}

void ServerAuswahlMenue::deinitialize() {
	delete ServerAuswahlMenue::serverAuswahlMenue;
}

ServerAuswahlMenue::ServerAuswahlMenue() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->hintergrund = new Background("bildMenueHintergrund");
	this->hintergrund->setzeKeyboardAnzeigen(true);
	this->hintergrund->setzeCursorAnzeigen(true);

	Texture *bild = new Texture(144, 20, "logo");
	this->textFehler = new Text(250, 260, "");
	this->textFehler->setBackgroundColor(0xff33337f);
	this->textBetreten = new Text(200, 160, "Server betreten...");
	this->textBetreten->visible(false);

	this->textServer = new Text(250, 124, "Server:");
	this->textFeldServer = new TextField(250, 140, "");
	this->textFeldServer->setzeBeimKlicken(
			&ServerAuswahlMenue::auswaehlenServer);
	this->textPort = new Text(250, 164, "Port:");
	this->textFeldPort = new TextField(250, 180, "25565");
	this->textFeldPort->setzeBeimKlicken(&ServerAuswahlMenue::auswaehlenPort);
	this->buttonBetreten = new Button(254, 220, "Betreten");
	this->buttonBetreten->setzeBeimKlicken(&ServerAuswahlMenue::betreten);

	this->hintergrund->fuegeUnterElementHinzu(bild);
	this->hintergrund->fuegeUnterElementHinzu(this->textFehler);
	this->hintergrund->fuegeUnterElementHinzu(this->textBetreten);
	this->hintergrund->fuegeUnterElementHinzu(this->textServer);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldServer);
	this->hintergrund->fuegeUnterElementHinzu(this->textPort);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldPort);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonBetreten);
}

ServerAuswahlMenue::~ServerAuswahlMenue() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

void ServerAuswahlMenue::zeigeServerAuswahlMenue() {
	GraphicHandler::getGraphicHandler()->setzeAnzeigeElement(
			ServerAuswahlMenue::serverAuswahlMenue->hintergrund);
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->setText(
				input);

		input = "";
		getline(cin, input);

		ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->setText(
				input);

		ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->beimKlicken(0);
#else
		pthread_mutex_lock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
		pthread_cond_wait(&ServerAuswahlMenue::serverAuswahlMenue->condwait,
				&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
		pthread_mutex_unlock(
				&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
#endif
		ServerAuswahlMenue::serverAuswahlMenue->hintergrund->setzeKeyboardAnzeigen(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textFehler->visible(false);
		ServerAuswahlMenue::serverAuswahlMenue->textServer->visible(false);
		ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->visible(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textPort->visible(false);
		ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->visible(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->visible(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textBetreten->visible(
				true);

		try {
			string _server =
					ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->getText();
			string _portString =
					ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->getText();
			int _portInt = atoi(_portString.c_str());
			bool verbunden = Verbindung::verbinde(_server, _portInt);

			if (verbunden) {
				Verbindung::starteSchnittstelle();

				string usernameAndHost;
				usernameAndHost.append(Session::getUsername());
				usernameAndHost.append(";");
				usernameAndHost.append(_server);
				usernameAndHost.append(";");
				usernameAndHost.append(_portString);

				PacketClient *p = new Packet02Handshake(usernameAndHost);
				Verbindung::zuVerschickendenPacketenHinzufuegen(p);
			} else {
				throw ExcSocketHTTPServerLoginFailed(
						"Verbindung zum Server konnte nicht hergestellt werden.");
			}
		} catch (ExcSocketHTTPServerLoginFailed &exception) {

			ServerAuswahlMenue::serverAuswahlMenue->textFehler->setText(
					exception.getFehler());
			ServerAuswahlMenue::serverAuswahlMenue->hintergrund->setzeKeyboardAnzeigen(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFehler->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textServer->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textPort->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->visible(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textBetreten->visible(
					false);
			continue;
		}
		break;
	}
}

void ServerAuswahlMenue::betreten() {
	pthread_mutex_lock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
	pthread_cond_signal(&ServerAuswahlMenue::serverAuswahlMenue->condwait);
	pthread_mutex_unlock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
}

void ServerAuswahlMenue::auswaehlenServer() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer);
}

void ServerAuswahlMenue::auswaehlenPort() {
	GraphicHandler::getGraphicHandler()->setSelectedElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldPort);
}
