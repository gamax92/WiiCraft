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

#include "Block006Sapling.h"

#include "../../util/GrrlibReplacement.h"
#include "../ItemManager.h"

using namespace std;

Item *Block006Sapling::getInstance() {
	return new Block006Sapling();
}

bool Block006Sapling::registiereItem() {
	ItemManager::registriereItem(new Block006Sapling());

	return true;
}

Block006Sapling::Block006Sapling() {
	this->setzeStandardWerte();

	Item::id = 0x006;
}

void Block006Sapling::zeichne(float x, float y, float z, byte meta) {
	// TODO je nach Metadaten das korrekte Picture laden
	// Dieser Wert ist zweigeteilt. Die erste Haelfte ist ein Zaehler von 0 bis 3,
	// der in zufaelligen Abstaenden um eins weiterlaeuft. Sobald der Zaehler 3 erreicht,
	// wird der Setzling durch einen Baum ersetzt. Die zweite Haelfte reicht von 0 bis 3
	// und definiert die Baumart. Dieser Wert ist identisch mit Baumstaemmen und Blaettern.

	ItemBlock::zeichnePflanze(x, y, z, 15);
}

bool Block006Sapling::istDurchsichtig() {
	return true;
}
