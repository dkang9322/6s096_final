#include <nbody/constants.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>
#include <nbody/Integrator.h>


#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace nbody{
  inline void System::interactBodies( size_t i, size_t j, float softFactor, Vector3f &acc ) const {
    Vector3f r = _body[j].position() - _body[i].position();
    float distance = r.norm() + softFactor;
    float invDist = 1.0f / distance;
    float invDistCubed = cube( invDist );
    acc = acc + NEWTON_G * _body[j].mass() * invDistCubed * r;
  }

  void System::computeGravitation() {
    for( size_t i = 0; i < _nBodies; ++i ) {
      Vector3f acc{ 0.0f, 0.0f, 0.0f };
      for( size_t j = 0; j < _nBodies; ++j ) {
        if( i != j ) {
          interactBodies( i, j, _softFactor, acc );
        }
      }
      _body[i].force() = acc;
    }
  }

  void System::integrateSystem( float dt ) {
    Vector3f r, v, a;
    for( size_t i = 0; i < _nBodies; ++i ) {
      r = _body[i].position();
      v = _body[i].velocity();
      a = _body[i].force();

      Integrator<float> iv{v, a, dt};
      v = iv.next();
      v = v * _dampingFactor;
      Integrator<float> ir{r, v, dt};
      r = ir.next();
      
      _body[i].position() = r;
      _body[i].velocity() = v;
    }
  }

  void System::update( float dt ) {
    computeGravitation();
    integrateSystem( dt );
  }

  void System::readState( std::istream &input ) {
    input >> _nBodies;
    if( _nBodies > MAX_BODIES_RECOMMENDED ) {
      throw std::runtime_error( "Too many input bodies" );
    }
    _body = new Body[_nBodies];
    for( size_t i = 0; i < _nBodies; ++i ) {
      input >> _body[i];
    }
  }

  void System::writeState( std::ostream &output ) const {
    output << _nBodies << "\n";
    for( size_t i = 0; i < _nBodies; ++i ) {
      output << _body[i] << "\n";
    }
  }


    void System::updatePositions( float *buf ) {
	// This function updates buf value to xyz values of System's Bodies
	for( size_t i = 0; i < _nBodies; i++ ) {
	    buf[4*i] = _body[i].x();
	    buf[4*i+1] = _body[i].y();
	    buf[4*i+2] = _body[i].z();
	    buf[4*i+3] = 1.0f;
	    
	}
    }

} // namespace nbody
