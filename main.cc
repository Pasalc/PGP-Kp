#include <iostream>
#include "random.h"
#include <fstream>
#include <iostream>


#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "sphere.h"
#include "octaeder.h"
#include "icosaeder.h"
#include "dodoecaeder.h"
#include "floor.h"
#include "light.h"
#include "light_list.h"
#define _NO_DEBUG_HEAP 1

inline std::istream& operator>>(std::istream &is, sphere &s) {
	s.mat_ptr=new my_material();
	vec3 clr;
	double ref,trn;
	is >> s.center>>clr>>s.radius>>ref>>trn>>s.l_amount;
	std::cerr<<"\n"<<s.center<<" "<<s.radius<<"\n";
	s.mat_ptr=new metal(vec3(0.2,1,0.2),0.5);//my_material(clr,ref,trn);//
	return is;
}

//#define MAXFLOAT 1e15f
int max_depth;
ofstream logi("logs.txt");

constexpr float maxfloat=1000000;
constexpr float minfloat=0.0001;

using namespace std;
vec3 color(const ray& r, hitable *world, light* lights, int depth) {
    hit_record rec;
					//logi<<"i:St\n"<<std::endl;
    if (world->hit(r, minfloat, maxfloat, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < max_depth && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			std::cerr<<"in";
			vec3 clr = lights->illumination(rec.normal,rec.p);
			vec3 ambient=rec.mat_ptr->ambient();
			clr=(vec3(1,1,1)-ambient)*clr+ambient;
			return clr + (vec3(1,1,1)-clr)*attenuation*color(scattered, world,lights, depth+1);
			//return attenuation*color(scattered, world, depth+1);
        }
        else {
            return rec.mat_ptr->surface_light();//redone with light check
        }
    }
    else {
		return vec3(0.1/2,0.1/2,0.1/2);
					
    }
}


std::pair<hitable*, light*> get_objects_scene() {
    int n = 10;
    hitable **list = new hitable*[n];
    int i = 0;
	double trans,refl;
	auto oct = new octaeder();
	auto ico = new icosaeder();
	auto dod = new dodoecaeder();
	auto flr = new Floor();
	std::cin>>(*oct)>>*ico>>*dod;
	hit_record rec;
	oct->hit(ray(vec3(1,0,0),vec3(0,1,0)), minfloat, maxfloat, rec);
	std::cin>>*flr;
	//reinterpret_cast<my_material*>(oct->mat_ptr)->albedo=vec3(1,0,0);
	//reinterpret_cast<my_material*>(ico->mat_ptr)->albedo=vec3(0,1,0);
	//reinterpret_cast<my_material*>(dod->mat_ptr)->albedo=vec3(0,0,1);
	
	/*				 
    list[i++] = oct;//new octaeder(vec3(0,-10,0), 1, new lambertian(vec3(1., 0.0, 0.0)));
    list[i++] = ico;//new icosaeder(vec3(10, -10, 1), 10.0, new dielectric(0.6));
	list[i++] = dod;//new dodoecaeder(vec3(0, 0, 1), 10.0, new metal(vec3(0., 0., 1.),0.5));
	*/
	//floor is uninitilize???
	//list[i++] = flr;//new Floor(vec3(1, 0, 0), vec3(0,0,0),vec3(0,1,0),vec3(1,1,0), new metal(vec3(0., 0., 1.),0.5));
	
	//std::cerr<<"\nmy:"<<reinterpret_cast<my_material*>(ico->mat_ptr)->albedo<<"\nmy:"<<reinterpret_cast<my_material*>(ico->mat_ptr)->trans<<"\nmy:"<<reinterpret_cast<my_material*>(ico->mat_ptr)->ref_idx<<"\nmy:"\
	<<ico->radius<<"\nmy:"<<ico->l_amount;
	
	/*
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                        center, 0.2,
                        new lambertian(vec3(random_double()*random_double(),
                                            random_double()*random_double(),
                                            random_double()*random_double()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                        center, 0.2,
                        new metal(vec3(0.5*(1 + random_double()),
                                       0.5*(1 + random_double()),
                                       0.5*(1 + random_double())),
                                  0.5*random_double())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
	*/
	/*
	int num_lights;
	std::cin>>num_lights;
	std::cerr<<num_lights;
	while(num_lights>0){
		--num_lights;
		light* l= new light();
		vec3 orig; vec3 clr;
		std::cin>>*l;
		list[i++] = l;
	}
	*/
	list[i++] = new sphere(
                        vec3(0,0,0), 0.2,
                        new lambertian(vec3(random_double()*random_double(),
                                            random_double()*random_double(),
                                            random_double()*random_double())));
											
	int num_lights;		
	int lc=0;
	light** l_list = new light*[num_lights];
	light* l=new light(vec3(2,2,2),new light_material(vec3(1,1,1)));
	list[i++] = l;
	l_list[lc++]=l;
	hit_record hh;
	ray rr(vec3(0,0,0),vec3(1,1,1)),t2;
	vec3 t1;
	assert(dynamic_cast<sphere*>(list[0])->mat_ptr->scatter(rr, hh, t1, t2));
	std::cerr<<"\nGG\n";
    return std::pair<hitable*,light*>(new hitable_list(list,i),new light_list(l_list,lc));
}


double comp(double b, double A, double w, double p,double t){
	return b+A*sin(w*t+p);
}


int main() {
	int max_steps=50;
	std::string str;
    int nx  = 640;//1200;
    int ny  = 320;//800;
	int pov =120;
	
    int ns = 20;
	char file_str[100];
    //hitable *world = random_scene();

    //vec3 lookat(10, -10, 0);
    float dist_to_focus = 1;
    float aperture = 1;
	double r0,phi0,z0,r1,phi1,z1;
	double Arc,wrc,prc,Arn,wrn,prn;
	double Azc,wzc,pzc,Azn,wzn,pzn;
	double wpc,wpn;
	
	
	
	std::cin>>max_steps>>str>>nx>>ny>>pov;
	std::cerr<<"nx"<<nx<<"ny"<<ny<<"\n";
	std::cin>>r0>>z0>>phi0>>Arc>>Azc>>wrc>>wzc>>wpc>>prc>>pzc;
	std::cin>>r1>>z1>>phi1>>Arn>>Azn>>wrn>>wzn>>wpn>>prn>>pzn;
	auto [world,light_world] = get_objects_scene();
	std::cerr<<"nx"<<nx<<"ny"<<ny<<"\n";
	std::cerr<<reinterpret_cast<hitable_list*>(world)->list_size;
	//std::cerr<<"\nsss"<<reinterpret_cast<light_material*>(reinterpret_cast<light*>(reinterpret_cast<hitable_list*>(world)->list[4])->mat_ptr)->color<<"\n";
	
	//Uncomment later
	//std::cin>>ns>>max_depth;
	
	std::cerr<<"nx"<<nx<<"ny"<<ny<<"\n";
	for(int t_step=0;t_step<max_steps;++t_step){
		std::cerr<<"t_step:"<<t_step<<std::endl;
		double t=t_step*(pi*2/max_steps);
		
		vec3 lookfrom(comp(r0,Arc,wrc,prc,t),
						comp(z0,Azc,wzc,pzc,t),
						phi0+wpc*t);
		vec3 lookat(comp(r1,Arn,wrn,prn,t),
						comp(z1,Azn,wzn,pzn,t),
						phi1+wpn*t);
						
		//vec3 lookfrom=vec3(30,30,3);//(20-40*sin(3.1415/25*t_step),20-40*cos(3.1415/25*t_step),3);
		//vec3 lookat=vec3(0,0,0);
		snprintf(file_str, 100,"render/out%d.ppm", t_step);
		std::ofstream image(file_str);
		image<< "P3\n" << nx << " " << ny << "\n255\n";
		camera cam(vec3(sin(t),cos(t),5),vec3(0,0,0),vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);//(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);
					 
		for (int j = ny-1; j >= 0; j--) {
			logi<<"j:"<<j<<std::endl;
			for (int i = 0; i < nx; i++) {
				vec3 col(0, 0, 0);
				for (int s=0; s < ns; s++) {
					float u = float(i + random_double()) / float(nx);
					float v = float(j + random_double()) / float(ny);
					ray r = cam.get_ray(u, v);
					col += color(r, world,light_world,0);
				}
				col /= float(ns);
				if(col[0]<0||col[1]<0||col[2]<0) {std::cerr<<"i:" << i <<"j:"<<j<<std::endl; abort();}
				col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
				int ir = int(255.99*col[0]);
				int ig = int(255.99*col[1]);
				int ib = int(255.99*col[2]);
				image<< ir << " " << ig << " " << ib << "\n";
			}
		}
	}
}