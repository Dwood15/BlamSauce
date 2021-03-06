#pragma once

namespace Yelo {
	namespace Enums {
		enum runtime_data_integer_operation {
			_runtime_data_integer_operation_invalid,

			//////////////////////////////////////////////////////////////////////////
			// mutable
				_runtime_data_integer_operation_eq,
				_runtime_data_integer_operation_plus_eq,
				_runtime_data_integer_operation_minus_eq,
				_runtime_data_integer_operation_mul_eq,
				_runtime_data_integer_operation_div_eq,
				_runtime_data_integer_operation_plus_plus,
				_runtime_data_integer_operation_minus_minus,
				_runtime_data_integer_operation_and_eq,
				_runtime_data_integer_operation_or_eq,
				_runtime_data_integer_operation_xor_eq,
				_runtime_data_integer_operation_lhs_eq,
				_runtime_data_integer_operation_rhs_eq,
			//////////////////////////////////////////////////////////////////////////
			// immutable
				_runtime_data_integer_operation_plus,
				_runtime_data_integer_operation_minus,
				_runtime_data_integer_operation_mul,
				_runtime_data_integer_operation_div,
				_runtime_data_integer_operation_and,
				_runtime_data_integer_operation_or,
				_runtime_data_integer_operation_xor,
				_runtime_data_integer_operation_lhs,
				_runtime_data_integer_operation_rhs,

			_runtime_data_integer_operation,
		};

		enum runtime_data_vector_set_operation {
			_runtime_data_vector_set_operation_invalid,

			_runtime_data_vector_set_operation_eq,
			_runtime_data_vector_set_operation_plus_eq,
			_runtime_data_vector_set_operation_minus_eq,
			_runtime_data_vector_set_operation_mul_eq,
			_runtime_data_vector_set_operation_div_eq,

			_runtime_data_vector_set_operation,
		};

		enum runtime_data_vector_operation {
			_runtime_data_vector_operation_invalid,

			_runtime_data_vector_operation_normalize,
			_runtime_data_vector_operation_inverse,
			_runtime_data_vector_operation_conjugate,
			_runtime_data_vector_operation_plus_eq,
			_runtime_data_vector_operation_minus_eq,
			_runtime_data_vector_operation_mul_eq,
			_runtime_data_vector_operation_div_eq,
			_runtime_data_vector_operation_cross_product,
			_runtime_data_vector_operation_dot_product,
			_runtime_data_vector_operation_scalar_mul,
			_runtime_data_vector_operation_scalar_div,
			_runtime_data_vector_operation_magnitude,

			_runtime_data_vector_operation,
		};
	};

	namespace GameState::RuntimeData {

		struct s_runtime_data {

			template<typename T, size_t kValueCount = Enums::k_runtime_data_max_values_count>
			struct s_value_array {
				bool initialized;
				unsigned char : 8;
				short count;		// Number of elements in the runtime data

				T values[kValueCount];

				void InitializeHeader()
				{
					initialized = true;
					count = kValueCount;
				}
				void Clear()
				{
					InitializeHeader();

					memset(values, 0, sizeof(values));
				}

				// Validate that an operation can be performed at [value_index]
				bool OperationValidate(short value_index)
				{
					return initialized && value_index >= 0 && value_index < kValueCount;
				}
			};

			struct s_integers : public s_value_array<long> {
			}integers;

			struct s_vectors : public s_value_array<real_vector3d> {
			}vectors;
		};
		// Allocated in the game state
		static s_runtime_data* runtime_data;

		// Validate that an operation can be performed at [value_index]
		static bool IntegerOperationValidate(short value_index)
		{
			return runtime_data != nullptr && runtime_data->integers.OperationValidate(value_index);
		}
		// Reset all integers back to zero
		static void IntegersReset()
		{
			if(runtime_data != nullptr)
				runtime_data->integers.Clear();
		}
		// Get the integer value at [value_index].
		// Returns NONE if this operation fails.
		static long IntegerGet(short value_index)
		{
			if(IntegerOperationValidate(value_index))
				return runtime_data->integers.values[value_index];

			return NONE;
		}
		// Get the integer value at [value_index], then set it equal [value].
		// Returns NONE if this operation fails.
		static long IntegerGetAndSet(short value_index, long value)
		{
			if(IntegerOperationValidate(value_index))
			{
				// swap the original with the new and return the original
				std::swap(value, runtime_data->integers.values[value_index]);

				return value;
			}

			return NONE;
		}
		// Get the integer value at [value_index], then post-increment it.
		// Returns NONE if this operation fails.
		static long IntegerGetAndIncrement(short value_index)
		{
			if(IntegerOperationValidate(value_index))
				return runtime_data->integers.values[value_index]++;

			return NONE;
		}
		// Get the integer value at [value_index], then post-decrement it.
		// Returns NONE if this operation fails.
		static long IntegerGetAndDecrement(short value_index)
		{
			if(IntegerOperationValidate(value_index))
				return runtime_data->integers.values[value_index]--;

			return NONE;
		}
		static bool ValidBitShift(long bit_count)
		{
			return bit_count >= 0 && bit_count < BIT_COUNT(long);
		}
#define __INTEGER_OP_CASE(op_code_name)				!strcmp(op_name, op_code_name)
#define __INTEGER_OP_CASE_ARG_NONZERO(op_code_name)__INTEGER_OP_CASE(op_code_name) && op_value != 0
		static long IntegerDoOperation(short value_index, const char * op_name, long op_value)
		{
			long result = NONE;

			if(IntegerOperationValidate(value_index))
			{
				long& value = runtime_data->integers.values[value_index];

				bool valid_bs = ValidBitShift(op_value);

				//////////////////////////////////////////////////////////////////////////
				// mutable
				if( __INTEGER_OP_CASE("=") )	result = value = op_value;
				else if( __INTEGER_OP_CASE("+=") )	result = value += op_value;
				else if( __INTEGER_OP_CASE("-=") )	result = value -= op_value;
				else if( __INTEGER_OP_CASE("*=") )	result = value *= op_value;
				else if( __INTEGER_OP_CASE_ARG_NONZERO("/=") )					result = value /= op_value;
				else if( __INTEGER_OP_CASE("++") )	result = value++;
				else if( __INTEGER_OP_CASE("--") )	result = value--;
				else if( __INTEGER_OP_CASE("&=") )	result = value &= op_value;
				else if( __INTEGER_OP_CASE("|=") )	result = value |= op_value;
				else if( __INTEGER_OP_CASE("^=") )	result = value ^= op_value;
				else if( __INTEGER_OP_CASE("<<=")&&valid_bs )					result = value <<= op_value;
				else if( __INTEGER_OP_CASE(">>=")&&valid_bs )					result = value >>= op_value;
					//////////////////////////////////////////////////////////////////////////
					// immutable
				else if( __INTEGER_OP_CASE("+") )	result = value + op_value;
				else if( __INTEGER_OP_CASE("-") )	result = value - op_value;
				else if( __INTEGER_OP_CASE("*") )	result = value * op_value;
				else if( __INTEGER_OP_CASE_ARG_NONZERO("/") )					result = value / op_value;
				else if( __INTEGER_OP_CASE("&") )	result = value & op_value;
				else if( __INTEGER_OP_CASE("|") )	result = value | op_value;
				else if( __INTEGER_OP_CASE("^") )	result = value ^ op_value;
				else if( __INTEGER_OP_CASE("<<")&&valid_bs )					result = value << op_value;
				else if( __INTEGER_OP_CASE(">>")&&valid_bs )					result = value >> op_value;
			}

			return result;
		}
#undef __INTEGER_OP_CASE
#undef __INTEGER_OP_CASE_ARG_NONZERO

#define __VECTOR_OP_CASE(op_code_name)				result && !strcmp(op_name, op_code_name)
#define __VECTOR_OP_CASE_ARG(op_code_name)			__VECTOR_OP_CASE(op_code_name) && (result = (vec_rhs != nullptr))
#define __VECTOR_OP_CASE_ARG_I_NONZERO(op_code_name)__VECTOR_OP_CASE_ARG(op_code_name) && (result = (vec_rhs->i != 0.0f))
		// Validate that an operation can be performed at [value_index]
		static bool VectorOperationValidate(short value_index, short element_index = 0)
		{
			return runtime_data != nullptr && runtime_data->vectors.OperationValidate(value_index) &&
					 element_index >= 0 && element_index < 3; // NOTE: 0=x, 1=y, 2=z
		}
		// Reset all vectors back to zero
		static void VectorsReset()
		{
			if(runtime_data != nullptr)
				runtime_data->vectors.Clear();
		}
		static real VectorGetElement(short value_index, short element_index)
		{
			if(VectorOperationValidate(value_index, element_index))
			{
				const real_vector3d& vector = runtime_data->vectors.values[value_index];

				switch(element_index)
				{
					case 0: return vector.i;
					case 1: return vector.j;
					case 2: return vector.k;
				}
			}

			return CAST(real, NONE);
		}
		static bool VectorSetElement(short value_index, short element_index,
											  const char * op_name, real op_value)
		{
			bool result = false;

			if(VectorOperationValidate(value_index, element_index))
			{
				real_vector3d& vector = runtime_data->vectors.values[value_index];
				real* element_ptr = nullptr;

				result = true;

				switch(element_index)
				{
					case 0: element_ptr = &vector.i; break;
					case 1: element_ptr = &vector.j; break;
					case 2: element_ptr = &vector.k; break;
				}

				if( __VECTOR_OP_CASE("=") )					*element_ptr = op_value;
				else if( __VECTOR_OP_CASE("+=") )					*element_ptr += op_value;
				else if( __VECTOR_OP_CASE("-=") )					*element_ptr -= op_value;
				else if( __VECTOR_OP_CASE("*=") )					*element_ptr *= op_value;
				else if( __VECTOR_OP_CASE("/=")&&op_value != 0.0f )	*element_ptr /= op_value;
				else result = false;
			}

			return result;
		}
		static bool VectorSet(short value_index, const char * op_name, real x, real y, real z)
		{
			bool result = false;

			if(VectorOperationValidate(value_index))
			{
				real_vector3d& vector = runtime_data->vectors.values[value_index];

				result = true;

				if( __VECTOR_OP_CASE("=") )		vector.Set(x, y, z);
				else if( __VECTOR_OP_CASE("+=") )		vector.Set(vector.i+x, vector.j+y, vector.k+z);
				else if( __VECTOR_OP_CASE("-=") )		vector.Set(vector.i-x, vector.j-y, vector.k-z);
				else if( __VECTOR_OP_CASE("*=") )		vector.Set(vector.i*x, vector.j*y, vector.k*z);
				else if( __VECTOR_OP_CASE("/=") )
				{
					if(x == 0.0f) x = 1.0f;
					if(y == 0.0f) y = 1.0f;
					if(z == 0.0f) z = 1.0f;
					vector.Set(vector.i/x, vector.j/y, vector.k/z);
				}
				else result = false;
			}

			return result;
		}
		static bool VectorDoOperation(short value_index, const char * op_name, short op_arg_vector_index)
		{
			bool result = false;

			if(VectorOperationValidate(value_index))
			{
				real_vector3d& vector = runtime_data->vectors.values[value_index];
				real_vector3d* vec_rhs = VectorOperationValidate(op_arg_vector_index) ?
												 &runtime_data->vectors.values[op_arg_vector_index] : nullptr;

				result = true;

				if( __VECTOR_OP_CASE("normalize") )				vector.Normalize();
				else if( __VECTOR_OP_CASE("inverse") )					vector.Inverse();
				else if( __VECTOR_OP_CASE("conjugate") )				vector = -vector;
				else if( __VECTOR_OP_CASE_ARG("+=") )					vector += *vec_rhs;
				else if( __VECTOR_OP_CASE_ARG("-=") )					vector -= *vec_rhs;
				else if( __VECTOR_OP_CASE_ARG("*=") )					vector *= vec_rhs->i;
				else if( __VECTOR_OP_CASE_ARG_I_NONZERO("/=") )			vector /= vec_rhs->i;
				else if( __VECTOR_OP_CASE_ARG("cross_product") )		vector = vector ^ *vec_rhs;
				else if( __VECTOR_OP_CASE_ARG("dot_product") )			vec_rhs->i = vector * *vec_rhs;
				else if( __VECTOR_OP_CASE_ARG("scalar_mul") )			vector = vector * vec_rhs->i;
				else if( __VECTOR_OP_CASE_ARG_I_NONZERO("scalar_div") )	vector = vector / vec_rhs->i;
				else if( __VECTOR_OP_CASE_ARG("magnitude") )			vec_rhs->i = vector.Magnitude();
				else result = false;
			}

			return result;
		}
		static char* VectorToString(short value_index)
		{
			static char static_buffer[128];
			static_buffer[0] = '\0';

			if(VectorOperationValidate(value_index))
			{
				const real_vector3d& vector = runtime_data->vectors.values[value_index];

				sprintf_s(static_buffer, "%f %f %f", vector.i, vector.j, vector.k);
			}

			return static_buffer;
		}
#undef __VECTOR_OP_CASE
#undef __VECTOR_OP_CASE_ARG
#undef __VECTOR_OP_CASE_ARG_I_NONZERO




		void Initialize() {
		}

		void Dispose() {
		}

		void InitializeForNewGameState() {
			runtime_data = GameState::GameStateMalloc<s_runtime_data>();
		}

		void InitializeForNewMap() {
			IntegersReset();
			VectorsReset();
		}

		void InitializeScripting() {
			Scripting::InitializeScriptFunction(Enums::_hs_function_runtime_integers_reset, scripting_runtime_integers_reset_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_integer_get, scripting_runtime_integer_get_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_integer_set, scripting_runtime_integer_set_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_integer_inc, scripting_runtime_integer_inc_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_integer_dec, scripting_runtime_integer_dec_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_integer_operation, scripting_runtime_integer_operation_evaluate);

			Scripting::InitializeScriptFunction(Enums::_hs_function_runtime_vectors_reset, scripting_runtime_vectors_reset_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_vector_get_element, scripting_runtime_vector_get_element_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_vector_set_element, scripting_runtime_vector_set_element_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_vector_set, scripting_runtime_vector_set_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_vector_operation, scripting_runtime_vector_operation_evaluate);
			Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_runtime_vector_to_string, scripting_runtime_vector_to_string_evaluate);
		}

		real_vector3d* VectorValueGetForModify(short value_index)
		{
			if(VectorOperationValidate(value_index))
				return &runtime_data->vectors.values[value_index];

			return nullptr;
		}
		const real_vector3d* VectorValueGet(short value_index)
		{
			if(VectorOperationValidate(value_index))
				return &runtime_data->vectors.values[value_index];

			return nullptr;
		}

	};
};
