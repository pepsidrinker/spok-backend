#include "ClMatrix.hpp"

ClMatrix::ClMatrix()
{
}

ClMatrix::~ClMatrix()
{
}

int ClMatrix::Create(std::size_t p_number_of_columns, std::size_t p_number_of_rows, std::shared_ptr<ClMatrix>& po_new_matrix)
{
    if(p_number_of_columns == 0 || p_number_of_rows == 0)
    {
        return -1;
    }

    auto new_instance = std::make_shared<ClMatrix>();
    new_instance->m_data = std::vector<int>(p_number_of_columns*p_number_of_rows, 0);
    new_instance->m_number_of_columns = p_number_of_columns;
    new_instance->m_number_of_rows = p_number_of_rows;
    po_new_matrix = new_instance;

    return 1;
}

int ClMatrix::ConvertCoordinatesToVectorIndex(std::size_t p_column_id, std::size_t p_row_id, std::size_t& po_vector_index)
{
    if(p_column_id >= this->m_number_of_columns || p_row_id >= this->m_number_of_rows)
    {
        return -1;
    }

    po_vector_index = p_column_id * this->m_number_of_columns + p_row_id;
    return 1;
}


int ClMatrix::ConvertVectorIndexToCoordinates(std::size_t p_vector_index, std::size_t& po_column_id, std::size_t& po_row_id)
{
    if(p_vector_index >= this->m_data.size())
    {
        return -1;
    }

    po_column_id = p_vector_index / this->m_number_of_columns;
    po_row_id = p_vector_index % this->m_number_of_columns;    

    return 1;
}


int ClMatrix::SetElement(std::size_t p_column_id, std::size_t p_row_id, int p_value)
{
    if(p_column_id >= this->m_number_of_columns || p_row_id >= this->m_number_of_rows)
    {
        return -1;
    }

    std::size_t vector_index = 0;
    this->ConvertCoordinatesToVectorIndex(p_column_id, p_row_id, vector_index);
    this->m_data[vector_index] = p_value;

    return 1;    
}



void ClMatrix::PrintFlat()
{
    std::cout << "==== Printing matrix (flat) ====" << std::endl;
    for (std::size_t i = 0; i < this->m_data.size(); ++i) 
    {
        std::size_t x, y;
        this->ConvertVectorIndexToCoordinates(i, x, y);
        std::cout << "Element at [" << x << ", " << y << "] => " << this->m_data[i] << std::endl;
    }
    std::cout << std::endl << "==== End of matrix ====" << std::endl;    
}

void ClMatrix::Print2D()
{
    std::cout << "==== Printing matrix (2D) ====" << std::endl;    
    for (std::size_t i = 0; i < this->m_number_of_rows; ++i) 
    {
        for (std::size_t j = 0; j < this->m_number_of_columns; ++j) 
        {
            std::size_t vector_index = 0;
            this->ConvertCoordinatesToVectorIndex(j,i,vector_index);
            std::cout << this->m_data[vector_index] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "==== End of matrix ====" << std::endl;
}

