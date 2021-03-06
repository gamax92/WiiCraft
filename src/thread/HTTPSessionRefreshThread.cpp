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

#include "HTTPSessionRefreshThread.h"

#include <unistd.h>
#include "../protocol/Session.h"
#include "../exception/ExcSocketHTTPServerRefreshFailed.h"

using namespace std;

HTTPSessionRefreshThread *HTTPSessionRefreshThread::sessionThread =
		NULL;

HTTPSessionRefreshThread::HTTPSessionRefreshThread() {
	this->gestoppt = false;

	pthread_mutex_init(&this->mutexStop, NULL);
}

HTTPSessionRefreshThread::~HTTPSessionRefreshThread() {
	pthread_mutex_destroy(&this->mutexStop);
}

void HTTPSessionRefreshThread::aktualisiereSessionRegelmaessig() {
	HTTPSessionRefreshThread::stoppeAktualisierung();

	HTTPSessionRefreshThread::sessionThread =
			new HTTPSessionRefreshThread();
	HTTPSessionRefreshThread::sessionThread->start();
}

void HTTPSessionRefreshThread::stoppeAktualisierung() {
	if (HTTPSessionRefreshThread::sessionThread != NULL) {
		HTTPSessionRefreshThread::sessionThread->stop();
		HTTPSessionRefreshThread::sessionThread = NULL;
	}
}

int HTTPSessionRefreshThread::exec() {
	bool ok = true;
	do {
		if (!this->istGestopped()) {
			try {
				Session::bleibeVerbunden();
			} catch (ExcSocketHTTPServerRefreshFailed &exception) {
				ok = false;
			}
		}

		// alle 5 Sekunden pr�fen ob der Thread beendet werden muss
		for (short i = 0; i < 60 && ok; i++) {
			if (this->istGestopped()) {
				ok = false;
				break;
			}
			usleep(5000000); // 5 Sekunden
		}
	} while (ok);

	return 0;
}

void HTTPSessionRefreshThread::stop() {
	pthread_mutex_lock(&this->mutexStop);
	this->gestoppt = true;
	pthread_mutex_unlock(&this->mutexStop);
}

bool HTTPSessionRefreshThread::istGestopped() {
	bool b = false;

	pthread_mutex_lock(&this->mutexStop);
	b = this->gestoppt;
	pthread_mutex_unlock(&this->mutexStop);

	return b;
}
