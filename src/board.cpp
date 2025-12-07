#include "board.h"

Board::Board()
:   m_board(SIZE, std::vector<Cell*>(SIZE, nullptr))

{
    for (int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            m_board[i][j] = new Emptycell;
        }
       
    }
}

Board::~Board()
{
    for (int i = 0; i < SIZE; ++i) 
    {
        for (int j = 0; j < SIZE; ++j) 
        {
            delete m_board[i][j]; 
        }
    } 
}

std::vector<std::vector<Cell *>> Board::get_board()
{
    return  m_board;
}

void Board::set_cell(size_t row, size_t col, Cell* cell)
{
    if (row >= SIZE || col >= SIZE)
    {
       std::cout << "Out of Bounds" ;  
    }
    Emptycell* tmp = dynamic_cast<Emptycell*>(m_board[row][col]);
    if (tmp)
    {
        delete tmp;
        m_board[row][col] = cell;
    }
    else
    {
        std::cout << "Cell is not empty\n";  
    }
}


void Board::read()
{
  std::ifstream file("state");
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file .\n";
        return;
    }
    char symbol;
    for (size_t i = 0; i < SIZE; ++i) 
    {
        for (size_t j = 0; j < SIZE; ++j) 
        {
            if (file.get(symbol)) 
            {
                if (symbol == '-') 
                {
                    set_cell(i, j, new Emptycell());

                } 
                else if (symbol == 'O') 
                {
                    set_cell(i, j, new Ocell());

                } 
                else if (symbol == 'X') 
                {
                    set_cell(i, j, new Xcell());

                }
            }
        }
    }
    file.close();
}


void Board::write()
{
    std::ofstream file("state", std::ofstream::out);
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (m_board[i][j]->get_value() == ' ')
            {
                file << '-';   
            }
            else
            {
                file << m_board[i][j]->get_value();
            }
        }
    }
}


