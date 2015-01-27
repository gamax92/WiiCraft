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

#include "Packet46NewInvalidState.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../world/Welt.h"
#include "../../exception/ExcPacketUnknownReason.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet46NewInvalidState::Packet46NewInvalidState() {
	PacketServer::id = 0x46;
	PacketServer::prio = 50;
}

PacketServer *Packet46NewInvalidState::gebeInstanz() {
	return new Packet46NewInvalidState();
}

bool Packet46NewInvalidState::registierePacket() {
	PacketManager::registrierePacket(new Packet46NewInvalidState());

	return true;
}

void Packet46NewInvalidState::lesePacketInhalt(DataInputStream *in) {
	this->reason = in->readByte();
	this->gameMode = in->readByte();
}

void Packet46NewInvalidState::verarbeitePacket() {
	if (this->reason == 0) {
		// Invalid Bed "tile.bed.notValid"
		// wird ignoriert
	} else if (this->reason == 1) {
		World::getWorld()->setzeRegen(true);
	} else if (this->reason == 2) {
		World::getWorld()->setzeRegen(false);
	} else if (this->reason == 3) {
		World::getWorld()->setzeServerModus(this->gameMode);
	} else if (this->reason == 4) {
		// Credits
		// wird ignoriert
	} else {
		throw ExcPacketUnknownReason(this->reason, this->gameMode);
	}

#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "reason: %x, gameMode: %x", this->reason, this->gameMode);
	Debug::schreibePacketLog("Packet46NewInvalidState", buffer);
	delete[] buffer;
#endif
}
