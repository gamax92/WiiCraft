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

#include "Keyboard.h"

#include <string>
#include "GraphicHandler.h"
#include "Button.h"

using namespace std;

bool Keyboard::initialisiert = false;
Keyboard *Keyboard::keyboard;

Keyboard::~Keyboard() {
}

Keyboard *Keyboard::getKeyboard() {
	if (!Keyboard::initialisiert) {
		Keyboard::keyboard = new Keyboard();
		Keyboard::initialisiert = true;
	}
	return Keyboard::keyboard;
}

Keyboard::Keyboard() {
	ContainerElement::setzeStandardWerte();

	this->setX(0);
	this->setY(300);
	this->setHeight(180);
	this->setWidth(640);

	char buchstabe;
	string *buchstabeS;

	// Button erstellen
	this->buttonAusrufeZeichen = new Button(20, 300, "!");
	this->button1 = new Button(20, 300, "1");
	this->buttonAt = new Button(70, 300, "@");
	this->button2 = new Button(70, 300, "2");
	this->buttonRaute = new Button(120, 300, "#");
	this->button3 = new Button(120, 300, "3");
	this->buttonDollar = new Button(170, 300, "$");
	this->button4 = new Button(170, 300, "4");
	this->buttonProzent = new Button(220, 300, "%");
	this->button5 = new Button(220, 300, "5");
	this->buttonDach = new Button(270, 300, "^");
	this->button6 = new Button(270, 300, "6");
	this->buttonUnd = new Button(320, 300, "&");
	this->button7 = new Button(320, 300, "7");
	this->buttonStern = new Button(370, 300, "*");
	this->button8 = new Button(370, 300, "8");
	this->buttonKlammerAuf = new Button(420, 300, "(");
	this->button9 = new Button(420, 300, "9");
	this->buttonKlammerZu = new Button(470, 300, ")");
	this->button0 = new Button(470, 300, "0");
	this->buttonRueckschritt = new Button(520, 300, "<---");

	this->buttonQ = new Button(20, 330, "Q");
	this->buttonq = new Button(20, 330, "q");
	this->buttonW = new Button(70, 330, "W");
	this->buttonw = new Button(70, 330, "w");
	this->buttonE = new Button(120, 330, "E");
	this->buttone = new Button(120, 330, "e");
	this->buttonR = new Button(170, 330, "R");
	this->buttonr = new Button(170, 330, "r");
	this->buttonT = new Button(220, 330, "T");
	this->buttont = new Button(220, 330, "t");
	this->buttonY = new Button(270, 330, "Y");
	this->buttony = new Button(270, 330, "y");
	this->buttonU = new Button(320, 330, "U");
	this->buttonu = new Button(320, 330, "u");
	this->buttonI = new Button(370, 330, "I");
	this->buttoni = new Button(370, 330, "i");
	this->buttonO = new Button(420, 330, "O");
	this->buttono = new Button(420, 330, "o");
	this->buttonP = new Button(470, 330, "P");
	this->buttonp = new Button(470, 330, "p");
	this->buttonUnterstrich = new Button(520, 330, "_");
	this->buttonBindestrich = new Button(520, 330, "-");
	buchstabe = 0x9a;
	buchstabeS = new string(&buchstabe);
	this->buttonUe = new Button(570, 330, *buchstabeS);
	this->buttonUe->deaktivieren(true);
	buchstabe = 0x81;
	buchstabeS = new string(&buchstabe);
	this->buttonue = new Button(570, 330, *buchstabeS);
	this->buttonue->deaktivieren(true);

	this->buttonA = new Button(20, 360, "A");
	this->buttona = new Button(20, 360, "a");
	this->buttonS = new Button(70, 360, "S");
	this->buttons = new Button(70, 360, "s");
	this->buttonD = new Button(120, 360, "D");
	this->buttond = new Button(120, 360, "d");
	this->buttonF = new Button(170, 360, "F");
	this->buttonf = new Button(170, 360, "f");
	this->buttonG = new Button(220, 360, "G");
	this->buttong = new Button(220, 360, "g");
	this->buttonH = new Button(270, 360, "H");
	this->buttonh = new Button(270, 360, "h");
	this->buttonJ = new Button(320, 360, "J");
	this->buttonj = new Button(320, 360, "j");
	this->buttonK = new Button(370, 360, "K");
	this->buttonk = new Button(370, 360, "k");
	this->buttonL = new Button(420, 360, "L");
	this->buttonl = new Button(420, 360, "l");
	this->buttonDoppelpunkt = new Button(470, 360, ":");
	this->buttonSemikolon = new Button(470, 360, ";");
	this->buttonAnfuehrungsstriche = new Button(520, 360, "\"");
	this->buttonHochkomma = new Button(520, 360, "'");
	buchstabe = 0x99;
	buchstabeS = new string(&buchstabe);
	this->buttonOe = new Button(570, 360, *buchstabeS);
	this->buttonOe->deaktivieren(true);
	buchstabe = 0x94;
	buchstabeS = new string(&buchstabe);
	this->buttonoe = new Button(570, 360, *buchstabeS);
	this->buttonoe->deaktivieren(true);

	this->buttonZ = new Button(20, 390, "Z");
	this->buttonz = new Button(20, 390, "z");
	this->buttonX = new Button(70, 390, "X");
	this->buttonx = new Button(70, 390, "x");
	this->buttonC = new Button(120, 390, "C");
	this->buttonc = new Button(120, 390, "c");
	this->buttonV = new Button(170, 390, "V");
	this->buttonv = new Button(170, 390, "v");
	this->buttonB = new Button(220, 390, "B");
	this->buttonb = new Button(220, 390, "b");
	this->buttonN = new Button(270, 390, "N");
	this->buttonn = new Button(270, 390, "n");
	this->buttonM = new Button(320, 390, "M");
	this->buttonm = new Button(320, 390, "m");
	this->buttonKleinerAls = new Button(370, 390, "<");
	this->buttonKomma = new Button(370, 390, ",");
	this->buttonGroesserAls = new Button(420, 390, ">");
	this->buttonPunkt = new Button(420, 390, ".");
	this->buttonFragezeichen = new Button(470, 390, "?");
	this->buttonSlash = new Button(470, 390, "/");
	buchstabe = 0x8e;
	buchstabeS = new string(&buchstabe);
	this->buttonAe = new Button(520, 390, *buchstabeS);
	this->buttonAe->deaktivieren(true);
	buchstabe = 0x84;
	buchstabeS = new string(&buchstabe);
	this->buttonae = new Button(520, 390, *buchstabeS);
	this->buttonae->deaktivieren(true);
	//this->buttonsz = new Button(570, 390, "�");

	this->buttonGrossKlein = new Button(20, 420, "ABC/abc");
	this->buttonLeertaste = new Button(200, 420, "                      ");

	// kleine Buchstaben zuerst darstellen
	this->kleinSchreiben = false;
	this->aendereGrossKlein();

	// Event hinzufuegen
	this->buttonAusrufeZeichen->setzeBeimKlicken(
			&Keyboard::drueckeAusrufeZeichen);
	this->button1->setzeBeimKlicken(&Keyboard::druecke1);
	this->buttonAt->setzeBeimKlicken(&Keyboard::drueckeAt);
	this->button2->setzeBeimKlicken(&Keyboard::druecke2);
	this->buttonRaute->setzeBeimKlicken(&Keyboard::drueckeRaute);
	this->button3->setzeBeimKlicken(&Keyboard::druecke3);
	this->buttonDollar->setzeBeimKlicken(&Keyboard::drueckeDollar);
	this->button4->setzeBeimKlicken(&Keyboard::druecke4);
	this->buttonProzent->setzeBeimKlicken(&Keyboard::drueckeProzent);
	this->button5->setzeBeimKlicken(&Keyboard::druecke5);
	this->buttonDach->setzeBeimKlicken(&Keyboard::drueckeDach);
	this->button6->setzeBeimKlicken(&Keyboard::druecke6);
	this->buttonUnd->setzeBeimKlicken(&Keyboard::drueckeUnd);
	this->button7->setzeBeimKlicken(&Keyboard::druecke7);
	this->buttonStern->setzeBeimKlicken(&Keyboard::drueckeStern);
	this->button8->setzeBeimKlicken(&Keyboard::druecke8);
	this->buttonKlammerAuf->setzeBeimKlicken(&Keyboard::drueckeKlammerAuf);
	this->button9->setzeBeimKlicken(&Keyboard::druecke9);
	this->buttonKlammerZu->setzeBeimKlicken(&Keyboard::drueckeKlammerZu);
	this->button0->setzeBeimKlicken(&Keyboard::druecke0);
	this->buttonRueckschritt->setzeBeimKlicken(&Keyboard::drueckeRueckschritt);

	this->buttonQ->setzeBeimKlicken(&Keyboard::drueckeQ);
	this->buttonq->setzeBeimKlicken(&Keyboard::drueckeq);
	this->buttonW->setzeBeimKlicken(&Keyboard::drueckeW);
	this->buttonw->setzeBeimKlicken(&Keyboard::drueckew);
	this->buttonE->setzeBeimKlicken(&Keyboard::drueckeE);
	this->buttone->setzeBeimKlicken(&Keyboard::drueckee);
	this->buttonR->setzeBeimKlicken(&Keyboard::drueckeR);
	this->buttonr->setzeBeimKlicken(&Keyboard::druecker);
	this->buttonT->setzeBeimKlicken(&Keyboard::drueckeT);
	this->buttont->setzeBeimKlicken(&Keyboard::druecket);
	this->buttonY->setzeBeimKlicken(&Keyboard::drueckeY);
	this->buttony->setzeBeimKlicken(&Keyboard::drueckey);
	this->buttonU->setzeBeimKlicken(&Keyboard::drueckeU);
	this->buttonu->setzeBeimKlicken(&Keyboard::drueckeu);
	this->buttonI->setzeBeimKlicken(&Keyboard::drueckeI);
	this->buttoni->setzeBeimKlicken(&Keyboard::drueckei);
	this->buttonO->setzeBeimKlicken(&Keyboard::drueckeO);
	this->buttono->setzeBeimKlicken(&Keyboard::drueckeo);
	this->buttonP->setzeBeimKlicken(&Keyboard::drueckeP);
	this->buttonp->setzeBeimKlicken(&Keyboard::drueckep);
	this->buttonUnterstrich->setzeBeimKlicken(&Keyboard::drueckeUnterstrich);
	this->buttonBindestrich->setzeBeimKlicken(&Keyboard::drueckeBindestrich);
	//this->buttonUe->setzeBeimKlicken(&Keyboard::drueckeUe);
	//this->buttonue->setzeBeimKlicken(&Keyboard::drueckeue);

	this->buttonA->setzeBeimKlicken(&Keyboard::drueckeA);
	this->buttona->setzeBeimKlicken(&Keyboard::drueckea);
	this->buttonS->setzeBeimKlicken(&Keyboard::drueckeS);
	this->buttons->setzeBeimKlicken(&Keyboard::drueckes);
	this->buttonD->setzeBeimKlicken(&Keyboard::drueckeD);
	this->buttond->setzeBeimKlicken(&Keyboard::druecked);
	this->buttonF->setzeBeimKlicken(&Keyboard::drueckeF);
	this->buttonf->setzeBeimKlicken(&Keyboard::drueckef);
	this->buttonG->setzeBeimKlicken(&Keyboard::drueckeG);
	this->buttong->setzeBeimKlicken(&Keyboard::drueckeg);
	this->buttonH->setzeBeimKlicken(&Keyboard::drueckeH);
	this->buttonh->setzeBeimKlicken(&Keyboard::drueckeh);
	this->buttonJ->setzeBeimKlicken(&Keyboard::drueckeJ);
	this->buttonj->setzeBeimKlicken(&Keyboard::drueckej);
	this->buttonK->setzeBeimKlicken(&Keyboard::drueckeK);
	this->buttonk->setzeBeimKlicken(&Keyboard::drueckek);
	this->buttonL->setzeBeimKlicken(&Keyboard::drueckeL);
	this->buttonl->setzeBeimKlicken(&Keyboard::drueckel);
	this->buttonDoppelpunkt->setzeBeimKlicken(&Keyboard::drueckeDoppelpunkt);
	this->buttonSemikolon->setzeBeimKlicken(&Keyboard::drueckeSemikolon);
	this->buttonAnfuehrungsstriche->setzeBeimKlicken(
			&Keyboard::drueckeAnfuehrungsstriche);
	this->buttonHochkomma->setzeBeimKlicken(&Keyboard::drueckeHochkomma);
	//this->buttonOe->setzeBeimKlicken(&Keyboard::drueckeOe);
	//this->buttonoe->setzeBeimKlicken(&Keyboard::drueckeoe);

	this->buttonZ->setzeBeimKlicken(&Keyboard::drueckeZ);
	this->buttonz->setzeBeimKlicken(&Keyboard::drueckez);
	this->buttonX->setzeBeimKlicken(&Keyboard::drueckeX);
	this->buttonx->setzeBeimKlicken(&Keyboard::drueckex);
	this->buttonC->setzeBeimKlicken(&Keyboard::drueckeC);
	this->buttonc->setzeBeimKlicken(&Keyboard::drueckec);
	this->buttonV->setzeBeimKlicken(&Keyboard::drueckeV);
	this->buttonv->setzeBeimKlicken(&Keyboard::drueckev);
	this->buttonB->setzeBeimKlicken(&Keyboard::drueckeB);
	this->buttonb->setzeBeimKlicken(&Keyboard::drueckeb);
	this->buttonN->setzeBeimKlicken(&Keyboard::drueckeN);
	this->buttonn->setzeBeimKlicken(&Keyboard::druecken);
	this->buttonM->setzeBeimKlicken(&Keyboard::drueckeM);
	this->buttonm->setzeBeimKlicken(&Keyboard::drueckem);
	this->buttonKleinerAls->setzeBeimKlicken(&Keyboard::drueckeKleinerAls);
	this->buttonKomma->setzeBeimKlicken(&Keyboard::drueckeKomma);
	this->buttonGroesserAls->setzeBeimKlicken(&Keyboard::drueckeGroesserAls);
	this->buttonPunkt->setzeBeimKlicken(&Keyboard::drueckePunkt);
	this->buttonFragezeichen->setzeBeimKlicken(&Keyboard::drueckeFragezeichen);
	this->buttonSlash->setzeBeimKlicken(&Keyboard::drueckeSlash);
	//this->buttonAe->setzeBeimKlicken(&Keyboard::drueckeAe);
	//this->buttonae->setzeBeimKlicken(&Keyboard::drueckeae);
	//this->buttonsz->setzeBeimKlicken(&Keyboard::drueckesz);

	this->buttonGrossKlein->setzeBeimKlicken(&Keyboard::drueckeGrossKlein);
	this->buttonLeertaste->setzeBeimKlicken(&Keyboard::drueckeLeertaste);

	// Button hinzufuegen
	this->fuegeUnterElementHinzu(this->buttonAusrufeZeichen);
	this->fuegeUnterElementHinzu(this->button1);
	this->fuegeUnterElementHinzu(this->buttonAt);
	this->fuegeUnterElementHinzu(this->button2);
	this->fuegeUnterElementHinzu(this->buttonRaute);
	this->fuegeUnterElementHinzu(this->button3);
	this->fuegeUnterElementHinzu(this->buttonDollar);
	this->fuegeUnterElementHinzu(this->button4);
	this->fuegeUnterElementHinzu(this->buttonProzent);
	this->fuegeUnterElementHinzu(this->button5);
	this->fuegeUnterElementHinzu(this->buttonDach);
	this->fuegeUnterElementHinzu(this->button6);
	this->fuegeUnterElementHinzu(this->buttonUnd);
	this->fuegeUnterElementHinzu(this->button7);
	this->fuegeUnterElementHinzu(this->buttonStern);
	this->fuegeUnterElementHinzu(this->button8);
	this->fuegeUnterElementHinzu(this->buttonKlammerAuf);
	this->fuegeUnterElementHinzu(this->button9);
	this->fuegeUnterElementHinzu(this->buttonKlammerZu);
	this->fuegeUnterElementHinzu(this->button0);
	this->fuegeUnterElementHinzu(this->buttonRueckschritt);

	this->fuegeUnterElementHinzu(this->buttonQ);
	this->fuegeUnterElementHinzu(this->buttonq);
	this->fuegeUnterElementHinzu(this->buttonW);
	this->fuegeUnterElementHinzu(this->buttonw);
	this->fuegeUnterElementHinzu(this->buttonE);
	this->fuegeUnterElementHinzu(this->buttone);
	this->fuegeUnterElementHinzu(this->buttonR);
	this->fuegeUnterElementHinzu(this->buttonr);
	this->fuegeUnterElementHinzu(this->buttonT);
	this->fuegeUnterElementHinzu(this->buttont);
	this->fuegeUnterElementHinzu(this->buttonY);
	this->fuegeUnterElementHinzu(this->buttony);
	this->fuegeUnterElementHinzu(this->buttonU);
	this->fuegeUnterElementHinzu(this->buttonu);
	this->fuegeUnterElementHinzu(this->buttonI);
	this->fuegeUnterElementHinzu(this->buttoni);
	this->fuegeUnterElementHinzu(this->buttonO);
	this->fuegeUnterElementHinzu(this->buttono);
	this->fuegeUnterElementHinzu(this->buttonP);
	this->fuegeUnterElementHinzu(this->buttonp);
	this->fuegeUnterElementHinzu(this->buttonUnterstrich);
	this->fuegeUnterElementHinzu(this->buttonBindestrich);
	this->fuegeUnterElementHinzu(this->buttonUe);
	this->fuegeUnterElementHinzu(this->buttonue);

	this->fuegeUnterElementHinzu(this->buttonA);
	this->fuegeUnterElementHinzu(this->buttona);
	this->fuegeUnterElementHinzu(this->buttonS);
	this->fuegeUnterElementHinzu(this->buttons);
	this->fuegeUnterElementHinzu(this->buttonD);
	this->fuegeUnterElementHinzu(this->buttond);
	this->fuegeUnterElementHinzu(this->buttonF);
	this->fuegeUnterElementHinzu(this->buttonf);
	this->fuegeUnterElementHinzu(this->buttonG);
	this->fuegeUnterElementHinzu(this->buttong);
	this->fuegeUnterElementHinzu(this->buttonH);
	this->fuegeUnterElementHinzu(this->buttonh);
	this->fuegeUnterElementHinzu(this->buttonJ);
	this->fuegeUnterElementHinzu(this->buttonj);
	this->fuegeUnterElementHinzu(this->buttonK);
	this->fuegeUnterElementHinzu(this->buttonk);
	this->fuegeUnterElementHinzu(this->buttonL);
	this->fuegeUnterElementHinzu(this->buttonl);
	this->fuegeUnterElementHinzu(this->buttonDoppelpunkt);
	this->fuegeUnterElementHinzu(this->buttonSemikolon);
	this->fuegeUnterElementHinzu(this->buttonAnfuehrungsstriche);
	this->fuegeUnterElementHinzu(this->buttonHochkomma);
	this->fuegeUnterElementHinzu(this->buttonOe);
	this->fuegeUnterElementHinzu(this->buttonoe);

	this->fuegeUnterElementHinzu(this->buttonZ);
	this->fuegeUnterElementHinzu(this->buttonz);
	this->fuegeUnterElementHinzu(this->buttonX);
	this->fuegeUnterElementHinzu(this->buttonx);
	this->fuegeUnterElementHinzu(this->buttonC);
	this->fuegeUnterElementHinzu(this->buttonc);
	this->fuegeUnterElementHinzu(this->buttonV);
	this->fuegeUnterElementHinzu(this->buttonv);
	this->fuegeUnterElementHinzu(this->buttonB);
	this->fuegeUnterElementHinzu(this->buttonb);
	this->fuegeUnterElementHinzu(this->buttonN);
	this->fuegeUnterElementHinzu(this->buttonn);
	this->fuegeUnterElementHinzu(this->buttonM);
	this->fuegeUnterElementHinzu(this->buttonm);
	this->fuegeUnterElementHinzu(this->buttonKleinerAls);
	this->fuegeUnterElementHinzu(this->buttonKomma);
	this->fuegeUnterElementHinzu(this->buttonGroesserAls);
	this->fuegeUnterElementHinzu(this->buttonPunkt);
	this->fuegeUnterElementHinzu(this->buttonFragezeichen);
	this->fuegeUnterElementHinzu(this->buttonSlash);
	this->fuegeUnterElementHinzu(this->buttonAe);
	this->fuegeUnterElementHinzu(this->buttonae);
	//this->fuegeUnterElementHinzu(this->buttonsz);

	this->fuegeUnterElementHinzu(this->buttonGrossKlein);
	this->fuegeUnterElementHinzu(this->buttonLeertaste);
}

void Keyboard::drawElement() {
	if (this->isVisible()) {
		this->zeichneUnterElement();
	}
}

void Keyboard::aendereGrossKlein() {
	this->kleinSchreiben = !this->kleinSchreiben;

	if (this->kleinSchreiben) {
		this->buttonAusrufeZeichen->visible(false);
		this->button1->visible(true);
		this->buttonAt->visible(false);
		this->button2->visible(true);
		this->buttonRaute->visible(false);
		this->button3->visible(true);
		this->buttonDollar->visible(false);
		this->button4->visible(true);
		this->buttonProzent->visible(false);
		this->button5->visible(true);
		this->buttonDach->visible(false);
		this->button6->visible(true);
		this->buttonUnd->visible(false);
		this->button7->visible(true);
		this->buttonStern->visible(false);
		this->button8->visible(true);
		this->buttonKlammerAuf->visible(false);
		this->button9->visible(true);
		this->buttonKlammerZu->visible(false);
		this->button0->visible(true);

		this->buttonQ->visible(false);
		this->buttonq->visible(true);
		this->buttonW->visible(false);
		this->buttonw->visible(true);
		this->buttonE->visible(false);
		this->buttone->visible(true);
		this->buttonR->visible(false);
		this->buttonr->visible(true);
		this->buttonT->visible(false);
		this->buttont->visible(true);
		this->buttonY->visible(false);
		this->buttony->visible(true);
		this->buttonU->visible(false);
		this->buttonu->visible(true);
		this->buttonI->visible(false);
		this->buttoni->visible(true);
		this->buttonO->visible(false);
		this->buttono->visible(true);
		this->buttonP->visible(false);
		this->buttonp->visible(true);
		this->buttonUnterstrich->visible(false);
		this->buttonBindestrich->visible(true);
		this->buttonUe->visible(false);
		this->buttonue->visible(true);

		this->buttonA->visible(false);
		this->buttona->visible(true);
		this->buttonS->visible(false);
		this->buttons->visible(true);
		this->buttonD->visible(false);
		this->buttond->visible(true);
		this->buttonF->visible(false);
		this->buttonf->visible(true);
		this->buttonG->visible(false);
		this->buttong->visible(true);
		this->buttonH->visible(false);
		this->buttonh->visible(true);
		this->buttonJ->visible(false);
		this->buttonj->visible(true);
		this->buttonK->visible(false);
		this->buttonk->visible(true);
		this->buttonL->visible(false);
		this->buttonl->visible(true);
		this->buttonDoppelpunkt->visible(false);
		this->buttonSemikolon->visible(true);
		this->buttonAnfuehrungsstriche->visible(false);
		this->buttonHochkomma->visible(true);
		this->buttonOe->visible(false);
		this->buttonoe->visible(true);

		this->buttonZ->visible(false);
		this->buttonz->visible(true);
		this->buttonX->visible(false);
		this->buttonx->visible(true);
		this->buttonC->visible(false);
		this->buttonc->visible(true);
		this->buttonV->visible(false);
		this->buttonv->visible(true);
		this->buttonB->visible(false);
		this->buttonb->visible(true);
		this->buttonN->visible(false);
		this->buttonn->visible(true);
		this->buttonM->visible(false);
		this->buttonm->visible(true);
		this->buttonKleinerAls->visible(false);
		this->buttonKomma->visible(true);
		this->buttonGroesserAls->visible(false);
		this->buttonPunkt->visible(true);
		this->buttonFragezeichen->visible(false);
		this->buttonSlash->visible(true);
		this->buttonAe->visible(false);
		this->buttonae->visible(true);
	} else {
		this->buttonAusrufeZeichen->visible(true);
		this->button1->visible(false);
		this->buttonAt->visible(true);
		this->button2->visible(false);
		this->buttonRaute->visible(true);
		this->button3->visible(false);
		this->buttonDollar->visible(true);
		this->button4->visible(false);
		this->buttonProzent->visible(true);
		this->button5->visible(false);
		this->buttonDach->visible(true);
		this->button6->visible(false);
		this->buttonUnd->visible(true);
		this->button7->visible(false);
		this->buttonStern->visible(true);
		this->button8->visible(false);
		this->buttonKlammerAuf->visible(true);
		this->button9->visible(false);
		this->buttonKlammerZu->visible(true);
		this->button0->visible(false);

		this->buttonQ->visible(true);
		this->buttonq->visible(false);
		this->buttonW->visible(true);
		this->buttonw->visible(false);
		this->buttonE->visible(true);
		this->buttone->visible(false);
		this->buttonR->visible(true);
		this->buttonr->visible(false);
		this->buttonT->visible(true);
		this->buttont->visible(false);
		this->buttonY->visible(true);
		this->buttony->visible(false);
		this->buttonU->visible(true);
		this->buttonu->visible(false);
		this->buttonI->visible(true);
		this->buttoni->visible(false);
		this->buttonO->visible(true);
		this->buttono->visible(false);
		this->buttonP->visible(true);
		this->buttonp->visible(false);
		this->buttonUnterstrich->visible(true);
		this->buttonBindestrich->visible(false);
		this->buttonUe->visible(true);
		this->buttonue->visible(false);

		this->buttonA->visible(true);
		this->buttona->visible(false);
		this->buttonS->visible(true);
		this->buttons->visible(false);
		this->buttonD->visible(true);
		this->buttond->visible(false);
		this->buttonF->visible(true);
		this->buttonf->visible(false);
		this->buttonG->visible(true);
		this->buttong->visible(false);
		this->buttonH->visible(true);
		this->buttonh->visible(false);
		this->buttonJ->visible(true);
		this->buttonj->visible(false);
		this->buttonK->visible(true);
		this->buttonk->visible(false);
		this->buttonL->visible(true);
		this->buttonl->visible(false);
		this->buttonDoppelpunkt->visible(true);
		this->buttonSemikolon->visible(false);
		this->buttonAnfuehrungsstriche->visible(true);
		this->buttonHochkomma->visible(false);
		this->buttonOe->visible(true);
		this->buttonoe->visible(false);

		this->buttonZ->visible(true);
		this->buttonz->visible(false);
		this->buttonX->visible(true);
		this->buttonx->visible(false);
		this->buttonC->visible(true);
		this->buttonc->visible(false);
		this->buttonV->visible(true);
		this->buttonv->visible(false);
		this->buttonB->visible(true);
		this->buttonb->visible(false);
		this->buttonN->visible(true);
		this->buttonn->visible(false);
		this->buttonM->visible(true);
		this->buttonm->visible(false);
		this->buttonKleinerAls->visible(true);
		this->buttonKomma->visible(false);
		this->buttonGroesserAls->visible(true);
		this->buttonPunkt->visible(false);
		this->buttonFragezeichen->visible(true);
		this->buttonSlash->visible(false);
		this->buttonAe->visible(true);
		this->buttonae->visible(false);
	}
}

void Keyboard::drueckeAusrufeZeichen() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("!");
		textElement->setText(text);
	}
}
void Keyboard::druecke1() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("1");
		textElement->setText(text);
	}
}
void Keyboard::drueckeAt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("@");
		textElement->setText(text);
	}
}
void Keyboard::druecke2() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("2");
		textElement->setText(text);
	}
}
void Keyboard::drueckeRaute() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("#");
		textElement->setText(text);
	}
}
void Keyboard::druecke3() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("3");
		textElement->setText(text);
	}
}
void Keyboard::drueckeDollar() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("$");
		textElement->setText(text);
	}
}
void Keyboard::druecke4() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("4");
		textElement->setText(text);
	}
}
void Keyboard::drueckeProzent() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("%");
		textElement->setText(text);
	}
}
void Keyboard::druecke5() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("5");
		textElement->setText(text);
	}
}
void Keyboard::drueckeDach() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("^");
		textElement->setText(text);
	}
}
void Keyboard::druecke6() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("6");
		textElement->setText(text);
	}
}
void Keyboard::drueckeUnd() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("&");
		textElement->setText(text);
	}
}
void Keyboard::druecke7() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("7");
		textElement->setText(text);
	}
}
void Keyboard::drueckeStern() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("*");
		textElement->setText(text);
	}
}
void Keyboard::druecke8() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("8");
		textElement->setText(text);
	}
}
void Keyboard::drueckeKlammerAuf() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("(");
		textElement->setText(text);
	}
}
void Keyboard::druecke9() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("9");
		textElement->setText(text);
	}
}
void Keyboard::drueckeKlammerZu() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(")");
		textElement->setText(text);
	}
}
void Keyboard::druecke0() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("0");
		textElement->setText(text);
	}
}
void Keyboard::drueckeRueckschritt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		if (text.size() > 0) {
			text = text.substr(0, text.size() - 1);
			textElement->setText(text);
		}
	}
}

void Keyboard::drueckeQ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("Q");
		textElement->setText(text);
	}
}
void Keyboard::drueckeq() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("q");
		textElement->setText(text);
	}
}
void Keyboard::drueckeW() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("W");
		textElement->setText(text);
	}
}
void Keyboard::drueckew() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("w");
		textElement->setText(text);
	}
}
void Keyboard::drueckeE() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("E");
		textElement->setText(text);
	}
}
void Keyboard::drueckee() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("e");
		textElement->setText(text);
	}
}
void Keyboard::drueckeR() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("R");
		textElement->setText(text);
	}
}
void Keyboard::druecker() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("r");
		textElement->setText(text);
	}
}
void Keyboard::drueckeT() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("T");
		textElement->setText(text);
	}
}
void Keyboard::druecket() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("t");
		textElement->setText(text);
	}
}
void Keyboard::drueckeY() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("Y");
		textElement->setText(text);
	}
}
void Keyboard::drueckey() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("y");
		textElement->setText(text);
	}
}
void Keyboard::drueckeU() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("U");
		textElement->setText(text);
	}
}
void Keyboard::drueckeu() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("u");
		textElement->setText(text);
	}
}
void Keyboard::drueckeI() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("I");
		textElement->setText(text);
	}
}
void Keyboard::drueckei() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("i");
		textElement->setText(text);
	}
}
void Keyboard::drueckeO() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("O");
		textElement->setText(text);
	}
}
void Keyboard::drueckeo() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("o");
		textElement->setText(text);
	}
}
void Keyboard::drueckeP() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("P");
		textElement->setText(text);
	}
}
void Keyboard::drueckep() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("p");
		textElement->setText(text);
	}
}
void Keyboard::drueckeUnterstrich() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("_");
		textElement->setText(text);
	}
}
void Keyboard::drueckeBindestrich() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("-");
		textElement->setText(text);
	}
}
/*void Keyboard::drueckeUe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }
 void Keyboard::drueckeue() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }*/

void Keyboard::drueckeA() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("A");
		textElement->setText(text);
	}
}
void Keyboard::drueckea() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("a");
		textElement->setText(text);
	}
}
void Keyboard::drueckeS() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("S");
		textElement->setText(text);
	}
}
void Keyboard::drueckes() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("s");
		textElement->setText(text);
	}
}
void Keyboard::drueckeD() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("D");
		textElement->setText(text);
	}
}
void Keyboard::druecked() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("d");
		textElement->setText(text);
	}
}
void Keyboard::drueckeF() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("F");
		textElement->setText(text);
	}
}
void Keyboard::drueckef() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("f");
		textElement->setText(text);
	}
}
void Keyboard::drueckeG() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("G");
		textElement->setText(text);
	}
}
void Keyboard::drueckeg() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("g");
		textElement->setText(text);
	}
}
void Keyboard::drueckeH() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("H");
		textElement->setText(text);
	}
}
void Keyboard::drueckeh() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("h");
		textElement->setText(text);
	}
}
void Keyboard::drueckeJ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("J");
		textElement->setText(text);
	}
}
void Keyboard::drueckej() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("j");
		textElement->setText(text);
	}
}
void Keyboard::drueckeK() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("K");
		textElement->setText(text);
	}
}
void Keyboard::drueckek() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("k");
		textElement->setText(text);
	}
}
void Keyboard::drueckeL() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("L");
		textElement->setText(text);
	}
}
void Keyboard::drueckel() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("l");
		textElement->setText(text);
	}
}
void Keyboard::drueckeDoppelpunkt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(":");
		textElement->setText(text);
	}
}
void Keyboard::drueckeSemikolon() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(";");
		textElement->setText(text);
	}
}
void Keyboard::drueckeAnfuehrungsstriche() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("\"");
		textElement->setText(text);
	}
}
void Keyboard::drueckeHochkomma() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("'");
		textElement->setText(text);
	}
}
/*void Keyboard::drueckeOe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }
 void Keyboard::drueckeoe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }*/

void Keyboard::drueckeZ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("Z");
		textElement->setText(text);
	}
}
void Keyboard::drueckez() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("z");
		textElement->setText(text);
	}
}
void Keyboard::drueckeX() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("X");
		textElement->setText(text);
	}
}
void Keyboard::drueckex() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("x");
		textElement->setText(text);
	}
}
void Keyboard::drueckeC() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("C");
		textElement->setText(text);
	}
}
void Keyboard::drueckec() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("c");
		textElement->setText(text);
	}
}
void Keyboard::drueckeV() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("V");
		textElement->setText(text);
	}
}
void Keyboard::drueckev() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("v");
		textElement->setText(text);
	}
}
void Keyboard::drueckeB() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("B");
		textElement->setText(text);
	}
}
void Keyboard::drueckeb() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("b");
		textElement->setText(text);
	}
}
void Keyboard::drueckeN() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("N");
		textElement->setText(text);
	}
}
void Keyboard::druecken() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("n");
		textElement->setText(text);
	}
}
void Keyboard::drueckeM() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("M");
		textElement->setText(text);
	}
}
void Keyboard::drueckem() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("m");
		textElement->setText(text);
	}
}
void Keyboard::drueckeKleinerAls() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("<");
		textElement->setText(text);
	}
}
void Keyboard::drueckeKomma() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(",");
		textElement->setText(text);
	}
}
void Keyboard::drueckeGroesserAls() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(">");
		textElement->setText(text);
	}
}
void Keyboard::drueckePunkt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(".");
		textElement->setText(text);
	}
}
void Keyboard::drueckeFragezeichen() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("?");
		textElement->setText(text);
	}
}
void Keyboard::drueckeSlash() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append("/");
		textElement->setText(text);
	}
}
/*void Keyboard::drueckeAe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }
 void Keyboard::drueckeae() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }
 void Keyboard::drueckesz() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("�");
 textElement->setzeText(text);
 }
 }*/

void Keyboard::drueckeGrossKlein() {
	Keyboard::getKeyboard()->aendereGrossKlein();
}
void Keyboard::drueckeLeertaste() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GraphicHandler::getGraphicHandler()->getSelectedElement());
	if (textElement != 0) {
		string text = textElement->getText();
		text.append(" ");
		textElement->setText(text);
	}
}
