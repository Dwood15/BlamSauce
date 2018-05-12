#pragma once
/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../cseries/cseries_base.h"
#include "datum_index.h"
#include "data.h"

namespace Yelo {
	namespace Memory {
		struct s_dynamic_array {
			size_t element_size;
			int32  count;
			void   *elements;
		}; static_assert(sizeof(s_dynamic_array) == 0xC);

		template <typename DatumT>
		struct DataArrayIteratorResult {
			datum_index index;
			DatumT      *datum;

			DataArrayIteratorResult(datum_index i, DatumT *d) : index(i), datum(d) {}

			DatumT *operator ->() const { return datum; }

			DatumT &operator *() const { return *datum; }

			datum_index::index_t GetAbsoluteIndex() const { return index.index; }
		};

		template <typename DatumT, size_t MaxDatumCount, size_t MaxDatumCountUpgrade = MaxDatumCount>
		class DataArray {
			typedef DataArray<DatumT, MaxDatumCount, MaxDatumCountUpgrade> DataArrayT;

		public:
			class Iterator {
				s_data_iterator m_iterator;
				DatumT          *m_current_instance;

			public:
				Iterator(DataArrayT &data) {
					blam::data_iterator_new(m_iterator, &data.Header);
					m_current_instance = nullptr;
				}

				DatumT *Next() {
					return m_current_instance =
								 CAST_PTR(DatumT*, blam::data_iterator_next(m_iterator));
				}

				datum_index Current() const { return this->m_iterator.index; }

				static const Iterator GetEndHack(DataArrayT &data) {
					auto hack = Iterator(data);
					hack.m_iterator.SetEndHack();
					return hack;
				}

				bool operator !=(const Iterator &other) const {
					return m_iterator != other.m_iterator;
				}

				Iterator &operator ++() {
					Next();
					return *this;
				}

				DataArrayIteratorResult<DatumT> operator *() const {
					return DataArrayIteratorResult<DatumT>(m_iterator.index, m_current_instance);
				}
			};

			s_data_array Header;

		public:

			Iterator &IteratorNew(Iterator &iter) {
				return iter = Iterator(this);
			}

			DatumT *Datums() {
				return CAST_PTR(DatumT*, this->Header.base_address);
			}

			operator s_data_array *() {
				return &this->Header;
			}

			DatumT *operator [](datum_index handle) {
				return &CAST_PTR(DatumT*, this->Header.base_address)[handle.index];
			}

			Iterator begin() /*const*/
			{
				auto iter = Iterator(*this);
				iter.Next();
				return iter;
			}

			const Iterator end() /*const*/
			{
				return Iterator::GetEndHack(*this);
			}

			void Verify() const { blam::data_verify(&Header); }

			void Dispose() { blam::data_dispose(&Header); }

			void MakeValid() { blam::data_make_valid(&Header); }

			void MakeInvalid() { blam::data_make_invalid(&Header); }

			void DeleteAll() { blam::data_delete_all(&Header); }

			datum_index NextIndex(datum_index cursor) { return blam::data_next_index(&Header, cursor); }

			datum_index NewAtIndex(datum_index index) { return blam::datum_new_at_index(&Header, index); }

			datum_index New() { return blam::datum_new(&Header); }

			void Delete(datum_index index) { return blam::datum_delete(&Header, index); }
		};

	};
};
