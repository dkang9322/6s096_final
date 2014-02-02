#ifndef _NBODY_BODY_H
#define _NBODY_BODY_H

#include <nbody/Vector3.h>

#include <iosfwd>

namespace nbody {

  class Body {
    Vector3f _position;
    Vector3f _velocity;
    Vector3f _force;
    float _mass;
  public:
    Body() : _position{}, _velocity{}, _force{}, _mass{} {}
    inline Vector3f position() const { return _position; } //if (5.0 == body.position())
    inline Vector3f& position() { return _position; } // body.position = (3.0, 2.0, 1.0)
    inline Vector3f velocity() const { return _velocity; }
    inline Vector3f& velocity() { return _velocity; }
    inline Vector3f force() const { return _force; }
    inline Vector3f& force() { return _force; }

    // Return x,y,z, we either modify all three, or none of three
    inline float x() const { return _position.x(); }
    inline float y() const { return _position.y(); }
    inline float z() const { return _position.z(); }
    
    inline float mass() const { return _mass; }
    friend std::istream& operator>>( std::istream &is, Body &body );
    friend std::ostream& operator<<( std::ostream &os, const Body &body );
  };

} // namespace nbody

#endif // _NBODY_BODY_H
