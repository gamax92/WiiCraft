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

#include "Packet02Handshake.h"

#include <cstdio>
#include "../Connection.h"
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "Packet01LoginRequest.h"
#include "../../exception/ExcSocketStringTooLong.h"
#include "../../exception/ExcSocketHTTPServerJoinFailed.h"
#include "../Session.h"
#include "../../util/ClientInfo.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet02Handshake::Packet02Handshake() {
	PacketServer::id = 0x02;
	PacketServer::prio = 50;
}

Packet02Handshake::Packet02Handshake(string _usernameAndHost) {
	PacketClient::id = 0x02;
	PacketClient::prio = 50;

	this->usernameAndHost = _usernameAndHost;
}

PacketServer *Packet02Handshake::getInstance() {
	return new Packet02Handshake();
}

bool Packet02Handshake::registerPacket() {
	PacketManager::registerPacket(new Packet02Handshake());

	return true;
}

void Packet02Handshake::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeString(this->usernameAndHost);
}

void Packet02Handshake::lesePacketInhalt(DataInputStream *in) {
	try {
		this->connectionHash = in->leseString(32);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}
}

void Packet02Handshake::verarbeitePacket() {
#ifdef DEBUG_ON
	Debug::schreibePacketLog("Packet02Handshake", this->connectionHash);
#endif

	if (this->connectionHash != "+") {
		Session::tretteServerBei(this->connectionHash);
	}

	PacketClient *p = new Packet01LoginRequest(ClientInfo::clientProtokollVersion,
			Session::getUsername());
	Connection::zuVerschickendenPacketenHinzufuegen(p);
}
