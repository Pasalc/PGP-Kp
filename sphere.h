#ifndef SPHEREH
#define SPHEREH
#include <array>

#include "hitable.h"
#include "material.h"

constexpr float gr = 1.618;
constexpr float pi =3.1415f;
using namespace std;

class sphere: public hitable  {
    public:
        sphere() : center(vec3(0,0,0)),radius(0),l_amount(0) {}
        sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m)  {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
        vec3 center;
        float radius;
        material *mat_ptr;
		int l_amount;
};


bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	//std::cerr<<"Sp"<<std::endl;
	//live_checker("Sphere");
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}




bool hit_triangle(const vec3& r,const vec3& p, const vec3& v0,const vec3& v1,const vec3& v2, hit_record& rec){
	auto E1 = v1-v0;
	auto E2 = v2-v0;
	auto T = p-v0;
	const auto& D=r;
	auto P = cross(D,E2);
	auto Q = cross(T,E1);
	double det=dot(P,E1);
	if (det < 1e-8 && det > -1e-8) {
		return false;
	}
	det=1/det;
	double u=det*dot(P,T);
	double v=det*dot(Q,D);
	if(u<0||u>1 || v<0 || u+v>1){
		return false;
	}
	rec.t=det*dot(Q,E2);
	rec.p = p + rec.t*r;
	rec.normal = -cross(E1,E2);
	rec.normal.make_unit_vector();
	return true;
}

bool hit_penta(const vec3& r,const vec3& p, const vec3& v0,const vec3& v1,const vec3& v2,const vec3& v3,const vec3& v4, hit_record& rec){
	if(hit_triangle(r,p,v0,v1,v2,rec))	return true;
	if(hit_triangle(r,p,v0,v2,v3,rec))	return true;
	if(hit_triangle(r,p,v0,v3,v4,rec))	return true;
	return false;
}


inline void on_hit(bool& hitted, hit_record& rec, hit_record& rec_temp, float& t_max, material* mat_ptr){
	hitted=true;
	rec=rec_temp;
	t_max=rec.t;
	rec.mat_ptr = mat_ptr;
}

#endif
