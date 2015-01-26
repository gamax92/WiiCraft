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

#include "Paket01LoginRequest.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../entity/Spieler.h"
#include "../../world/Welt.h"
#include "../../protocol/Chat.h"
#include "../../protocol/ServerInfo.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket01LoginRequest::Paket01LoginRequest() {
	PaketServer::id = 0x01;
	PaketServer::prio = 0;
}

Paket01LoginRequest::Paket01LoginRequest(int _protocolVersion,
		string _userName) {
	PaketClient::id = 0x01;
	PaketClient::prio = 50;

	this->protocolVersion = _protocolVersion;
	this->userName = _userName;
}

PaketServer *Paket01LoginRequest::gebeInstanz() {
	return new Paket01LoginRequest();
}

bool Paket01LoginRequest::registierePaket() {
	PaketManager::registrierePaket(new Paket01LoginRequest());

	return true;
}

void Paket01LoginRequest::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->protocolVersion);
	out->schreibeString(this->userName);
	out->schreibeString("");
	out->schreibeInt(0);
	out->schreibeInt(0);
	out->schreibeByte(0);
	out->schreibeByte(0);
	out->schreibeByte(0);
}

void Paket01LoginRequest::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();

	try {
		in->leseString(16);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}

	try {
		this->levelType = in->leseString(16);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}

	this->serverMode = in->leseInt();
	this->dimension = in->leseInt();
	this->difficulty = in->leseByte();
	this->worldHeight = in->leseByte();
	this->maxPlayers = in->leseByte();
}

void Paket01LoginRequest::verarbeitePaket() {
	Spieler::initialisiereSpieler(this->entityId);
	Welt::initialisiereWelt(this->dimension, this->levelType, this->difficulty,
			this->serverMode, this->worldHeight);
	ServerInfo::initialisiereServerInfo(this->maxPlayers);
	Chat::initialisiereChat();

#ifdef DEBUG_ON
	char *buffer = new char[1000];
	sprintf(buffer,
			"entityId: %i, levelType: %s, serverMode: %i, dimension: %i, difficulty: %i, worldHeight: %i, maxPlayers: %i",
			this->entityId, this->levelType.data(), this->serverMode,
			this->dimension, this->difficulty, this->worldHeight,
			this->maxPlayers);
	Debug::schreibePaketLog("Paket01LoginRequest", buffer);
	delete[] buffer;
#endif
}
