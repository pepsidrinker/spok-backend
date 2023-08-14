#pragma once

#include <memory>
#include <vector>
#include <iostream>

class ClMatrix
{
    protected:
        std::size_t m_number_of_columns;
        std::size_t m_number_of_rows;


    public:
        std::vector<int> m_data;

        ClMatrix();
        ~ClMatrix();
        static int Create(std::size_t p_number_of_columns, std::size_t p_number_of_rows, std::shared_ptr<ClMatrix>& po_new_matrix);
        int ConvertCoordinatesToVectorIndex(std::size_t p_column_id, std::size_t p_row_id, std::size_t& po_vector_index);
        int ConvertVectorIndexToCoordinates(std::size_t p_vector_index, std::size_t& po_column_id, std::size_t& po_row_id);
        int SetElement(std::size_t p_column_id, std::size_t p_row_id, int p_value);
        void PrintFlat();
        void Print2D();
};

typedef std::shared_ptr<ClMatrix> MATRIX_POINTER;