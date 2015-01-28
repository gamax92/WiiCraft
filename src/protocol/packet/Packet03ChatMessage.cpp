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

#include "Packet03ChatMessage.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringTooLong.h"
#include "../../protocol/Chat.h"
#include "../PacketManager.h"
#include "../../util/Debug.h"

using namespace std;

Packet03ChatMessage::Packet03ChatMessage() {
	PacketServer::id = 0x03;
	PacketServer::prio = 50;
}

Packet03ChatMessage::Packet03ChatMessage(string _message) {
	PacketClient::id = 0x03;
	PacketClient::prio = 50;

	this->message = _message;
}

PacketServer *Packet03ChatMessage::getInstance() {
	return new Packet03ChatMessage();
}

bool Packet03ChatMessage::registerPacket() {
	PacketManager::registerPacket(new Packet03ChatMessage());

	return true;
}

void Packet03ChatMessage::schreibePacketInhalt(DataOutputStream *out) {
	out->schreibeString(this->message);
}

void Packet03ChatMessage::lesePacketInhalt(DataInputStream *in) {
	try {
		this->message = in->leseString(119);
	} catch (ExcSocketStringTooLong &exception) {
		throw ExcSocketStringTooLong(PacketServer::id);
	}
}

void Packet03ChatMessage::verarbeitePacket() {
	// Steuerzeichen �
	//this->message.substr(0, 1);

	// Farbcode
	string color = this->message.substr(1, 1);

	// eigentliche Nachricht
	string message = this->message.substr(2);

#ifdef DEBUG_ON
	string farbcode;
	if (color == "0") {
		farbcode = "#000000";
	} else if (color == "1") {
		farbcode = "#0000aa";
	} else if (color == "2") {
		farbcode = "#00aa00";
	} else if (color == "3") {
		farbcode = "#00aaaa";
	} else if (color == "4") {
		farbcode = "#aa0000";
	} else if (color == "5") {
		farbcode = "#aa00aa";
	} else if (color == "6") {
		farbcode = "#ffaa00";
	} else if (color == "7") {
		farbcode = "#aaaaaa";
	} else if (color == "8") {
		farbcode = "#555555";
	} else if (color == "9") {
		farbcode = "#5555ff";
	} else if (color == "a") {
		farbcode = "#55ff55";
	} else if (color == "b") {
		farbcode = "#55ffff";
	} else if (color == "c") {
		farbcode = "#ff5555";
	} else if (color == "d") {
		farbcode = "#ff55ff";
	} else if (color == "e") {
		farbcode = "#ffff55";
	} else if (color == "f") {
		farbcode = "#ffffff";
	} else {
		farbcode = "unbakannt";
	}

	char *buffer = new char[200];
	sprintf(buffer, "farbe=%s, text=%s", farbcode.data(), message.data());
	Debug::schreibePacketLog("Packet03ChatMessage", buffer);
	delete[] buffer;
#endif

	Chat::getChat()->addMessage(message, color);
}
