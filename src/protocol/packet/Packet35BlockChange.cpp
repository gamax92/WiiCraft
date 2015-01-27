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

#include "Packet35BlockChange.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../world/Welt.h"
#include "../../world/BlockAenderung.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet35BlockChange::Packet35BlockChange() {
	PacketServer::id = 0x35;
	PacketServer::prio = 50;
}

PacketServer *Packet35BlockChange::gebeInstanz() {
	return new Packet35BlockChange();
}

bool Packet35BlockChange::registierePacket() {
	PacketManager::registrierePacket(new Packet35BlockChange());

	return true;
}

void Packet35BlockChange::lesePacketInhalt(DataInputStream *in) {
	this->x = in->leseInt();
	this->y = in->readByte();
	this->z = in->leseInt();
	this->blockType = in->readByte();
	this->blockMetadata = in->readByte();
}

void Packet35BlockChange::verarbeitePacket() {
	int chunkX;
	int chunkZ;
	World::calculateChunkPosition(this->x, this->z, chunkX, chunkZ);

	byte startX;
	byte startY;
	byte startZ;
	World::getWorld()->getChunkPos(this->x, this->y, this->z, startX, startY,
			startZ);

	short index = World::getWorld()->berechneIndex(startX, startY, startZ);

	BlockAenderung * b = new BlockAenderung(index, this->blockType,
			this->blockMetadata);
	World::getWorld()->ergaenzeBlockAenderung(chunkX, chunkZ, b);

#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "chunk: %ix%i, blockType: %i, blockMetadata: %i, index: %i",
			chunkX, chunkZ, this->blockType, this->blockMetadata, index);
	Debug::schreibePacketLog("Packet35BlockChange", buffer);
	delete[] buffer;
#endif
}
