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

#include "PacketCAPlayerAbilities.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../entity/Spieler.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

PacketCAPlayerAbilities::PacketCAPlayerAbilities() {
	PacketServer::id = 0xca;
	PacketServer::prio = 50;
}

PacketCAPlayerAbilities::PacketCAPlayerAbilities(bool _invulnerability,
		bool _isFlying, bool _canFly, bool _instantDestroy) {
	PacketClient::id = 0xca;
	PacketClient::prio = 50;

	this->invulnerability = _invulnerability;
	this->isFlying = _isFlying;
	this->canFly = _canFly;
	this->instantDestroy = _instantDestroy;
}

PacketServer *PacketCAPlayerAbilities::gebeInstanz() {
	return new PacketCAPlayerAbilities();
}

bool PacketCAPlayerAbilities::registierePacket() {
	PacketManager::registrierePacket(new PacketCAPlayerAbilities());

	return true;
}

void PacketCAPlayerAbilities::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeBoolean(this->invulnerability);
	out->schreibeBoolean(this->isFlying);
	out->schreibeBoolean(this->canFly);
	out->schreibeBoolean(this->instantDestroy);
}

void PacketCAPlayerAbilities::lesePacketInhalt(DataInputStream *in) {
	this->invulnerability = in->leseBoolean();
	this->isFlying = in->leseBoolean();
	this->canFly = in->leseBoolean();
	this->instantDestroy = in->leseBoolean();
}

void PacketCAPlayerAbilities::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer,
			"invulnerability: %i, isFlying: %i, canFly: %i, instantDestroy: %i",
			this->invulnerability, this->isFlying, this->canFly,
			this->instantDestroy);
	Debug::schreibePacketLog("PacketCAPlayerAbilities", buffer);
	delete[] buffer;
#endif

	Spieler::getSpieler()->setzeFaehigkeit(this->isFlying, this->canFly,
			this->instantDestroy, this->invulnerability);
}
