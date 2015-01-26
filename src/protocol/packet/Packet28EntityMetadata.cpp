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

#include "Packet28EntityMetadata.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataInputStream.h"
#include "../../entity/Metadata.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../exception/ExcMetadata.h"
#include "../../entity/Entity.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet28EntityMetadata::Packet28EntityMetadata() {
	PacketServer::id = 0x28;
	PacketServer::prio = 50;
}

Packet28EntityMetadata::~Packet28EntityMetadata() {
	delete this->entityMetadata;
}

PacketServer *Packet28EntityMetadata::gebeInstanz() {
	return new Packet28EntityMetadata();
}

bool Packet28EntityMetadata::registierePacket() {
	PacketManager::registrierePacket(new Packet28EntityMetadata());

	return true;
}

void Packet28EntityMetadata::lesePacketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	try {
		this->entityMetadata = Metadata::leseDaten(in);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PacketServer::id);
	} catch (ExcMetadata &exception) {
		throw ExcMetadata(PacketServer::id);
	}
}

void Packet28EntityMetadata::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "entityId: %i", this->entityId);
	Debug::schreibePacketLog("Packet28EntityMetadata", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Packetverarbeitung implementieren
}
