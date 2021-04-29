#ifndef ICOSAEDER_H
#define ICOSAEDER_H
#include "sphere.h"
#include <array>

class icosaeder : public sphere{
	public:
	icosaeder(){};
	icosaeder(vec3 cen, float r, material *m) : sphere(cen,r,m)  {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
};

/*
inline void check_hit(bool& hitted, hit_record& rec, hit_record& rec_temp, float& t_max, material* mat_ptr){
	if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[3],ptrs[7],rec_temp)){
		if(rec_temp.t>t_min&&rec_temp.t<t_max){
			on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
		}
	}
}
*/
bool icosaeder::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
	//std::cerr<<"ico"<<std::endl;
	//live_checker("Ico");
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
			array<vec3,12> ptrs;
			
			ptrs[0]=center+vec3(0,-1,-gr);
			ptrs[1]=center+vec3(0,-1,gr);
			ptrs[2]=center+vec3(0,1,-gr);
			ptrs[3]=center+vec3(0,1,gr);
			
			ptrs[4]=center+vec3(-1,-gr,0);
			ptrs[5]=center+vec3(-1,gr,0);
			ptrs[6]=center+vec3(1,-gr,0);
			ptrs[7]=center+vec3(1,gr,0);
			
			ptrs[8] =center+vec3(-gr,0,-1);
			ptrs[9] =center+vec3(-gr,0,1);
			ptrs[10]=center+vec3(gr,0,-1);
			ptrs[11]=center+vec3(gr,0,1);
			hit_record rec_temp;
			//lm,pr
			{
			if(hit_triangle(r.direction(),r.origin(),ptrs[4],ptrs[6],ptrs[0],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[4],ptrs[6],ptrs[1],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[5],ptrs[7],ptrs[2],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[5],ptrs[7],ptrs[3],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			}
			//dr,lm
			{
			if(hit_triangle(r.direction(),r.origin(),ptrs[8],ptrs[9],ptrs[4],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[8],ptrs[9],ptrs[5],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[10],ptrs[11],ptrs[6],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[10],ptrs[11],ptrs[7],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			}
			//pr,dr
			{
			if(hit_triangle(r.direction(),r.origin(),ptrs[1],ptrs[3],ptrs[9],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[1],ptrs[3],ptrs[11],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[2],ptrs[8],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[2],ptrs[10],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			}
			//up down
			{
			if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[4],ptrs[8],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[1],ptrs[4],ptrs[9],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			
			if(hit_triangle(r.direction(),r.origin(),ptrs[2],ptrs[5],ptrs[8],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[3],ptrs[5],ptrs[9],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			}
			{
			if(hit_triangle(r.direction(),r.origin(),ptrs[0],ptrs[6],ptrs[10],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[1],ptrs[6],ptrs[11],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			
			if(hit_triangle(r.direction(),r.origin(),ptrs[2],ptrs[7],ptrs[10],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			if(hit_triangle(r.direction(),r.origin(),ptrs[3],ptrs[7],ptrs[11],rec_temp)){
				if(rec_temp.t>t_min&&rec_temp.t<t_max){
					on_hit(hitted, rec, rec_temp, t_max, mat_ptr);
				}
			}
			
			}
			return hitted;
		}
    }
    return false;
}
#endif