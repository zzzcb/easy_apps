#ifndef EXPORT_H
#define EXPORT_H

	#if defined(_WIN32) || defined(_WIN64)
		#ifdef BUILDING_DLL
			#define API_EXPORT __declspec(dllexport)
		#else
			#define API_EXPORT __declspec(dllimport)
		#endif
	#else
		#define API_EXPORT 
	#endif

#endif 
