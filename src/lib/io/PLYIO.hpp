/**
 * @file       PLYIO.hpp
 * @brief      I/O support for PLY files.
 * @details    I/O support for PLY files: Reading and writing meshes and
 *             pointclouds, including color information, confidence, intensity
 *             and normals.
 * @author     Lars Kiesow (lkiesow), lkiesow@uos.de
 * @version   110922
 * @date       Created:       2011-09-16 17:28:28
 * @date       Last modified: 09/22/11 18:33:30
 *
 */


#ifndef __PLY_IO_H__
#define __PLY_IO_H__

#include "BaseIO.hpp"
#include "MeshLoader.hpp"
#include "PointLoader.hpp"
#include <rply.h>
#include <stdint.h>
#include <cstdio>
#include <vector>

using std::vector;

namespace lssr {

/**
 * @brief A class for input and output to ply files.
 */
class PLYIO : public BaseIO, public MeshLoader,  public PointLoader {

public:

	void save( string filename, e_ply_storage_mode mode, 
			vector<string> obj_info = vector<string>(), 
			vector<string> comment = vector<string>() );
	void save( string filename );
	void read( string filename, bool readColor, bool readConfidence = true, 
			bool readIntensity = true, bool readNormals = true, 
			bool readFaces = true );
	void read( string filename );

	static int readVertexCb( p_ply_argument argument );
	static int readColorCb( p_ply_argument argument );
	static int readFaceCb( p_ply_argument argument );

	virtual ~PLYIO();

};

}

#endif
