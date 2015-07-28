/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CCPARTICLE_SYSTEM_H__
#define __CCPARTICLE_SYSTEM_H__

#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "base/CCValue.h"

NS_CC_BEGIN

/**
 * @addtogroup particle_nodes
 * @{
 */

class ParticleBatchNode;

/**
Structure that contains the values of each particle
*/
typedef struct sParticle {
    Vec2     pos;
    Vec2     startPos;

    Color4F    color;
    Color4F    deltaColor;

    float        size;
    float        deltaSize;

    float        rotation;
    float        deltaRotation;

    float        timeToLive;

    unsigned int    atlasIndex;

    //! Mode A: gravity, direction, radial accel, tangential accel
    struct {
        Vec2        dir;
        float        radialAccel;
        float        tangentialAccel;
    } modeA;

    //! Mode B: radius mode
    struct {
        float        angle;
        float        degreesPerSecond;
        float        radius;
        float        deltaRadius;
    } modeB;

}tParticle;

//typedef void (*CC_UPDATE_PARTICLE_IMP)(id, SEL, tParticle*, Vec2);

class Texture2D;

/** @brief Particle System base class.
Attributes of a Particle System:
- emission rate of the particles
- Gravity Mode (Mode A):
- gravity
- direction
- speed +-  variance
- tangential acceleration +- variance
- radial acceleration +- variance
- Radius Mode (Mode B):
- startRadius +- variance
- endRadius +- variance
- rotate +- variance
- Properties common to all modes:
- life +- life variance
- start spin +- variance
- end spin +- variance
- start size +- variance
- end size +- variance
- start color +- variance
- end color +- variance
- life +- variance
- blending function
- texture

cocos2d also supports particles generated by Particle Designer (http://particledesigner.71squared.com/).
'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
cocos2d uses a another approach, but the results are almost identical. 

cocos2d supports all the variables used by Particle Designer plus a bit more:
- spinning particles (supported when using ParticleSystemQuad)
- tangential acceleration (Gravity mode)
- radial acceleration (Gravity mode)
- radius direction (Radius mode) (Particle Designer supports outwards to inwards direction only)

It is possible to customize any of the above mentioned properties in runtime. Example:

@code
emitter.radialAccel = 15;
emitter.startSpin = 0;
@endcode

*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

class CC_DLL ParticleSystem : public Node, public TextureProtocol
{
public:
    enum class Mode
    {
        GRAVITY,
        RADIUS,
    };
    
    /** @typedef PositionType
     possible types of particle positions
     */
    enum class PositionType
    {
        /** Living particles are attached to the world and are unaffected by emitter repositioning. */
        FREE,
        
        /** Living particles are attached to the world but will follow the emitter repositioning.
         Use case: Attach an emitter to an sprite, and you want that the emitter follows the sprite.
         */
        RELATIVE,
        
        /** Living particles are attached to the emitter and are translated along with it. */
        GROUPED,
    };
    
    //* @enum
    enum {
        /** The Particle emitter lives forever */
        DURATION_INFINITY = -1,
        
        /** The starting size of the particle is equal to the ending size */
        START_SIZE_EQUAL_TO_END_SIZE = -1,
        
        /** The starting radius of the particle is equal to the ending radius */
        START_RADIUS_EQUAL_TO_END_RADIUS = -1,
    };
    
    /** creates an initializes a ParticleSystem from a plist file.
    This plist files can be created manually or with Particle Designer:
    http://particledesigner.71squared.com/
    @since v2.0
    */
    static ParticleSystem * create(const std::string& plistFile);

    //! create a system with a fixed number of particles
    static ParticleSystem* createWithTotalParticles(int numberOfParticles);

    //! Add a particle to the emitter
    bool addParticle();
    //! Initializes a particle
    void initParticle(tParticle* particle);
    //! stop emitting particles. Running particles will continue to run until they die
    void stopSystem();
    //! Kill all living particles.
    void resetSystem();
    //! whether or not the system is full
    bool isFull();

    //! should be overridden by subclasses
    virtual void updateQuadWithParticle(tParticle* particle, const Vec2& newPosition);
    //! should be overridden by subclasses
    virtual void postStep();

    virtual void updateWithNoTime(void);

    virtual bool isAutoRemoveOnFinish() const;
    virtual void setAutoRemoveOnFinish(bool var);

    // mode A
    virtual const Vec2& getGravity();
    virtual void setGravity(const Vec2& g);
    virtual float getSpeed() const;
    virtual void setSpeed(float speed);
    virtual float getSpeedVar() const;
    virtual void setSpeedVar(float speed);
    virtual float getTangentialAccel() const;
    virtual void setTangentialAccel(float t);
    virtual float getTangentialAccelVar() const;
    virtual void setTangentialAccelVar(float t);
    virtual float getRadialAccel() const;
    virtual void setRadialAccel(float t);
    virtual float getRadialAccelVar() const;
    virtual void setRadialAccelVar(float t);
    virtual bool getRotationIsDir() const;
    virtual void setRotationIsDir(bool t);
    // mode B
    virtual float getStartRadius() const;
    virtual void setStartRadius(float startRadius);
    virtual float getStartRadiusVar() const;
    virtual void setStartRadiusVar(float startRadiusVar);
    virtual float getEndRadius() const;
    virtual void setEndRadius(float endRadius);
    virtual float getEndRadiusVar() const;
    virtual void setEndRadiusVar(float endRadiusVar);
    virtual float getRotatePerSecond() const;
    virtual void setRotatePerSecond(float degrees);
    virtual float getRotatePerSecondVar() const;
    virtual void setRotatePerSecondVar(float degrees);

    virtual void setScale(float s);
    virtual void setRotation(float newRotation);
    virtual void setScaleX(float newScaleX);
    virtual void setScaleY(float newScaleY);

    virtual bool isActive() const;
    virtual bool isBlendAdditive() const;
    virtual void setBlendAdditive(bool value);

    virtual ParticleBatchNode* getBatchNode() const;
    virtual void setBatchNode(ParticleBatchNode* batchNode);
    
    // index of system in batch node array
    inline int getAtlasIndex() const { return _atlasIndex; };
    inline void setAtlasIndex(int index) { _atlasIndex = index; };

    /** Quantity of particles that are being simulated at the moment */
    inline unsigned int getParticleCount() const { return _particleCount; };
    
    /** How many seconds the emitter will run. -1 means 'forever' */
    inline float getDuration() const { return _duration; };
    inline void setDuration(float duration) { _duration = duration; };
    
    /** sourcePosition of the emitter */
    inline const Vec2& getSourcePosition() const { return _sourcePosition; };
    inline void setSourcePosition(const Vec2& pos) { _sourcePosition = pos; };
    
    /** Position variance of the emitter */
    inline const Vec2& getPosVar() const { return _posVar; };
    inline void setPosVar(const Vec2& pos) { _posVar = pos; };

    /** life, and life variation of each particle */
    inline float getLife() const { return _life; };
    inline void setLife(float life) { _life = life; };

    /** life variance of each particle */
    inline float getLifeVar() const { return _lifeVar; };
    inline void setLifeVar(float lifeVar) { _lifeVar = lifeVar; };

    /** angle and angle variation of each particle */
    inline float getAngle() const { return _angle; };
    inline void setAngle(float angle) { _angle = angle; };

    /** angle variance of each particle */
    inline float getAngleVar() const { return _angleVar; };
    inline void setAngleVar(float angleVar) { _angleVar = angleVar; };
    
    /** Switch between different kind of emitter modes:
     - kParticleModeGravity: uses gravity, speed, radial and tangential acceleration
     - kParticleModeRadius: uses radius movement + rotation
     */
    inline Mode getEmitterMode() const { return _emitterMode; };
    inline void setEmitterMode(Mode mode) { _emitterMode = mode; };
    
    /** start size in pixels of each particle */
    inline float getStartSize() const { return _startSize; };
    inline void setStartSize(float startSize) { _startSize = startSize; };

    /** size variance in pixels of each particle */
    inline float getStartSizeVar() const { return _startSizeVar; };
    inline void setStartSizeVar(float sizeVar) { _startSizeVar = sizeVar; };

    /** end size in pixels of each particle */
    inline float getEndSize() const { return _endSize; };
    inline void setEndSize(float endSize) { _endSize = endSize; };

    /** end size variance in pixels of each particle */
    inline float getEndSizeVar() const { return _endSizeVar; };
    inline void setEndSizeVar(float sizeVar) { _endSizeVar = sizeVar; };

    /** start color of each particle */
    inline const Color4F& getStartColor() const { return _startColor; };
    inline void setStartColor(const Color4F& color) { _startColor = color; };

    /** start color variance of each particle */
    inline const Color4F& getStartColorVar() const { return _startColorVar; };
    inline void setStartColorVar(const Color4F& color) { _startColorVar = color; };

    /** end color and end color variation of each particle */
    inline const Color4F& getEndColor() const { return _endColor; };
    inline void setEndColor(const Color4F& color) { _endColor = color; };

    /** end color variance of each particle */
    inline const Color4F& getEndColorVar() const { return _endColorVar; };
    inline void setEndColorVar(const Color4F& color) { _endColorVar = color; };

    //* initial angle of each particle
    inline float getStartSpin() const { return _startSpin; };
    inline void setStartSpin(float spin) { _startSpin = spin; };

    //* initial angle of each particle
    inline float getStartSpinVar() const { return _startSpinVar; };
    inline void setStartSpinVar(float pinVar) { _startSpinVar = pinVar; };

    //* initial angle of each particle
    inline float getEndSpin() const { return _endSpin; };
    inline void setEndSpin(float endSpin) { _endSpin = endSpin; };

    //* initial angle of each particle
    inline float getEndSpinVar() const { return _endSpinVar; };
    inline void setEndSpinVar(float endSpinVar) { _endSpinVar = endSpinVar; };

    /** emission rate of the particles */
    inline float getEmissionRate() const { return _emissionRate; };
    inline void setEmissionRate(float rate) { _emissionRate = rate; };

    /** maximum particles of the system */
    virtual int getTotalParticles() const;
    virtual void setTotalParticles(int totalParticles);

    /** does the alpha value modify color */
    inline void setOpacityModifyRGB(bool opacityModifyRGB) { _opacityModifyRGB = opacityModifyRGB; };
    inline bool isOpacityModifyRGB() const { return _opacityModifyRGB; };
    CC_DEPRECATED_ATTRIBUTE inline bool getOpacityModifyRGB() const { return isOpacityModifyRGB(); }
    
    /** particles movement type: Free or Grouped
     @since v0.8
     */
    inline PositionType getPositionType() const { return _positionType; };
    inline void setPositionType(PositionType type) { _positionType = type; };
    
    // Overrides
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    *@code
    *When this function bound into js or lua,the parameter will be changed
    *In js: var setBlendFunc(var src, var dst)
    *In lua: local setBlendFunc(local src, local dst)
    *@endcode
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc &getBlendFunc() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSystem();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystem();

    /** initializes a ParticleSystem*/
    bool init();
    /** initializes a ParticleSystem from a plist file.
     This plist files can be created manually or with Particle Designer:
     http://particledesigner.71squared.com/
     @since v0.99.3
     */
    bool initWithFile(const std::string& plistFile);
    
    /** initializes a QuadParticleSystem from a Dictionary.
     @since v0.99.3
     */
    bool initWithDictionary(ValueMap& dictionary);
    
    /** initializes a particle system from a NSDictionary and the path from where to load the png
     @since v2.1
     */
    bool initWithDictionary(ValueMap& dictionary, const std::string& dirname);
    
    //! Initializes a system with a fixed number of particles
    virtual bool initWithTotalParticles(int numberOfParticles);

protected:
    virtual void updateBlendFunc();

    /** whether or not the particles are using blend additive.
     If enabled, the following blending function will be used.
     @code
     source blend function = GL_SRC_ALPHA;
     dest blend function = GL_ONE;
     @endcode
     */
    bool _isBlendAdditive;

    /** whether or not the node will be auto-removed when it has no particles left.
     By default it is false.
     @since v0.8
     */
    bool _isAutoRemoveOnFinish;

    std::string _plistFile;
    //! time elapsed since the start of the system (in seconds)
    float _elapsed;

    // Different modes
    //! Mode A:Gravity + Tangential Accel + Radial Accel
    struct {
        /** Gravity value. Only available in 'Gravity' mode. */
        Vec2 gravity;
        /** speed of each particle. Only available in 'Gravity' mode.  */
        float speed;
        /** speed variance of each particle. Only available in 'Gravity' mode. */
        float speedVar;
        /** tangential acceleration of each particle. Only available in 'Gravity' mode. */
        float tangentialAccel;
        /** tangential acceleration variance of each particle. Only available in 'Gravity' mode. */
        float tangentialAccelVar;
        /** radial acceleration of each particle. Only available in 'Gravity' mode. */
        float radialAccel;
        /** radial acceleration variance of each particle. Only available in 'Gravity' mode. */
        float radialAccelVar;
        /** set the rotation of each particle to its direction Only available in 'Gravity' mode. */
        bool rotationIsDir;
    } modeA;

    //! Mode B: circular movement (gravity, radial accel and tangential accel don't are not used in this mode)
    struct {
        /** The starting radius of the particles. Only available in 'Radius' mode. */
        float startRadius;
        /** The starting radius variance of the particles. Only available in 'Radius' mode. */
        float startRadiusVar;
        /** The ending radius of the particles. Only available in 'Radius' mode. */
        float endRadius;
        /** The ending radius variance of the particles. Only available in 'Radius' mode. */
        float endRadiusVar;
        /** Number of degrees to rotate a particle around the source pos per second. Only available in 'Radius' mode. */
        float rotatePerSecond;
        /** Variance in degrees for rotatePerSecond. Only available in 'Radius' mode. */
        float rotatePerSecondVar;
    } modeB;

    //! Array of particles
    tParticle *_particles;

    //Emitter name
    std::string _configName;

    // color modulate
    //    BOOL colorModulate;

    //! How many particles can be emitted per second
    float _emitCounter;

    //!  particle idx
    int _particleIdx;

    // Optimization
    //CC_UPDATE_PARTICLE_IMP    updateParticleImp;
    //SEL                        updateParticleSel;

    /** weak reference to the SpriteBatchNode that renders the Sprite */
    ParticleBatchNode* _batchNode;

    // index of system in batch node array
    int _atlasIndex;

    //true if scaled or rotated
    bool _transformSystemDirty;
    // Number of allocated particles
    int _allocatedParticles;

    /** Is the emitter active */
    bool _isActive;
    
    /** Quantity of particles that are being simulated at the moment */
    int _particleCount;
    /** How many seconds the emitter will run. -1 means 'forever' */
    float _duration;
    /** sourcePosition of the emitter */
    Vec2 _sourcePosition;
    /** Position variance of the emitter */
    Vec2 _posVar;
    /** life, and life variation of each particle */
    float _life;
    /** life variance of each particle */
    float _lifeVar;
    /** angle and angle variation of each particle */
    float _angle;
    /** angle variance of each particle */
    float _angleVar;

    /** Switch between different kind of emitter modes:
     - kParticleModeGravity: uses gravity, speed, radial and tangential acceleration
     - kParticleModeRadius: uses radius movement + rotation
     */
    Mode _emitterMode;

    /** start size in pixels of each particle */
    float _startSize;
    /** size variance in pixels of each particle */
    float _startSizeVar;
    /** end size in pixels of each particle */
    float _endSize;
    /** end size variance in pixels of each particle */
    float _endSizeVar;
    /** start color of each particle */
    Color4F _startColor;
    /** start color variance of each particle */
    Color4F _startColorVar;
    /** end color and end color variation of each particle */
    Color4F _endColor;
    /** end color variance of each particle */
    Color4F _endColorVar;
    //* initial angle of each particle
    float _startSpin;
    //* initial angle of each particle
    float _startSpinVar;
    //* initial angle of each particle
    float _endSpin;
    //* initial angle of each particle
    float _endSpinVar;
    /** emission rate of the particles */
    float _emissionRate;
    /** maximum particles of the system */
    int _totalParticles;
    /** conforms to CocosNodeTexture protocol */
    Texture2D* _texture;
    /** conforms to CocosNodeTexture protocol */
    BlendFunc _blendFunc;
    /** does the alpha value modify color */
    bool _opacityModifyRGB;
    /** does FlippedY variance of each particle */
    int _yCoordFlipped;


    /** particles movement type: Free or Grouped
     @since v0.8
     */
    PositionType _positionType;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSystem);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_SYSTEM_H__
