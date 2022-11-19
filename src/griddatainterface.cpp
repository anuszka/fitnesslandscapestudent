#include <iostream>
#include <math.h>
#include "include/griddatainterface.h"
#include "include/readcsv.h"

GridDataInterface::GridDataInterface(const std::string &pPath) : path(pPath)
{
    setDoc(path);
    if (fileDataSortingCorrect())
    {
        setXgrid();
        setYgrid();
        setZvalues();
    }
}

void GridDataInterface::setDoc(const std::string &path_)
{
    // File with 3 columns (x, y, z) and arbitrary column labels
    doc = new Data(path_);
}

bool GridDataInterface::fileDataSortingCorrect()
{
    // This function checks only first two lines and columns for now.
    // This is to determine the sorting direction.

    double x0 = doc->X[0];
    double x1 = doc->X[1];
    double y0 = doc->Y[0];
    double y1 = doc->Y[1];
    if ((x0 == x1) && (y0 < y1))
    {
        file_data_sorting_direction = FileDataSorting::along_y_column_first;
    }
    else if ((x0 < x1) && (y0 == y1))
    {
        file_data_sorting_direction = FileDataSorting::along_x_column_first;
    }
    else
    {
        std::cerr << "Incorrect data sorting in the file!\n";
        return (file_data_sorting_correct = false);
    }
    return (file_data_sorting_correct = true);
}

void GridDataInterface::setXgrid()
{
    x_grid = collect_nonrepeating_values(doc->X);
    x_grid_size = x_grid.size();
}

void GridDataInterface::setYgrid()
{
    y_grid = collect_nonrepeating_values(doc->Y);
    y_grid_size = y_grid.size();
}

void GridDataInterface::setZvalues()
{
    double z;
    if (file_data_sorting_direction == FileDataSorting::along_x_column_first)
    {

        for (int i = 0; i < (int)x_grid_size; i++)
            for (int j = 0; j < (int)y_grid_size; j++)
            {
                z = doc->Z[j * x_grid_size + i];
                z_values.push_back(z);
            }
    }
    else
    {
        for (int i = 0; i < (int)x_grid_size; i++)
            for (int j = 0; j < (int)y_grid_size; j++)
            {
                z = doc->Z[i * y_grid_size + j];
                z_values.push_back(z);
            }
    }
}

std::vector<double> GridDataInterface::collect_nonrepeating_values(std::vector<double> v)
{
    std::vector<double> output;
    double prev_val = v[0];
    output.push_back(prev_val);
    for (const auto &value : v)
    {
        if (value > prev_val)
        {
            output.push_back(value);
            prev_val = value;
        }
    }
    return (output);
}

void GridDataInterface::printGridValues()
{
    if (file_data_sorting_correct)
    {
        std::cout << "X grid values:\n";
        for (const auto &value : getXgrid())
            std::cout << value << "\n";
        std::cout << "X grid size: " << getXgrid().size() << "\n";

        std::cout << "Y grid values:\n";
        for (const auto &value : getYgrid())
            std::cout << value << "\n";
        std::cout << "Y grid size: " << getYgrid().size() << "\n";
    }
}

void GridDataInterface::printZvalues()
{

    if (file_data_sorting_correct)
    {
        std::cout << "z values, sorted:\n";
        for (const auto &value : getZvalues())
            std::cout << value << "\n";
        std::cout << "z vector size: " << getZvalues().size() << "\n";
    }
}

void GridDataInterface::setItr(unsigned long long int *itr){
    iterator = *itr;
}

void GridDataInterface::setLevel(int lvl)
{
    for(long long unsigned int i = 0; i < doc->Z.size(); i++)
    {
        if(doc->Z[i] < lvl){
            x_lvl.push_back(doc->X[i]);
            y_lvl.push_back(doc->Y[i]);
            z_lvl.push_back(doc->Z[i]);
        }
    }

    isAr = true;
}

bool GridDataInterface::checkLevel(timeposition2D p, int ntraj)
{
    bool t = false;
    for(long long unsigned int i = 0; i < x_lvl.size(); i++){
       
            if(round(p.pos.x) == x_lvl[i] && round(p.pos.y) == y_lvl[i]){
                setItr(&i);
                if(ntraj == 1)
                    showLastPoint(p);

                t = true;
            }
    }
    return t;
}

void GridDataInterface::showLastPoint(timeposition2D p){

    std::clog << "Simulation stopped at:\nX: " << round(p.pos.x) << "\n"
                                            <<"Y: " << round(p.pos.y) << "\n"
                                            <<"Z: " << findPotential(p) << "\n";

}

void GridDataInterface::setArea(int kmr1, int kmr2, int kr1, int kr2){
    x1 = kmr1;
    x2 = kmr2;
    y1 = kr1;
    y2 = kr2;

    isAr = true;
}

double GridDataInterface::findPotential(timeposition2D p){
    for(long long unsigned int i = 0; doc->Z.size(); i++){
            if(round(p.pos.x) == doc->X[i] && round(p.pos.y) == doc->Y[i]){
                return doc->Z[i];
            }
    }
    return 0;
}


bool GridDataInterface::checkArea(timeposition2D p, int ntraj){

    bool t = false;

    if( p.pos.x >= x1 && p.pos.x <= x2 && p.pos.y >= y1 && p.pos.y <= y2 ){ 
        if(ntraj == 1)
            showLastPoint(p);
            
        t = true;
    }

    return t;
}