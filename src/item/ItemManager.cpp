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

#include "ItemManager.h"

#include <stddef.h>
#include <stdlib.h>
#include "Item.h"
#include "ItemBlock.h"
#include "../exception/ExcItemUnknownItem.h"
#include "block/Block001Stone.h"
#include "block/Block002Grass.h"
#include "block/Block003Dirt.h"
#include "block/Block004CobbleStone.h"
#include "block/Block005Planks.h"
#include "block/Block006Sapling.h"
#include "block/Block007Bedrock.h"
#include "block/Block008FlowingWater.h"
#include "block/Block009StillWater.h"
#include "block/Block00AFlowingLava.h"
#include "block/Block00BStehendeLava.h"
#include "block/Block00CSand.h"
#include "block/Block00DGravel.h"
#include "block/Block00EGoldOre.h"
#include "block/Block00FIronOre.h"
#include "block/Block010Coal.h"
#include "block/Block011Wood.h"
#include "block/Block012Leaves.h"
#include "block/Block013Sponge.h"
#include "block/Block014Glass.h"
#include "block/Block015LapisLazuliOre.h"
#include "block/Block016LapisLazuliBlock.h"
#include "block/Block017Dispenser.h"
#include "block/Block018Sandstone.h"
#include "block/Block019NoteBlock.h"
#include "block/Block01ABed.h"
#include "block/Block01BBoosterTrack.h"
#include "block/Block01CDetectorTrack.h"
#include "block/Block01DStickyPiston.h"
#include "block/Block01ECobweb.h"
#include "block/Block01FTallGrass.h"
#include "block/Block020DeadStrauch.h"
#include "block/Block021Piston.h"
#include "block/Block022PistonHead.h"
#include "block/Block023Wool.h"
#include "block/Block024MovedBlock.h"
#include "block/Block025Loewenzahn.h"
#include "block/Block026Rose.h"
#include "block/Block027BrownMushroom.h"
#include "block/Block028RedMushroom.h"
#include "block/Block029Goldblock.h"
#include "block/Block02AIronblock.h"
#include "block/Block02BDoubleStairs.h"
#include "block/Block02CStairs.h"
#include "block/Block02DBrickstone.h"
#include "block/Block02ETNT.h"
#include "block/Block02FBuecherregal.h"
#include "block/Block030MossyCobbleStone.h"
#include "block/Block031Obsidian.h"
#include "block/Block032Torch.h"
#include "block/Block033Fire.h"
#include "block/Block034MonsterSpawner.h"
#include "block/Block035Planksstairs.h"
#include "block/Block036Chest.h"
#include "block/Block037Redstonekabel.h"
#include "block/Block038DiamondOre.h"
#include "block/Block039Diamondblock.h"
#include "block/Block03AWorkbench.h"
#include "block/Block03BGetreide.h"
#include "block/Block03CFarmland.h"
#include "block/Block03DFurnace.h"
#include "block/Block03EBurningFurnace.h"
#include "block/Block03FSign.h"
#include "block/Block040WoodenDoor.h"
#include "block/Block041Ladder.h"
#include "block/Block042Track.h"
#include "block/Block043Stonestairs.h"
#include "block/Block044Wallschild.h"
#include "block/Block045Hebel.h"
#include "block/Block046PressurePlate.h"
#include "block/Block047Irondoor.h"
#include "block/Block048WoodenPressurePlate.h"
#include "block/Block049RedstoneOre.h"
#include "block/Block04AGlowingRedstoneOre.h"
#include "block/Block04BRedstoneTorchOff.h"
#include "block/Block04CRedstoneTorchOn.h"
#include "block/Block04DStoneLever.h"
#include "block/Block04ESnow.h"
#include "block/Block04FIce.h"
#include "block/Block050Snowblock.h"
#include "block/Block051Cactus.h"
#include "block/Block052Lehm.h"
#include "block/Block053Zuckerrohr.h"
#include "block/Block054Jukebox.h"
#include "block/Block055Fence.h"
#include "block/Block056Kuerbis.h"
#include "block/Block057Netherrack.h"
#include "block/Block058SoulSand.h"
#include "block/Block059Glowstone.h"
#include "block/Block05APortal.h"
#include "block/Block05BJackOLantern.h"
#include "block/Block05CCakeblock.h"
#include "block/Block05DRedstoneRepeaterOff.h"
#include "block/Block05ERedstoneRepeaterOn.h"
#include "block/Block05FLockedChest.h"
#include "block/Block060Trapdoor.h"
#include "block/Block061StoneWithSilverfish.h"
#include "block/Block062StonezBrick.h"
#include "block/Block063BrownMushroomblock.h"
#include "block/Block064RoterMushroomblock.h"
#include "block/Block065Irongitter.h"
#include "block/Block066GlassPane.h"
#include "block/Block067Melon.h"
#include "block/Block068Kuerbisplant.h"
#include "block/Block069Melonnplant.h"
#include "block/Block06ALiane.h"
#include "block/Block06BFencetor.h"
#include "block/Block06CBrickstairs.h"
#include "block/Block06DStonezBrickstairs.h"
#include "block/Block06EMyzel.h"
#include "block/Block06FSearose.h"
#include "block/Block070NetherrackBrick.h"
#include "block/Block071NetherrackBrickFence.h"
#include "block/Block072NetherrackBrickstairs.h"
#include "block/Block073Netherwarze.h"
#include "block/Block074Zaubertisch.h"
#include "block/Block075Braustand.h"
#include "block/Block076Kessel.h"
#include "block/Block077Enderportal.h"
#include "block/Block078EnderportalBlock.h"
#include "block/Block079Endstone.h"
#include "block/Block07ADrachenei.h"
#include "block/Block07BRedstoneLampeOff.h"
#include "block/Block07CRedstoneLampeOn.h"
#include "item/Item101EisenSpitzhacke.h"
#include "item/Item105Bogen.h"
#include "item/Item106Pfeil.h"
#include "item/Item111SteinSchaufel.h"
#include "item/Item113SteinAxt.h"
#include "item/Item114DiamantSchwert.h"
#include "item/Item115DiamantSchaufel.h"
#include "item/Item116DiamantSpitzhacke.h"
#include "item/Item117DiamantAxt.h"
#include "item/Item11FFaden.h"
#include "item/Item121Schiesspulver.h"
#include "item/Item148Minecart.h"
#include "item/Item14AEisentuer.h"
#include "item/Item159Kompass.h"
#include "item/Item15BUhr.h"
#include "item/Item160Knochen.h"
#include "item/Item166Karte.h"
#include "item/Item168Melonenscheibe.h"
#include "item/Item16FFauligesFleisch.h"
#include "item/Item170EnderPerle.h"
#include "item/Item177Spinnenauge.h"
#include "item/ItemDummy.h"
#include "../util/Debug.h"
#ifdef DEBUG_ON
#include "../gui/GraphicHandler.h"
#endif

using namespace std;

Item **ItemManager::itemListe = NULL;

void ItemManager::registriereItem(Item *item) {
	delete ItemManager::itemListe[item->getItemId()];

	ItemManager::itemListe[item->getItemId()] = item;
}

void ItemManager::initializeItemListe() {
	ItemManager::itemListe = (Item **) malloc(sizeof(Item *) * 2048);

	for (short i = 0; i < 2048; i++) {
		ItemManager::itemListe[i] = new ItemDummy();
	}

	Block001Stone::registiereItem();
	Block002Grass::registiereItem();
	Block003Dirt::registiereItem();
	Block004CobbleStone::registiereItem();
	Block005Planks::registiereItem();
	Block006Sapling::registiereItem();
	Block007Bedrock::registiereItem();
	Block008FlowingWater::registiereItem();
	Block009StillWater::registiereItem();
	Block00AFlowingLava::registiereItem();
	Block00BStehendeLava::registiereItem();
	Block00CSand::registiereItem();
	Block00DGravel::registiereItem();
	Block00EGoldOre::registiereItem();
	Block00FIronOre::registiereItem();
	Block010Coal::registiereItem();
	Block011Wood::registiereItem();
	Block012Leaves::registiereItem();
	Block013Sponge::registiereItem();
	Block014Glass::registiereItem();
	Block015LapisLazuliOre::registiereItem();
	Block016LapisLazuliBlock::registiereItem();
	Block017Dispenser::registiereItem();
	Block018Sandstone::registiereItem();
	Block019NoteBlock::registiereItem();
	Block01ABed::registiereItem();
	Block01BBoosterTrack::registiereItem();
	Block01CDetectorTrack::registiereItem();
	Block01DStickyPiston::registiereItem();
	Block01ECobweb::registiereItem();
	Block01FTallGrass::registiereItem();
	Block020DeadStrauch::registiereItem();
	Block021Piston::registiereItem();
	Block022PistonHead::registiereItem();
	Block023Wool::registiereItem();
	Block024MovedBlock::registiereItem();
	Block025Loewenzahn::registiereItem();
	Block026Rose::registiereItem();
	Block027BrownMushroom::registiereItem();
	Block028RedMushroom::registiereItem();
	Block029Goldblock::registiereItem();
	Block02AIronblock::registiereItem();
	Block02BDoubleStairs::registiereItem();
	Block02CStairs::registiereItem();
	Block02DBrickstone::registiereItem();
	Block02ETNT::registiereItem();
	Block02FBuecherregal::registiereItem();
	Block030MossyCobbleStone::registiereItem();
	Block031Obsidian::registiereItem();
	Block032Torch::registiereItem();
	Block033Fire::registiereItem();
	Block034MonsterSpawner::registiereItem();
	Block035Planksstairs::registiereItem();
	Block036Chest::registiereItem();
	Block037Redstonekabel::registiereItem();
	Block038DiamondOre::registiereItem();
	Block039Diamondblock::registiereItem();
	Block03AWorkbench::registiereItem();
	Block03BGetreide::registiereItem();
	Block03CFarmland::registiereItem();
	Block03DFurnace::registiereItem();
	Block03EBurningFurnace::registiereItem();
	Block03FSign::registiereItem();
	Block040WoodenDoor::registiereItem();
	Block041Ladder::registiereItem();
	Block042Track::registiereItem();
	Block043Stonestairs::registiereItem();
	Block044Wallschild::registiereItem();
	Block045Hebel::registiereItem();
	Block046PressurePlate::registiereItem();
	Block047Irondoor::registiereItem();
	Block048WoodenPressurePlate::registiereItem();
	Block049RedstoneOre::registiereItem();
	Block04AGlowingRedstoneOre::registiereItem();
	Block04BRedstoneTorchOff::registiereItem();
	Block04CRedstoneTorchOn::registiereItem();
	Block04DStoneLever::registiereItem();
	Block04ESnow::registiereItem();
	Block04FIce::registiereItem();
	Block050Snowblock::registiereItem();
	Block051Cactus::registiereItem();
	Block052Lehm::registiereItem();
	Block053Zuckerrohr::registiereItem();
	Block054Jukebox::registiereItem();
	Block055Fence::registiereItem();
	Block056Kuerbis::registiereItem();
	Block057Netherrack::registiereItem();
	Block058SoulSand::registiereItem();
	Block059Glowstone::registiereItem();
	Block05APortal::registiereItem();
	Block05BJackOLantern::registiereItem();
	Block05CCakeblock::registiereItem();
	Block05DRedstoneRepeaterOff::registiereItem();
	Block05ERedstoneRepeaterOn::registiereItem();
	Block05FLockedChest::registiereItem();
	Block060Trapdoor::registiereItem();
	Block061StoneWithSilverfish::registiereItem();
	Block062StonezBrick::registiereItem();
	Block063BrownMushroomblock::registiereItem();
	Block064RoterMushroomblock::registiereItem();
	Block065Irongitter::registiereItem();
	Block066GlassPane::registiereItem();
	Block067Melon::registiereItem();
	Block068Kuerbisplant::registiereItem();
	Block069Melonnplant::registiereItem();
	Block06ALiane::registiereItem();
	Block06BFencetor::registiereItem();
	Block06CBrickstairs::registiereItem();
	Block06DStonezBrickstairs::registiereItem();
	Block06EMyzel::registiereItem();
	Block06FSearose::registiereItem();
	Block070NetherrackBrick::registiereItem();
	Block071NetherrackBrickFence::registiereItem();
	Block072NetherrackBrickstairs::registiereItem();
	Block073Netherwarze::registiereItem();
	Block074Zaubertisch::registiereItem();
	Block075Braustand::registiereItem();
	Block076Kessel::registiereItem();
	Block077Enderportal::registiereItem();
	Block078EnderportalBlock::registiereItem();
	Block079Endstone::registiereItem();
	Block07ADrachenei::registiereItem();
	Block07BRedstoneLampeOff::registiereItem();
	Block07CRedstoneLampeOn::registiereItem();
	Item101EisenSpitzhacke::registiereItem();
	Item105Bogen::registiereItem();
	Item106Pfeil::registiereItem();
	Item111SteinSchaufel::registiereItem();
	Item113SteinAxt::registiereItem();
	Item114DiamantSchwert::registiereItem();
	Item115DiamantSchaufel::registiereItem();
	Item116DiamantSpitzhacke::registiereItem();
	Item117DiamantAxt::registiereItem();
	Item11FFaden::registiereItem();
	Item121Schiesspulver::registiereItem();
	Item148Minecart::registiereItem();
	Item14AEisentuer::registiereItem();
	Item159Kompass::registiereItem();
	Item15BUhr::registiereItem();
	Item160Knochen::registiereItem();
	Item166Karte::registiereItem();
	Item168Melonenscheibe::registiereItem();
	Item16FFauligesFleisch::registiereItem();
	Item170EnderPerle::registiereItem();
	Item177Spinnenauge::registiereItem();
}

Item *ItemManager::getInstance(short itemId) {
	ItemDummy *itemDummy =
			dynamic_cast<ItemDummy *>(ItemManager::itemListe[itemId]);
	if (itemDummy != 0) {
		throw ExcItemUnknownItem(itemId);
	}

	return ItemManager::itemListe[itemId]->getInstance();
}

void ItemManager::zeichne(short itemId, float x, float y, float z, byte meta) {
#ifdef DEBUG_ON
	GraphicHandler::blockAnzahl++;
#endif

	ItemDummy *itemDummy =
			dynamic_cast<ItemDummy *>(ItemManager::itemListe[itemId]);
	if (itemDummy != 0) {
		throw ExcItemUnknownItem(itemId);
	}

	ItemBlock *itemBlock =
			dynamic_cast<ItemBlock *>(ItemManager::itemListe[itemId]);
	if (itemBlock != 0) {
		itemBlock->zeichne(x, y, z, meta);
	}
}

bool ItemManager::istDurchsichtig(short itemId) {
	ItemDummy *itemDummy =
			dynamic_cast<ItemDummy *>(ItemManager::itemListe[itemId]);
	if (itemDummy != 0) {
		throw ExcItemUnknownItem(itemId);
	}

	ItemBlock *itemBlock =
			dynamic_cast<ItemBlock *>(ItemManager::itemListe[itemId]);
	if (itemBlock != 0) {
		return itemBlock->istDurchsichtig();
	}

	return true;
}
