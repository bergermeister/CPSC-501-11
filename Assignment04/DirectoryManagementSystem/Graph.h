/* 
 * File:   Graph.h
 * Author: anitageorge
 *
 * Created on November 1, 2018, 10:44 AM
 * Graph class to interface with Microsoft Excel
 */

#ifndef GRAPH_H
#define GRAPH_H

#import "MSO.DLL" \
	rename("RGB","MSORGB")
using namespace Office;

#import "VBE6EXT.OLB"
using namespace VBIDE;

#import "EXCEL.EXE" \
    rename( "DialogBox", "ExcelDialogBox" ) \
    rename( "RGB", "ExcelRGB" ) \
    rename( "CopyFile", "ExcelCopyFile" ) \
    rename( "ReplaceText", "ExcelReplaceText" ) \
    exclude( "IFont", "IPicture" ) no_dual_interfaces

#include <string>
#include <map>
using namespace std;

class Graph{
    string x_axis_name;
    string y_axis_name;
    string chart_name;
    map<string,int> items;
    
	Excel::_ApplicationPtr pXL;
	Excel::_WorksheetPtr wsheet;
	Excel::_ChartPtr pChart;

    public:
        Graph(string = "",string = "", string = "");
        void addItem(string,int);
        bool initializeGraph();
        void generateGraph();
        void display();
};

#endif /* GRAPH_H */

