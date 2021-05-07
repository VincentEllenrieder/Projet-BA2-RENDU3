//constantes.h RENDU 2, Vincent Ellenrieder - Luis Rodriguez, Version finale

#ifndef CONSTANTES_H
#define CONSTANTES_H

constexpr double dim_max(1000.);				//km
constexpr double rayon_min(50.);				//km
constexpr double rayon_max(150.);				//km
constexpr double rayon_base(1.);				//km
constexpr double rayon_com(300.);				//km

constexpr double deltaD(5.);					//km
constexpr double maxD_prosp(10*dim_max);		//km
constexpr double maxD_forage(1.42*dim_max);		//km
constexpr double maxD_transp(5*dim_max);		//km
constexpr double maxD_com(1.42*dim_max);		//km
constexpr unsigned int max_robot(3);			//km

constexpr double iniR(1000.);					//ktonne
constexpr double finR(10*iniR);					//ktonne
constexpr double deltaR(iniR/4.);				//ktonne
constexpr double cout_reparation(0.0005);		//ktonne/km
constexpr double cout_prosp(iniR/100.);			//ktonne
constexpr double cout_forage(iniR/10.);			//ktonne
constexpr double cout_transp(iniR/10.);			//ktonne
constexpr double cout_com(iniR/1000.);			//ktonne

constexpr unsigned max_ligne(80);				//nombre de caractères par 
												//ligne de fichier

#endif
