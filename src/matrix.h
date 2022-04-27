#include "cursor.h"

/**
 * @brief The Matrix class holds all information related to a loaded matrix. It
 * also implements methods that interact with the parsers, executors, cursors
 * and the buffer manager. There in one way a matrix object gets
 * created through the course of the workflow - the first is by using the LOAD
 * command 
 *
 */
class Matrix {
    int findValueAtIndex(int row, int col);

public:
    string sourceFileName = "";
    string matrixName = "";
    vector<uint> distinctValuesPerColumnCount;
    uint columnCount = 0;
    long long int rowCount = 0;
    uint blockCount = 0;
    uint maxRowsPerBlock = 0;
    bool isSparse = false;
    uint rowBlocks = 0;
    uint colBlocks = 0;
    bool isTransposed = false;

    void calculateStats();
    bool blockify();
    Matrix();
    Matrix(string matrixName);
    bool load();
    void printToSource(ostream& fout, uint rowCount);
    void print();
    void makePermanent();
    bool isPermanent();
    void getNextPage(Cursor* cursor);
    Cursor getCursor();
    void unload();

    /**
 * @brief Static function that takes a vector of valued and prints them out in a
 * comma seperated format.
 *
 * @tparam T current usaages include int and string
 * @param row 
 */
    template <typename T>
    void writeRow(vector<T> row, ostream& fout, bool end)
    {
        logger.log("Matrix::printRow");
        for (int columnCounter = 0; columnCounter < row.size(); columnCounter++) {
            if (columnCounter != 0)
                fout << ", ";
            fout << row[columnCounter];
        }
        
        if(end)
            fout << endl;
        else
            fout << ", ";
        
    }

    /**
 * @brief Static function that takes a vector of valued and prints them out in a
 * comma seperated format.
 *
 * @tparam T current usaages include int and string
 * @param row 
 */
    template <typename T>
    void writeRow(vector<T> row, bool end)
    {
        logger.log("Matrix::printRow");
        ofstream fout(this->sourceFileName, ios::app);
        this->writeRow(row, fout, end);
        fout.close();
    }
};