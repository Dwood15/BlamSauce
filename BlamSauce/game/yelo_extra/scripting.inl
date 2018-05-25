#pragma once
#include <precompile.h>

static void* scripting_data_array_info_evaluate(void** arguments)
{
	struct s_arguments {
		cstring data_array_name;
	}* args = reinterpret_cast<s_arguments *>(arguments);

	DataArrayInfoDumpToConsole(args->data_array_name);

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// physics constants

static void* scripting_physics_get_gravity_evaluate()
{
	TypeHolder result; result.pointer = nullptr;

	result.real = GameState::Physics()->gravity;

	return result.pointer;
}

static void* scripting_physics_set_gravity_evaluate(void** arguments)
{
	struct s_arguments {
		real gravity_fraction;
	}* args = reinterpret_cast<s_arguments *>(arguments);

	GameState::Physics()->SetGravityScale(args->gravity_fraction);

	return nullptr;
}

static void* scripting_physics_constants_reset_evaluate()
{
	GameState::Physics()->Reset();

	return nullptr;
}


//////////////////////////////////////////////////////////////////////////
// integers
static void* scripting_runtime_integers_reset_evaluate()
{
	IntegersReset();

	return nullptr;
}

static void* scripting_runtime_integer_get_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.long = IntegerGet(args->value_index);

	return result.pointer;
}

static void* scripting_runtime_integer_set_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		long value;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.long = IntegerGetAndSet(args->value_index, args->value);

	return result.pointer;
}

static void* scripting_runtime_integer_inc_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.long = IntegerGetAndIncrement(args->value_index);

	return result.pointer;
}

static void* scripting_runtime_integer_dec_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.long = IntegerGetAndDecrement(args->value_index);

	return result.pointer;
}

static void* scripting_runtime_integer_operation_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		cstring op_name;
		long op_value;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.long = IntegerDoOperation(args->value_index, args->op_name, args->op_value);

	return result.pointer;
}


//////////////////////////////////////////////////////////////////////////
// vectors
static void* scripting_runtime_vectors_reset_evaluate()
{
	VectorsReset();

	return nullptr;
}
static void* scripting_runtime_vector_get_element_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		short element_index;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.real = VectorGetElement(args->value_index, args->element_index);

	return result.pointer;
}
static void* scripting_runtime_vector_set_element_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		short element_index;
		unsigned short : 16;
		cstring op_name;
		real op_value;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.boolean = VectorSetElement(args->value_index, args->element_index,
												 args->op_name, args->op_value);

	return result.pointer;
}
static void* scripting_runtime_vector_set_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		cstring op_name;
		real op_x; real op_y; real op_z;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.boolean = VectorSet(args->value_index, args->op_name, args->op_x, args->op_y, args->op_z);

	return result.pointer;
}
static void* scripting_runtime_vector_operation_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
		cstring op_name;
		short op_arg_vector_index;
		unsigned short : 16;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.boolean = VectorDoOperation(args->value_index, args->op_name, args->op_arg_vector_index);

	return result.pointer;
}
static void* scripting_runtime_vector_to_string_evaluate(void** arguments)
{
	struct s_arguments {
		short value_index;
		unsigned short : 16;
	}* args = reinterpret_cast<s_arguments *>(arguments);
	TypeHolder result; result.pointer = nullptr;

	result.pointer = VectorToString(args->value_index);

	return result.pointer;
}
