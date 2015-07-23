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

#include "PacketProcessingThread.h"

#include <cstdio>
#include "../protocol/PacketServer.h"
#include "../exception/ExcThreadStopped.h"
#include "../util/Debug.h"

using namespace std;

PacketProcessingThread::PacketProcessingThread() {
	this->gestoppt = false;

	pthread_mutex_init(&this->mutexqueue, NULL);
	pthread_mutex_init(&this->mutexstop, NULL);
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);
}

PacketProcessingThread::~PacketProcessingThread() {
	pthread_mutex_destroy(&this->mutexqueue);
	pthread_mutex_destroy(&this->mutexstop);
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

int PacketProcessingThread::exec() {
	bool ok;
	do {
		ok = this->gebeNaechstesPacket();
	} while (ok);

	return 0;
}

void PacketProcessingThread::verarbeitePacket(PacketServer *p) {
	if (this->istGestopped()) {
		return;
	}

	pthread_mutex_lock(&this->mutexqueue);

	this->verarbeitungPuffer.push(p);
	pthread_mutex_unlock(&this->mutexqueue);

	pthread_mutex_lock(&this->mutexwait);
	pthread_cond_signal(&this->condwait);
	pthread_mutex_unlock(&this->mutexwait);
}

bool PacketProcessingThread::gebeNaechstesPacket() {
	pthread_mutex_lock(&this->mutexqueue);
	bool leer = this->verarbeitungPuffer.empty();
	pthread_mutex_unlock(&this->mutexqueue);

	if (leer) {
		pthread_mutex_lock(&this->mutexwait);
		pthread_cond_wait(&this->condwait, &this->mutexwait);
		pthread_mutex_unlock(&this->mutexwait);
	}

	if (this->istGestopped()) {
		pthread_mutex_lock(&this->mutexqueue);

#ifdef DEBUG_ON
		char *buffer = new char[100];
		pthread_mutex_lock(&this->mutexqueue);
		sprintf(buffer, "Verarbeitung wird gestoppt, Queue: %i\n",
				this->verarbeitungPuffer.size());
		pthread_mutex_unlock(&this->mutexqueue);
		Debug::schreibeLog("sd:/apps/WiiCraft/Packet.log", buffer,
				Debug::DATEI_ERWEITERN);
		delete[] buffer;
#endif

		this->verarbeitungPuffer = priority_queue<PacketServer *,
				vector<PacketServer*>, PacketMatcher>();
		pthread_mutex_unlock(&this->mutexqueue);

		return false;
	}

	pthread_mutex_lock(&this->mutexqueue);
	PacketServer *p = this->verarbeitungPuffer.top();
	this->verarbeitungPuffer.pop();
	pthread_mutex_unlock(&this->mutexqueue);

	p->verarbeitePacket();

	delete p;

	return true;
}

void PacketProcessingThread::stop() {
	pthread_mutex_lock(&this->mutexstop);
	this->gestoppt = true;
	pthread_mutex_unlock(&this->mutexstop);

	pthread_mutex_lock(&this->mutexwait);
	pthread_cond_signal(&this->condwait);
	pthread_mutex_unlock(&this->mutexwait);
}

bool PacketProcessingThread::istGestopped() {
	pthread_mutex_lock(&this->mutexstop);
	bool b = this->gestoppt;
	pthread_mutex_unlock(&this->mutexstop);

	return b;
}
