/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "GrColor.h"
#include "GrRenderTargetContext.h"
#include "GrSamplerState.h"
#include "GrTypesPriv.h"
#include "SkCanvas.h"
#include "SkRefCnt.h"

class GrColorSpaceXform;
class GrDrawOp;
class GrTextureProxy;
struct SkRect;
class SkMatrix;

namespace GrTextureOp {

/**
 * Creates an op that draws a sub-rectangle of a texture. The passed color is modulated by the
 * texture's color. 'srcRect' specifies the rectangle of the texture to draw. 'dstRect' specifies
 * the rectangle to draw in local coords which will be transformed by 'viewMatrix' to be in device
 * space. 'viewMatrix' must be affine. If GrAAType is kCoverage then AA is applied to the edges
 * indicated by GrQuadAAFlags. Otherwise, GrQuadAAFlags is ignored.
 */
std::unique_ptr<GrDrawOp> Make(GrRecordingContext*,
                               sk_sp<GrTextureProxy>,
                               GrSamplerState::Filter,
                               const SkPMColor4f&,
                               const SkRect& srcRect,
                               const SkRect& dstRect,
                               GrAAType,
                               GrQuadAAFlags,
                               SkCanvas::SrcRectConstraint,
                               const SkMatrix& viewMatrix,
                               sk_sp<GrColorSpaceXform> textureXform);

std::unique_ptr<GrDrawOp> Make(GrRecordingContext*,
                               const GrRenderTargetContext::TextureSetEntry[],
                               int cnt,
                               GrSamplerState::Filter,
                               GrAAType,
                               const SkMatrix& viewMatrix,
                               sk_sp<GrColorSpaceXform> textureXform);

/**
 * Returns true if bilerp texture filtering matters when rendering the src rect
 * texels to dst rect, with the given view matrix.
 */
bool GetFilterHasEffect(const SkMatrix& viewMatrix, const SkRect& srcRect, const SkRect& dstRect);

}
