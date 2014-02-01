#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include <nbody/Vector3.h>

template<typename T> 
class Integrator {
	Vector3<T> _x, _dxdt;
	T _dt;
	Integrator();
public:
	inline Integrator(Vector3<T> &x, Vector3<T> &dxdt, T &dt) : _x{x}, _dxdt{dxdt}, _dt{dt} {}
    Vector3<T> next(); 
};

template<typename T>
Vector3<T> Integrator<T>::next() {
	Vector3<T> mid = _x + 0.5f*_dt*_dxdt;
	Vector3<T> dxdt = 0.5f*_dt*(mid - _x);
	Vector3<T> result = _x + (_dt * dxdt);
	return result;
}


#endif
