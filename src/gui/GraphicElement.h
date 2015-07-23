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

#ifndef GRAPHICELEMENT_H_
#define GRAPHICELEMENT_H_

#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include "../util/pthread.h"
#endif /* __wii__ */

namespace std {

class GraphicElement {
public:
	virtual ~GraphicElement();

	bool isVisible();
	bool istDeaktiviert();
	bool istAusgewaehlt();
	virtual void drawElement() = 0;
	void visible(bool _sichtbar);
	void deaktivieren(bool _deaktiviert);
	void selected(bool _ausgewaehlt);
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	void setX(float _x);
	void setY(float _y);
	void setWidth(float _breite);
	void setHeight(float _hoehe);
	void setzeCursorDarueber(bool _cursorDarueber);
	void setzeBeimKlicken(void(*_ausfuehrenBeimKlicken)());
	void beimKlicken(u32 gedrueckt);
protected:
	bool istCursorDarueber();
	void setzeStandardWerte();
private:
	bool sichtbar;
	bool deaktiviert;
	bool cursorDarueber;
	bool ausgewaehlt;
	float x;
	float y;
	float breite;
	float hoehe;
	void (*ausfuehrenBeimKlicken)();
	pthread_mutex_t mutexAusfuehrenBeimKlicken;
	pthread_mutex_t mutexSichtbarkeit;
	pthread_mutex_t mutexDeaktiviert;
	pthread_mutex_t mutexCursorDarueber;
	pthread_mutex_t mutexPosition;
	pthread_mutex_t mutexAusgewaehlt;

	static void tueNix();
};

}
#endif /* GRAPHICELEMENT_H_ */
