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

#include "Packet09Respawn.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringTooLong.h"
#include "../../world/Welt.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet09Respawn::Packet09Respawn() {
	PacketServer::id = 0x09;
	PacketServer::prio = 50;
}

Packet09Respawn::Packet09Respawn(int _dimension, byte _difficulty,
		byte _creativeMode, short _worldHeight, string _levelType) {
	PacketClient::id = 0x09;
	PacketClient::prio = 50;

	this->dimension = _dimension;
	this->difficulty = _difficulty;
	this->creativeMode = _creativeMode;
	this->worldHeight = _worldHeight;
	this->levelType = _levelType;
}

PacketServer *Packet09Respawn::gebeInstanz() {
	return new Packet09Respawn();
}

bool Packet09Respawn::registierePacket() {
	PacketManager::registrierePacket(new Packet09Respawn());

	return true;
}

void Packet09Respawn::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->dimension);
	out->schreibeByte(this->difficulty);
	out->schreibeByte(this->creativeMode);
	out->schreibeShort(this->worldHeight);
	out->schreibeString(this->levelType);
}

void Packet09Respawn::lesePacketInhalt(DataInputStream *in) {
	this->dimension = in->leseInt();
	this->difficulty = in->readByte();
	this->creativeMode = in->readByte();
	this->worldHeight = in->readShort();

	try {
		this->levelType = in->leseString(16);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}
}

void Packet09Respawn::verarbeitePacket() {
	World::initialisiereWelt(this->dimension, this->levelType, this->difficulty,
			this->creativeMode, this->worldHeight);

#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(
			buffer,
			"dimension: %i, difficulty: %i, creativeMode: %i, worldHeight: %i, levelType: %s",
			this->dimension, this->difficulty, this->creativeMode,
			this->worldHeight, this->levelType.data());
	Debug::schreibePacketLog("Packet09Respawn", buffer);
	delete[] buffer;
#endif
}
