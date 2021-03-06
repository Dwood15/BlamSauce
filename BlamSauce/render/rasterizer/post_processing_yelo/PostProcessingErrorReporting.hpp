#pragma once
namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace ErrorReporting
	{
		// TODO: these functions should be outside of the postprocessing system,
		// as other code may want the functionality they provide
		enum
		{
			k_max_error_line_count = 3,
		};

		void Write(const char * string);
		void WriteLine(const char * format, ...);
		void WriteD3DXErrors(LPD3DXBUFFER buffer);
	};};};
};
