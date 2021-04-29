#ifndef LIGHT_H
#define LIGHT_H
#include "sphere.h"
#include "material.h"
using namespace std;


class light: public sphere  {
    public:
        light() {radius=light_radius;};
        light(vec3 cen, light_material* color) {center=cen; radius=light_radius; mat_ptr=color;};
		virtual  bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
	static constexpr float light_radius=0.4;
};

bool light::hit(const ray& r, float tmin, float tmax, hit_record& rec) const{
	//live_checker("Light");
	return sphere::hit(r, tmin, tmax, rec);
}

inline std::istream& operator>>(std::istream &is, light &l) {
	//std::cerr<<"l in"<<std::endl;
	is >> l.center;
	light_material* m= new light_material();
	is>>*m;
	l.mat_ptr=reinterpret_cast<material*>(m);
	return is;
}
#endif
