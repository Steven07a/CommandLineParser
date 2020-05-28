#include "CommandLineParser.h"
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\stringTokenizer\StringTokenizer\STokenizer.h"
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\stringTokenizer\StringTokenizer\token.h"
#include "C:/Users/Steven_Dev/Desktop/CS_Stuff/includes/\table.h"
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\Map-Class\MapClass\MapClass\Map.h"
#include <iostream>

using namespace std;
Parser::Parser() {
	build_keyword_list();
	make_table(_adjancencyMatrix);
	_flag = false;

}

Parser::Parser(char* s) : _st(s) {
	_token = Token();
	build_keyword_list();
	make_table(_adjancencyMatrix);
	set_string(s);
}

void Parser::build_keyword_list() {
	_keyWords.insert("select", select);
	_keyWords.insert("from", from);
	_keyWords.insert("where", where);
	_keyWords.insert("other", other);
	_keyWords.insert("<", Operator);
	_keyWords.insert("=", Operator);
	_keyWords.insert(">", Operator);
	_keyWords.insert(">=", Operator);
	_keyWords.insert("<=", Operator);
	_keyWords.insert("star", star);
	_keyWords.insert("or", Or);
	_keyWords.insert("and", And);
	_keyWords.insert("insert", insert);
	_keyWords.insert("into", into);
	_keyWords.insert("create", create);
	_keyWords.insert("make", make);
	_keyWords.insert(",", comma);
}

void Parser::make_table(int _adjancencyMatrix[][MAX_COLUMN]) {
	//marks all cells as -1 
	mark_cells(_adjancencyMatrix, 0, MAX_ROW, 0, MAX_COLUMN, -1);

	//reserves column 1 in row 0 for Select
	mark_cells(_adjancencyMatrix, 0, 1, 1, 2, select);

	//makes it so if u call select then give it an other it will give u the 
	//from state
	mark_cells(_adjancencyMatrix, 1, 2, other, other+1, from);

	//once inside the from state we are expecting a where
	mark_cells(_adjancencyMatrix, 2, 3, from, from+1, where);
	mark_cells(_adjancencyMatrix, 2, 3, comma, comma+1, 4);

	mark_cells(_adjancencyMatrix, 3, 4, other, other+1, 6);

	mark_cells(_adjancencyMatrix, 4, 5, other, other+1, 2);

	mark_cells(_adjancencyMatrix, 6, 7, 0, 1, 1);
	mark_cells(_adjancencyMatrix, 6, 7, where, where+1, 7);
	mark_cells(_adjancencyMatrix, 7, 8, other, other+1, 8);
	mark_cells(_adjancencyMatrix, 8, 9, Operator, Operator+1, 9);
	mark_cells(_adjancencyMatrix, 9, 10, other, other+1, 10);
	mark_cells(_adjancencyMatrix, 10, 11, Or, Or+1, 11);
	mark_cells(_adjancencyMatrix, 10, 11, And, And+1, 11);
	mark_cells(_adjancencyMatrix, 10, 11, 0, 1, 1);
	mark_cells(_adjancencyMatrix, 11, 12, other, other+1, 8);
}

MMap<string,string> Parser::parse_tree() {
	return _parseTree;
}

bool Parser::get_parse_tree() {
	string item;
	int state = 0;
	for (int i = 0; i < input_q.size(); i++) {
		item = input_q[i];
		if (_keyWords.contains(item)) {
			state = _adjancencyMatrix[state][_keyWords[item]];
		} else {
			state = _adjancencyMatrix[state][other];
		}
		
		switch (state) {
		case select:
			_parseTree.insert("command", item);
			break;
		case from:
			_parseTree.insert("fields", item);
			break;
		case comma:
			break;
		case 6:
			_parseTree.insert("table", item);
			break;
		case 7:
			_parseTree.insert("where", "yes");
			break;
		case 8:
			_parseTree.insert("conditions", item);
			break;
		case 9:
			_parseTree.insert("conditions", item);
			break;
		case 10:
			_parseTree.insert("conditions", item);
			break;
		case 11:
			_parseTree.insert("conditions", item);
			break;
		default:
			break;
		}
	}
	if (_adjancencyMatrix[state][0] == 1) {
		return true;
	} else {
		_parseTree.clear();
		return false;
	}
}

void Parser::set_string(char* s) {
	input_q.clear();
	//_token = Token();
	_st >> _token;
	while (_st.more()) {
		if (_token.token_str() != " ") {
			input_q.push_back(_token.token_str());
		}
		_token = Token();
		_st >> _token;
	}
	_flag = get_parse_tree();

}