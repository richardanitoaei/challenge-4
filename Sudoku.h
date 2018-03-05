#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <iostream>
#include <vector>
#include <set>
#include <math.h>
using namespace std;

// TODO: Your Sudoku class goes here:

class Sudoku {
public:
    vector<vector<set<int>>> vec;
    set<int> myset = {1, 2, 3, 4, 5, 6, 7, 8, 9};

public:
    Sudoku(int size_board)
    {
        for (int i = 0; i < size_board; i++)
        {
            vector<set<int>> row; // Create an empty row
            for (int j = 0; j < size_board; j++) {
                row.push_back(myset); // Add an element(set) to the row
            }
            vec.push_back(row); // Add the row to the main vector/board
        }
    }

    int getSquare(int row, int col)
    {
        auto element = vec[row][col];
        if(element.size() == 1)
        {
            auto square  = element.begin();
            return *square;
        }
        else
            return -1;
    }
    
   bool setSquare(int row, int col, int value)
    {
        set<int> newset = {value};
        vec[row][col] = newset;

        for ( int i=0; i<vec.size(); i++ )
        { 
            for ( int j=0; j<vec.size(); j++ )
                if(vec[i][j].size() == 1)
                {
                    auto elem = vec[i][j].begin();
                    int root = static_cast<int>(ceil(sqrt(static_cast<double>(vec.size()))));
                    return (removeFromSetInRow(i, *elem)&&
                            removeFromSetInCol(j, *elem)&&
                            removeFromSetInBox(i-i%root, j-j%root, *elem));
                }
        }
    }
    
    bool removeFromSetInRow(int row, int elem)
    {
        for (int k = 0; k < vec.size(); k++)
        {
            auto elem_row = vec[row][k];
            elem_row.erase(elem);
            if(elem_row.size()==0)
            {
            return false;
            }
        }
    return true;
    }
 
    bool removeFromSetInCol(int col, int elem)
    {
        for (int k = 0; k < vec.size(); k++)
        {
            auto elem_col = vec[k][col];
            elem_col.erase(elem);
            if(elem_col.size()==0)
            {
                return false;
            }
    }
    return true;
}
 
    bool removeFromSetInBox(int boxStartRow, int boxStartCol, int elem)
    {
        for (int row = 0; row < sqrt(vec.size()); row++)
        {
            for (int col = 0; col < sqrt(vec.size()); col++)
        {
            auto elem_box = vec[row+boxStartRow][col+boxStartCol];
            elem_box.erase(elem);
            if ( elem_box.size()==0)
                return false;
        }
    }
    return true;
    }

};

#endif
