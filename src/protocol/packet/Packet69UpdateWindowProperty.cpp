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

#include "Packet69UpdateWindowProperty.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet69UpdateWindowProperty::Packet69UpdateWindowProperty() {
	PacketServer::id = 0x69;
	PacketServer::prio = 50;
}

PacketServer *Packet69UpdateWindowProperty::gebeInstanz() {
	return new Packet69UpdateWindowProperty();
}

bool Packet69UpdateWindowProperty::registierePacket() {
	PacketManager::registrierePacket(new Packet69UpdateWindowProperty());

	return true;
}

void Packet69UpdateWindowProperty::lesePacketInhalt(DataInputStream *in) {
	this->windowId = in->readByte();
	this->property = in->readShort();
	this->value = in->readShort();
}

void Packet69UpdateWindowProperty::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer, "windowId: %i, property: %i, value: %i", this->windowId,
			this->property, this->value);
	Debug::schreibePacketLog("Packet69UpdateWindowProperty", buffer);
	delete[] buffer;
#endif

	// TODO Packetverarbeitung implementieren
}
