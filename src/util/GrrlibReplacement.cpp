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

#include "GrrlibReplacement.h"

#include "../gui/GraphicHandler.h"

#if defined _WIN32 || defined __CYGWIN__
GXRModeObj *rmode;
#endif

using namespace std;

GRRLIB_texImg *GrrlibReplacement::textur;

/**
 * Ersetzt die von GRRLIB mitgelieferte Methode. Da dort jedesmal
 * die Textur geladen wird.
 * @param Textur
 * @param wiederholen
 */
void GrrlibReplacement::GRRLIB_SetTexture(GRRLIB_texImg *tex, bool wiederholen) {
	GXTexObj texObj;

	GrrlibReplacement::textur = tex;

	GX_InitTexObj(&texObj, tex->data, tex->w, tex->h, GX_TF_RGBA8, GX_CLAMP,
			GX_CLAMP, GX_FALSE);
	GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0,
			GX_ANISO_1);
	GX_SetCopyFilter(GX_FALSE, rmode->sample_pattern, GX_FALSE, rmode->vfilter);

	GX_LoadTexObj(&texObj, GX_TEXMAP0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

}

/**
 * Draw a tile Quad.
 * @param pos Vector array of the 4 points.
 * @param frame Specifies the frame to draw.
 */
void GrrlibReplacement::GRRLIB_DrawImgQuadTile(const guVector pos[4],
		const int frame) {
	//f32 width, height;
	//Mtx m, m1, m2, mv;
	f32 s1, s2, t1, t2;

	//f32 degrees = 0;
	//f32 scaleX = 1;
	//f32 scaleY = 1;
	//u32 color = 0xffffffff;

	// The 0.001f/x is the frame correction formula by spiffen
	s1 = (frame % GrrlibReplacement::textur->nbtilew)
			* GrrlibReplacement::textur->ofnormaltexx;
	s2 = s1 + GrrlibReplacement::textur->ofnormaltexx;
	t1 = (int) (frame / GrrlibReplacement::textur->nbtilew)
			* GrrlibReplacement::textur->ofnormaltexy;
	t2 = t1 + GrrlibReplacement::textur->ofnormaltexy;

	//width = GrrlibReplacement::textur->tilew * 0.5f;
	//height = GrrlibReplacement::textur->tileh * 0.5f;

	//guMtxIdentity(m1);
	//guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0f);
	//guMtxRotAxisDeg(m2, &axis, degrees);
	//guMtxConcat(m2, m1, m);

	//guMtxTransApply(m, m,
	//		xpos + width + GrrlibReplacement::textur->handlex
	//				- GrrlibReplacement::textur->offsetx
	//				+ (scaleX
	//						* (-GrrlibReplacement::textur->handley
	//								* sin(-DegToRad(degrees))
	//								- GrrlibReplacement::textur->handlex
	//										* cos(-DegToRad(degrees)))),
	//		ypos + height + tex->handley - GrrlibReplacement::textur->offsety
	//				+ (scaleY
	//						* (-GrrlibReplacement::textur->handley
	//								* cos(-DegToRad(degrees))
	//								+ GrrlibReplacement::textur->handlex
	//										* sin(-DegToRad(degrees)))), 0);

	//guMtxConcat(GXmodelView2D, m, mv);

	//GX_LoadPosMtxImm(mv, GX_PNMTX0);

	//TexturMatrix texturMatrix = GraphicHandler::getGraphicHandler()->gebeTexturMatrix(frame);

	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
	GX_Position3f32(pos[0].x, pos[0].y, pos[0].z);
	GX_Color1u32(0xffffffff);
	GX_TexCoord2f32(s1, t1);

	GX_Position3f32(pos[1].x, pos[1].y, pos[1].z);
	GX_Color1u32(0xffffffff);
	GX_TexCoord2f32(s2, t1);

	GX_Position3f32(pos[2].x, pos[2].y, pos[2].z);
	GX_Color1u32(0xffffffff);
	GX_TexCoord2f32(s2, t2);

	GX_Position3f32(pos[3].x, pos[3].y, pos[3].z);
	GX_Color1u32(0xffffffff);
	GX_TexCoord2f32(s1, t2);
	GX_End();
	//GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

	//GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	//GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
}
