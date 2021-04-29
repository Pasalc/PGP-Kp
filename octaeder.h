#ifndef OCTAEDER_H
#define OCTAEDER_H
#include "sphere.h"
#include <array>

using namespace std;

class octaeder : public sphere{
	public:
	octaeder(){};
	octaeder(vec3 cen, float r, material *m) : sphere(cen,r,m)  {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
};

bool octaeder::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	//std::cerr<<"Just tell me why"<<std::endl;
	//live_checker("Octo");
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
		bool touch=false;
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
			touch=true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
			touch=true;
        }
		if(touch){
			bool hitted=false;
			array<vec3,6> ptrs;
			constexpr float pi=3.1415f;
			//ptrs[0]=center+vec3(radius*sin(pi/2)*cos(0),radius*sin(pi/2)*sin(0),radius*cos(pi/2));
			ptrs[0]=center+vec3(radius,0,0);
			ptrs[1]=center+vec3(radius*cos(pi/2),radius*sin(pi/2),0);
			ptrs[2]=center+vec3(radius*cos(pi),radius*sin(pi),0);
			ptrs[3]=center+vec3(radius*cos(pi*1.5),radius*sin(pi*1.5),0);
			ptrs[4]=center+vec3(0,0,radius);
			ptrs[5]=center+vec3(0,0,-radius);
			hit_record rec_temp;
			for(int i=0;i<3;++i){
				for(int j=4;j<6;++j){
					if(hit_triangle(r.direction(),r.origin(),ptrs[i],ptrs[i+1],ptrs[j],rec_temp)){
						if(rec_temp.t>t_min&&rec_temp.t<t_max){
							hitted=true;
							rec=rec_temp;
							t_max=rec.t;
							rec.mat_ptr = mat_ptr;
						}
					}
				}
			}
			for(int j=4;j<6;++j){
				if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[3],ptrs[j],rec)){
					if(rec_temp.t>t_min&&rec_temp.t<t_max){
						hitted=true;
						rec=rec_temp;
						t_max=rec.t;
						rec.mat_ptr = mat_ptr;
					}
				}
			}
			return hitted;
		}
    }
    return false;
}


#endif