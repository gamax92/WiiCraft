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

#include "PacketFAPluginmessage.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringTooLong.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

PacketFAPluginmessage::PacketFAPluginmessage() {
	PacketServer::id = 0xfa;
	PacketServer::prio = 50;
}

PacketFAPluginmessage::PacketFAPluginmessage(string _channel, short _length,
		byte *_data) {
	PacketClient::id = 0xfa;
	PacketClient::prio = 50;

	this->channel = _channel;
	this->length = _length;
	this->data = _data;
}

PacketFAPluginmessage::~PacketFAPluginmessage() {
	free(this->data);
}

PacketServer *PacketFAPluginmessage::getInstance() {
	return new PacketFAPluginmessage();
}

bool PacketFAPluginmessage::registerPacket() {
	PacketManager::registerPacket(new PacketFAPluginmessage());

	return true;
}

void PacketFAPluginmessage::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeString(this->channel);
	out->schreibeShort(this->length);
	for (short i = 0; i < this->length; i++) {
		out->schreibeByte(this->data[i]);
	}
}

void PacketFAPluginmessage::lesePacketInhalt(DataInputStream *in) {
	try {
		this->channel = in->leseString(16);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}

	this->length = in->readShort();
	this->data = new byte[this->length];

	for (short i = 0; i < this->length; i++) {
		this->data[i] = in->readByte();
	}
}

void PacketFAPluginmessage::verarbeitePacket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer, "channel: %s, length: %i", this->channel.data(),
			this->length);
	Debug::schreibePacketLog("PacketFAPluginmessage", buffer);
	delete[] buffer;
#endif
	// TODO nur fuer Plugin API
}
