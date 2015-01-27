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

#include "Packet34MultiBlockChange.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../world/World.h"
#include "../../world/BlockChange.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet34MultiBlockChange::Packet34MultiBlockChange() {
	PacketServer::id = 0x34;
	PacketServer::prio = 50;
}

Packet34MultiBlockChange::~Packet34MultiBlockChange() {
	delete[] this->data;

	this->data = NULL;
}

PacketServer *Packet34MultiBlockChange::gebeInstanz() {
	return new Packet34MultiBlockChange();
}

bool Packet34MultiBlockChange::registierePacket() {
	PacketManager::registrierePacket(new Packet34MultiBlockChange());

	return true;
}

void Packet34MultiBlockChange::lesePacketInhalt(DataInputStream *in) {
	this->chunkX = in->leseInt();
	this->chunkZ = in->leseInt();
	this->recordCount = in->readShort() & 0xffff;
	this->dataSize = in->leseInt();

	this->data = new byte[this->dataSize];

	this->data = in->leseBytes(this->dataSize);
}

void Packet34MultiBlockChange::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "chunk: %ix%i, count: %i", this->chunkX, this->chunkZ,
			this->recordCount);
	Debug::schreibePacketLog("Packet34MultiBlockChange", buffer);
	delete[] buffer;
	buffer = NULL;
#endif

	short datenPosition = 0;
	for (unsigned short i = 0; i < this->recordCount; i++) {

		/*
		 * 00 00 00 0F	4 bits	Block metadata
		 * 00 00 FF F0	12 bits	Block ID
		 * 00 FF 00 00	8 bits	Y co-ordinate
		 * 0F 00 00 00	4 bits	Z co-ordinate, relative to chunk
		 * F0 00 00 00	4 bits	X co-ordinate, relative to chunk
		 */

		byte byte0 = this->data[datenPosition];
		byte byte1 = this->data[datenPosition + 1];
		byte byte2 = this->data[datenPosition + 2];
		byte byte3 = this->data[datenPosition + 3];

		short blockTyp = (byte2 << 4) | ((byte3 & 0xf0) >> 4);
		byte blockMetadata = (byte3 & 0x0f);
		byte x = ((byte0 & 0xf0) >> 4);
		byte z = (byte0 & 0x0f);
		byte y = byte1;

		short index = World::getWorld()->berechneIndex(x, y, z);

#ifdef DEBUG_ON
		char *buffer = new char[100];
		sprintf(
				buffer,
				"blockTyp: %i, blockMetadata: %i, x: %i, z: %i, y: %i, index: %i",
				blockTyp, blockMetadata, x, z, y, index);
		Debug::schreibePacketLog("Packet34MultiBlockChange", buffer);
		delete[] buffer;
		buffer = NULL;
#endif

		BlockAenderung * b = new BlockAenderung(index, blockTyp, blockMetadata);
		World::getWorld()->ergaenzeBlockAenderung(this->chunkX, this->chunkZ, b);

		datenPosition += 4;
	}
}
