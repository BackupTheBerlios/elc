/*!
\brief Special effects for all of the harvesting events.
*/

#ifdef MINES

#ifdef EYE_CANDY

#ifndef EFFECT_MINES_H
#define EFFECT_MINES_H

// I N C L U D E S ////////////////////////////////////////////////////////////

#include "eye_candy.h"

namespace ec
{

// C L A S S E S //////////////////////////////////////////////////////////////

class MineEffect : public Effect
{
public: 
  enum MineType
  {
    CREATE,
	PRIME,
	DEACTIVATE,
    DETONATE_TYPE1,
    DETONATE_TYPE2
  };

  MineEffect(EyeCandy* _base, bool* _dead, Vec3* _pos, const MineType _type, const Uint16 _LOD);
  ~MineEffect(); 
  
  virtual EffectEnum get_type() { return EC_MINES; };
  bool idle(const Uint64 usec);
  static Uint64 get_max_end_time() { return 5000000; };
  virtual Uint64 get_expire_time() { return 5000000 + born; };

  ParticleSpawner* spawner;
  ParticleMover* mover;
  ParticleSpawner* spawner2;
  ParticleMover* mover2;
  Vec3 effect_center;
  Vec3 gravity_center;
  MineType type;
};

class MineParticle : public Particle
{
public:
  MineParticle(Effect* _effect, ParticleMover* _mover, const Vec3 _pos, const Vec3 _velocity, const coord_t _size, const alpha_t _alpha, const color_t red, const color_t green, const color_t blue, Texture* _texture, const Uint16 _LOD, const MineEffect::MineType _type);
  ~MineParticle() {}
  
  virtual bool idle(const Uint64 delta_t);
  void draw(const Uint64 usec);
  virtual GLuint get_texture(const Uint16 res_index);
  virtual light_t estimate_light_level() const { return 0.0015; };
  virtual light_t get_light_level();
  
  Texture* texture;
  Uint16 LOD;
  MineEffect::MineType type;
};


///////////////////////////////////////////////////////////////////////////////

}	// End namespace ec

#endif	// defined EFFECT_MINES_H

#endif	// #ifdef EYE_CANDY

#endif // MINES