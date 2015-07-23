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

#include "Block062StonezBrick.h"

#include "../ItemManager.h"

using namespace std;

Item *Block062StonezBrick::getInstance() {
	return new Block062StonezBrick();
}

bool Block062StonezBrick::registiereItem() {
	ItemManager::registriereItem(new Block062StonezBrick());

	return true;
}

Block062StonezBrick::Block062StonezBrick() {
	this->setzeStandardWerte();

	Item::id = 0x062;
}

void Block062StonezBrick::zeichne(float x, float y, float z, byte meta) {

	if (meta == 1) { // Bemoost
		ItemBlock::zeichneBlock(x, y, z, 100);
	} else if (meta == 2) { // Rissig
		ItemBlock::zeichneBlock(x, y, z, 101);
	} else if (meta == 3) { // Kaestchen
		ItemBlock::zeichneBlock(x, y, z, 213);
	} else { // Normal
		ItemBlock::zeichneBlock(x, y, z, 54);
	}
}

bool Block062StonezBrick::istDurchsichtig() {
	return false;
}
