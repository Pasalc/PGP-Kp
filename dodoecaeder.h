#ifndef DODOECAEDER_H
#define DODOECAEDER_H
#include "sphere.h"
#include <array>

class dodoecaeder : public sphere{
	public:
	dodoecaeder(){};
	dodoecaeder(vec3 cen, float r, material *m) : sphere(cen,r,m)  {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
};

#define CHECK_PENTA(v0,v1,v2,v3,v4) \
do{	\
	if(hit_penta(r.direction(),r.origin(),ptrs[v0],ptrs[v1],ptrs[v2],ptrs[v3],ptrs[v4],rec_temp)){		\
		if(rec_temp.t>t_min&&rec_temp.t<t_max && dot(rec_temp.normal,r.direction())<0){					\
			on_hit(hitted, rec, rec_temp, t_max, mat_ptr);												\
			return true;																				\
		}																								\
	}																									\
} while(0)

bool dodoecaeder::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	
	//live_checker("Dod");
	//std::cerr<<"dodo"<<std::endl;
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
			array<vec3,20> ptrs;
			//or
			ptrs[0]=center+vec3(-1,-1,-1);
			ptrs[1]=center+vec3(-1,-1,1);
			ptrs[2]=center+vec3(-1,1,-1);
			ptrs[3]=center+vec3(-1,1,1);
			ptrs[4]=center+vec3(1,-1,-1);
			ptrs[5]=center+vec3(1,-1,1);
			ptrs[6]=center+vec3(1,1,-1);
			ptrs[7]=center+vec3(1,1,1);
			//gr
			ptrs[8] =center+vec3(0,-gr,-1/gr);
			ptrs[9] =center+vec3(0,-gr,1/gr);
			ptrs[10]=center+vec3(0,gr,-1/gr);
			ptrs[11]=center+vec3(0,gr,1/gr);
			//bl
			ptrs[12]=center+vec3(-1/gr,0,-gr);
			ptrs[13]=center+vec3(-1/gr,0,gr);
			ptrs[14]=center+vec3(1/gr,0,-gr);
			ptrs[15]=center+vec3(1/gr,0,gr);
			//pn
			ptrs[16]=center+vec3(-gr,-1/gr,0);
			ptrs[17]=center+vec3(-gr,1/gr,0);
			ptrs[18]=center+vec3(gr,-1/gr,0);
			ptrs[19]=center+vec3(gr,1/gr,0);
			
			hit_record rec_temp;
			
			int v0,v1,v2,v3,v4;
			v0=11,v1=10,v2=2,v3=17,v4=3;
			//gr
			CHECK_PENTA(8,9,5,18,4);
			CHECK_PENTA(9,8,0,16,1);
			
			CHECK_PENTA(10,11,3,17,2);//CHECK_PENTA(10,11,3,17,2);//CHECK_PENTA(10,11,3,17,2);
			CHECK_PENTA(11,10,6,19,7);//CHECK_PENTA(10,11,7,19,6);
			
			//pn
			CHECK_PENTA(18,19,6,14,4);
			CHECK_PENTA(19,18,5,15,7);
			
			CHECK_PENTA(17,16,0,12,2);
			CHECK_PENTA(16,17,3,13,1);
			//bl
			//CHECK_PENTA(15,13,1,9,3);
			//CHECK_PENTA(13,15,7,11,3);
			CHECK_PENTA(13,15,5,9,1);
			CHECK_PENTA(15,13,3,11,7);
			
			CHECK_PENTA(12,14,6,10,2);
			CHECK_PENTA(14,12,0,8,4);
			
			return hitted;
		}
    }
    return false;
}
#endif