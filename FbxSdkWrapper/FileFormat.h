#pragma once

namespace FbxWrapper
{
	public ref class FileFormat
	{
	public:
		FileFormat();
		string ^Description;
		string ^Extension;
	};


	public enum class EnumFileFormat : int
	{
		AutoDetect = -1,

		///FBX binary(*.fbx)
		FBX_binary = 0,
		///FBX ascii(*.fbx)
		FBX_ascii,
		///FBX encrypted(*.fbx)
		FBX_encrypted,
		///FBX 6.0 binary(*.fbx)
		FBX_6_binary,
		///FBX 6.0 ascii(*.fbx)
		FBX_6_ascii,
		///FBX 6.0 encrypted(*.fbx)
		FBX_6_encrypted,
		///AutoCAD DXF(*.dxf)
		DXF_autocad,
		///Alias OBJ(*.obj)
		OBJ_alias,
		///Collada DAE(*.dae)
		DAE_collada,
		///Biovision BVH(*.bvh)
		BVH_biovision,
		///Motion Analysis HTR(*.htr)
		HTR_motion_analysis,
		///Motion Analysis TRC(*.trc)
		TRC_motion_analysis,
		///Acclaim ASF(*.asf)
		ASF_acclain,
		///Acclaim AMC(*.amc)
		AMC_acclaim,
		///Vicon C3D(*.c3d)
		C3D_vicon,
		///Adaptive Optics AOA(*.aoa)
		AOA_adaptive_optics,
		///Superfluo MCD(*.mcd)
		MCD_superfluo
	};
}

