/* 
 * File:   Graph.cpp
 * Author: anitageorge
 *
 * Created on November 1, 2018, 10:45 AM
 * Implementation file for Graph Class
 */
#include "Graph.h"
#include <iostream>
#include <algorithm>
#include<Objbase.h>

using namespace std;

Graph::Graph(string xname, string yname, string cname) {
    x_axis_name = xname;
    y_axis_name = yname;
    chart_name = cname;
}

void Graph::addItem(string key, int value) {
    items[key] = value;
}

void Graph::display() {
    for(map<string,int>::iterator it = items.begin(); it != items.end(); ++it) {
        cout<<it->first<<":"<<it->second<<endl;
    }
}

bool Graph::initializeGraph() {
	try {
		HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hr)) {
			cout << "Failed to initialize COM Library" << hr << endl;
			return 0;
		}
		if (FAILED(pXL.CreateInstance("Excel.Application")))
		{
			std::cout << "Failed to initialize Excel::_Application!" << std::endl;
			return 0;
		}
		//Open an existing excel file
		pXL->Visible = true; //this makes the file visible
		pXL->Workbooks->Add(Excel::xlWorksheet); //Opens a new excel file
		wsheet = pXL->ActiveSheet; //object of the active sheet
		wsheet->Name = "Chart Data";
	}
	catch (_com_error & error) {
		cout << "Com Error 1 " << &_com_error::ErrorInfo<< endl;
		return false;
	}
	return true;
}

void Graph::generateGraph() {
	try {
		Excel::RangePtr prange = wsheet->Cells; // object of the cells in the sheet

		prange->Item[1][1] = x_axis_name.c_str();
		prange->Item[1][2] = y_axis_name.c_str();

		unsigned i = 0;
		for (map<string, int>::iterator it = items.begin(); it != items.end(); ++it) {
			const char *x = it->first.c_str();
			int y = it->second;
			cout << x << ":" << y << endl;
			prange->Item[i + 2][1] = x;
			prange->Item[i + 2][2] = y;
			i++;
		}

		Excel::RangePtr pBeginRange = prange->Item[1][1];
		Excel::RangePtr pEndRange = prange->Item[10 + 1][2];

		Excel::RangePtr pTotalRange =
			wsheet->Range[(Excel::Range*)pBeginRange][(Excel::Range*)pEndRange];

		pChart = pXL->ActiveWorkbook->Charts->Add(); //Adding a chart

		pChart->ChartWizard((Excel::Range*)pTotalRange,
			(long)Excel::xlColumn,
			6L, (long)Excel::xlColumns, 1L, 1L, true,
			chart_name.c_str(), x_axis_name.c_str() , y_axis_name.c_str());

	}
	catch (_com_error & error) {
		cout << "Com Error " << &_com_error::ErrorInfo << endl;
	}
}