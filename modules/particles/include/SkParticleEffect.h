/*
* Copyright 2019 Google LLC
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef SkParticleEffect_DEFINED
#define SkParticleEffect_DEFINED

#include "SkAutoMalloc.h"
#include "SkColor.h"
#include "SkCurve.h"
#include "SkParticleData.h"
#include "SkRandom.h"
#include "SkRefCnt.h"
#include "SkTArray.h"

class SkAnimTimer;
class SkCanvas;
class SkFieldVisitor;
class SkParticleAffector;
class SkParticleDrawable;
class SkParticleEmitter;
struct SkRSXform;

class SkParticleEffectParams : public SkRefCnt {
public:
    int       fMaxCount = 128;
    float     fEffectDuration = 1.0f;
    float     fRate = 8.0f;
    SkCurve   fLifetime = 1.0f;
    SkColor4f fStartColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    SkColor4f fEndColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Drawable (image, sprite sheet, etc.)
    sk_sp<SkParticleDrawable> fDrawable;

    // Emitter shape & parameters
    sk_sp<SkParticleEmitter> fEmitter;

    // Rules that configure particles at spawn time
    SkTArray<sk_sp<SkParticleAffector>> fSpawnAffectors;

    // Rules that update existing particles over their lifetime
    SkTArray<sk_sp<SkParticleAffector>> fUpdateAffectors;

    void visitFields(SkFieldVisitor* v);
};

class SkParticleEffect : public SkRefCnt {
public:
    SkParticleEffect(sk_sp<SkParticleEffectParams> params, const SkRandom& random);

    void start(const SkAnimTimer& timer, bool looping = false);
    void update(const SkAnimTimer& timer);
    void draw(SkCanvas* canvas);

    bool isAlive() { return fSpawnTime >= 0; }

    SkParticleEffectParams* getParams() { return fParams.get(); }

private:
    void setCapacity(int capacity);

    struct Particle {
        double fTimeOfBirth;
        double fTimeOfDeath;
        SkRandom fStableRandom;

        // Texture coord rects and colors are stored in parallel arrays for drawAtlas.
        SkParticlePoseAndVelocity fPV;
    };

    sk_sp<SkParticleEffectParams> fParams;

    SkRandom fRandom;

    bool   fLooping;
    double fSpawnTime;

    int    fCount;
    double fLastTime;
    float  fSpawnRemainder;

    SkAutoTMalloc<Particle>  fParticles;
    SkAutoTMalloc<SkRSXform> fXforms;
    SkAutoTMalloc<float>     fFrames;
    SkAutoTMalloc<SkColor>   fColors;

    // Cached
    int fCapacity;
};

#endif // SkParticleEffect_DEFINED
