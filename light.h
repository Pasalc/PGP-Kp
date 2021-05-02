#ifndef LIGHT_H
#define LIGHT_H
#include "sphere.h"
#include "material.h"
#include "vec3.h"
using namespace std;


class light: public sphere  {
    public:
        light() {radius=light_radius;};
        light(vec3 cen, light_material* color) {center=cen; radius=light_radius; mat_ptr=color;};
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
		virtual vec3 illumination(const vec3& norm, const vec3& intersection) const;
	static constexpr float light_radius=0.2;
	double light_intensity=10;
};

bool light::hit(const ray& r, float tmin, float tmax, hit_record& rec) const{
	//live_checker("Light");
	return sphere::hit(r, tmin, tmax, rec);
}
vec3 light::illumination(const vec3& norm, const vec3& intersection) const{
	vec3 color=vec3(0,0,0);
	
	vec3 vec_lit=center-intersection;
	vec3 dir_lit=unit_vector(vec_lit);
	//if(dot(dir_lit,norm)>0){
		double len=(vec_lit).length();
		double distance_fade = (light_intensity - len) / light_intensity;
		double sc;
		if (distance_fade > 0) {
			vec3 color=vec3(1,1,1);//mat_ptr.surface_light();
			sc = distance_fade * dot(norm, dir_lit);
			
			sc = abs(sc);

			color*sc;
		}
	//}
	return color;
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
