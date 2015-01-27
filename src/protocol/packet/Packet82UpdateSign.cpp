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

#include "Packet82UpdateSign.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet82UpdateSign::Packet82UpdateSign() {
	PacketServer::id = 0x82;
	PacketServer::prio = 50;
}

Packet82UpdateSign::Packet82UpdateSign(int _x, short _y, int _z, string _text1,
		string _text2, string _text3, string _text4) {
	PacketClient::id = 0x82;
	PacketClient::prio = 50;

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->text1 = _text1;
	this->text2 = _text2;
	this->text3 = _text3;
	this->text4 = _text4;
}

PacketServer *Packet82UpdateSign::gebeInstanz() {
	return new Packet82UpdateSign();
}

bool Packet82UpdateSign::registierePacket() {
	PacketManager::registrierePacket(new Packet82UpdateSign());

	return true;
}

void Packet82UpdateSign::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->x);
	out->schreibeShort(this->y);
	out->schreibeInt(this->z);
	out->schreibeString(this->text1);
	out->schreibeString(this->text2);
	out->schreibeString(this->text3);
	out->schreibeString(this->text4);
}

void Packet82UpdateSign::lesePacketInhalt(DataInputStream *in) {
	this->x = in->leseInt();
	this->y = in->readShort();
	this->z = in->leseInt();

	try {
		this->text1 = in->leseString(15);
		this->text2 = in->leseString(15);
		this->text3 = in->leseString(15);
		this->text4 = in->leseString(15);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PacketServer::id);
	}
}

void Packet82UpdateSign::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[300];
	sprintf(buffer,
			"x: %i, y: %i, z: %i, text1: %s, text2: %s, text3: %s, text4: %s",
			this->x, this->y, this->z, this->text1.data(), this->text2.data(),
			this->text3.data(), this->text4.data());
	Debug::schreibePacketLog("Packet82UpdateSign", buffer);
	delete[] buffer;
#endif

	// TODO Packetverarbeitung implementieren
}
