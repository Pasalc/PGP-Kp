#ifndef FLOOR_H
#define FLOOR_H
#include <cassert>

#include "hitable.h"
#include "vec3.h"

inline namespace My_space{

	class Floor: public hitable{
		public:
		void fix_cord(){
			if(a.y()>b.y()) swap(a,b);
			if(c.y()>d.y()) swap(c,d);
			if(a.x()>c.x()) swap(a,c);
			if(b.x()>d.x()) swap(b,d);
			std::cerr<<"a:"<<a<<std::endl;
			std::cerr<<"b:"<<b<<std::endl;
			std::cerr<<"c:"<<c<<std::endl;
			std::cerr<<"d:"<<d<<std::endl;
			assert(a.x()==b.x());
			assert(a.y()==c.y());
			assert(d.x()==c.x());
			assert(d.y()==b.y());
			norm=unit_vector(cross(b-a,c-a));
			center=(a+d)/2;
		};
		Floor(){a=b=c=d=vec3(1,1,0);norm=vec3(0,0,1);a.e[0]-=1;b.e[0]-=1;c.e[1]-=1;mat_ptr=new metal(vec3(1,0,0),0.5);};
		Floor(vec3 ld,vec3 lu,vec3 rd,vec3 ru, material* material_ptr) : a(ld), b(lu),c(rd),d(ru), mat_ptr(material_ptr){
			fix_cord();
		};
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
		bool intersection(const vec3& orig, const vec3& dir,hit_record& rec) const;
		bool cull(const vec3& p) const;
		vec3 a,b,c,d;
		vec3 norm;
		vec3 center;
		material *mat_ptr;
		static constexpr float epsil=0.000001f;
	};

	bool Floor::cull(const vec3& p) const{
		return p.x()>a.x()&&p.x()<d.x()&&p.y()>a.y()&&p.y()<d.y();
	}

	bool Floor::intersection(const vec3& orig, const vec3& dir,hit_record& rec) const{
		bool not_collinear;
		bool intersected=false;
		
		float denom = dot(dir,norm);
		if (abs(denom) > epsil) 
		{
			float t = dot(center - orig,norm) / denom;
			if (t >= 0) {
				rec.t=t;
				rec.p=orig+t*dir;
				rec.normal=norm;
				intersected= true; 
			}
		}
		return intersected;
	}

	bool Floor::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
		//live_checker("Floor");
		//std::cerr<<"Flr"<<std::endl;
		vec3 p,norm;
		double t;
		hit_record rec_temp;
		bool hitted;
		
		if(intersection(r.origin(),r.direction(),rec_temp)){
			if(cull(rec_temp.p)){
				on_hit(hitted, rec, rec_temp, t_max, mat_ptr);	
			}
		}
		//std::cerr<<"Flr end"<<std::endl;
		return hitted;
	}


	inline std::istream& operator>>(std::istream &is, Floor &f) {
		is >> f.a >> f.b >> f.c>>f.d;
		f.fix_cord();
		vec3 a;
		string str;
		std::cin>>str;
		std::cerr<<str;
		float fuzz;
		is >> a >> fuzz;
		f.mat_ptr=new metal(a,fuzz);
		return is;
	}

}
#endif