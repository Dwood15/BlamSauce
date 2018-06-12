#pragma once

#include <d3d9.h>
#include <precompile.h>

namespace Yelo {
	namespace DX9 {
		
		static IDirect3D9* d3d;
		static IDirect3DDevice9* global_d3d_device;

		void Initialize() {}
		void Dispose() {}


		void Initialize3D(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
		{
			d3d = GET_DPTR(D3D);
			global_d3d_device = GET_DPTR(Device);

			D3DADAPTER_IDENTIFIER9 d3d_id;
			if(SUCCEEDED(d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &d3d_id)))
			{
				char property_string[256] = "";

				Debug::AddPropertyToCrashReport("D3DDriver", d3d_id.Driver);
				Debug::AddPropertyToCrashReport("D3DDescription", d3d_id.Description);
				Debug::AddPropertyToCrashReport("D3DDeviceName", d3d_id.DeviceName);

				if(-1 != sprintf_s(property_string, sizeof(property_string), "%i.%i.%i.%i", HIWORD(d3d_id.DriverVersion.HighPart), LOWORD(d3d_id.DriverVersion.HighPart), HIWORD(d3d_id.DriverVersion.LowPart), LOWORD(d3d_id.DriverVersion.LowPart))) {
					Debug::AddPropertyToCrashReport("D3DDriverVersion", property_string);
				}

				if (-1 != sprintf_s(property_string, sizeof(property_string), "0x%X", d3d_id.VendorId)) { Debug::AddPropertyToCrashReport("D3DVendorId", property_string); }
				if (-1 != sprintf_s(property_string, sizeof(property_string), "0x%X", d3d_id.DeviceId)) { Debug::AddPropertyToCrashReport("D3DDeviceId", property_string); }
				if (-1 != sprintf_s(property_string, sizeof(property_string), "0x%X", d3d_id.SubSysId)) { Debug::AddPropertyToCrashReport("D3DSubSysId", property_string); }
				if (-1 != sprintf_s(property_string, sizeof(property_string), "0x%X", d3d_id.Revision)) { Debug::AddPropertyToCrashReport("D3DRevision", property_string); }
			}
		}


		void OnLostDevice()									{}
		void OnResetDevice(D3DPRESENT_PARAMETERS* params)	{}
		void Render()										{}
		void Release()										{}

		// D3D Present Properties
		D3DPRESENT_PARAMETERS*	D3DPresetParams()		PTR_IMP_GET2(Params);

		// D3D Properties
		IDirect3D9*				Direct3D9()				{ return d3d; }

		// D3D Caps
		D3DCAPS9*				D3DCaps()				PTR_IMP_GET2(Caps);

		// D3D Device Properties
		IDirect3DDevice9*		Direct3DDevice()		{ return global_d3d_device; }
		
		// DInput* Properties
		IDirectInput8*			DirectInput8()			DPTR_IMP_GET(DInput8);

		// IDirectInputDevice8 Properties
		IDirectInputDevice8*	InputDeviceKeyboard()	DPTR_IMP_GET(DInput8DeviceKeyboard);
		IDirectInputDevice8*	InputDeviceMouse()		DPTR_IMP_GET(DInput8DeviceMouse);
		
		IDirectInputDevice8*	InputDeviceJoystick(short index) {
			if(index >= 8) return NULL;
			return GET_DPTR2(DInput8DeviceJoysticks)[index];
		}

		void GetSMVersion(const DWORD sm_version, byte& major, byte& minor) {
			union{
				DWORD version;
				struct{
					struct{
						char minor_version;
						char major_version;
					};
					WORD type;
				};
			};

			version = sm_version;
			major = major_version;
			minor = minor_version;
		}
	};
};

struct COLOR_VERTEX 
{
	float x;
	float y;
	float z;
	float rhw;
	D3DCOLOR color;

	API_INLINE void Set(float _x, float _y, float _z, float _rhw, D3DCOLOR _color)
	{
		x = _x;
		y = _y;
		z = _z;
		rhw = _rhw;
		color = _color;
	}

	API_INLINE void Set(float _x, float _y, float _z, float _rhw, float _a, float _r, float _g, float _b)
	{
		x = _x;
		y = _y;
		z = _z;
		rhw = _rhw;
		color = D3DXCOLOR(_r, _g, _b, _a);
	}
};
#define NEW_COLOR_VERTEX(vert, x, y, z, rhw, color) vert.Set((float)x, (float)y, (float)z, (float)rhw, color)

struct TEXTURE_VERTEX
{
	float x;
	float y;
	float z;
	float rhw;
	float u;
	float v;

	API_INLINE void Set(float _x, float _y, float _z, float _rhw, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		rhw = _rhw;
		u = _u;
		v = _v;
	}
};
#define NEW_TEXTURE_VERTEX(vert, x, y, z, rhw, u, v) vert.Set((float)x, (float)y, (float)z, (float)rhw, (float)u, (float)v)
